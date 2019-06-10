// Source: https://www.w3resource.com/c-programming-exercises/basic-declarations-and-expressions/index.php
// Question: Write a C program to calculate the distance between the two points.
// Info: Two dimensional euclidian distance
#include <stdio.h>
#include <math.h>

int main(){
    float firstX = 0, firstY = 0, secondX = 0, secondY = 0, distance = 0;

    printf("Please enter first x coordinate: ");
    scanf("%f", &firstX);

    printf("Please enter first y coordinate: ");
    scanf("%f", &firstY);

    printf("Please enter second x coordinate: ");
    scanf("%f", &secondX);

    printf("Please enter second y coordinate: ");
    scanf("%f", &secondY);

    distance = sqrt((firstX - secondX)*(firstX - secondX) + (firstY - secondY)*(firstY - secondY));

    printf("Distance between the two points: %f", distance);

    return 0;
}
