// Source: https://www.w3resource.com/c-programming-exercises/basic-declarations-and-expressions/index.php
// Question: 26. Write a C program that prints all even numbers between 1 and 50 (inclusive)

#include <stdio.h>

int main(){
    int i;

    for(i = 0; i <= 50; i++){

        if(i % 2 == 0){
            printf("%d ", i);
        }

    }
    return 0;

}
