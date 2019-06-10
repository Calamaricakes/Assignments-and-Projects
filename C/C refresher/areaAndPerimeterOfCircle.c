// Source: https://www.w3resource.com/c-programming-exercises/basic-declarations-and-expressions/index.php
// Question: 6. Write a C program to compute the perimeter and area of a circle with a radius of 6 inches.

#include <stdio.h>
#include <math.h>

int main(){
    float perimeterOfCircle = 0, areaOfCircle = 0, radius = 6;

    perimeterOfCircle = 2*M_PI*radius; // perimeter equation for circles
    areaOfCircle = M_PI*radius*radius; // area of circle equation

    printf("Perimeter of circle = %.2f units\n", perimeterOfCircle);
    printf("Area of circle = %.2f units", areaOfCircle);

    return 0;
}
