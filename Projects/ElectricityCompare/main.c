#include <stdio.h>

int main(int argc, char** argv){
    int number1, number2;

    printf("Enter a number:");
    scanf("%d", &number1);
    printf("Number is %d\n", number1);
    printf("Enter a number:");
    scanf("%d", &number2);
    printf("Number is %d\n", number2);

    return 0;
}