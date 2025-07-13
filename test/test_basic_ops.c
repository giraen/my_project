#include "unity.h"
#include "basic_ops.h"

void test_add_should_add_two_numbers(void) {
    TEST_ASSERT_EQUAL(5, add(2, 3));
}