


#include <stdio.h>

char* text1 = "This is a string.";
char* text2 = "Yet another thing.";
int count = 0;
int list1[80];
int list2[80];


void copy_codes( char **a0, int *a1, int *a2)
{
	// finish yo
}


void work()
{
	char **a0 = &text1;
	int *a1 = list1;
	int *a2 = &count;
	copy_codes( a0, a1, a2 );

}

void printlist(const int* lst){
  printf("ASCII codes and corresponding characters.\n");
  while(*lst != 0){
    printf("0x%03X '%c' ", *lst, (char)*lst);
    lst++;
  }
  printf("\n");
}

void endian_proof(const char* c){
  printf("\nEndian experiment: 0x%02x,0x%02x,0x%02x,0x%02x\n", 
         (int)*c,(int)*(c+1), (int)*(c+2), (int)*(c+3));
  
}

int main(void){
  work();

  printf("\nlist1: ");
  printlist(list1);
  printf("\nlist2: ");
  printlist(list2);
  printf("\nCount = %d\n", count);

  endian_proof((char*) &count);
}
