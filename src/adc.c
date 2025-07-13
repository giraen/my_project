#include "adc.h"

volatile int adc_value = 0;

int adc_read (void) {
    return adc_value;
}