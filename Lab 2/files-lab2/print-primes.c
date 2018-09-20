/*
 print-prime.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/

/* 
 * Writer: Andreas Gunnahr
 * Analyzer: Kevin Nordwall
 * */

#include <stdio.h>
#include <stdlib.h>

int counter = 0;
#define COLUMNS 6

int is_prime(int n){
  if( n <= 1 )
          return 0;
  else if( n <= 3 )
          return 1;
  else if( n % 2 == 0 || n % 3 == 0 )
          return 0;

  int i = 5;
  while( i*i <= n  )
  {
        if( n % i == 0 || n % (i+2) == 0)
                return 0;
        i += 6;
  }

  return 1;
}

void print_number( int n )
	{
		if( counter % COLUMNS == 0)
		{
			printf("\n");
		}
		printf("%10d ", n);

	}

void print_primes(int n){
  // Should print out all prime numbers less than 'n'
  // with the following formatting. Note that
  // the number of columns is stated in the define
  // COLUMNS
	for( int i = 2; i <= n; i++ )
	{
		if(is_prime(i) == 1)
		{
			print_number(i);
			counter++;
		}
	}
 }

// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[]){
  if(argc == 2)
    print_primes(atoi(argv[1]));
  else
    printf("Please state an integer number.\n");

  return 0;
}
 
