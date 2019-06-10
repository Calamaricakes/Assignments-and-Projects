// Source: https://www.w3resource.com/c-programming-exercises/basic-declarations-and-expressions/index.php
// Question: 4. Write a C program to print the following characters in a reverse way.

#include <stdio.h>
#include <string.h>

#define HUNDRED 100

int main(){

    char string[HUNDRED];
    int len = 0, i;

    printf("Please enter less than (<) 10 characters\n");
    scanf("%s", string);

    len = strlen(string);

    for(i = len - 1; i >= 0; i--){
        printf("%c", string[i]);
    }

    return 0;
}
