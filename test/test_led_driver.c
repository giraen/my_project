#include "unity.h"
#include "led_driver.h"

void setUp(void) {}
void tearDown(void) {}

void test_set_led_state_should_update_led_state(void) {
    set_led_state(1);
    TEST_ASSERT_EQUAL(1, get_led_state());

    set_led_state(0);
    TEST_ASSERT_EQUAL(0, get_led_state());
}