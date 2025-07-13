

#include "unity.h"

#include "counter.h"

extern counter;

void setUp(void)
{
    counter = 100;
}

void tearDown(void)
{
}

void test_reset_counter_should_set_value_to_0(void)
{
    reset_counter();
    TEST_ASSERT_EQUAL_UINT16(0, counter);
}

