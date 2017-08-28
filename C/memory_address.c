#include <stdio.h>

int main(int argc, char *argv[]){
	int a = 10;
	int *ptr;

	ptr = &a;
	printf("value of a = %d\n", a);
	printf("address of a = %p", ptr);
	return 0;
}