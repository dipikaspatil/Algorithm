//Including standard library
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <time.h>

//macro declaration
#define ZERO 0
#define ARRAY_SIZE(x) sizeof(x)/sizeof(x[0])

/********************************* Function Declaration **********************************/
//heap sort
int heap_sort(int input_array[], int input_array_size);

int build_max_heap(int input_array[], int input_array_size);

int max_heapify(int input_array[], int root_index, int input_array_size);

//radix sort
int radix_sort(int input_array[], int input_array_size);

int radix_sort_count(int input_array[], int input_array_size, int digit_position);

int find_max_num(int input_array[], int input_array_size);

//additional function
int swap(int input_array[], int array_index1, int array_index2);

int sorting(int input_array_m[], int size_m, int sorting_method);

//visual represntation function
int display_star(int input_array[], int size_input_array);

/********************************* Global Variable Declaration **************************/
int display = 0; //false
