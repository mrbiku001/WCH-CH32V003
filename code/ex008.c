// To use GPIO input in the interrupt mode we need to use External Interrupt (EXTI)

// let us see how we need to configure it to receive the interrupt.

// Code works like GPIO D4 is configured for output, D3 is configured for input with internal pull up. External interrupt line in enabled on D3 using function GPIO_EXTILineConfig for interrupt on falling edge (EXTI_Trigger_Falling). Interrupt in enable on EXTI7_0_IRQn so that when falling edge is detected on D3, Interrupt handler funcion (EXTI7_0_IRQHandler) will be called.

// In the code below what we are doing is initally we are making LED OFF and when D3 gets falling edge, interrupt occurs and it rases a Flag(interruptFlag, declared as global variable).

// This flag is then check in While(1), if Flag is high, LED is made ON.


/* Global Variable */
uint8_t interruptFlag = 0;

/*********************************************************************
 * @fn      EXTI0_INT_INIT
 *
 * @brief   Initializes EXTI0 collection.
 *
 * @return  none
 */
void EXTI0_INT_INIT(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    EXTI_InitTypeDef EXTI_InitStructure = {0};
    NVIC_InitTypeDef NVIC_InitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOD, ENABLE);

    // Configuration for LED on D4
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);


    //Configuration for GPIO Input on D3
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    /* GPIOD ----> EXTI_Line0 */
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOD, GPIO_PinSource3);
    EXTI_InitStructure.EXTI_Line = EXTI_Line3;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = EXTI7_0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
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

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    SystemCoreClockUpdate();
    Delay_Init();
    EXTI0_INT_INIT();
    GPIO_WriteBit(GPIOD, GPIO_Pin_4, SET); // Set LED OFF initially
    while(1)
    {
        Delay_Ms(100);
        if(interruptFlag == 1)
        {
            GPIO_WriteBit(GPIOD, GPIO_Pin_4, RESET);
            interruptFlag = 0;
        }
    }
}


void EXTI7_0_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

/*********************************************************************
 * @fn      EXTI0_IRQHandler
 *
 * @brief   This function handles EXTI0 Handler.
 *
 * @return  none
 */
void EXTI7_0_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line3)!=RESET)
    {
        interruptFlag = 1;
        EXTI_ClearITPendingBit(EXTI_Line3);     /* Clear Flag */
    }
}