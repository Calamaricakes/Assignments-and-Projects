// Source: https://www.w3resource.com/c-programming-exercises/basic-declarations-and-expressions/index.php
// Question: Write a C program that accepts three integers and find the maximum of three.

#include <stdio.h>

int main(){
    int arr[3] = { 0 };
    int max = 0;

    printf("Please enter first integer: ");
    scanf("%d", &arr[0]);

    printf("Please enter second integer: ");
    scanf("%d", &arr[1]);

    printf("Please enter third integer: ");
    scanf("%d", &arr[2]);

    max = arr[0];

    if (max < arr[1]){
        max = arr[1];
    }
    if(max < arr[2]){
        max = arr[2];
    }

    printf("Max integer = %d", max);
    return 0;
}
