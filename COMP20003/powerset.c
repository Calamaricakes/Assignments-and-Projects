#include <stdio.h>
#include <stdlib.h>

int main(int argc, char*argv[]){	
	int number, num_rows, num_columns ,row_count = 0, column_count = 0, i;

	printf("Please enter rows and columns: ");
	scanf("%d %d", &num_rows, &num_columns);
	
	int *pty[num_rows];
	
	while(scanf("%d", &number) == 1){
		
		if(pty == NULL){
			pty[row_count] = (int*)malloc(5*sizeof(int));
		}
		
		if(number){
			if(column_count < num_columns){
				pty[row_count][column_count] = number;
			}
			else{
				printf("Please enter 0 as you have run out of memory.");	
			}
		}
		else{
			row_count++;
			pty[row_count] = (int*)malloc(5*sizeof(int));
		}
	}
	for(i = 0; i < num_rows; i++){
		free(pty[i]);
	}	
	
}