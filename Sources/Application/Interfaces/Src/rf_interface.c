#include "rf_interface.h"

const struct rf_config rf_config_defaults = RF_CFG_DFLT_INITIALIZER;

void compute_vswr(struct rf_measurement * const measurement)
{
    float numerator = measurement->forward_power + measurement->reflected_power;
    float denominator = measurement->forward_power - measurement->reflected_power;
    measurement->vswr = numerator / denominator;
}