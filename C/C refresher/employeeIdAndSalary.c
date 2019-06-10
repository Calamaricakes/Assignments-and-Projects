// Source: https://www.w3resource.com/c-programming-exercises/basic-declarations-and-expressions/index.php
// Question: Write a C program that accepts an employee's ID, total worked
//           hours of a month and the amount he received per hour. Print the
//           employee's ID and salary (with two decimal places) of a particular
//           month.

#include <stdio.h>

int main(){
    char id[10];
    int workedHours = 0, amountPerHour = 0;

    printf("Enter employee ID: ");
    scanf("%s", id);

    printf("Enter employee total work hours: ");
    scanf("%d", &workedHours);

    printf("Enter amount received per hour: ");
    scanf("%d", &amountPerHour);

    printf("Employee ID = %s\nSalary = $%d", id, workedHours*amountPerHour);

    return 0;
}
