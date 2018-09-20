#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/* Writer: Andreas Gunnahr
 * Analyser: Kevin Nordwall
 * */

#define COLUMNS 6
int counter = 0;

void print_number( const int n )
{
        if( counter % COLUMNS == 0)
        {
			printf("\n");
        }
      	printf("%10d ", n);
}

void print_sieves(const int n)
{
 	int *array = malloc(n);
	for( int i = 0; i < n; i++)
		array[i] = 1;
	
	for( int i = 2; i < sqrt(n); i++)
	{
		if (array[i])
		{
			for( int j = i*i; j < n; j += i)
			{
				array[j] = 0;
			}

		}
	}

	for( int i = 2; i < n; i++)
	{
		if(array[i])
		{
			print_number(i);
			counter++;
		}
	}
	free(array);
 }

// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[]){
  if(argc == 2)
    print_sieves(atoi(argv[1]));
  else
    printf("Please state an integer number.\n");

  return 0;
}

