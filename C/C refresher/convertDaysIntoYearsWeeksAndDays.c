// Source: https://www.w3resource.com/c-programming-exercises/basic-declarations-and-expressions/index.php
// Question: 8. Write a C program to convert specified days into years, weeks and days.

#include <stdio.h>

#define YEAR_LEN 365
#define WEEK_LEN 7

int main(){
    int inputDays = 0;
    int years = 0, weeks = 0, days = 0;

    printf("Please enter days to convert: ");
    scanf("%d", &inputDays);

    years = inputDays / YEAR_LEN;
    weeks = ( inputDays - (years * YEAR_LEN) )/ WEEK_LEN;
    days  = inputDays - (years * YEAR_LEN) - (weeks * WEEK_LEN) ;

    printf("Years = %d\nWeeks = %d\nDays = %d", years, weeks, days);

    return 0;
}
