


#include <stdio.h>

char* text1 = "This is a string.";
char* text2 = "Yet another thing.";
int count = 0;
int list1[80];
int list2[80];


void copy_codes( char *text, int *list, int *count)
{
	
	while(*text != '\0')
	{
		char temp = *text;
		*list = (int) temp;

		list++;
		*count = *count + 1; 
		text++;
	}

}


void work()
{
	int *l1 = list1;
	copy_codes( text1, l1, &count );

	int *l2 = list2;
	copy_codes( text2, l2, &count);
	

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
  printf("\nEndian experiment: 0x%02x,0x%02x,0x%02x,0x%02x,0x%02x\n", 
         (int)*c,(int)*(c+1), (int)*(c+2), (int)*(c+3), (int)*(c+4));
  
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
