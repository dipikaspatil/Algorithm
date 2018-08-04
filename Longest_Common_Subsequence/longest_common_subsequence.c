//header file inclusion
#include"longest_common_subsequence.h"

/*
 This function takes 2 strings as input from user and finds the common sequence between them
*/
int main(int argc, char *argv[]) {
    printf("\n\n********************** Start of Program - LCS Algorithm **********************");

    if (argc != 3) {
        printf("\n\nIncorrect parameters passed from command line.....Please provide 2 strings as parameter\n\n");
        return 0;
    }

    //local variable declaration
    str1_length = strlen(argv[1]);
    str2_length = strlen(argv[2]);
    char str1[str1_length];
    char str2[str2_length];
    int output_length;


    if (str1_length > str2_length) {
        output_length = str1_length;
    } else {
        output_length = str2_length;
    }

    char output_lcs[output_length];
    memset(output_lcs, '\0', output_length);

    //loop counter declaration
    int i;

    //maximum input string length is 100
    if (str1_length > 100 || str2_length > 100) {
        printf("\n\nString length is greater than 100....please enter string with length less than 100\n\n");
        return 0;
    }

    //copy of user input to local array
    strcpy(str1, argv[1]);
    strcpy(str2, argv[2]);

    //calling of lcs funcion
    lcs(str1, str2, output_lcs);

    output_length = strlen(output_lcs);

    //printf("Common Sequence is --> %s", output_lcs);
    printf("\n\nLength of common sequnce is --> %d", output_length);

    printf("\n\nCommon Sequence is --> ");
    for (i = output_length - 1; i >= 0; i--) {
        printf("%c", output_lcs[i]);
    }

    printf("\n\n********************** End of Program - LCS Algorithm **********************\n\n");
    return 0;
}

/*
 This function takes 2 strings as input and one output string which is copied with common sequence
*/
int lcs(char str1[], char str2[], char output_lcs[]) {
    //loop counter declaration
    int i, j;

    //local variable declaration
    int row = str1_length + 1;
    int column = str2_length + 1;
    char intermediate_p[row][column];
    int intermediate_n[row][column];

    //displaying 2 input strings
    printf("\n\nString 1 is --> %s\n", str1);
    printf("\nString 2 is --> %s\n", str2);

    //initializing number array
    initialize_array(intermediate_n);

    //traverse through string1
    for (i = 1; i < row; i++) {
        //traverse through string2
        for (j = 1; j < column; j++) {
            //in both string are same as per recursion equation, calculate number matrix value and diagonal
            if (str1[i - 1] == str2[j - 1]) {
                intermediate_n[i][j] = intermediate_n[i - 1][j - 1] + 1;
                intermediate_p[i][j] = 'D'; //diagonal element
            } else {
                if (str1_length >= str2_length) {
                    //if upper element is greater or equal with left element ....save it accordingly
                    if (intermediate_n[i - 1][j] >= intermediate_n[i][j - 1]) {
                        intermediate_n[i][j] = intermediate_n[i - 1][j];
                        intermediate_p[i][j] = 'U';  //upper element
                    }
                        //if left element is greater than upper element ....save it accordingly
                    else {
                        intermediate_n[i][j] = intermediate_n[i][j - 1];
                        intermediate_p[i][j] = 'L';
                    }
                } else {
                    //if left element is greater or equal with left element ....save it accordingly
                    if (intermediate_n[i][j - 1] >= intermediate_n[i - 1][j]) {
                        intermediate_n[i][j] = intermediate_n[i][j - 1];
                        intermediate_p[i][j] = 'L';  //left element
                    }
                        //if upper element is greater than upper element ....save it accordingly
                    else {
                        intermediate_n[i][j] = intermediate_n[i - 1][j];
                        intermediate_p[i][j] = 'U'; //upper element
                    }
                }
            }
        }
    }

    printf("\n\nNumber matrix is:\n");
    if (row >= column) {
        //traverse through first index i
        for (i = 1; i < row; i++) {
            //traverse through second index j
            for (j = 1; j < column; j++) {
                //print using both index i, j
                printf("%d\t\t", intermediate_n[i][j]);
            }
            printf("\n");
        }
    } else {
        //traverse through first index i
        for (i = 1; i < row; i++) {
            //traverse through second index j
            for (j = 1; j < column; j++) {
                //print using both index i, j
                printf("%d\t\t", intermediate_n[i][j]);
            }
            printf("\n");
        }
    }


    printf("\n\nPointer matrix is:\n");
    //traverse through first index i
    for (i = 1; i < str1_length + 1; i++) {
        //traverse through second index j
        for (j = 1; j < str2_length + 1; j++) {
            //print using both index i, j
            printf("%c\t\t", intermediate_p[i][j]);
        }
        printf("\n");
    }

    //calling function to load output using pointer matrix and string 1
    load_output(str1, intermediate_p, output_lcs);
    return 0;
}

/*
 This function initializes first row and first column of number matrix
 */
int initialize_array(int intermediate_n[str1_length + 1][str2_length + 1]) {
    int i, j;
    //initialize first row with 0
    for (i = 0; i < str1_length + 1; i++) {
        intermediate_n[i][0] = 0;
    }
    //initialize first column with 0
    for (j = 0; j < str2_length + 1; j++) {
        intermediate_n[0][j] = 0;
    }

    return 0;
}

/*
 This function load output array using pointer matrix and string 1 using directions , U, L, D
 */
int load_output(char str1[], char intermediate_p[str1_length + 1][str2_length + 1], char output_lcs[]) {
    //local variable declaration
    int i, j;
    int row = str1_length;
    int column = str2_length;
    int output_index = 0;

    //if either row or column gets zero, stop the loop
    //start loop with last row, last column element
    while (row != 0 && column != 0) {
        //if pointer matrix shows D, store character in output array
        if (intermediate_p[row][column] == 'D') {
            output_lcs[output_index] = str1[row - 1];
            //reduce counter to reach diagonal element above current element in matrix
            row--;
            column--;
            //increase counter of output array
            output_index++;
        }
            //if pointer matrix shows U, move one row up in matrix
        else if (intermediate_p[row][column] == 'U') {
            //reduce row counter
            row--;
        }
            //if pointer matrix shows L, move one column up in matrix
        else if (intermediate_p[row][column] == 'L') {
            //reduce column counter
            column--;
        }
    }

    return 0;
}
