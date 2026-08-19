#include <stdio.h>
#include <stdlib.h>
#include "../src/math/sum.h"

typedef struct
{
    const char *name;
    int (*fn)(void);
} test_case_t;

static int passed = 0;
static int failed = 0;

#define RUN(name)                          \
    do                                     \
    {                                      \
        if (name())                        \
        {                                  \
            printf("  PASS: %s\n", #name); \
            passed++;                      \
        }                                  \
        else                               \
        {                                  \
            printf("  FAIL: %s\n", #name); \
            failed++;                      \
        }                                  \
    } while (0)

static int test_sum_positive_numbers(void)
{
    return sum(2, 3) == 5;
}

static int test_sum_negative_numbers(void)
{
    return sum(-2, -3) == -5;
}

static int test_sum_zero(void)
{
    return sum(7, 0) == 7;
}

static int test_sum_commutative(void)
{
    return sum(12, 34) == sum(34, 12);
}

int main(void)
{
    printf("desktop_test_sum starting...\n");
    RUN(test_sum_positive_numbers);
    RUN(test_sum_negative_numbers);
    RUN(test_sum_zero);
    RUN(test_sum_commutative);
    printf("\nResults: %d passed, %d failed\n", passed, failed);
    return failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
