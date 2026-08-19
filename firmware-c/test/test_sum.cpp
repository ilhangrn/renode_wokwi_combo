#include <unity.h>
#include "../src/math/sum.h"

void test_sum_positive_numbers(void)
{
    TEST_ASSERT_EQUAL(5, sum(2, 3));
}

void test_sum_negative_numbers(void)
{
    TEST_ASSERT_EQUAL(-5, sum(-2, -3));
}

void test_sum_zero(void)
{
    TEST_ASSERT_EQUAL(7, sum(7, 0));
}

void test_sum_commutative(void)
{
    TEST_ASSERT_EQUAL(sum(12, 34), sum(34, 12));
}

void setup()
{
    UNITY_BEGIN();
    RUN_TEST(test_sum_positive_numbers);
    RUN_TEST(test_sum_negative_numbers);
    RUN_TEST(test_sum_zero);
    RUN_TEST(test_sum_commutative);
    UNITY_END();
}

void loop()
{
}
