#include <unity.h>

#if defined(ARDUINO)
#include <Arduino.h>
#else
#include "stm32f1xx_hal.h"
#endif

#include <sum.h>

#if !defined(ARDUINO)
static UART_HandleTypeDef uart1;

static void configure_stm32_uart(void)
{
    RCC_OscInitTypeDef oscillator = {};
    RCC_ClkInitTypeDef clock = {};
    GPIO_InitTypeDef gpio = {};

    HAL_Init();

    oscillator.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    oscillator.HSIState = RCC_HSI_ON;
    oscillator.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    oscillator.PLL.PLLState = RCC_PLL_NONE;
    HAL_RCC_OscConfig(&oscillator);

    clock.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK |
                      RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    clock.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
    clock.AHBCLKDivider = RCC_SYSCLK_DIV1;
    clock.APB1CLKDivider = RCC_HCLK_DIV1;
    clock.APB2CLKDivider = RCC_HCLK_DIV1;
    HAL_RCC_ClockConfig(&clock, FLASH_LATENCY_0);

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_USART1_CLK_ENABLE();

    gpio.Pin = GPIO_PIN_9;
    gpio.Mode = GPIO_MODE_AF_PP;
    gpio.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &gpio);

    uart1.Instance = USART1;
    uart1.Init.BaudRate = 115200;
    uart1.Init.WordLength = UART_WORDLENGTH_8B;
    uart1.Init.StopBits = UART_STOPBITS_1;
    uart1.Init.Parity = UART_PARITY_NONE;
    uart1.Init.Mode = UART_MODE_TX;
    uart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    uart1.Init.OverSampling = UART_OVERSAMPLING_16;
    HAL_UART_Init(&uart1);
}
#endif

extern "C" void unity_output_char(char character)
{
#if defined(ARDUINO)
    Serial.write(character);
#else
    HAL_UART_Transmit(&uart1, reinterpret_cast<uint8_t *>(&character), 1, HAL_MAX_DELAY);
#endif
}

extern "C" void setUp(void)
{
}

extern "C" void tearDown(void)
{
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

static int run_tests(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_sum_positive_numbers);
    RUN_TEST(test_sum_negative_numbers);
    RUN_TEST(test_sum_zero);
    RUN_TEST(test_sum_commutative);
    return UNITY_END();
}

#if defined(ARDUINO)
void setup()
{
    Serial.begin(115200);
    run_tests();
}

void loop()
{
}
#else
int main(void)
{
    configure_stm32_uart();
    return run_tests();
}
#endif