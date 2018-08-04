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

bool check_num(int num);

int ip_array_size;
int print_array_size;

//function declaration
bool check_num(int num);

int print_array(int input_array[]);

int
general_number_mult(int number_size, int result_size, int input_number_1[], int input_number_2[], int output_array[]);

int large_number_mult_split2(int number_size, int result_size, int input_number_1[], int input_number_2[],
                             int output_number[]);

int large_number_mult_split3(int number_size, int result_size, int input_number_1[], int input_number_2[],
                             int output_number[]);

int ten_power_mult(int pow, int output_array_size, int output_array[]);

int large_number_add(int num_size, int input_num_1[], int input_num_2[], int output_num[]);
