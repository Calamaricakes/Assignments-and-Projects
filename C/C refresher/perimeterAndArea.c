// Source: https://www.w3resource.com/c-programming-exercises/basic-declarations-and-expressions/index.php
// Question: Write a C program to compute the perimeter and area of a rectangle with a height of 7 inches.
//           and width of 5 inches

#include <stdio.h>

int main(){

    int perimeter, area;
    int height = 7, width = 5;

    perimeter = 2*height + 2*width;
    area = height*width;

    printf("Perimeter = %d inches\nArea = %d square inches\n", perimeter, area);

    return 0;
}
