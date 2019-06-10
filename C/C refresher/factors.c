// Source: https://www.w3resource.com/c-programming-exercises/basic-declarations-and-expressions/index.php
// Question: Write a C program that reads two integers and checks if they are multiplied or not.

#include <stdio.h>

int main(){
    int first, second;

    printf("Please enter first number: ");
    scanf("%d", &first);

    printf("Please enter second number: ");
    scanf("%d", &second);

    if( first > 0 && second > 0 ){
        if( first % second == 0 ){
            printf("Multiplied!\n");
        }
        else if ( second % first == 0 ){
            printf("Multiplied!\n");
        }
        else{
            printf("Not multiplied!\n");
        }
    }
    else{
        printf("Not multiplied!\n");
    }
    return 0;

}
