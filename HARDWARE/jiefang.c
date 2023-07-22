#include "jiefang.h"
#include "led.h"
#include "delay.h"


//***********һԪ���η������*****************/
//a->x2  b->x1   c-> x0-y
double _2_cifang(double a, double b, double c)		
{
  double p;                         		     /*����������ͱ��ʽ�ı���ֵ*/
	double x;
	
	p=b*b-4*a*c;                            		   /*�����ʽ��ֵ*/
    x=(-b+sqrt(p))/(2.0*a);                           /*��1��ֵ*/
 //   x[2]=(-b-sqrt(p))/(2.0*a);                           /*��2��ֵ*/

	return x;
}
/*************һԪ���η������***********************/ 
//a->x3  b->x2   c->x1  d-> x0-y

u8 _3_cifang(double a,double b,double c,double d) //�������
{
	double x1=0,x2=30;
	double x0,fx0,fx1,fx2;
	u8 ans;
		fx1 = a*x1*x1*x1 + b*x1*x1 + c*x1 + d;   //�����������˵㣬������ֵ
		fx2 = a*x2*x2*x2 + b*x2*x2 + c*x2 + d;
	
	
	do
	{
		x0=(x1+x2)/2;       //x0Ϊ������е�
		fx0=a*x0*x0*x0 + b*x0*x0 + c*x0 + d;   //�е�ĺ���ֵ
		if((fx0*fx1)<0)      //���е��޸�Ϊ����ֵ���е㺯��ֵͬ�ŵĶ˵�
		{
			x2=x0;
			fx2=fx0;
		}
		else
		{
			x1=x0;
			fx1=fx0;
		}
	}while(fabs(fx0)>=0.0001); //ֱ���е�ĺ���ֵ��0�㹻�ӽ�
//	if(x0>8.0)
//	{
//		if((u16)(x0+0.4)==(u16)(x0))
//			ans=(u16)x0;
//		else
//			ans=(u16)x0+1;
//	}
//	else
//	{
		if((u16)(x0+0.5)==(u16)(x0))
			ans=(u16)x0;
		else
			ans=(u16)x0+1;
//  }
	return (u8)ans;
}
	
	