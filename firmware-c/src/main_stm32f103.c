#include "stm32f1xx_hal.h"

#include <stdio.h>
#include <string.h>

#include <sum.h>

static UART_HandleTypeDef uart1;

void SysTick_Handler(void)
{
    HAL_IncTick();
}

static void configure_gpio(void)
{
    GPIO_InitTypeDef gpio = {0};

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();

    gpio.Pin = GPIO_PIN_13;
    gpio.Mode = GPIO_MODE_OUTPUT_PP;
    gpio.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOC, &gpio);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);

    gpio.Pin = GPIO_PIN_9;
    gpio.Mode = GPIO_MODE_AF_PP;
    gpio.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &gpio);

    gpio.Pin = GPIO_PIN_10;
    gpio.Mode = GPIO_MODE_INPUT;
    gpio.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &gpio);
}

static void configure_uart(void)
{
    __HAL_RCC_USART1_CLK_ENABLE();

    uart1.Instance = USART1;
    uart1.Init.BaudRate = 115200;
    uart1.Init.WordLength = UART_WORDLENGTH_8B;
    uart1.Init.StopBits = UART_STOPBITS_1;
    uart1.Init.Parity = UART_PARITY_NONE;
    uart1.Init.Mode = UART_MODE_TX_RX;
    uart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    uart1.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&uart1) != HAL_OK)
    {
        while (1)
        {
        }
    }
}

static void uart_write(const char *message)
{
    HAL_UART_Transmit(&uart1, (uint8_t *)message, strlen(message), HAL_MAX_DELAY);
}

int main(void)
{
    char message[48];

    HAL_Init();
    configure_gpio();
    configure_uart();

    uart_write("Hello from STM32F103 C Firmware!\r\n");
    snprintf(message, sizeof(message), "sum(10, 32) = %d\r\n", sum(10, 32));
    uart_write(message);

    while (1)
    {
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
        uart_write("Blink STM32 loop executed. Pin PC13 state: 1\r\n");
        HAL_Delay(1000);

        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
        uart_write("Blink STM32 loop executed. Pin PC13 state: 0\r\n");
        HAL_Delay(1000);
    }
}