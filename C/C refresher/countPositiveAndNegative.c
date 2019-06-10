// Source: https://www.w3resource.com/c-programming-exercises/basic-declarations-and-expressions/index.php
// Question: 27. Write a C program that read 5 numbers and counts the number of positive numbers and negative numbers.

#include <stdio.h>

int main(){
    int i, num, positiveNumbers = 0, negativeNumbers = 0;

    for( i = 0; i < 5; i++){
        printf("Please enter number: ");
        scanf("%d", &num);

        if(num > 0){
            positiveNumbers++;
        }
        else if (num < 0){
            negativeNumbers++;
        }
    }
    printf("Positive numbers: %d\nNegative number: %d", positiveNumbers, negativeNumbers);
    return 0;
}
