#include <Arduino.h>
#include <unity.h>
#include "../src/math/sum.h"

extern "C" void unity_output_char(char c)
{
    Serial.write(c);
}

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
    Serial.begin(115200);
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
