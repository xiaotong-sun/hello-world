#include <stdio.h> 
#include <math.h>
#include <conio.h>
#define EPS 1e-1
int main ()
{
	while (1){
	
		float a,b,c;
		printf("�����������ε����߳���");
		scanf("%f%f%f",&a,&b,&c) ;
		if (a+b>c&&a+c>b&&b+c>a)
			{
				if(fabs(a*a+b*b-c*c)<=EPS||fabs(a*a+c*c-b*b)<=EPS||fabs(b*b+c*c-a*a)<=EPS)
					printf("������Ϊֱ��������\n");
				else if (fabs(a-b)<=EPS||fabs(a-c)<=EPS||fabs(b-c)<=EPS)
					printf("������Ϊ����������\n");
				else 
					printf("������Ϊһ��������\n");
			}
		else 
			printf("������������\n"); 
		getch ();
	}
	return 0; 
}
