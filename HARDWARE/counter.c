#include "counter.h"
#include "stdio.h"
#include "usart.h"
/***********************************************************************************************
  //上升沿捕获
************************************************************************************************/
TIM_ICInitTypeDef  TIM3_ICInitStructure;

void TIM3_counter_Init(u16 arr,u16 psc)
{	 
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
   	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//使能TIM5时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);   //使能GPIOA时钟
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_7;  //PA7 清除之前设置  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //PA7 浮空输入  
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA,GPIO_Pin_7);						 //PA7 下拉
	
	//初始化定时器5 TIM5	 
	TIM_TimeBaseStructure.TIM_Period = arr; //设定计数器自动重装值 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 	//预分频器   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
  
	//初始化TIM5输入捕获参数
	TIM3_ICInitStructure.TIM_Channel = TIM_Channel_2; // 	选择输入端 IC1映射到TI1上
  	TIM3_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
  	TIM3_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
  	TIM3_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 		//配置输入分频,不分频 
  	TIM3_ICInitStructure.TIM_ICFilter = 0x00;						//IC1F=0000 配置输入滤波器 不滤波
  	TIM_ICInit(TIM3, &TIM3_ICInitStructure);

	TIM_SelectInputTrigger(TIM3, TIM_TS_TI2FP2); //选择IC2为始终触发源
    TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Reset);//TIM从模式：触发信号的上升沿重新初始化计数器和触发寄存器的更新事件
    TIM_SelectMasterSlaveMode(TIM3, TIM_MasterSlaveMode_Enable); //启动定时器的被动触发
	
	//中断分组初始化
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级2级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //从优先级0级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 	//IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器 
	
	TIM_ITConfig(TIM3,TIM_IT_CC2,ENABLE);//不能允许更新中断 ,允许CC2IE捕获中断	
	
   	TIM_Cmd(TIM3,ENABLE); 	//使能定时器3
  
}
/***********************************************************************************************

************************************************************************************************/
u32 counter=0;					  // 每秒计数
u32 Frequency=0;
void TIM3_IRQHandler(void)
{ 
	if (TIM_GetITStatus(TIM3, TIM_IT_CC2) == SET)
   
    { 
     	  TIM_ClearITPendingBit(TIM3, TIM_IT_CC2);  //清楚TIM的中断待处理位
          counter = (u32)TIM_GetCapture2(TIM3);
		  printf("当前计数为:%d \r\n",counter);		//打印数据					
          Frequency =72000000/counter;

		  printf("当前频率为:%d Hz\r\n",Frequency);//打印数据
    }
}

