#include "led_driver.h"

static int led_state = 0;

void set_led_state (int state) {
    led_state = state;
}

int get_led_state(void) {
    return led_state;
}