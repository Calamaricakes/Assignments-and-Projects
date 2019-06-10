// Source: https://www.w3resource.com/c-programming-exercises/basic-declarations-and-expressions/index.php
// Question: Write a C program that accepts two item’s weight
//           (floating points' values ) and number of purchase
//           (floating points' values) and calculate the average value of the items.

#include <stdio.h>

int main(){
    float item1Weight = 0, item2Weight = 0;
    float numItem1 = 0, numItem2 = 0;

    // info Item1
    printf("Enter Item 1 weight: ");
    scanf("%f", &item1Weight);
    printf("Enter number of Item 1: ");
    scanf("%f", &numItem1);

    // info Item2
    printf("Enter Item 2 weight: ");
    scanf("%f", &item2Weight);
    printf("Enter number of Item 2: ");
    scanf("%f", &numItem2);

    if( (numItem1 + numItem2) != 0 ){
        printf("Average Values: %f", (item1Weight * numItem1 + item2Weight * numItem2)/(numItem1 + numItem2) );
    }
    return 0;
}
