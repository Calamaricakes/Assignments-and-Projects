// Source: https://www.w3resource.com/c-programming-exercises/basic-declarations-and-expressions/index.php
// Question: 9. Write a C program that accepts two integers from the user and calculate the sum of the two integers

#include <stdio.h>

int main(){
    int integer1 = 0, integer2 = 0;

    printf("Input integer 1: ");
    scanf("%d", &integer1);
    printf("Input integer 2: ");
    scanf("%d", &integer2);

    printf("Sum of integers = %d", integer1 + integer2);

    return 0;
}
