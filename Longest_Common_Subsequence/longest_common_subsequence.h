//standard library inclusion
#include <stdio.h>
#include <string.h>

//global variable declaration
int str1_length;
int str2_length;

//function declaration
int lcs(char str1[], char str2[], char output_lcs[]);

int initialize_array(int intermediate_n[str1_length + 1][str2_length + 1]);

int load_output(char str1[], char intermediate_p[str1_length + 1][str2_length + 1], char output_lcs[]);