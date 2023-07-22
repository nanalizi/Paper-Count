 /********************STMicroelectronics ********************
* File Name          : main.c
* Author             : 
* Date First Issued  : 8-8-19
* Description        : ��С���˷��������
*************************************************************/
#include "sys.h"
#include "ols.h"

#include <stdio.h>
#include <math.h>   

//double atemp[2 * (rank_ + 1)],b[rank_ + 1], a[rank_ + 1][rank_ + 1];     
double b[rank_ + 1];
void polyfit(double x[],double y[])
{	
		double atemp[2 * (rank_ + 1)], a[rank_ + 1][rank_ + 1]; 

		int i, j, k;
		int column=0;
		double mainelement=0;
		double temp=0;
		double btemp=0;
		double Mik=0;
		double sum=0;
		for(i=0;i<7;i++)
	  {
				if(i<4)
					b[i]=0;
				atemp[i]=0;
	  }
    for(i = 0; i < maxn; i++)
	  {  
        atemp[1] += x[i];
        atemp[2] += pow(x[i], 2);
        atemp[3] += pow(x[i], 3);
        atemp[4] += pow(x[i], 4);
        atemp[5] += pow(x[i], 5);
        atemp[6] += pow(x[i], 6);
        b[0] += y[i];
        b[1] += x[i] * y[i];
        b[2] += pow(x[i], 2) * y[i];
        b[3] += pow(x[i], 3) * y[i];
    }

	
    atemp[0] = maxn;
    /*
    for(i = 0; i <= 2 * rank_; i++)  printf("atemp[%d] = %f\n", i, atemp[i]);
    printf("\n");
    for(i = 0; i <= rank_; i++)  printf("b[%d] = %f\n", i, b[i]);
    printf("\n");
    */
    for(i = 0; i < rank_ + 1; i++){  //�������Է�����ϵ������b[]����
        k = i;
        for(j = 0; j < rank_ + 1; j++)  a[i][j] = atemp[k++];
    }

    /*
    for(i = 0; i < rank_ + 1; i++){
        for(j = 0; j < rank_ + 1; j++)  printf("a[%d][%d] = %-17f  ", i, j, a[i][j]);
        printf("\n");
    }
    printf("\n");
    */

    //����Ϊ��˹����Ԫ��ȥ�������Է�����
    for(k = 0; k < rank_ + 1 - 1; k++){  //n - 1��
        column = k;
        mainelement = a[k][k];
        for(i = k; i < rank_ + 1; i++)  //����Ԫ��
            if(fabs(a[i][k]) > mainelement)
						{
                mainelement = fabs(a[i][k]);
                column = i;
            }
        for(j = k; j < rank_ + 1; j++){  //��������
            temp = a[k][j];
            a[k][j] = a[column][j];
            a[column][j] = temp;
        }
        btemp = b[k];
        b[k] = b[column];
        b[column] = btemp;

        for(i = k + 1; i < rank_ + 1; i++){  //��Ԫ����
            Mik = a[i][k] / a[k][k];
            for(j = k; j < rank_ + 1; j++)  a[i][j] -= Mik * a[k][j];
            b[i] -= Mik * b[k];
        }
    }

    /*
    for(i = 0; i < rank_ + 1; i++){  //������Ԫ��˹��ȥ���õ�����������(���һ��Ϊ��ϵ��)
        for(j = 0; j < rank_ + 1; j++)  printf("%20f", a[i][j]);
        printf("%20f\n", b[i]);
    }
    printf("\n");
    */
    b[rank_ + 1 - 1] /= a[rank_ + 1 - 1][rank_ + 1 - 1];  //�ش�����
    for(i = rank_ + 1 - 2; i >= 0; i--){
        sum = 0;
        for(j = i + 1; j < rank_ + 1; j++)  sum += a[i][j] * b[j];
        b[i] = (b[i] - sum) / a[i][i];
    }
		
    //��˹����Ԫ��ȥ������

  //  printf("P(x) = %f%+fx%+fx^2%+fx^3\n\n", b[0], b[1], b[2], b[3]);
    /*
    for(i = 0; i < maxn; i++){  //���Ƚ�
        double temp = b[0] + b[1] * x[i] + b[2] * x[i] * x[i] + b[3] * x[i] * x[i] * x[i];
        printf("%f    %f    error: %f\n", y[i], temp, temp - y[i]);
    }
    */

//			OLED_ShowNum(0,0 ,b[0]*10000,8,12);//��ʾASCII�ַ�����ֵ
//			OLED_ShowNum(0,12,b[1]*10000,8,12);//��ʾASCII�ַ�����ֵ
//			OLED_ShowNum(0,24,b[2]*10000*(-1),8,12);//��ʾASCII�ַ�����ֵ
//		  OLED_ShowNum(0,36,b[3]*10000,8,12);//��ʾASCII�ַ�����ֵ
//	

//			
//  		OLED_Refresh_Gram();

}
