#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int insert_into_node(char key_weight_str[]);

int main(int argc, char* argv[]){

    insert_into_node("10003;Kate");
    return 0;
}

int insert_into_node(char key_weight_str[]){
    int weight;
    //char* key;

    weight = atoi(strtok(key_weight_str, ";"));
    printf("%d", weight);
    /*key = strtok(NULL, ";");
    printf("%s", key);*/
    return 1;
}
