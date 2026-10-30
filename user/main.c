#include "stm32f10x.h"
void My_OnBoardLED_Init();
int main(void)
{
	My_OnBoardLED_Init();
	 GPIO_InitTypeDef GPIO_InitStruct;
    USART_InitTypeDef USART_InitStruct;

    /* 开启 GPIOB、AFIO、USART1 时钟 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB |
                          RCC_APB2Periph_AFIO |
                          RCC_APB2Periph_USART1,
                          ENABLE);

    /* USART1 重映射：TX -> PB6，RX -> PB7 */
    GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);

//    /* PB6：复用推挽输出 */
////    GPIO_StructInit(&GPIO_InitStruct);
//    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
//    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
//    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
//    GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* PB7：上拉输入 */
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* USART1：115200，8 位数据，1 位停止位，无校验 */
//    USART_StructInit(&USART_InitStruct);
    USART_InitStruct.USART_BaudRate = 115200;
    USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
    USART_InitStruct.USART_StopBits = USART_StopBits_1;
    USART_InitStruct.USART_Parity = USART_Parity_No;
    USART_Init(USART1, &USART_InitStruct);

    USART_Cmd(USART1, ENABLE);
	while(1)
	{
		while(USART_GetFlagStatus(USART1,USART_FLAG_RXNE)==RESET);
		uint8_t byteRecd=USART_ReceiveData(USART1);
		if(byteRecd=='0'){
		GPIO_WriteBit(GPIOC,GPIO_Pin_13,Bit_SET);
		}else{
		GPIO_WriteBit(GPIOC,GPIO_Pin_13,Bit_RESET);
		}
	}
}
void My_OnBoardLED_Init(){

	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_13;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_OD;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_2MHz;
	GPIO_Init(GPIOC,&GPIO_InitStruct);
	
	GPIO_WriteBit(GPIOC,GPIO_Pin_13,Bit_SET);
	
}