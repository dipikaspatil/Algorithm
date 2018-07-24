//Including standard library
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

//macro declaration
#define ZERO 0

//Global variable declaration
int ip_matrix_size;
int print_matrix_size;
//int matrix_size;
int result_matrix_size;

//Function declaration
int print_matrix(int **input_matrix);

//general matrix multiplication
int general_matrix_mult(int **input_matrix_1, int **input_matrix_2,
                        int **result_matrix);

//function to perform various matrix calculation like addition , subtraction
int matrix_function(int matrix_size, char function[], int **input_matrix_1,
                    int **input_matrix_2,
                    int **output_matrix);

//strassen matrix multiplication
int strassen_matrix_mult(int size, int **input_matrix_1,
                         int **input_matrix_2,
                         int **result_matrix);

//compose matrix divided as a part of Strassen algorithm
int compose_matrix(int size, int **input_matrix_1, int **input_matrix_2,
                   int **input_matrix_3, int **input_matrix_4,
                   int **result_matrix_stressen);

bool check_num(int num);