//standard library inclusion
#include<stdio.h>
#include<ctype.h>
#include <time.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <memory.h>
#include <stdbool.h>

#define MAX_VALUE 9999

#define MAX_NUM_LIMIT 8
#define MIN_NUM_LIMIT 4
#define MAX_WT_LIMIT 20
#define MIN_WT_LIMIT 5
#define MAX_PROFIT_LIMIT 30
#define MIN_PROFIT_LIMIT 10


//global variable declaration
int num_of_elements = 0;
int capacity_of_knapsack = 0;
int value = 0;
int value1 = 0;
int profit = 0;

typedef struct brute_force_str {
    int element;
    int weight;
    int profit;
} bf_elements_str;

typedef struct backtracking_str {
    int element;
    int weight;
    int profit;
    double profit_div_weight;
} backtacking_elements_str;

int maxprofit = 0;
int best_set[8];

int brute_force_algorithm(bf_elements_str bf_elements[num_of_elements]);

int dynamic_algorithm(int knapsack_matrix[num_of_elements + 1][capacity_of_knapsack + 1],
                      bf_elements_str bf_elements[num_of_elements],
                      int row_element, int column_element);

int knapsack_backtrack_algorithm(backtacking_elements_str bk_element_str[], int current_element, int current_weight,
                                 int current_profit, int include[]);

bool promising(int current_element, int current_weight, int current_profit,
               backtacking_elements_str input_bk_element_str[]);

int KWF2(int current_element, int current_weight, int current_profit, backtacking_elements_str input_bk_element_str[]);


