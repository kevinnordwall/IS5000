#include <stdlib.h>
#include <stdio.h>


void adder(const int *x, const int *y, int *z)
{
	*z = *x + *y;
}
int main()
{
	int a = 5;
	const int k = 10;
	int z;
	adder(&a,&k,&z);
	printf("%d\n",z);
	return 0;
}
