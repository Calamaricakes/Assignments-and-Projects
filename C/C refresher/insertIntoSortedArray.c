#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

int* insertIntoSortedArray(int* arr,int sizeArr, int num);

int main(){

    int* arr;
    int i, numInputs, arrSize, number;

    arr = (int*)malloc(SIZE);
    numInputs = 0;
    arrSize = SIZE;

    printf("\nEnter number to be inserted: ");

    while(scanf("%d", &number) != EOF){

        insertIntoSortedArray(arr, numInputs, number);
        numInputs++;

        if(numInputs == arrSize){
            arr = (int*)realloc(arr, arrSize * 2 * sizeof(int));
            arrSize = arrSize * 2;
        }

        for(i = 0; i < numInputs; i++){
            printf("%d ", arr[i]);
        }

        printf("\nEnter number to be inserted: ");

    }
    free(arr);

    return 0;
}

int* insertIntoSortedArray(int* arr, int arrSizeBeforeInsertion, int num){

    if( arrSizeBeforeInsertion == 0 ){
        arr[arrSizeBeforeInsertion] = num;
        return arr;
    }

    int i = arrSizeBeforeInsertion - 1;

    //shift everything larger to the right
    while(num < arr[i] && i >= 0){
        arr[i + 1] = arr[i];
        i--;
    }

    arr[i + 1] = num;

    return arr;
}
