#ifndef RIMOT_REGISTER_BIT_OPS
#define RIMOT_REGISTER_BIT_OPS
#ifdef __cplusplus
extern "C" {
#endif /* C linkage */

#define BITMSK(bit) ((1 << bit))

#define ISBITSET(reg, bit) (BITMSK(bit) == (reg & BITMSK(bit)))



#ifdef __cplusplus
}
#endif /* C linkage */
#endif /* RIMOT_REGISTER_BIT_OPS */