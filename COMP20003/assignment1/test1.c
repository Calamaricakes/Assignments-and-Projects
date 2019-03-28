#include <stdio.h>
#include <math.h>

int max_sum(int arr[], int len);

int main(int argc, char* argv[]){
    int i = 1;

    for(i = 0; i < 11; i++){
        printf("%d\n", (int)pow(2, i));
    }
}

int max_sum(int arr[], int len){
    int i;
    int sum = 0;

    for(i = 0; i < len; i++){
        if(arr[i] < 0){
            sum += -arr[i];
        }
        else{
            sum += arr[i];
        }

    }
    return sum;
}
