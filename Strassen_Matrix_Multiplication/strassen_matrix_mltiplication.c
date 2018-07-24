/********************************* Main Function Start **********************************/

#include "strassen_matrix_mltiplication.h"

/*
 This function  will take input from user and will generate random number.
 As per user's input main will call sorting function
*/
int main() {
    printf("\n\n");
    //variable declaration
    int counter = ZERO;
    int min_display_num = 1;
    int count_number;
    //declaration of loop variables
    int i, j;

    //Input From User - includes sorting method and number of count of input numbers to be sorted
    START:
    printf("\n------------------------------------- START OF PROGRAM : MATRIX MULTIPLICATION--------------------------------------------\n");
    bool valid_num;
    char answer;

    GET_COUNT:
    //take the count of numbers to be sorted from user. If input is between 1 to 1000 then continue ....else ask again to enter correct number
    printf("\nPlease enter count of numbers to be sorted between 1 to 1024....number needs to be in 2^k (2 power k) form\n:- ");
    scanf("%d", &count_number);

    if (count_number < 1 || count_number > 1024) {
        printf("\n***** Input count of numbers is not in range. Please enter number between 1 and 1024. *****\n"
                       "\nDo you want to continue? (y/n)\n:- ");
        scanf(" %c", &answer);
        //if user enter yes....comtinue program ...else exit
        if (toupper(answer) == 'Y') {
            counter = counter + 1;
            // if user gives wrong input 3 times....exit the program with respective message
            if (counter == 3) {
                printf("\n\nUser has exceeded number of chances....so exiting the program\n");
                return ZERO;
            }
            //continue program by going back  to take correct count from user
            goto GET_COUNT;
        } else {
            //if user select no to continue the program....exit the program
            printf("\nExiting program....\n");
            printf("\n----------------------------------------------------------------------------\n\n");
            return ZERO;
        }
    } else {
        valid_num = check_num(count_number);
        if (!valid_num) {
            printf("\n***** Number needs to be in 2^k (2 power k) form....Please enter valid number between 1..1024\n"
                           "\nDo you want to continue? (y/n)\n:- ");
            scanf(" %c", &answer);
            //if user enter yes....continue program ...else exit
            if (toupper(answer) == 'Y') {
                counter = counter + 1;
                // if user gives wrong input 3 times....exit the program with respective message
                if (counter == 3) {
                    printf("\n\nUser has exceeded number of chances....so exiting the program\n");
                    return ZERO;
                }
                //continue program by going back  to take correct count from user
                goto GET_COUNT;
            } else {
                //if user select no to continue the program....exit the program
                printf("\nExiting program....\n");
                printf("\n----------------------------------------------------------------------------\n\n");
                return ZERO;
            }
        }
    }

    //Generating array of random numbers as per count given by user
    ip_matrix_size = count_number;
    int **input_matrix_1 = malloc(ip_matrix_size * sizeof(*input_matrix_1));//[ip_matrix_size][ip_matrix_size];
    int **input_matrix_2 = malloc(ip_matrix_size * sizeof(*input_matrix_2));//[ip_matrix_size][ip_matrix_size];
    int max_limit = (int) floor(sqrt((INT_MAX / ip_matrix_size)));

    for (i = 0; i < ip_matrix_size; i++) {
        input_matrix_1[i] = malloc(ip_matrix_size * sizeof(*input_matrix_1[i]));
        input_matrix_2[i] = malloc(ip_matrix_size * sizeof(*input_matrix_2[i]));
    }
    //need to clear random generator to null before generation of random number
    srand((unsigned) time(NULL));
    //generating random number using rand() function and including the same into input matrix 1 and 2 of integers
    for (i = 0; i < ip_matrix_size; i++) {
        for (j = 0; j < ip_matrix_size; j++) {
            input_matrix_1[i][j] = (rand() % max_limit) + min_display_num;
            input_matrix_2[i][j] = (rand() % max_limit) + min_display_num;
        }
    }

    printf("\n\n******************** Input Matrix 1 **********************\n\n");
    print_matrix_size = ip_matrix_size;
    print_matrix(input_matrix_1);

    printf("\n\n******************** Input Matrix 2 **********************\n\n");
    print_matrix_size = ip_matrix_size;
    print_matrix(input_matrix_2);

    int **result_matrix_general = malloc(
            ip_matrix_size * sizeof(*result_matrix_general));//[ip_matrix_size][ip_matrix_size];
    int **result_matrix_stressen = malloc(
            ip_matrix_size * sizeof(*result_matrix_stressen));//[ip_matrix_size][ip_matrix_size];

    for (i = 0; i < ip_matrix_size; i++) {
        result_matrix_general[i] = malloc(ip_matrix_size * sizeof(*result_matrix_general[i]));
        result_matrix_stressen[i] = malloc(ip_matrix_size * sizeof(*result_matrix_stressen[i]));
    }


    printf("\n\n******************** Result from Standard Algorithm **********************\n\n");
    general_matrix_mult(input_matrix_1, input_matrix_2, result_matrix_general);

    print_matrix_size = ip_matrix_size;
    print_matrix(result_matrix_general);

    printf("\n\n******************** Result from Strassen's Algorithm *******************\n\n");
    strassen_matrix_mult(ip_matrix_size, input_matrix_1, input_matrix_2, result_matrix_stressen);

    print_matrix_size = ip_matrix_size;
    print_matrix(result_matrix_stressen);

    for (i = 0; i < ip_matrix_size; i++) {
        free(input_matrix_1[i]);
        free(input_matrix_2[i]);
        free(result_matrix_general[i]);
        free(result_matrix_stressen[i]);
    }

    free(input_matrix_1);
    free(input_matrix_2);
    free(result_matrix_general);
    free(result_matrix_stressen);
    printf("\n\n");
    return 0;
}
/********************************* Main Function End *************************************/
/*
 This function checks if number is power of 2 or not
 */
bool check_num(int num) {
    int num_1;
    //if number is 1 or 2 , return true
    if (num == 1 || num == 2) {
        return true;
    } else {
        //bitwise operation
        num_1 = (num & ~(num - 1));
        if (num == num_1) {
            return true;
        } else {
            return false;
        }
    }
}

/*
 This function display matrix element
 */
int print_matrix(int **input_matrix) {
    int i, j;
    //traverse through first index i
    for (i = 0; i < print_matrix_size; i++) {
        //traverse through second index j
        for (j = 0; j < print_matrix_size; j++) {
            //print using both index i, j
            printf("%d\t\t", input_matrix[i][j]);
        }
        printf("\n");
    }
    return 0;
}

/*
 This function is a general algorithm to multiply two matrix with time complexity O(n^3)
 */
int general_matrix_mult(int **input_matrix_1,
                        int **input_matrix_2,
                        int **result_matrix_general) {
    //loop counter declaration
    int k, l, m;

    //traverse through first index i
    for (k = 0; k < ip_matrix_size; k++) {
        //traverse through second index j
        for (l = 0; l < ip_matrix_size; l++) {
            //traverse through output matrix
            result_matrix_general[k][l] = 0;
            for (m = 0; m < ip_matrix_size; m++) {
                result_matrix_general[k][l] = result_matrix_general[k][l] + input_matrix_1[k][m] * input_matrix_2[m][l];
            }
        }
    }
    return 0;
}

/*
 This function complete matrix multiplication using Strassen's Algorithm
 1) It split n X n matrix into n/2 X n/2 matrix
 2) It calculate seven basic value ranging from M1 to M7
 3) It calculates small sub matrix C11, C12, C21 and C22
 4) Finally it compose the C11, C12, C21 and C22 and creae result matrix
 It works in recursive manner
 */
int strassen_matrix_mult(int ip_matrix_size, int **input_matrix_1,
                         int **input_matrix_2,
                         int **result_matrix_stressen) {
    //If matrix size is 2 X 2 , calculate result using general matrix multiplication algorithm
    if (ip_matrix_size <= 2) {
        matrix_function(ip_matrix_size, "MUL", input_matrix_1, input_matrix_2, result_matrix_stressen);
    } else {
        //declaration of loop counter
        int i, j;
        //declaration and initialization of new matrix size
        int new_matrix_size = floor(ip_matrix_size / 2);
        //declaration of 4 output for each input matrix .... input matrix is divided ino 4 parts each
        int **output_matrix_1_11 = malloc(new_matrix_size * sizeof(*output_matrix_1_11));
        int **output_matrix_1_12 = malloc(new_matrix_size * sizeof(*output_matrix_1_12));
        int **output_matrix_1_21 = malloc(new_matrix_size * sizeof(*output_matrix_1_21));
        int **output_matrix_1_22 = malloc(new_matrix_size * sizeof(*output_matrix_1_22));

        int **output_matrix_2_11 = malloc(new_matrix_size * sizeof(*output_matrix_2_11));
        int **output_matrix_2_12 = malloc(new_matrix_size * sizeof(*output_matrix_2_12));
        int **output_matrix_2_21 = malloc(new_matrix_size * sizeof(*output_matrix_2_21));
        int **output_matrix_2_22 = malloc(new_matrix_size * sizeof(*output_matrix_2_22));

        //declaration of 7 sub matrix M1 to M7
        int **matrix_m1 = malloc(new_matrix_size * sizeof(*matrix_m1));
        int **matrix_m2 = malloc(new_matrix_size * sizeof(*matrix_m2));
        int **matrix_m3 = malloc(new_matrix_size * sizeof(*matrix_m3));
        int **matrix_m4 = malloc(new_matrix_size * sizeof(*matrix_m4));
        int **matrix_m5 = malloc(new_matrix_size * sizeof(*matrix_m5));
        int **matrix_m6 = malloc(new_matrix_size * sizeof(*matrix_m6));
        int **matrix_m7 = malloc(new_matrix_size * sizeof(*matrix_m7));

        int **matrix_function_op1 = malloc(new_matrix_size * sizeof(*matrix_function_op1));
        int **matrix_function_op2 = malloc(new_matrix_size * sizeof(*matrix_function_op2));

        //declaration of 4 matrix c11, c12, c21, c22
        int **matrix_c11 = malloc(new_matrix_size * sizeof(*matrix_c11));
        int **matrix_c12 = malloc(new_matrix_size * sizeof(*matrix_c12));
        int **matrix_c21 = malloc(new_matrix_size * sizeof(*matrix_c21));
        int **matrix_c22 = malloc(new_matrix_size * sizeof(*matrix_c22));

        for (i = 0; i < new_matrix_size; i++) {
            output_matrix_1_11[i] = malloc(new_matrix_size * sizeof(*output_matrix_1_11[i]));
            output_matrix_1_12[i] = malloc(new_matrix_size * sizeof(*output_matrix_1_12[i]));
            output_matrix_1_21[i] = malloc(new_matrix_size * sizeof(*output_matrix_1_21[i]));
            output_matrix_1_22[i] = malloc(new_matrix_size * sizeof(*output_matrix_1_22[i]));

            output_matrix_2_11[i] = malloc(new_matrix_size * sizeof(*output_matrix_2_11[i]));
            output_matrix_2_12[i] = malloc(new_matrix_size * sizeof(*output_matrix_2_12[i]));
            output_matrix_2_21[i] = malloc(new_matrix_size * sizeof(*output_matrix_2_21[i]));
            output_matrix_2_22[i] = malloc(new_matrix_size * sizeof(*output_matrix_2_22[i]));

            matrix_m1[i] = malloc(new_matrix_size * sizeof(*matrix_m1[i]));
            matrix_m2[i] = malloc(new_matrix_size * sizeof(*matrix_m2[i]));
            matrix_m3[i] = malloc(new_matrix_size * sizeof(*matrix_m3[i]));
            matrix_m4[i] = malloc(new_matrix_size * sizeof(*matrix_m4[i]));
            matrix_m5[i] = malloc(new_matrix_size * sizeof(*matrix_m5[i]));
            matrix_m6[i] = malloc(new_matrix_size * sizeof(*matrix_m6[i]));
            matrix_m7[i] = malloc(new_matrix_size * sizeof(*matrix_m7[i]));

            matrix_function_op1[i] = malloc(new_matrix_size * sizeof(*matrix_function_op1[i]));
            matrix_function_op2[i] = malloc(new_matrix_size * sizeof(*matrix_function_op2[i]));

            matrix_c11[i] = malloc(new_matrix_size * sizeof(*matrix_c11[i]));
            matrix_c12[i] = malloc(new_matrix_size * sizeof(*matrix_c12[i]));
            matrix_c21[i] = malloc(new_matrix_size * sizeof(*matrix_c21[i]));
            matrix_c22[i] = malloc(new_matrix_size * sizeof(*matrix_c22[i]));
        }



        //Division of input matrix 1 into 4 parts - 11,12,21,22
        for (i = 0; i < new_matrix_size; i++) {
            for (j = 0; j < new_matrix_size; j++) {
                output_matrix_1_11[i][j] = input_matrix_1[i][j];
                output_matrix_1_12[i][j] = input_matrix_1[i][j + new_matrix_size];
                output_matrix_1_21[i][j] = input_matrix_1[i + new_matrix_size][j];
                output_matrix_1_22[i][j] = input_matrix_1[i + new_matrix_size][j + new_matrix_size];
            }
        }

        //Division of input matrix 2 into 4 parts - 11,12,21,22
        for (i = 0; i < new_matrix_size; i++) {
            for (j = 0; j < new_matrix_size; j++) {
                output_matrix_2_11[i][j] = input_matrix_2[i][j];
                output_matrix_2_12[i][j] = input_matrix_2[i][j + new_matrix_size];
                output_matrix_2_21[i][j] = input_matrix_2[i + new_matrix_size][j];
                output_matrix_2_22[i][j] = input_matrix_2[i + new_matrix_size][j + new_matrix_size];
            }
        }

        //calculation of M1 - (A11 + A22) * (B11+B22)
        matrix_function(new_matrix_size, "ADD", output_matrix_1_11, output_matrix_1_22, matrix_function_op1);
        matrix_function(new_matrix_size, "ADD", output_matrix_2_11, output_matrix_2_22, matrix_function_op2);
        strassen_matrix_mult(new_matrix_size, matrix_function_op1, matrix_function_op2, matrix_m1);

        //calculation of M2 - (A21 + A22) * B11
        matrix_function(new_matrix_size, "ADD", output_matrix_1_21, output_matrix_1_22, matrix_function_op1);
        strassen_matrix_mult(new_matrix_size, matrix_function_op1, output_matrix_2_11, matrix_m2);

        //calculation of M3 - A11 * (B12 – B22)
        matrix_function(new_matrix_size, "SUB", output_matrix_2_12, output_matrix_2_22, matrix_function_op1);
        strassen_matrix_mult(new_matrix_size, output_matrix_1_11, matrix_function_op1, matrix_m3);

        //calculation of M4 - A22 * (B21 – B11)
        matrix_function(new_matrix_size, "SUB", output_matrix_2_21, output_matrix_2_11, matrix_function_op1);
        strassen_matrix_mult(new_matrix_size, output_matrix_1_22, matrix_function_op1, matrix_m4);

        //calculation of M5 - (A11 + A12) * B22
        matrix_function(new_matrix_size, "ADD", output_matrix_1_11, output_matrix_1_12, matrix_function_op1);
        strassen_matrix_mult(new_matrix_size, matrix_function_op1, output_matrix_2_22, matrix_m5);

        //calculation of M6 -  (A21 – A11) * (B11+B12)
        matrix_function(new_matrix_size, "SUB", output_matrix_1_21, output_matrix_1_11, matrix_function_op1);
        matrix_function(new_matrix_size, "ADD", output_matrix_2_11, output_matrix_2_12, matrix_function_op2);
        strassen_matrix_mult(new_matrix_size, matrix_function_op1, matrix_function_op2, matrix_m6);

        //calculation of M7 -  (A12 – A22)(B21 + B22)
        matrix_function(new_matrix_size, "SUB", output_matrix_1_12, output_matrix_1_22, matrix_function_op1);
        matrix_function(new_matrix_size, "ADD", output_matrix_2_21, output_matrix_2_22, matrix_function_op2);
        strassen_matrix_mult(new_matrix_size, matrix_function_op1, matrix_function_op2, matrix_m7);

        //calculate matrix_c11 - M1 + M4 - M5 + M7
        matrix_function(new_matrix_size, "ADD", matrix_m1, matrix_m4, matrix_function_op1);
        matrix_function(new_matrix_size, "SUB", matrix_function_op1, matrix_m5, matrix_function_op2);
        matrix_function(new_matrix_size, "ADD", matrix_function_op2, matrix_m7, matrix_c11);

        //calculate matrix_c12 - M3 + M5
        matrix_function(new_matrix_size, "ADD", matrix_m3, matrix_m5, matrix_c12);

        //calculate matrix_c21 - M2 + M4
        matrix_function(new_matrix_size, "ADD", matrix_m2, matrix_m4, matrix_c21);

        //calculate matrix_c22 - M1 + M3 - M2 + M6
        matrix_function(new_matrix_size, "ADD", matrix_m1, matrix_m3, matrix_function_op1);
        matrix_function(new_matrix_size, "SUB", matrix_function_op1, matrix_m2, matrix_function_op2);
        matrix_function(new_matrix_size, "ADD", matrix_function_op2, matrix_m6, matrix_c22);

        //New size calculation of result matrix
        result_matrix_size = (new_matrix_size) * 2;
        result_matrix_stressen[result_matrix_size][result_matrix_size];

        //Calling function compose matrix which will combine all 4 sub matrix - C11, C12, C21 and C22
        compose_matrix((new_matrix_size), matrix_c11, matrix_c12, matrix_c21, matrix_c22, result_matrix_stressen);

        //free up the space
        for (i = 0; i < new_matrix_size; i++) {
            free(output_matrix_1_11[i]);
            free(output_matrix_1_12[i]);
            free(output_matrix_1_21[i]);
            free(output_matrix_1_22[i]);

            free(output_matrix_2_11[i]);
            free(output_matrix_2_12[i]);
            free(output_matrix_2_21[i]);
            free(output_matrix_2_22[i]);

            free(matrix_m1[i]);
            free(matrix_m2[i]);
            free(matrix_m3[i]);
            free(matrix_m4[i]);
            free(matrix_m5[i]);
            free(matrix_m6[i]);
            free(matrix_m7[i]);

            free(matrix_function_op1[i]);
            free(matrix_function_op2[i]);

            free(matrix_c11[i]);
            free(matrix_c12[i]);
            free(matrix_c21[i]);
            free(matrix_c22[i]);
        }

        free(output_matrix_1_11);
        free(output_matrix_1_12);
        free(output_matrix_1_21);
        free(output_matrix_1_22);

        free(output_matrix_2_11);
        free(output_matrix_2_12);
        free(output_matrix_2_21);
        free(output_matrix_2_22);

        free(matrix_m1);
        free(matrix_m2);
        free(matrix_m3);
        free(matrix_m4);
        free(matrix_m5);
        free(matrix_m6);
        free(matrix_m7);

        free(matrix_function_op1);
        free(matrix_function_op2);

        free(matrix_c11);
        free(matrix_c12);
        free(matrix_c21);
        free(matrix_c22);
    }
    return 0;
}

/*
 This function is created to to perform various matrix function like addition, subtraction and multiplication
 */
int matrix_function(int matrix_size, char function[], int **input_matrix_1,
                    int **input_matrix_2, int **output_matrix) {
    int i, j, k;
    //addition of two matrix
    if (strncmp(function, "ADD", 3) == 0) {
        for (i = 0; i < matrix_size; i++) {
            for (j = 0; j < matrix_size; j++) {
                output_matrix[i][j] = input_matrix_1[i][j] + input_matrix_2[i][j];
            }
        }
    }
        //subtraction of two matrix
    else if (strncmp(function, "SUB", 3) == 0) {
        for (i = 0; i < matrix_size; i++) {
            for (j = 0; j < matrix_size; j++) {
                output_matrix[i][j] = input_matrix_1[i][j] - input_matrix_2[i][j];
            }
        }
    }
        //multiplication of two matrix - using general algorithm with complexity - O(n^3)
    else if (strncmp(function, "MUL", 3) == 0) {
        for (i = 0; i < matrix_size; i++) {
            for (j = 0; j < matrix_size; j++) {
                output_matrix[i][j] = 0;
                for (k = 0; k < matrix_size; k++) {
                    output_matrix[i][j] = output_matrix[i][j] + input_matrix_1[i][k] * input_matrix_2[k][j];
                }
            }
        }
    }
    return 0;
}

/*
 This function combine all sub matrix into one final result matrix
 */
int compose_matrix(int size, int **input_matrix_1, int **input_matrix_2,
                   int **input_matrix_3, int **input_matrix_4,
                   int **result_matrix_stressen) {

    int i, j;
    // traverse through first loop
    for (i = 0; i < size; i++) {
        //traverse through second loop
        for (j = 0; j < size; j++) {
            result_matrix_stressen[i][j] = input_matrix_1[i][j];
            result_matrix_stressen[i][j + size] = input_matrix_2[i][j];
            result_matrix_stressen[i + size][j] = input_matrix_3[i][j];
            result_matrix_stressen[i + size][j + size] = input_matrix_4[i][j];
        }

    }

    return 0;
}
