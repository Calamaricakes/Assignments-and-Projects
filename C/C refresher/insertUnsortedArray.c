#include <stdio.h>

#define SIZE 10

int main(){

    int arr[SIZE];
    int i, count = 0;

    while(scanf("%d", &arr[count]) != EOF){
        count++;
    }

    for(i = 0; i < count; i++){
        printf("%d ", arr[i]);
    }

    return 0;
}
