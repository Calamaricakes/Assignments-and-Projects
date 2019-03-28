autocomplete1: autocomplete1.o asst1_functions.o
	gcc -Wall autocomplete1.c -o autocomplete1

autocomplete1.o: autocomplete1.c
	gcc -c -Wall autocomplete1.c

asst1_functions.o: asst1_functions.h
	gcc -c -Wall asst1_functions.h
