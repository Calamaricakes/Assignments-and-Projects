#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]){
    int i;

    printf("%s\n", argv[0]);

    for(i = 0; i < argc; i++){
        printf("%s\n", argv[i]);
    }
    /*while(scanf("%s", input) == 1){
        printf("%s\n", input);
    }*/
    return 0;

}
