#include<stdio.h>
int main()
{
	int n;
	scanf("%d",&n);
	int remainder,originer,reverser=0;
	originer=n;
	while(n!=0){
		remainder=n%10;
		reverser=reverser*10+remainder;
		n/=10;
	}
	if(originer==reverser){
		printf("Y");
	}else{
		printf("N");
	}
	return 0;
}
