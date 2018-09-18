#include <stdlib.h>
#include <math.h>
#include <stdio.h>

void square_reverse(const double *x, double *y, const int len)
{
	
	for(int i = 0; i < len; i++)
	{
		*(y + len - i - 1) = pow( *( x + i ), 2 );
	}

	for(int j = 0; j<len;j++)
	{
		printf("%f\n", *(y + j));
	}

}

int main()
{
	double in[] = {11.0, 20.0, 100.0};
	double out[3];
	square_reverse( in, out, 3 );
	return 0;
}
