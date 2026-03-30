#include <stdint.h>
#include <string.h>
#include "stm32f4xx.h"
#include "led.h"
#include "key.h"
#include "usart.h"
#include "cpu_delay.h"

#define delay(ms) cpu_delay((ms) * 1000)

int main(void)
{
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    
    key_init();
    usart_init();
    
    while(1)
    {
//        uint8_t key1 = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);
//        if (key1 == Bit_SET)
//        {
//            usart_write("key1 pressed\r\n");
//        }
        if (!key_read(2))
        {
            delay(20);
            if (!key_read(2))
            {
                usart_write("key2 pressed\r\n");
                while (!key_read(2));
                delay(20);
            }
        }
        if (!key_read(3))
        {
            delay(20);
            if (!key_read(3))
            {
                usart_write("key3 pressed\r\n");
                while (!key_read(3));
                delay(20);
            }
        }
    }
}
