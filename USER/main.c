#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "oled.h"
#include "timer.h"
#include "ols.h"
#include "jiefang.h"
#include "Kalman.h"
#include "counter.h"
#include "exti.h"
#include "stmflash.h"

/*
	�����������Ѿ���ͷ�ļ��н��ж�����
*/
//����Ƶ�ʲ���
extern u8  TIM5CH1_CAPTURE_STA;		//���벶��״̬		    				
extern u16 TIM5CH1_CAPTURE_VAL;	//���벶��ֵ
extern u16 Freq; //˲��Ƶ��
extern u8  k;		//���벶��״̬

long double time;
unsigned char TimeCount;//ʱ�����ֵ
u16   Freq_array[6]={0};//���Ƶ�����ֵ
u8    times=0;

u16   NumOfTest = 0;//������ʼλ
u16   Num = 0;//��ǰֽ������
u16   temp=0; 
u16   t=0;







Kalman_Typedef klm;

int f1=0,f2=0,f3=0,f4=0,f5=0,f6=0;

  //Ҫ��ϵ�����
  double x1[maxn] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10,11,12,13,14,15}; 
	double x2[maxn] = {16, 17, 18, 19, 20, 21, 22, 23, 24, 25,26,27,28,29,30}; 
	double x3[maxn] = {31, 32, 33, 34, 35, 36, 37, 38, 39, 40,41,42,43,44,45}; 
	double x4[maxn] = {46, 47, 48, 49, 50, 51, 52, 53, 54, 55,56,57,58,59,60}; 
	double x5[maxn] = {61, 62, 63, 64, 65, 66, 67, 68, 69, 70,71,72,73,74,75}; 
	double x6[maxn] = {76, 77, 78, 79, 80, 81, 82, 83, 84, 85,86,87,88,89,90}; 
  double y[maxn] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};// 102.350, 102.470, 102.540, 102.580, 102.600};
	double ttt=0;

u8 Duanlu=0;//��·

u8 Zhangshu=0;//����
u8 Cishu=0;//����

	
u8 mode=0;//ģʽ
u8 Jiaozhun=0;//��У׼
u8 Test=0;//����
	
extern double count;
extern  double b[rank_ + 1];
extern  double Frequency;
extern volatile u16    CAPTURE;
	
	

u8 string[10] = {0};	
 int main(void)
 {	
	
		delay_init();	    	 //��ʱ������ʼ��	  

		NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
  	uart_init(9600);	 //���ڳ�ʼ��Ϊ9600
		TIM3_counter_Init(0XFFFF,0);			//72Mhz��Ƶ�ʼ�����
		LED_Init();			     //LED�˿ڳ�ʼ��
		KEY_Init();          //��ʼ���밴�����ӵ�Ӳ���ӿ�
	  
		Kalman_Init(&klm,0,0.25);
		uart_init(115200);	 //���ڳ�ʼ��Ϊ115200

		OLED_Init();
		OLED_ShowString(40,0,"zhizhang",16);
		OLED_Refresh();


	while(1) 
	{		  		
		sprintf((char *)string,"f :%.2f",Frequency);//0300
		OLED_ShowString(16,16,string,16);
		OLED_Refresh();
		
		
//		printf("����Ƶ��\r\n");
//		delay_ms(10000); 
//		printf("Ƶ�ʣ�%.2f\r\n",Frequency);
////		KalmanFilter(&klm,Kfrequence);
////		if(klm.out!=0) mode=1;
////		printf("�˲���%f\r\n",klm.out);
//	
//		delay_ms(200);
//			polyfit(x1,y);
//						ttt=Frequency;
//						Zhangshu =_3_cifang ( b[3] , b[2], b[1], (b[0]-ttt));
//		sprintf((char *)string,"F%.2f",Frequency);//0300
//						OLED_ShowString(16,16,string,16);
//						sprintf((char *)string,"num  :%d",Zhangshu);//0300
//						OLED_ShowString(16,32,string,16);
//						OLED_Refresh();
//		
//		
//		

////		if(mode==1){
////			switch(mode){
////				case KEY0_PRES:{
////					/*********У׼ģʽ***********/
////					for(i=0;i<15;i++)
////					{
////						y[i]=0;
////					}
////					
////					Jiaozhun=1;			//set   ��У׼ ��־λ	
////				
////					Test=0;					//reset ���� ��־λ	
////				}break;
////				case KEY1_PRES:{	
////					/***************����ģʽ***************/
////					Test=1;					//set  ���� ��־λ
////				
////				  Jiaozhun=0;			//reset��У׼ ��־λ
////				}break;

////				case KEY2_PRES:{
////					/********����ģʽ***********/
////						if(Jiaozhun==1)
////					{
////						if(klm.out<f2){
////							y[Cishu]=klm.out;
////							Cishu++;
////							BEE=1;	delay_ms(50);		
////							if(Cishu==15)//���1��15��
////							{
////								Cishu=0;
////								polyfit(x1,y);
////							
////								delay_ms(50);
////							}
////							BEE=0;
////						}
////						else if(klm.out>f2&&klm.out<f3){
////							y[Cishu]=klm.out;
////							Cishu++;
////							BEE=1;	delay_ms(50);		
//							if(Cishu==15)//���15��30��
//							{
//								Cishu=0;
//								polyfit(x2,y);
//								
//								delay_ms(50);
//							}
//							BEE=0;
//						}
//						else if(klm.out>f3&&klm.out<f4){
//							y[Cishu]=klm.out;
//							Cishu++;
//							BEE=1;	delay_ms(50);		
//							if(Cishu==15)//���30��45��
//							{
//								Cishu=0;
//								polyfit(x3,y);
//							
//								delay_ms(50);
//							}
//							BEE=0;
//						}
//						else if(klm.out>f4&&klm.out<f5){
//							y[Cishu]=klm.out;
//							Cishu++;
//							BEE=1;	delay_ms(50);		
//							if(Cishu==15)//���45��60��
//							{
//								Cishu=0;
//								polyfit(x4,y);
//								
//								delay_ms(50);
//							}
//							BEE=0;
//						}
//						else if(klm.out>f5&&klm.out<f6){
//							y[Cishu]=klm.out;
//							Cishu++;
//							BEE=1;	delay_ms(50);		
//							if(Cishu==15)//���60��75��
//							{
//								Cishu=0;
//								polyfit(x5,y);
//								
//								delay_ms(50);
//							}
//							BEE=0;
//						}else{
//							y[Cishu]=klm.out;
//							Cishu++;
//							BEE=1;	delay_ms(50);		
//							if(Cishu==15)//���75��90��
//							{
//								Cishu=0;
//								polyfit(x6,y);
//								
//								delay_ms(50);
//							}
//							BEE=0;
//						}
//					}
//				/*************����****************/
//					if(Test==1)
//					{
//						ttt=klm.out;
//						Zhangshu =_3_cifang ( b[3] , b[2], b[1], (b[0]-ttt));
//						printf("ֽ����Ϊ��%d",Zhangshu);
//						BEE=1;	delay_ms(50);		BEE=0;
//					}
//				}break;	
//				
//					
//			}
//		}
//		else {
//			//��·����
//			BEE=1;
//			delay_ms(100);
//		}			   
	}
 }

