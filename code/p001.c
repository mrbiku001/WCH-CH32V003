// Code to blink 2 leds at D0 and D2

#include "debug.h"

/* Global define */

void GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
}

int main(void)
{

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    SystemCoreClockUpdate();
    Delay_Init();

    GPIO_Config();

    while(1)
    {
        Delay_Ms(500);
            GPIO_WriteBit(GPIOD, GPIO_Pin_0, SET);
            GPIO_WriteBit(GPIOD, GPIO_Pin_2, SET);
            Delay_Ms(500);
            GPIO_WriteBit(GPIOD, GPIO_Pin_0, RESET);
            GPIO_WriteBit(GPIOD, GPIO_Pin_2, RESET);
    }
}
