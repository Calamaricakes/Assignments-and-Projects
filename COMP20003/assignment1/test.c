#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NUM 50

int main(int argc, char* argv[]){
    int i = 0;
    FILE* file_input;
    char input[250];
    char str[500];

    file_input = fopen("cities.csv", "r");
    char* ptr_token;
    srand(time(NULL));

    if(!freopen("test_cities_50", "w", stdout)){
        printf("fail");
        exit(EXIT_FAILURE);
    }

    while(fgets(input, 250, file_input) != NULL){
        ptr_token = strtok(input, ";");
        ptr_token = strtok(NULL, "\n");
        strcpy(str, ptr_token);
        str[2] = '\0';
        if(rand() % 10 < 3){
            printf("%s\n", str);
            i++;
        }
        if(i >= MAX_NUM){
            break;
        }
    }
    fclose(file_input);
    fclose(stdout);
    return 0;
}
