#include <stdlib.h>
#include <stdio.h>

int main()
{
    int n = 5;


    int a0 = n;
    int a1 = a0 - 1;
    int a2 = 0;
    int a3 = 0;
    int v0 = 0;

    while(a1!=0)
    {
        a3 = a1; //3
        while(a1!=0)
        {
            a2 = a2 + a0; //4 // 12 // 24
            a1 = a1 - 1; //2
        }
    
    a0 = a2; // 12 // 24 // 24
    a2 = 0;
    a1 = a3 - 1; // 2 // 1

    }
    v0 = a0;
    printf("%d", v0);
    return v0;

}