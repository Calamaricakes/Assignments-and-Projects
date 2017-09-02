#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]){

    char cat[100];

    while(scanf(" %s", cat) == 1){
        printf("%s\n", cat);
    }
    return 0;

}
