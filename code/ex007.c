// Let is now see how we can write the code to check the status GPIO Inpt pin and then glow the LED as per the status. So, we will see if GPIO Input pin is Low we will glow the LED and if it is High LED will be OFF.

// D3 is the input and D4 is output for LED.

void GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0}; //structure variable used for the GPIO configuration

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE); // to Enable the clock for Port D

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; // Defines which Pin to configure
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; // Defines Output Type
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4; // Defines which Pin to configure
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // Defines Output Type
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // Defines speed
    GPIO_Init(GPIOD, &GPIO_InitStructure);

}

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
    uint8_t GPIOInputStatus = 0;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    SystemCoreClockUpdate();
    Delay_Init();
    GPIO_Config();

    while(1)
    {
        GPIOInputStatus = GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_3);
        if(GPIOInputStatus == 0)
        {
            GPIO_WriteBit(GPIOD, GPIO_Pin_4, RESET);
        }
        else
        {
            GPIO_WriteBit(GPIOD, GPIO_Pin_4, SET);
        }
        Delay_Ms(100);

    }
}