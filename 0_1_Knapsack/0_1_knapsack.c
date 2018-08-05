#include "0_1_knapsack.h"

/*
 This function  will take input from user and will generate random number.
*/

int main() {
    printf("\n\n************Start of 0/1 Knapsack problem using Brute Force Algorithm**********\n\n");

    //variable declaration
    int wt_of_elements = 0;
    int profit_of_elements = 0;

    //loop counter declaration
    int i, j, k;

    //srand function used to get proper random numbers
    srand((unsigned) time(NULL));
    //random generation of num between 4 to 8
    while (num_of_elements < MIN_NUM_LIMIT || num_of_elements > MAX_NUM_LIMIT) {
        num_of_elements = (rand() % MAX_NUM_LIMIT) + MIN_NUM_LIMIT;
    }

    printf("\nNumber of elements are --> %d\n\n", num_of_elements);

    bf_elements_str bf_elements[num_of_elements];

    for (i = 0; i < num_of_elements; i++) {
        bf_elements[i].element = i;
        printf("Element --> %-2d\t\t", i);
        //generate wt of elements
        while (wt_of_elements < MIN_WT_LIMIT || wt_of_elements > MAX_WT_LIMIT) {
            wt_of_elements = (rand() % MAX_WT_LIMIT) + MIN_WT_LIMIT;
        }

        bf_elements[i].weight = wt_of_elements;
        printf("Weight --> %-2d\t\t", bf_elements[i].weight);
        capacity_of_knapsack = capacity_of_knapsack + bf_elements[i].weight;
        wt_of_elements = 0;

        while (profit_of_elements < MIN_PROFIT_LIMIT || profit_of_elements > MAX_PROFIT_LIMIT) {
            profit_of_elements = (rand() % MAX_PROFIT_LIMIT) + MIN_PROFIT_LIMIT;
        }

        bf_elements[i].profit = profit_of_elements;
        printf("Profit = %-2d\t\t", bf_elements[i].profit);
        profit_of_elements = 0;
        printf("\n");
    }
    capacity_of_knapsack = floor((capacity_of_knapsack * 6) / 10);

    printf("\nCapacity of Knapsack --> %d\n", capacity_of_knapsack);

    brute_force_algorithm(bf_elements);

    printf("\n\n************End of 0/1 Knapsack problem using Brute Force Algorithm**********\n\n");

    printf("\n\n************Start of 0/1 Knapsack problem using Dynamic Refinement Algorithm **********\n\n");


    //dynamic programming
    int knapsack_matrix[num_of_elements + 1][capacity_of_knapsack + 1];

    //initialize matrix
    printf("\n\nKnapsack_matrix is:\n\n");
    for (i = 0; i < (num_of_elements + 1); i++) {
        for (j = 0; j < (capacity_of_knapsack + 1); j++) {
            knapsack_matrix[i][j] = -1;
            knapsack_matrix[i][0] = 0;
            knapsack_matrix[0][j] = 0;
        }
    }


    dynamic_algorithm(knapsack_matrix, bf_elements, num_of_elements, capacity_of_knapsack);

    printf("\n\nModified Knapsack_matrix is:\n\n");
    for (i = 0; i < (num_of_elements + 1); i++) {
        for (j = 0; j < (capacity_of_knapsack + 1); j++) {
            if (knapsack_matrix[i][j] == -1) {
                printf("%-2d ", 0);
            } else {
                printf("%-2d ", knapsack_matrix[i][j]);
            }
        }
        printf("\n");
    }

    printf("\n\nFinal Profit = %d\n\n", knapsack_matrix[num_of_elements][capacity_of_knapsack]);

    int column = capacity_of_knapsack, row = num_of_elements;
    int include_element[num_of_elements];

    for (k = 0; k < num_of_elements; k++) {
        include_element[k] = 9999;
    }

    while (row > 0 && column > 0) {
        if (knapsack_matrix[row][column] != knapsack_matrix[row - 1][column]) {
            include_element[row - 1] = 1;
            column = column - bf_elements[row - 1].weight;
            row = row - 1;
        } else {
            row = row - 1;
        }
    }

    column = 0;
    printf("\nSelected Items:\n\n");
    for (k = 0; k < num_of_elements; k++) {
        if (include_element[k] == 1) {
            printf("Element --> %-2d\t\t Weight --> %-2d\t\t Profit --> %-2d\t\t\n", bf_elements[k].element,
                   bf_elements[k].weight, bf_elements[k].profit);
            column = column + bf_elements[k].weight;
        }
    }

    printf("\n\nFinal Weight = %d\n\n", column);

    printf("\n\n************End of 0/1 Knapsack problem using Dynamic Refinement Algorithm **********\n\n");

    printf("\n\n************Start of 0/1 Knapsack problem using Backtrack Algorithm **********\n\n");
    backtacking_elements_str bk_element_str[num_of_elements], tmp_bk_element_str[num_of_elements];

    for (k = 0; k < num_of_elements; k++) {
        bk_element_str[k].profit = bf_elements[k].profit;
        bk_element_str[k].weight = bf_elements[k].weight;
        bk_element_str[k].element = bf_elements[k].element;
        bk_element_str[k].profit_div_weight = (double) bf_elements[k].profit / bf_elements[k].weight;
    }

    //sort elements in non ascending order
    for (j = 0; j < num_of_elements; j++) {
        for (k = j + 1; k <= num_of_elements; k++)
            if (bk_element_str[k].profit_div_weight > bk_element_str[j].profit_div_weight) {
                tmp_bk_element_str[j] = bk_element_str[k];
                bk_element_str[k] = bk_element_str[j];
                bk_element_str[j] = tmp_bk_element_str[j];
            }
    }

    //printing elements
    printf("\nSorting of elements considering Profit/Weight :\n");

    printf("\nElement  \t\t Weight \t\t Profit \t\t Profit/Weight\n");
    for (j = 0; j < num_of_elements; j++) {
        printf("%-2d \t\t\t\t %-2d \t\t\t %-2d \t\t\t %-2f\n", bk_element_str[j].element, bk_element_str[j].weight,
               bk_element_str[j].profit,
               bk_element_str[j].profit_div_weight);
    }

    printf("\nTraversing of elements using DFS :\n");
    printf("------------------------------------------------------------------------------------\n");


    int include[8];

    //initialize best set elements to -1
    for (int i = 0; i < 8; i++) {
        best_set[i] = 9999;
        include[i] = 9999;
    }

    int current_element = -1;
    int current_weight = 0;
    int current_profit = 0;


    //for (i = 0; i < num_of_elements; i++) {
    knapsack_backtrack_algorithm(bk_element_str, current_element, current_weight, current_profit, include);
    //}
    printf("\n------------------------------------------------------------------------------------\n");
    printf("\n\nFinal Profit = %d\n\n", maxprofit);


    int weight = 0;

    printf("\nSelected Items:\n\n");
    for (k = 0; k < num_of_elements; k++) {
        if (best_set[k] == 1) {
            printf("Element --> %-2d\t\t Weight --> %-2d\t\t Profit --> %-2d\t\t\n", bk_element_str[k].element,
                   bk_element_str[k].weight, bk_element_str[k].profit);
            weight = weight + bk_element_str[k].weight;
        }
    }

    printf("\n\nFinal Weight = %d\n\n", weight);

    printf("\n\n************End of 0/1 Knapsack problem using Backtrack Algorithm **********\n\n");


    printf("\n\n********************************End of Program********************************\n\n");
    return 0;
}


int brute_force_algorithm(bf_elements_str bf_elements[num_of_elements]) {
    int i, j, k;
    //generate 2^n combination
    int total_combination = pow(2, num_of_elements);
    int counter = 0;
    int element_count = 0;
    int profit = 0;
    int weight = 0;
    int new_weight = 0;
    int new_profit = 0;
    int elements[num_of_elements];
    int new_elements[num_of_elements];
    //char elements[2*num_of_elements];
    //printf("\n\nElement \t\t Total Profit\t\t Total Weight \n\n");

    for (i = 0; i < num_of_elements; i++) {
        new_elements[i] = 9999;
        elements[i] = 9999;
    }
    for (i = 1; i < total_combination; i++) {
        for (j = 0; j < num_of_elements; j++) {
            if ((1 << j) & i) {
                profit = profit + bf_elements[j].profit;
                weight = weight + bf_elements[j].weight;
                elements[j] = bf_elements[j].element;
            }

        }

        if ((new_profit < profit) && (weight <= capacity_of_knapsack)) {
            //memset(new_elements, 9999, num_of_elements);
            for (k = 0; k < num_of_elements; k++) {
                new_elements[k] = 9999;
            }
            new_profit = profit;
            new_weight = weight;
            for (k = 0; k < num_of_elements; k++) {
                new_elements[k] = elements[k];
            }
        }
        weight = 0;
        profit = 0;
        for (k = 0; k < num_of_elements; k++) {
            elements[k] = 9999;
        }
    }

    printf("\n\nFinal Profit: %d\n\n", new_profit);

    printf("\nSelected Items:\n\n");
    for (k = 0; k < num_of_elements; k++) {
        if (new_elements[k] != 9999) {
            printf("Element --> %-2d\t\t Weight --> %-2d\t\t Profit --> %-2d\t\t\n",
                   bf_elements[new_elements[k]].element,
                   bf_elements[new_elements[k]].weight, bf_elements[new_elements[k]].profit);
        }
    }

    printf("\nFinal Weight: %d\n", new_weight);


    return 0;
}

int dynamic_algorithm(int knapsack_matrix[num_of_elements + 1][capacity_of_knapsack + 1],
                      bf_elements_str bf_elements[num_of_elements],
                      int row_element, int column_element) {

    int r = row_element, c = column_element;
    int matrix_row = num_of_elements;
    int matrix_column = capacity_of_knapsack;
    int wk, w;

    wk = bf_elements[r - 1].weight;
    w = c;
    if (c >= 0) {
        if ((r == 1) || (knapsack_matrix[r][c] != -1)) {
            if ((wk <= w) &&
                ((knapsack_matrix[r - 1][c - wk] + bf_elements[r - 1].profit) > knapsack_matrix[r - 1][c])) {

                knapsack_matrix[r][c] = knapsack_matrix[r - 1][c - wk] + bf_elements[r - 1].profit;
            } else {
                knapsack_matrix[r][c] = knapsack_matrix[r - 1][c];
            }
            return knapsack_matrix[r][c];
        } else {
            if ((wk <= w) &&
                ((dynamic_algorithm(knapsack_matrix, bf_elements, r - 1, w - wk) + bf_elements[r - 1].profit) >
                 (dynamic_algorithm(knapsack_matrix, bf_elements, r - 1, c)))) {

                knapsack_matrix[r][c] =
                        dynamic_algorithm(knapsack_matrix, bf_elements, r - 1, w - wk) + bf_elements[r - 1].profit;

                value = knapsack_matrix[r][c];
                profit = bf_elements[r - 1].profit;

            } else {
                knapsack_matrix[r][c] = dynamic_algorithm(knapsack_matrix, bf_elements, r - 1, c);
            }

            return knapsack_matrix[r][c];
        }
    }
    return 0;
}


int knapsack_backtrack_algorithm(backtacking_elements_str bk_element_str[], int current_element, int current_weight,
                                 int current_profit, int include[]) {

    if (current_weight <= capacity_of_knapsack && current_profit > maxprofit) {
        //save better solution
        maxprofit = current_profit;

        for (int i = 0; i < num_of_elements; i++) {
            best_set[i] = include[i];
        }
    }

    if (promising(current_element, current_weight, current_profit, bk_element_str)) {

        include[current_element + 1] = 1; //included

        knapsack_backtrack_algorithm(bk_element_str, current_element + 1,
                                     current_weight + bk_element_str[current_element + 1].weight,
                                     current_profit + bk_element_str[current_element + 1].profit, include);

        include[current_element + 1] = 0; //not included
        knapsack_backtrack_algorithm(bk_element_str, current_element + 1, current_weight, current_profit, include);
    }
    return 0;
}

bool promising(int current_element, int current_weight, int current_profit,
               backtacking_elements_str input_bk_element_str[]) {

    //Cannot get a solution by expanding node
    if (current_weight >= capacity_of_knapsack) {
        printf("\nCurrent Profit --> %d \t\t Current weight --> %d \t\t Bound --> NOT PROMISING NODE", current_profit,
               current_weight);
        return false;
    }

    //compute upper bound
    int bound = KWF2(current_element + 1, current_weight, current_profit, input_bk_element_str);

    printf("\nCurrent Profit --> %d \t\t Current weight --> %d \t\t Bound --> %d", current_profit, current_weight,
           bound);


    if (bound > maxprofit) {
        return true;
    } else {
        return false;
    }
};

int KWF2(int current_element, int current_weight, int current_profit, backtacking_elements_str input_bk_element_str[]) {
    int bound = current_profit;

    int x[num_of_elements];
    int counter = current_element;

    for (int j = current_element; j < num_of_elements; j++) {
        x[j] = 0; //initialize variables to 0
    }
    while (current_weight < capacity_of_knapsack &&
           current_element < num_of_elements) { //not full and more items

        if ((current_weight + input_bk_element_str[current_element].weight) <= capacity_of_knapsack) {
            x[current_element] = 1;
            current_weight = current_weight + input_bk_element_str[current_element].weight;
            bound = bound + input_bk_element_str[current_element].profit;

        } else {
            x[current_element] = (capacity_of_knapsack - current_weight) / input_bk_element_str[current_element].weight;
            bound = bound + ((capacity_of_knapsack - current_weight) * (input_bk_element_str[current_element].profit /
                                                                        input_bk_element_str[current_element].weight));

            current_weight = capacity_of_knapsack;
        }
        current_element = current_element + 1;

    }

    return bound;

}
















