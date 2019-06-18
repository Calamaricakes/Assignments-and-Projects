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

typedef double point_t[MAX_NUM_DIMENSIONS];

/* function prototypes */
void stage_one(point_t one_point, int *num_points, int num_dimensions);
void stage_two(point_t points[], int *num_points, int num_dimensions, 
	double *coordinate_sums);
void stage_three(double *coordinate_sums, int num_points);
void stage_four(point_t points[], int num_points, int num_dimensions);

void print_stage_heading(int stage);
void print_cum_sum(int point_num, double sum);
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

	/* stage 1 */
	stage_one(points[0], &num_points, num_dimensions);
	stage_two(points, &num_points, num_dimensions, coordinate_sums);
	stage_three(coordinate_sums, num_points);
	stage_four(points, num_points, num_dimensions);
	return 0;
}

void stage_one(point_t one_point, int *num_points, int num_dimensions) {
	
	int j;

	read_one_point(one_point, num_dimensions);
	*num_points += 1;
	/* print stage heading for stage 1 */
	print_stage_heading(STAGE_NUM_ONE);

	printf("Point 0%d: <", *num_points);
		
	for(j = 0; j < num_dimensions; j++){
		printf("%.2lf", one_point[j]);
		
		if (j != num_dimensions - 1){
			printf(", ");
		}
	}
	printf(">\n");
}

void stage_two(point_t points[], int *num_points, int num_dimensions, 
	double *coordinate_sums) {
	/* print stage heading for stage 2 */
	print_stage_heading(STAGE_NUM_TWO);
	
	int i = 0, j = 0;

	while (read_one_point(points[*num_points], num_dimensions)){
		*num_points += 1;
	}
	
	for(i = 0; i < *num_points; i++){
		for(j = 0; j < num_dimensions; j++){
			coordinate_sums[i] += points[i][j];	
		}
		print_cum_sum(i, coordinate_sums[i]);
	}
}

void stage_three(double *coordinate_sums, int num_points) {
	/* print stage heading for stage 3 */
	int i, point_max_sum;
	double max_sum = 0;
	
	print_stage_heading(STAGE_NUM_THREE);
	
	printf("Total: %d points\n", num_points);
	
	for(i = 0; i < num_points; i++){
		if (coordinate_sums[i] > max_sum){
			max_sum = coordinate_sums[i];
			point_max_sum = i;
		}
	}
	if(point_max_sum < 9){
		printf("Point of the largest sum of coordinates: 0%d\n"
			, point_max_sum + 1);
	}
	else{
		printf("Point of the largest sum of coordinates: %.2d\n"
			, point_max_sum + 1);
	}
	
	printf("Largest sum of coordinates: %.2lf\n", max_sum);

}

void stage_four(point_t points[], int num_points, int num_dimensions) {
	int i, j, k;
	int count = 0;
	
	/* print stage heading for stage 4 */
	print_stage_heading(STAGE_NUM_FOUR);
	
	for(i = 0; i < num_points; i+=){
		for(j = i + 1; j < num_points; j++){
			for(k = 0; k < num_dimensions; k++){
				if(points[i][k] > points[j][k]){
					count++;
				}
				if(count == num_dimensions){
					
				}
			}
		}
	}
	/* add your code here for stage 4 */
}
void print_stage_heading(int stage) {
	/* main job is to print the stage number passed as an argument */
	if (stage > STAGE_NUM_ONE) {
		/* separate the stages */
		printf("\n");
	}
	printf("Stage %d\n%s\n", stage, DIV);
}

int read_one_point(point_t one_point, int num_dimensions) {
	int i = 0;
	
	/* keep reading until num_dimensions numbers have been obtained */
	while (i < num_dimensions) {
		if (scanf("%lf", one_point+i) != 1) {
			return READ_FAILED;
		}
		i++;
	}
	
	return READ_OK;
}

void print_cum_sum(int point_num, double sum){
	double i, j, k, count = 0;

	if(point_num < 9){
		printf("Point 0%d, sum of coordinates (/100): %5.2lf |",
			point_num+1, sum/100);
	}
	
	else{
		printf("Point %d, sum of coordinates (/100): %5.2lf |",
			point_num+1, sum/100);
	}
	
	i =  fmod(sum, 100);
	j = sum / 100;

	if(i){
		count = j + 1;
	}
	else{
		count = j;
	}
	
	for(k = 1; k < count; k++){
		if (fmod(k, 10) == 0){
			printf("+");
		}
		else{
			printf("-");
		}
	}
	printf("\n");
}
