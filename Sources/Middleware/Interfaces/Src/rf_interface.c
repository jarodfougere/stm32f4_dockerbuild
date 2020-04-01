/**
 * @file rf_interface.c
 * @author Carl Mattatall
 * @brief  This module provides an interface that bundles measurement
 * of signal power envelope, statistical normalization of samples,
 * voltage conversion from the directional coupler, insertion loss
 * correction, and so on. The interface is used primarily by the RF task.
 * @version 0.1
 * @date 2020-03-30
 * 
 * @copyright Copyright (c) 2020 Rimot.io Incorporated
 */

#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#include "arm_math.h"
#include "rf_interface.h"
#include "analog_measurements.h"






struct RF_measurement
{
    struct analog_measurement OUTA;   /*  FWD coupled power           */
    struct analog_measurement OUTB;   /*  REV coupled power           */
    struct analog_measurement OUTP;   /*  Power difference positive   */
    struct analog_measurement OUTN;   /*  Power difference negative   */
    struct analog_measurement DIFF;   /*  Power difference            */
    struct analog_measurement TEMP;   /*  Temperature                 */
};

const struct rf_config rf_config_defaults = RF_CFG_DFLT_INITIALIZER;

/*******************/
/* ADL5519 related */
/*******************/

/* slope to convert OUT, OUTB, OUTP, or OUTN from volts to dB */
#define ADL5519__SLOPE_VOverdB (-0.022) 

/* OUTA/B Intercept in dBm @ 900 MHz */
#define ADL5519__INTER_dB (20.3)    

/* if return loss is < than this value then set VSWR to open-circuit value */
#define RL_OPEN_LIMIT (1.0)   

#if 0 /* [CTM, MARCH 29, 2020] : Currently Unused */

/* OUTA/B Intercept in dBm @ 400 MHz (interpolated) */
#define ADL5519__INTER_dB                                                 (21.3)

/* OUTA/B Intercept in dBm @ 400 MHz (interpolated) */
#define ADL5519__INTER_dB                                                 (21.3)
#endif /* END OF UNUSED */

/* Coupler IPP-8036 values */


/* FWD coupling path coefficient (typical vals from data sheet, 50dB nominal */
#define COUPLER_FWD (50.0) //(49.7)

/* FWD coupling path additional on-board attenuation, dB */
#define ATTEN_FWD (10.0) 


/* Temperature Reference */

/* voltage at 27 Celcius */
#define ADL5519__TEMP_INTERCEPT_VOLTAGE_27C ((double)(1.36)) 

/* senstivity of temperature reference in V/Celcius */
#define ADL5519__TEMP_SENSITIVITY_V_PER_C ((double)(4.5e-3)) 

/* VSWR average must be >= this number of samples to be valid */
#define VSWR_MIN_SAMPLES (20) 

/* ADL5519 OUTA/OUTB voltages below this imply RF event */
#define RF_VTHRESH (1.25) 

/* Transmit Threshhold */
#define ADC_FWD_VOLT_THRESHHOLD VOLTS_TO_ADC(1.25)


static struct RF_measurement measurements;
static float RF_returnLossToVSWR(float rl);
static float RF_vswrToReturnLoss(float vswr);


/*******************************************************************************
 * @fn      RF_process
 * @brief   Calculate measurement values for data buffer
 *          Buffer is assumed to have samples ordered as described above
 * @param   buffer   ... samples
 *          len      ... number of samples to process
 * @return  0 if the RF pulse surpasses the minimum level
 *          temperature is always valid on return 
 ******************************************************************************/
enum RF_interface_status RF_process(uint16_t *buf, int len)
{
    int i; //,j;
    /* initialize local variables */
    uint16_t outa, outb, outp, outn, temp;
    uint16_t min_outa = 0xffff;
    uint16_t min_outb = 0xffff;
    uint16_t min_outp = 0xffff;
    uint16_t min_outn = 0xffff;
    uint16_t min_temp = 0xffff;
    uint16_t max_outa = 0x0;
    uint16_t max_outb = 0x0;
    uint16_t max_outp = 0x0;
    uint16_t max_outn = 0x0;
    uint16_t max_temp = 0x0;

    uint32_t avg_outa_sum = 0;
    uint32_t avg_outp_sum = 0;
    uint32_t avg_outn_sum = 0;
    uint32_t avg_outb_sum = 0;
    uint32_t avg_temp_sum = 0;

    uint8_t fwd_txmask_bit = 0;
    uint8_t rev_txmask_bit = 0;
    uint16_t txthreshold   = ADC_FWD_VOLT_THRESHHOLD;  
    int16_t diff;
    int16_t min_diff     = 32767;
    int16_t max_diff     = -32767;
    int32_t avg_diff_sum = 0;
    uint16_t Nprocessed  = 0;
    uint16_t N = 0;

    /* positive length that is a multiple of the number of ADC channels */
    if (len < 0) //|| (len&0x3))
    {
        return RF_INVALID;
    }

    /* buffer is not allocated */
    if (buf == NULL)
    {
        return RF_INVALID;
    }

    /*
     *  [CDM, May 10, 2016] TODO:
     * 
     *  Combine tx mask generation and min./max.
     *  value (and average) calculation.
     */


    /*
     *  Extremes are antenna perfectly matched, all power in FWD, 
     *  and open-circuited, all power in REV. So combine
     *  masks with an OR to determine if DIFF value should
     *  be included in the RL calculation.
     * 
     *  Assumes:
     *  1. Sample 1 is FWD 
     *  2. Sample 2 is OUTP
     *  3. Sample 3 is OUTN
     *  4. Sample 4 is REV
     *  5. Sample 5 is TEMP
     */
    
    i = 0;
    do
    {
        /* load values for next sample time */
        outa = *(buf + (i++));
        outp = *(buf + (i++));
        outn = *(buf + (i++));
        outb = *(buf + (i++));
        temp = *(buf + (i++));

        /* determine transmit mask bits */
        if (outa < txthreshold)
        {
            fwd_txmask_bit = 1;
        }
        else
        {
            fwd_txmask_bit = 0;
        }
        if (outb < txthreshold)
        {
            rev_txmask_bit = 1;
        }
        else
        {
            rev_txmask_bit = 0;
        }

        /* calculate masked values */
        if (fwd_txmask_bit || rev_txmask_bit)
        {
            Nprocessed++;

            /* calculate difference channel value */
            diff = (outp - outn) / 2;

            /* find maximum and minimum values */
            if (min_outa > outa)
            {
                min_outa = outa;
            }

            if (max_outa < outa)
            {
                max_outa = outa;
            }

            if (min_outp > outp)
            {
                min_outp = outp;
            }

            if (max_outp < outp)
            {
                max_outp = outp;
            }

            if (min_outn > outn)
            {
                min_outn = outn;
            }

            if (max_outn < outn)
            {
                max_outn = outn;
            }
            
            if (min_outb > outb)
            {
                min_outb = outb;
            }

            if (max_outb < outb)
            {
                max_outb = outb;
            }

            if (min_diff > diff)
            {
                min_diff = diff;
            }

            if (max_diff < diff)
            {
                max_diff = diff;
            }

            /* update averages */
            avg_outa_sum += outa;
            avg_outp_sum += outp;
            avg_outn_sum += outn;
            avg_outb_sum += outb;
            avg_diff_sum += diff;
        }

        /* temperature does not need to be gated, use every sample */
        if (min_temp > outa)
        {
            min_temp = temp;
        }
        if (max_temp < outa)
        {
            max_temp = temp;
        }
        avg_temp_sum += temp;
        N++;

    } while (i < len);

    /* store results */
    measurements.OUTA.min = min_outa;
    measurements.OUTP.min = min_outp;
    measurements.OUTN.min = min_outn;
    measurements.OUTB.min = min_outb;
    measurements.DIFF.min = min_diff;
    measurements.OUTA.max = max_outa;
    measurements.OUTP.max = max_outp;
    measurements.OUTN.max = max_outn;
    measurements.OUTB.max = max_outb;
    measurements.DIFF.max = max_diff;
    measurements.OUTA.avg = (uint16_t)(avg_outa_sum / Nprocessed);
    measurements.OUTP.avg = (uint16_t)(avg_outp_sum / Nprocessed);
    measurements.OUTN.avg = (uint16_t)(avg_outn_sum / Nprocessed);
    measurements.OUTB.avg = (uint16_t)(avg_outb_sum / Nprocessed);
    measurements.DIFF.avg = (int16_t)(avg_diff_sum / Nprocessed);
    measurements.TEMP.avg = (uint16_t)(avg_temp_sum / N);
    measurements.OUTA.Navg = Nprocessed;
    measurements.OUTP.Navg = Nprocessed;
    measurements.OUTN.Navg = Nprocessed;
    measurements.OUTB.Navg = Nprocessed;
    measurements.DIFF.Navg = Nprocessed;
    measurements.TEMP.Navg = len;

    /* success */
    if (measurements.DIFF.Navg < VSWR_MIN_SAMPLES)
    {
        return RF_INVALID;
    }
    else
    {
        return RF_VALID;
    }
}


/*******************************************************************************
 * @fn      RF_returnLossToVSWR
 * @brief   Converts return loss in dB to VSWR
 * @param   float rl return loss in dB
 * @return  float VSWR (unitless)
 ******************************************************************************/
static float RF_returnLossToVSWR(float rl)
{
    double exp_term, num, den;
    double vswr;

    if (rl == 0.0)
    {
        /* error, infinite VSWR */
        return -1.0;
    }

    /* calculate exponent term */
    exp_term = pow(10.0, rl / 20.0);

    /* calculate numerator and denominator */
    num = exp_term + 1;
    den = exp_term - 1;

    /* calculate VSWR */
    vswr = num / den;

    /* success */
    return (float)vswr;
}


/*******************************************************************************
 * @fn      RF_vswrToReturnLoss
 * @brief   Converts VSWR to return loss in dB
 * @param   float vswr VSWR value to be converted
 * @return  float return loss in dB
 ******************************************************************************/
static float RF_vswrToReturnLoss(float vswr)
{
    double gamma, rl;

    /* calculate reflection coefficient */
    gamma = (vswr + 1) / (vswr - 1);

    /* calculate return loss */
    rl = (-1.0) * 20.0 * log10(gamma);

    /* success */
    return (float)rl;
}


/*******************************************************************************
 * @fn      RF_getFWDMinVoltage
 * @brief   Returns current minimum FWD power measurement
 * @param   None
 * @return  float value in volts
 ******************************************************************************/
float RF_getFWDMinVoltage() 
{ 
    return ADC_TO_VOLTS(measurements.OUTA.min); 
}


float RF_getREVMinVoltage() 
{
    return ADC_TO_VOLTS(measurements.OUTB.min); 
}


float RF_getDIFMinVoltage() 
{ 
    return ADC_TO_VOLTS(measurements.DIFF.min); 
}


float RF_getTEMPMinVoltage() 
{ 
    return ADC_TO_VOLTS(measurements.TEMP.min);
}


/*******************************************************************************
 * @fn      RF_getFWDMaxVoltage
 * @brief   Returns current maximum FWD power measurement
 * @param   None
 * @return  float value in volts
 ******************************************************************************/
float RF_getFWDMaxVoltage() 
{ 
    return ADC_TO_VOLTS(measurements.OUTA.max);
}


float RF_getREVMaxVoltage() 
{ 
    return ADC_TO_VOLTS(measurements.OUTB.max);
}


float RF_getDIFMaxVoltage() 
{ 
    return ADC_TO_VOLTS(measurements.DIFF.max); 
}


float RF_getTEMPMaxVoltage() 
{ 
    return ADC_TO_VOLTS(measurements.TEMP.max); 
}

/*******************************************************************************
 * @fn      RF_getFWDAvgVoltage
 * @brief   Returns current average FWD power measurement
 * @param   None
 * @return  float value in volts
 ******************************************************************************/
float RF_getFWDAvgVoltage() 
{ 
    return ADC_TO_VOLTS(measurements.OUTA.avg); 
}

float RF_getREVAvgVoltage() 
{ 
    return ADC_TO_VOLTS(measurements.OUTB.avg); 
}

float RF_getDIFAvgVoltage() 
{ 
    return ADC_TO_VOLTS(measurements.DIFF.avg); 
}


float RF_getTEMPAvgVoltage() 
{ 
    return ADC_TO_VOLTS(measurements.TEMP.avg); 
}


/*******************************************************************************
 * @fn      RF_getFWDMedVoltage
 * @brief   Returns current median FWD power measurement
 * @param   None
 * @return  float value in volts
 ******************************************************************************/
float RF_getFWDMedVoltage() 
{ 
    return ADC_TO_VOLTS(measurements.OUTA.median); 
}


float RF_getREVMedVoltage() 
{ 
    return ADC_TO_VOLTS(measurements.OUTB.median); 
}


float RF_getDIFMedVoltage() 
{ 
    return ADC_TO_VOLTS(measurements.DIFF.median); 
}


float RF_getTEMPMedVoltage() 
{ 
    return ADC_TO_VOLTS(measurements.TEMP.median); 
}



/*******************************************************************************
 * @fn      RF_getFWDNAvgVoltage
 * @brief   Returns current average FWD power measurement
 * @param   None
 * @return  float value in volts
 ******************************************************************************/
uint16_t RF_getFWDNAvg() 
{ 
    return (measurements.OUTA.Navg); 
}


uint16_t RF_getREVNAvg() 
{ 
    return (measurements.OUTB.Navg); 
}


uint16_t RF_getDIFNAvg() 
{ 
    return (measurements.DIFF.Navg); 
}


/*******************************************************************************
 * @fn      RF_getVSWR
 * @brief   Copies current VSWR value into user variable. Returns 0
 *          if VSWR is valid, 1 otherwise.
 * @param   float pointer to variable to copy VSWR to
 * @return  uint8_t 0 if VSWR value is valid; 1 otherwise
 ******************************************************************************/
uint16_t RF_getVSWRAvg(float *value)
{
    float rl_volts, rl_db, vswr;

    /* check for bad data pointer */
    if (value == NULL)
    {
        return RF_INVALID;
    }

    /* did the past data window have enough valid samples */
    if (measurements.DIFF.Navg < VSWR_MIN_SAMPLES)
    {
        *value = -1.0;
        return RF_INVALID;
    }

    /* convert DIFF measurement to voltage */
    rl_volts = RF_getDIFAvgVoltage();
    rl_db = rl_volts / ADL5519__SLOPE_VOverdB;

    if (rl_db < RL_OPEN_LIMIT)
    {
        vswr = -1.0;
    }
    else
    {
        /* calculate vswr from return loss */
        vswr = RF_returnLossToVSWR(rl_db);
    }

    /* success */
    *value = vswr;
    return RF_VALID;
}
/*******************************************************************************
 * @fn      RF_getVSWR
 * @brief   Copies current VSWR value into user variable. Returns 0
 *          if VSWR is valid, 1 otherwise.
 * @param   float pointer to variable to copy VSWR to
 * @return  uint8_t 0 if VSWR value is valid; 1 otherwise
 ******************************************************************************/
uint16_t RF_getVSWRMedian(float *value)
{
    float rl_volts, rl_db, vswr;

    /* check for bad data pointer */
    if (value == NULL)
    {
        return RF_INVALID;
    }

    /* did the past data window have enough valid samples */
    if (measurements.DIFF.Navg < VSWR_MIN_SAMPLES)
    {
        *value = -1.0;
        return RF_INVALID;
    }

    /* convert DIFF measurement to voltage */
    rl_volts = RF_getDIFMedVoltage();
    rl_db = rl_volts / ADL5519__SLOPE_VOverdB;

    if (rl_db < RL_OPEN_LIMIT)
    {
        vswr = -1.0;
    }
    else
    {
        /* calculate vswr from return loss */
        vswr = RF_returnLossToVSWR(rl_db);
    }

    /* success */
    *value = vswr;
    return RF_VALID;
}


uint16_t RF_getVSWRMax(float *value)
{
    float rl_volts, rl_db, vswr;

    /* check for bad data pointer */
    if (value == NULL)
    {
        return RF_INVALID;
    }

    /* did the past data window have enough valid samples */
    if (measurements.DIFF.Navg < VSWR_MIN_SAMPLES)
    {
        *value = -1.0;
        return RF_INVALID;
    }

    /* convert DIFF measurement to voltage */
    rl_volts = RF_getDIFMaxVoltage();
    rl_db = rl_volts / ADL5519__SLOPE_VOverdB;

    if (rl_db < RL_OPEN_LIMIT)
    {
        vswr = -1.0;
    }
    else
    {
        /* calculate vswr from return loss */
        vswr = RF_returnLossToVSWR(rl_db);
    }

    /* success */
    *value = vswr;
    return RF_VALID;
}
uint16_t RF_getVSWRMin(float *value)
{
    float rl_volts, rl_db, vswr;

    /* check for bad data pointer */
    if (value == NULL)
    {
        return RF_INVALID;
    }

    /* did the past data window have enough valid samples */
    if (measurements.DIFF.Navg < VSWR_MIN_SAMPLES)
    {
        *value = -1.0;
        return RF_INVALID;
    }

    /* convert DIFF measurement to voltage */
    rl_volts = RF_getDIFMinVoltage();
    rl_db = rl_volts / ADL5519__SLOPE_VOverdB;

    if (rl_db < RL_OPEN_LIMIT)
    {
        vswr = -1.0;
    }
    else
    {
        /* calculate vswr from return loss */
        vswr = RF_returnLossToVSWR(rl_db);
    }

    /* success */
    *value = vswr;
    return RF_VALID;
}
/*******************************************************************************
 * @fn      RF_getRL
 * @brief   Copies current RL value into user variable. Returns 0
 *          if RL is valid, 1 otherwise.
 * @param   float pointer to variable to copy RL to
 * @return  uint8_t 0 if RL value is valid; 1 otherwise
 ******************************************************************************/
uint16_t RF_getRLAvg(float *value)
{
    double rl_volts, rl_db;

    /* did the past data window have enough valid samples */
    if (measurements.DIFF.Navg < VSWR_MIN_SAMPLES)
    {
        *value = -1.0;
        return RF_INVALID;
    }

    /* convert DIFF measurement to voltage */
    rl_volts = RF_getDIFMinVoltage();
    rl_db = rl_volts / ADL5519__SLOPE_VOverdB;

    /* correct for negative RL values (caused by noise and offset errors) */
    if (rl_db < 0)
    {
        rl_db = 0.0;
    }

    /* success */
    *value = rl_db;
    return RF_VALID;
}
/*******************************************************************************
 * @fn      RF_getFWDMinPower
 * @brief   Calculates and returns FWD power min. in dBm
 * @param   float pointer to variable to copy Power to
 * @return  uint8_t 0 if Power value is valid; 1 otherwise
 ******************************************************************************/
uint16_t RF_getFWDMinPower(float *value)
{
    double fwdPower_voltage, fwdPower_dBm;

    /* did the past data window have enough valid samples */
    if (measurements.DIFF.Navg < VSWR_MIN_SAMPLES)
    {
        *value = -1.0;
        return RF_INVALID;
    }

    /* convert voltage measurement to dBm */
    /* voltage is inversely proportional to power so get max. voltage */
    fwdPower_voltage = RF_getFWDMaxVoltage();
    fwdPower_dBm = (fwdPower_voltage / ADL5519__SLOPE_VOverdB) +
                   ADL5519__INTER_dB +
                   COUPLER_FWD +
                   ATTEN_FWD;

    /* correct for negative RL values (caused by noise and offset errors) */
    if (fwdPower_dBm < 0)
    {
        *value = -1.0;
        return RF_INVALID;
    }

    /* success */
    *value = fwdPower_dBm;
    return RF_VALID;
}

/*******************************************************************************
 * @fn      RF_getFWDMaxPower
 * @brief   Calculates and returns FWD power max. in dBm
 * @param   float pointer to variable to copy Power to
 * @return  uint8_t 0 if Power value is valid; 1 otherwise
 ******************************************************************************/
uint16_t RF_getFWDMaxPower(float *value)
{
    double fwdPower_voltage, fwdPower_dBm;

    /* did the past data window have enough valid samples */
    if (measurements.DIFF.Navg < VSWR_MIN_SAMPLES)
    {
        *value = -1.0;
        return RF_INVALID;
    }

    /* convert voltage measurement to dBm */
    /* voltage is inversely proportional to power so get min. voltage */
    fwdPower_voltage = RF_getFWDMinVoltage();
    fwdPower_dBm = (fwdPower_voltage / ADL5519__SLOPE_VOverdB) +
                   ADL5519__INTER_dB +
                   COUPLER_FWD +
                   ATTEN_FWD;

    /* correct for negative RL values (caused by noise and offset errors) */
    if (fwdPower_dBm < 0)
    {
        *value = -1.0;
        return RF_INVALID;
    }

    /* success */
    *value = fwdPower_dBm;
    return RF_VALID;
}

/*******************************************************************************
 * @fn      RF_getFWDMAvgPower
 * @brief   Calculates and returns FWD power avg. in dBm
 * @param   float pointer to variable to copy Power to
 * @return  uint8_t 0 if Power value is valid; 1 otherwise
 ******************************************************************************/
uint16_t RF_getFWDAvgPower(float *value)
{
    double fwdPower_voltage, fwdPower_dBm;

    /* did the past data window have enough valid samples */
    if (measurements.DIFF.Navg < VSWR_MIN_SAMPLES)
    {
        *value = -1.0;
        return RF_INVALID;
    }

    /* convert voltage measurement to dBm */
    fwdPower_voltage = RF_getFWDAvgVoltage();
    fwdPower_dBm = (fwdPower_voltage / ADL5519__SLOPE_VOverdB) +
                   ADL5519__INTER_dB +
                   COUPLER_FWD +
                   ATTEN_FWD;

    /* correct for negative RL values (caused by noise and offset errors) */
    if (fwdPower_dBm < 0)
    {
        *value = -1.0;
        return RF_INVALID;
    }

    /* success */
    *value = fwdPower_dBm;
    return RF_VALID;
}

/*******************************************************************************
 * @fn      RF_getFWDMMedianPower
 * @brief   Calculates and returns FWD power avg. in dBm
 * @param   float pointer to variable to copy Power to
 * @return  uint8_t 0 if Power value is valid; 1 otherwise
 ******************************************************************************/
uint16_t RF_getFWDMedianPower(float *value)
{
    double fwdPower_voltage, fwdPower_dBm;

    /* did the past data window have enough valid samples */
    if (measurements.DIFF.Navg < VSWR_MIN_SAMPLES)
    {
        *value = -1.0;
        return RF_INVALID;
    }

    /* convert voltage measurement to dBm */
    fwdPower_voltage = RF_getFWDMedVoltage();
    fwdPower_dBm = (fwdPower_voltage / ADL5519__SLOPE_VOverdB) +
                   ADL5519__INTER_dB +
                   COUPLER_FWD +
                   ATTEN_FWD;

    /* correct for negative RL values (caused by noise and offset errors) */
    if (fwdPower_dBm < 0)
    {
        *value = -1.0;
        return RF_INVALID;
    }

    /* success */
    *value = fwdPower_dBm;
    return RF_VALID;
}

/*******************************************************************************
 * @fn      RF_getREVMinPower
 * @brief   Calculates and returns REV power min. in dBm
 * @param   float pointer to variable to copy Power to
 * @return  uint8_t 0 if Power value is valid; 1 otherwise
 ******************************************************************************/
uint16_t RF_getREVMinPower(float *value)
{
    double revPower_voltage, revPower_dBm;

    /* did the past data window have enough valid samples */
    if (measurements.DIFF.Navg < VSWR_MIN_SAMPLES)
    {
        *value = -1.0;
        return RF_INVALID;
    }

    /* convert voltage measurement to dBm */
    /* voltage is inversely proportional to power so get max. voltage */
    revPower_voltage = RF_getREVMaxVoltage();
    revPower_dBm = (revPower_voltage / ADL5519__SLOPE_VOverdB) +
                   ADL5519__INTER_dB +
                   COUPLER_FWD +
                   ATTEN_FWD;

    /* correct for negative RL values (caused by noise and offset errors) */
    if (revPower_dBm < 0)
    {
        *value = -1.0;
        return RF_INVALID;
    }

    /* success */
    *value = revPower_dBm;
    return RF_VALID;
}

/*******************************************************************************
 * @fn      RF_getREVMaxPower
 * @brief   Calculates and returns REV power max. in dBm
 * @param   float pointer to variable to copy Power to
 * @return  uint8_t 0 if Power value is valid; 1 otherwise
 ******************************************************************************/
uint16_t RF_getREVMaxPower(float *value)
{
    double revPower_voltage, revPower_dBm;

    /* did the past data window have enough valid samples */
    if (measurements.DIFF.Navg < VSWR_MIN_SAMPLES)
    {
        *value = -1.0;
        return RF_INVALID;
    }

    /* convert voltage measurement to dBm */
    /* voltage is inversely proportional to power so get min. voltage */
    revPower_voltage = RF_getREVMinVoltage();
    revPower_dBm = (revPower_voltage / ADL5519__SLOPE_VOverdB) +
                   ADL5519__INTER_dB +
                   COUPLER_FWD +
                   ATTEN_FWD;

    /* correct for negative RL values (caused by noise and offset errors) */
    if (revPower_dBm < 0)
    {
        *value = -1.0;
        return RF_INVALID;
    }

    /* success */
    *value = revPower_dBm;
    return RF_VALID;
}

/*******************************************************************************
 * @fn      RF_getREVAvgPower
 * @brief   Calculates and returns REV power avg. in dBm
 * @param   float pointer to variable to copy Power to
 * @return  uint8_t 0 if Power value is valid; 1 otherwise
 ******************************************************************************/
uint16_t RF_getREVAvgPower(float *value)
{
    double revPower_voltage, revPower_dBm;

    /* did the past data window have enough valid samples */
    if (measurements.DIFF.Navg < VSWR_MIN_SAMPLES)
    {
        *value = -1.0;
        return RF_INVALID;
    }

    /* convert voltage measurement to dBm */
    revPower_voltage = RF_getREVAvgVoltage();
    revPower_dBm = (revPower_voltage / ADL5519__SLOPE_VOverdB) +
                   ADL5519__INTER_dB +
                   COUPLER_FWD +
                   ATTEN_FWD;

    /* correct for negative RL values (caused by noise and offset errors) */
    if (revPower_dBm < 0.0)
    {
        *value = -1.0;
        return RF_INVALID;
    }

    /* success */
    *value = revPower_dBm;
    return RF_VALID;
}

/*******************************************************************************
 * @fn      RF_getREVMedianPower
 * @brief   Calculates and returns REV power avg. in dBm
 * @param   float pointer to variable to copy Power to
 * @return  uint8_t 0 if Power value is valid; 1 otherwise
 ******************************************************************************/
uint16_t RF_getREVMedianPower(float *value)
{
    double revPower_voltage, revPower_dBm;

    /* did the past data window have enough valid samples */
    if (measurements.DIFF.Navg < VSWR_MIN_SAMPLES)
    {
        *value = -1.0;
        return RF_INVALID;
    }

    /* convert voltage measurement to dBm */
    revPower_voltage = RF_getREVMedVoltage();
    revPower_dBm = (revPower_voltage / ADL5519__SLOPE_VOverdB) +
                   ADL5519__INTER_dB +
                   COUPLER_FWD +
                   ATTEN_FWD;

    /* correct for negative RL values (caused by noise and offset errors) */
    if (revPower_dBm < 0)
    {
        *value = -1.0;
        return RF_INVALID;
    }

    /* success */
    *value = revPower_dBm;
    return RF_VALID;
}

/*******************************************************************************
 * @fn      RF_getTEMPAvg
 * @brief   Calculates and returns temperature in Celcius
 * @param   float pointer to variable to copy temperature to
 * @return  uint8_t 0 if Temperature value is valid; 1 otherwise
 ******************************************************************************/
uint16_t RF_getTEMPAvg(float *value)
{
    double temperature_voltage, temperature_celcius;

    /* convert voltage measurement to Celcius */
    temperature_voltage = RF_getTEMPAvgVoltage();
    temperature_celcius = ((double)27.0) +
                          (temperature_voltage - ADL5519__TEMP_INTERCEPT_VOLTAGE_27C) / ADL5519__TEMP_SENSITIVITY_V_PER_C;

    /* success */
    *value = temperature_celcius;

    return RF_VALID;
}