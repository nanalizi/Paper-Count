#include "jiefang.h"
#include "led.h"
#include "delay.h"


//***********一元二次方程求解*****************/
//a->x2  b->x1   c-> x0-y
double _2_cifang(double a, double b, double c)		
{
  double p;                         		     /*定义根变量和表达式的变量值*/
	double x;
	
	p=b*b-4*a*c;                            		   /*给表达式赋值*/
    x=(-b+sqrt(p))/(2.0*a);                           /*根1的值*/
 //   x[2]=(-b-sqrt(p))/(2.0*a);                           /*跟2的值*/

	return x;
}
/*************一元三次方程求解***********************/ 
//a->x3  b->x2   c->x1  d-> x0-y

u8 _3_cifang(double a,double b,double c,double d) //求根函数
{
	double x1=0,x2=30;
	double x0,fx0,fx1,fx2;
	u8 ans;
		fx1 = a*x1*x1*x1 + b*x1*x1 + c*x1 + d;   //计算在两个端点，函数的值
		fx2 = a*x2*x2*x2 + b*x2*x2 + c*x2 + d;
	
	
	do
	{
		x0=(x1+x2)/2;       //x0为区间的中点
		fx0=a*x0*x0*x0 + b*x0*x0 + c*x0 + d;   //中点的函数值
		if((fx0*fx1)<0)      //将中点修改为函数值与中点函数值同号的端点
		{
			x2=x0;
			fx2=fx0;
		}
		else
		{
			x1=x0;
			fx1=fx0;
		}
	}while(fabs(fx0)>=0.0001); //直到中点的函数值与0足够接近
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
	
	