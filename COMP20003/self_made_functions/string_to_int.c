#include <stdio.h>
#include <math.h>

int string_to_int(const char numeric_string[]);

int string_to_int(const char numeric_string[]){
    /* converts a positive numeric string ("10023"), to an integer(10023) */
    // REQUIRES SERIOUS CHECKS, THEY ARE INCOMPLETE! INPUT ASSUMED PERFECT.

    int length = 0, parsed_int = 0, i;

    while(numeric_string[length] != '\0'){ //find index of smallest int value("3")
        length++;
    }

    for(i = 0; i < length; i++){
        parsed_int += (numeric_string[i] - '0') * (int) (pow(10, length - 1 - i) + 0.5);
    }
    return parsed_int;
}
