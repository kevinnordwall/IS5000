#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/* Writer: Kevin Nordwall
 * Analyzer: Andreas Gunnahr
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
 	char array[8000];
	for( int i = 0; i < 8000; i++)
		array[i] = '0';
	
	for( int i = 2; i < sqrt(8000); i++)
	{
		if (array[i] == '0')
		{
			for( int j = i*i; j < 8000; j += i)
			{
				array[j] = '1';
			}

		}
	}
	
	for(int j = 0; j < 8000; j++)
	{
		if(array[j] == '0' && j!= 0 && j!=1)
			counter++;
		if(counter == n)
		{
			printf("%10d\n", j);
			break;
		}
	}

	/*for( int i = 2; i < n; i++)
	{
		if(array[i] == '0')
		{
			print_number(i);
			counter++;
		}
	}*/
 }


void nth_sieves(const int n)
{
	print_sieves(n);

}


// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[]){
  if(argc == 2)
	  nth_sieves(atoi(argv[1]));
	//	print_sieves(atoi(argv[1]));
  else
    printf("Please state an integer number.\n");

  return 0;
}

