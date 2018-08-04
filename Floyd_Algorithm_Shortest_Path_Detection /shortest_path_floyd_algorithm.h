//standard library inclusion
#include<stdio.h>
#include<ctype.h>
#include <time.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>

//global variable declaration
int num_of_vertices = 0;

//function declaration
int floyd_algorithm(int **w_matrix, int **p_matrix);

int print_path(int index_q, int index_r, int **p_matrix);