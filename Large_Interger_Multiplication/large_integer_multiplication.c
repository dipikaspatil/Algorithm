/********************************* Main Function Start **********************************/

#include "large_integer_multiplication.h"

/*
 This function  will take input from user and will generate random number.
 As per user's input main will call sorting function
*/
int main() {
    printf("\n\n");
    //variable declaration
    int counter = ZERO;
    int min_limit = 0;
    int count_number;
    //declaration of loop variables
    int i, j;

    //Input From User - includes sorting method and number of count of input numbers to be sorted
    START:
    printf("\n------------------------------------- START OF PROGRAM : LARGE NUMBER MULTIPLICATION--------------------------------------------\n");
    bool valid_num;
    char answer;

    GET_COUNT:
    /*
      take the count of numbers to be sorted from user. If input is between multiple of 6 then continue
      ....else ask again to enter correct number
    */
    printf("\nPlease enter number multiple of 6\n:- ");
    scanf("%d", &count_number);

    if (count_number <= 0) {
        printf("\n***** Input count of numbers is not multiple of 6. *****\n"
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
            printf("\n***** Input count of numbers is not multiple of 6 .... Please enter number multiple of 6\n"
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
    ip_array_size = count_number;
    int input_number_1[ip_array_size];
    int input_number_2[ip_array_size];
    //max limit is set to 9 .....so that random digit is generated between 0 to 9 ....for most significant digit it is 1 to 9
    int max_limit = 9;
    int result_size = count_number * 2;
    int output_number_general[result_size];
    int output_number_large_split2[result_size];
    int output_number_large_split3[result_size];

    //need to clear random generator to null before generation of random number
    srand((unsigned) time(NULL));
    //generating random number using rand() function and including the same into input matrix 1 and 2 of integers
    for (i = 0; i < ip_array_size; i++) {
        if (i == (ip_array_size - 1)) {
            min_limit = 1;
        } else {
            min_limit = 0;
        }
        input_number_1[i] = (rand() % max_limit) + min_limit;
        input_number_2[i] = (rand() % max_limit) + min_limit;
    }

    printf("\n\n******************* input large number 1 **************\n\n");
    print_array_size = ip_array_size;
    print_array(input_number_1);

    printf("\n\n******************* input large number 2 **************\n\n");
    print_array_size = ip_array_size;
    print_array(input_number_2);

    printf("\n\n******************* Result using large number multiplication algorithm split 2 **************\n\n");
    large_number_mult_split2(ip_array_size, result_size, input_number_1, input_number_2, output_number_large_split2);
    print_array_size = result_size;
    print_array(output_number_large_split2);

    printf("\n\n******************* Result using large number multiplication algorithm split 3 **************\n\n");
    large_number_mult_split3(ip_array_size, result_size, input_number_1, input_number_2, output_number_large_split3);
    print_array_size = result_size;
    print_array(output_number_large_split3);

    printf("\n\n");
    return 0;
}
/********************************* Main Function End *************************************/
/*
 This function checks if number is power of 2 or not
 */
bool check_num(int num) {
    int num_1;
    //if number is multiple of 6, return true
    num_1 = num % 6;
    if (num_1 == 0) {
        return true;
    } else {
        return false;
    }
}

/*
 This function display array element
 */
int print_array(int input_array[]) {
    int i, j;
    //traverse through loop
    for (i = 0; i < print_array_size; i++) {
        printf("%d", input_array[i]);
    }
    printf("\n\n");
    return 0;
}

/*
 This functions created to multiple numbers....when it reaches to threshold level in large number multiplication algorithm
 */
int general_number_mult(int number_size, int result_size, int input_number_1[], int input_number_2[],
                        int output_array[result_size]) {
    //declaration of loop counter
    int i, j, k, l;
    //initialize array with 0
    for (k = 0; k < result_size; k++) {
        output_array[k] = 0;
    }
    // local variable declaration
    int counter = result_size;
    int carry = 0;
    int digit = 0;
    int output_array_size = result_size;

    //loop of second number
    for (i = (number_size - 1); i >= 0; i--) {
        counter = output_array_size - 1;
        //loop of first number
        for (j = (number_size - 1); j >= 0; j--) {
            //inclusion of multiplication into output number array
            output_array[counter] = output_array[counter] + (input_number_1[j] * input_number_2[i]);
            counter--;
        }
        output_array_size--;
    }

    //inclusion of addition of numbers multiplied in earlier loop
    for (l = (result_size - 1); l >= 0; l--) {
        //calculate carry which will be added to next number
        carry = output_array[l] / 10;
        //calculate unit place number
        digit = output_array[l] % 10;
        //assignment of digit to result output array .... finally have multiplication result
        output_array[l] = digit;
        if (carry > 0) {
            output_array[l - 1] = output_array[l - 1] + carry;
        }
    }
    return 0;
}

/*
 This function perform large number multiplication using lecture slide 5 - divide and conquer
 It divides number into 2 parts and uses formula as follows -
 Formula for multiplication -
 u × v
 u = x × 10^m + y
 v = w × 10^m + z
 u×v =	xw × 10^2m + (xz+wy)× 10^m + yz
 */
int large_number_mult_split2(int number_size, int result_size, int input_number_1[], int input_number_2[],
                             int output_number[]) {
    //if threshold condition occur ....calculate multiplication using general multiplication algorithm of - general_number_mult()
    if (number_size % 2 != 0) {
        general_number_mult(number_size, result_size, input_number_1, input_number_2, output_number);
    } else {
        //calculate the new size in which large number is divided
        int new_num_size = floor(number_size / 2);

        //Declaration of 4 sub arrays, x, y, z, w - as per formula (please refer function description)
        int input_number_x[new_num_size];
        int input_number_y[new_num_size];
        int input_number_w[new_num_size];
        int input_number_z[new_num_size];

        //Declaration of 4 sub arrays for multiplication, xw, xz, wy, yz - as per formula (please refer function description)
        int output_number_prod_xw[result_size];
        int output_number_prod_xz[result_size];
        int output_number_prod_wy[result_size];
        int output_number_prod_yz[result_size];

        //Declaration of 3 sub arrays for addition, xzwy, xw_xzwy, xw_xzwy_yz - as per formula (please refer function description)
        int output_number_add_xzwy[result_size];
        int output_number_add_xw_xzwy[result_size];
        int output_number_add_xw_xzwy_yz[result_size];

        //declaration of power of 10 - as per formula (please refer function description).... it is analogous to m
        int ten_power = new_num_size;

        //loop counter declaration
        int i, j, k;

        //loop to assign values to 4 sub-array from 2 input large numbers
        for (i = 0; i < new_num_size; i++) {
            input_number_x[i] = input_number_1[i];
            input_number_y[i] = input_number_1[i + new_num_size];
            input_number_w[i] = input_number_2[i];
            input_number_z[i] = input_number_2[i + new_num_size];
        }

        //multiplication of x and w
        large_number_mult_split2(new_num_size, result_size, input_number_x, input_number_w, output_number_prod_xw);

        //multiplication of x and z
        large_number_mult_split2(new_num_size, result_size, input_number_x, input_number_z, output_number_prod_xz);

        //multiplication of w and y
        large_number_mult_split2(new_num_size, result_size, input_number_w, input_number_y, output_number_prod_wy);

        //multiplication of y and z
        large_number_mult_split2(new_num_size, result_size, input_number_y, input_number_z, output_number_prod_yz);

        //multiply xw with 10^2m
        ten_power_mult((ten_power * 2), result_size, output_number_prod_xw);

        //add xz and wy
        large_number_add(result_size, output_number_prod_xz, output_number_prod_wy, output_number_add_xzwy);

        //multiply xzwy with 10^m
        ten_power_mult((ten_power), result_size, output_number_add_xzwy);

        //add xw and xzwy
        large_number_add(result_size, output_number_prod_xw, output_number_add_xzwy, output_number_add_xw_xzwy);

        //add xw_xzwy and yz
        large_number_add(result_size, output_number_add_xw_xzwy, output_number_prod_yz, output_number_add_xw_xzwy_yz);

        //assignment of final multiplication result to output number which is printed in main() function
        for (k = 0; k < result_size; k++) {
            output_number[k] = output_number_add_xw_xzwy_yz[k];
        }
    }
    return 0;
}

/*
 This function is created to multiply any number with power of 10
 It takes 3 input, power of ten, array size and actual array
 It changes digit position using power of 10
 */
int ten_power_mult(int pow, int output_array_size, int output_array[]) {
    //loop counter declaration
    int i, j;
    //traverse through output array and move digit as per power of 10
    for (i = 0; i < (output_array_size - pow); i++) {
        output_array[i] = output_array[pow + i];
    }
    //assign 0 at the end of large number as per poer of 10
    for (j = 0; j < pow; j++) {
        output_array[(output_array_size - 1) - j] = 0;
    }
    return 0;
}

/*
 This function is created to add 2 large numbers (sub arrays) as per their digit position
 It takes 4 parameters
 1- array size
 2- large number 1 in array form
 3- large number 2 in array form
 4- outpur number - result of addition
 */
int large_number_add(int num_size, int input_num_1[], int input_num_2[], int output_num[]) {
    //loop counter declaration
    int i, j;
    //local variable declaration
    int carry = 0;
    int place_digit;
    int add_digit;

    //initialization of output array to 0
    for (j = 0; j < num_size; j++) {
        output_num[j] = 0;
    }

    //traverse through array using large number size
    for (i = num_size - 1; i >= 0; i--) {
        //add digits of 2 large numbers
        add_digit = input_num_1[i] + input_num_2[i];
        //calculate place digit using mod 10....eg - for 8+8 = 16 - place digit is 6
        place_digit = add_digit % 10;
        //calculate carry using divide by 10....eg - for 8+8 = 16 - carry is 1
        carry = add_digit / 10;
        //if carry > 0.... add the same into next digit place....so that it can be counted in next addition in loop
        if (carry > 0) {
            output_num[i - 1] = carry;
        }
        //final output number digit value calculation
        output_num[i] = output_num[i] + place_digit;
    }
    return 0;
}

/*
 This function perform large number as per modified algorithm
 It divides number into 2 parts and uses formula as follows -
 Formula for multiplication -
 u × v
 u = p × 10^2m + q x 10^m + r
 v = s × 10^2m + t x 10^m + u
 u×v =	{[(p x s) x 10^4m]} + {[(p x t) + (q x s)] x 10^3m} + {[(p x u) + (q x t) + (r x s)] x 10^2m} + {[(q x u) + (r x t)] x 10^m} + {[(r x u)]}
 */
int large_number_mult_split3(int number_size, int result_size, int input_number_1[], int input_number_2[],
                             int output_number[]) {
    /*
     if threshold condition occur i.e if we can not divide number into 3 equal parts
     ....calculate multiplication using general multiplication algorithm of - general_number_mult()
    */
    if (number_size % 3 != 0) {
        general_number_mult(number_size, result_size, input_number_1, input_number_2, output_number);
    } else {
        //calculate the new size in which large number is divided
        int new_num_size = floor(number_size / 3);

        //Declaration of 6 sub arrays, p,q,r,s - as per formula (please refer function description)
        int input_number_p[new_num_size];
        int input_number_q[new_num_size];
        int input_number_r[new_num_size];
        int input_number_s[new_num_size];
        int input_number_t[new_num_size];
        int input_number_u[new_num_size];

        //Declaration of 9 sub arrays for multiplication, ps,pt,qs,pu,qt,rs,qu,rt,ru  - as per formula (please refer function description)
        int output_number_prod_ps[result_size];
        int output_number_prod_pt[result_size];
        int output_number_prod_qs[result_size];
        int output_number_prod_pu[result_size];
        int output_number_prod_qt[result_size];
        int output_number_prod_rs[result_size];
        int output_number_prod_qu[result_size];
        int output_number_prod_rt[result_size];
        int output_number_prod_ru[result_size];

        //Declaration of 4 sub arrays for addition, ptqs, puqt, puqtrs, qurt - as per formula (please refer function description)
        int output_number_add_ptqs[result_size];
        int output_number_add_puqt[result_size];
        int output_number_add_puqtrs[result_size];
        int output_number_add_qurt[result_size];

        //Declaration of 4 sub arrays for addition, ps_ptqs, ps_ptqs_puqtrs, ps_ptqs_puqtrs_qurt, ps_ptqs_puqtrs_qurt_ru - as per formula (please refer function description)
        int output_number_add_ps_ptqs[result_size];
        int output_number_add_ps_ptqs_puqtrs[result_size];
        int output_number_add_ps_ptqs_puqtrs_qurt[result_size];
        int output_number_add_ps_ptqs_puqtrs_qurt_ru[result_size];

        //declaration of power of 10 - as per formula (please refer function description).... it is analogous to m
        int ten_power_m = new_num_size;

        //loop counter declaration
        int i, j, k;

        //loop to assign values to 6 sub-array from 2 input large numbers
        for (i = 0; i < new_num_size; i++) {
            input_number_p[i] = input_number_1[i];
            input_number_q[i] = input_number_1[i + new_num_size];
            input_number_r[i] = input_number_1[i + (new_num_size * 2)];
            input_number_s[i] = input_number_2[i];
            input_number_t[i] = input_number_2[i + new_num_size];
            input_number_u[i] = input_number_2[i + (new_num_size * 2)];
        }

        /*************************************** Equation 1 *********************************************/
        //multiplication of p and s
        large_number_mult_split2(new_num_size, result_size, input_number_p, input_number_s, output_number_prod_ps);

        //multiply ps with 10^4m
        ten_power_mult((ten_power_m * 4), result_size, output_number_prod_ps);

        /*************************************** Equation 2 *********************************************/

        //multiplication of p and t
        large_number_mult_split2(new_num_size, result_size, input_number_p, input_number_t, output_number_prod_pt);

        //multiplication of q and s
        large_number_mult_split2(new_num_size, result_size, input_number_q, input_number_s, output_number_prod_qs);

        //add pt and qs
        large_number_add(result_size, output_number_prod_pt, output_number_prod_qs, output_number_add_ptqs);

        //multiply ptqs with 10^3m
        ten_power_mult((ten_power_m * 3), result_size, output_number_add_ptqs);

        /*************************************** Equation 3 *********************************************/

        //multiplication of p and u
        large_number_mult_split2(new_num_size, result_size, input_number_p, input_number_u, output_number_prod_pu);

        //multiplication of q and t
        large_number_mult_split2(new_num_size, result_size, input_number_q, input_number_t, output_number_prod_qt);

        //multiplication of r and s
        large_number_mult_split2(new_num_size, result_size, input_number_r, input_number_s, output_number_prod_rs);

        //add pu and qt
        large_number_add(result_size, output_number_prod_pu, output_number_prod_qt, output_number_add_puqt);

        //add puqt and rs
        large_number_add(result_size, output_number_add_puqt, output_number_prod_rs, output_number_add_puqtrs);

        //multiply puqtrs with 10^2m
        ten_power_mult((ten_power_m * 2), result_size, output_number_add_puqtrs);

        /*************************************** Equation 4 *********************************************/

        //multiplication of q and u
        large_number_mult_split2(new_num_size, result_size, input_number_q, input_number_u, output_number_prod_qu);

        //multiplication of r and t
        large_number_mult_split2(new_num_size, result_size, input_number_r, input_number_t, output_number_prod_rt);

        //add qu and rt
        large_number_add(result_size, output_number_prod_qu, output_number_prod_rt, output_number_add_qurt);

        //multiply puqtrs with 10^m
        ten_power_mult((ten_power_m * 1), result_size, output_number_add_qurt);

        /*************************************** Equation 5 *********************************************/

        //multiplication of r and u
        large_number_mult_split2(new_num_size, result_size, input_number_r, input_number_u, output_number_prod_ru);


        /*************************************** Equation 1 + Equation 2 *********************************************/

        //add ps and ptqs
        large_number_add(result_size, output_number_prod_ps, output_number_add_ptqs, output_number_add_ps_ptqs);

        /********************************* result (Equation 1 + Equation 2) + Equation 3 *********************/

        //add ps_ptqs + puqtrs
        large_number_add(result_size, output_number_add_ps_ptqs, output_number_add_puqtrs,
                         output_number_add_ps_ptqs_puqtrs);


        /*************************** result (Equation 1 + Equation 2 + Equation 3) + Equation 4 ******************/

        //add ps_ptqs + puqtrs
        large_number_add(result_size, output_number_add_ps_ptqs_puqtrs, output_number_add_qurt,
                         output_number_add_ps_ptqs_puqtrs_qurt);

        /*************************** result (Equation 1 + Equation 2 + Equation 3) + Equation 4 ******************/

        //add ps_ptqs + puqtrs
        large_number_add(result_size, output_number_add_ps_ptqs_puqtrs_qurt, output_number_prod_ru,
                         output_number_add_ps_ptqs_puqtrs_qurt_ru);

        //assignment of final multiplication result to output number which is printed in main() function
        for (k = 0; k < result_size; k++) {
            output_number[k] = output_number_add_ps_ptqs_puqtrs_qurt_ru[k];
        }


    }
    return 0;
}
