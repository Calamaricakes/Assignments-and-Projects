/* File Name: assmt1.c
   Author: Lai Nge Nern 639702
   Date: 26/4/17
   Function: Assignment 1: Cold start Skyline Operator with statistics
   Comment: Algorithms are fun!!!!!!
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DIV "==========" /* stage header */
/* stage numbers */
#define STAGE_NUM_ONE 1 
#define STAGE_NUM_TWO 2
#define STAGE_NUM_THREE 3
#define STAGE_NUM_FOUR 4
#define STAGE_NUM_FIVE 5

#define READ_OK 1 /* reading point succeeded */
#define READ_FAILED 0 /* reading point failed */

#define MAX_NUM_POINTS 99 /* maximum number of points */
#define MAX_NUM_DIMENSIONS 10 /* maximum number of dimensions */

#define true 1
#define false 0

typedef double point_t[MAX_NUM_DIMENSIONS];

/* function prototypes */
void stage_one(point_t one_point, int *num_points, int num_dimensions);
void stage_two(point_t points[], int *num_points, int num_dimensions, 
	double *coordinate_sums);
void stage_three(double *coordinate_sums, int num_points);
void stage_four(point_t points[], int num_points, int num_dimensions);
void stage_five(point_t points[], int num_points, int num_dimensions);
void print_stage_heading(int stage);
void print_point(point_t one_point, int point_number, int num_dimension);
void print_cum_sum(int point_num, double sum);
void print_skyline_points(int arr_skyline_points[], int num_skyline_points, 
						  point_t points[], int num_dimensions);
int read_one_point(point_t one_point, int num_dimensions);


/* main program binds it all together */
int main(int argc, char *argv[]){
	/* storage for the input data */
	int num_dimensions;
	point_t points[MAX_NUM_POINTS];
	
	/* storage for statistics */
	int num_points = 0; /* number of points read in */
	double coordinate_sums[MAX_NUM_POINTS]; /* coordinate sums of the points */
	
	/* read the first line - number of dimensions */
	scanf("%d", &num_dimensions);
	
	/* stages */
	stage_one(points[0], &num_points, num_dimensions);
	stage_two(points, &num_points, num_dimensions, coordinate_sums);
	stage_three(coordinate_sums, num_points);
	stage_four(points, num_points, num_dimensions);
	stage_five(points, num_points, num_dimensions);

	return 0;
}

void stage_one(point_t one_point, int *num_points, int num_dimensions) {
	
	int num_points_holder;

	/* read single point */
	read_one_point(one_point, num_dimensions);
	*num_points += 1;
	
	/* print stage heading for stage 1 */
	print_stage_heading(STAGE_NUM_ONE);
	
	num_points_holder = *num_points;
	print_point(one_point, num_points_holder, num_dimensions);
}

void stage_two(point_t points[], int *num_points, int num_dimensions, 
	double *coordinate_sums) {
	
/* print stage heading for stage 2 */
	print_stage_heading(STAGE_NUM_TWO);
	
	int i = 0, j = 0;
	int value_holder;

	/* read all points */
	while (read_one_point(points[*num_points], num_dimensions)){
		*num_points += 1;
	}
	
	/* control privilage *Triggered* */
	value_holder = *num_points;
	
	/* calculate sums for each point */
	for(i = 0; i < value_holder; i++){
		for(j = 0; j < num_dimensions; j++){
			coordinate_sums[i] += points[i][j];	
		}
		/* print coordinate sums */
		print_cum_sum(i, coordinate_sums[i]);
	}
}

void stage_three(double *coordinate_sums, int num_points) {
	
	int i, point_max_sum;
	double max_sum = 0;
	
	/* print stage heading for stage 3 */
	print_stage_heading(STAGE_NUM_THREE);
	
	/* print total points */
	printf("Total: %d points\n", num_points);
	
	/* find maximum coordinate */
	for(i = 0; i < num_points; i++){
		if (coordinate_sums[i] > max_sum){
			max_sum = coordinate_sums[i];
			point_max_sum = i;
		}
	}
	
	/* print point where max_sum is found */
	if(point_max_sum < 9){
		printf("Point of the largest sum of coordinates: 0%d\n"
			, point_max_sum + 1);
	}
	else{
		printf("Point of the largest sum of coordinates: %.2d\n"
			, point_max_sum + 1);
	}
	
	/* print max sum */
	printf("Largest sum of coordinates: %.2lf\n", max_sum);

}

void stage_four(point_t points[], int num_points, int num_dimensions) {
	
	int i, j, k, num_skyline_points;
	int p = 0, count = 0;
	int arr_skyline_points[MAX_NUM_POINTS];
	int superior_point = false;
	
	/* compare each point with other points to determine if skyline point */
	for(i = 0; i < num_points; i++){
		for(j = 0; j < num_points; j++){
			/* if comparing same point */
		    if (i == j){
		        continue;
		    }
		    /* compare each coordinate between points */
			for(k = 0; k < num_dimensions; k++){
				/* use lazy evaluation */
				if( points[i][k] > points[j][k] ){
					superior_point = false;
					count = 0;
					break;
				}
				count++;
			}
			/* if there is a better point */
			if(count == num_dimensions){
				superior_point = true;
				break;
			}
		}
		/* if there exists no better points, add to skyline */
		if( superior_point == false ){
			arr_skyline_points[p] = i;
			p++;
		}
	}
	num_skyline_points = p;
	
	/* print stage heading for stage 4 */
	print_stage_heading(STAGE_NUM_FOUR); 
	
	/* print skyline points */
	print_skyline_points(arr_skyline_points, num_skyline_points, points,
		num_dimensions);
}

void stage_five(point_t points[], int num_points, int num_dimensions) {
	/* print stage heading for stage 5 */
	print_stage_heading(STAGE_NUM_FIVE);
	
	int i, j, k, n, num_skyline_point;
	int y = 0, p = 0, count = 0, dominated = 0;
	int arr_skyline_points[MAX_NUM_POINTS];
	int arr_skyline_dominated[MAX_NUM_POINTS];
	int superior_point = false;

	/* look for skyline points */
	for(i = 0; i < num_points; i++){
		for(j = 0; j < num_points; j++){
			/* if comparing same point */
		    if (i == j){
		        continue;
		    }
		    /* compare each coordinate between points */
			for(k = 0; k < num_dimensions; k++){
				/* use lazy evaluation */
				if( points[i][k] > points[j][k] ){
					superior_point = false;
					count = 0;
					break;
				}
				count++;
			}
			/* if there is a better point */
			if(count == num_dimensions){
				superior_point = true;
				break;
			}
		}
		/* if there exists no better points, add to skyline */
		if( superior_point == false ){
			arr_skyline_points[p] = i;
			p++;
		}
	}
	num_skyline_point = p;
	
	/* look for dominated points */
	for(i = 0; i < num_points; i++){
		for(j = 0; j < num_points; j++){
			if( i == j ){
				continue;
			}
			/* compares each coordinate */
			for( k = 0; k < num_dimensions; k++){
				if( points[i][k] >= points[j][k]){
					count++;
				}
			}
			/* dominates one point */
			if(count == num_dimensions){
				dominated++;
			}
			/* if comparator point dominates, break*/
			if( count == 0 ){
				superior_point = true;
				dominated = 0;
				break;
			}
			count = 0;
		}
		/* add number of dominated points to array */
		if(superior_point == false){
			arr_skyline_dominated[y] = dominated;
			y++;
			dominated = 0;
		}
		else{
		    superior_point = false;
		}
	}
	/* prints out results */
	for(n = 0; n < num_skyline_point; n++){
	    print_point(points[arr_skyline_points[n]], arr_skyline_points[n] + 1,
	    num_dimensions);   
	    printf("Number of points dominated: %d\n", arr_skyline_dominated[n]);
	}
}


void print_stage_heading(int stage) {
	/* main job is to print the stage number passed as an argument */
	if ( stage > STAGE_NUM_ONE ) {
		/* separate the stages */
		printf("\n");
	}
	printf("Stage %d\n%s\n", stage, DIV);
}

int read_one_point(point_t one_point, int num_dimensions) {
	int i = 0;
	
	/* keep reading until num_dimensions numbers have been obtained */
	while ( i < num_dimensions ) {
		if (scanf("%lf", one_point+i) != 1) {
			return READ_FAILED;
		}
		i++;
	}
	
	return READ_OK;
}

void print_point(point_t one_point, int point_number, int num_dimension){
	int i;
	
	/* print point number */
	if( point_number < 10 ){
		printf("Point 0%d: <", point_number);
	}
	else{
		printf("Point %d: <", point_number);
	}
	
	/* print point coordinates */
	for(i = 0; i < num_dimension; i++){
		printf("%.2lf", one_point[i]);
		
		if( i != num_dimension - 1 ){
			printf(", ");
		}
	}
	printf(">\n");
}

void print_cum_sum(int point_num, double sum){
	double i, j, k, count = 0;
	
	/* print point number */
	if( point_num < 9 ){
		printf("Point 0%d, sum of coordinates (/100): %5.2lf |",
			point_num+1, sum/100);
	}
	
	else{
		printf("Point %d, sum of coordinates (/100): %5.2lf |",
			point_num+1, sum/100);
	}
	
	/* find number of points to print */
	i =  fmod(sum, 100);
	j = sum / 100;

	if( i ){
		count = j + 1;
	}
	else{
		count = j;
	}
	
	/* print points, "+" if divisible by 10, else "-" */
	for(k = 1; k < count; k++){
		if ( fmod(k, 10) == 0 ){
			printf("+");
		}
		else{
			printf("-");
		}
	}
	printf("\n");
}

void print_skyline_points(int arr_skyline_points[], int num_skyline_points, 
						  point_t points[], int num_dimensions){

	int i;
	
	/* sends each point to print_point to be printed */
	for(i = 0; i < num_skyline_points; i++){
		print_point(points[arr_skyline_points[i]] , arr_skyline_points[i] + 1,
			num_dimensions); 
	}
	
}