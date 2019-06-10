// Source: https://www.w3resource.com/c-programming-exercises/basic-declarations-and-expressions/index.php
// Question: Write a C program that accepts 4 integers p, q, r, s from the user
//           where r and s are positive and p is even. If q is greater than r
//           and s is greater than p and if the sum of r and s is greater than
//           the sum of p and q print "Correct values", otherwise print "Wrong values"

#include <stdio.h>

int main(){
    int p = 0, q = 0, r = 0, s = 0;

    printf("Please enter p: ");
    scanf("%d", &p);

    printf("Please enter q: ");
    scanf("%d", &q);

    printf("Please enter r: ");
    scanf("%d", &r);

    printf("Please enter s: ");
    scanf("%d", &s);

    if( ( q > r ) && ( s > p ) && (( r + s ) > ( p + q )) ){
        printf("Correct values");
    }
    else{
        printf("Wrong values");
    }

    return 0;
}
