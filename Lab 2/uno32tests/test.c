#include <stdio.h>

int main()
{
	char a[9] = "Bonjour!";
	char *b = a;
	printf("%d\n",sizeof(b));
}
