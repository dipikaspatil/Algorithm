/********************************* Main Function Start **********************************/

#include "heap_radix_sort.h"

/*
 This function  will take input from user and will generate random number.
 As per user's input main will call sorting function
*/
int main() {
    //variable declaration
    int counter = ZERO;
    int max_display_num_15 = 15;
    int max_display_num_999 = 999;
    int min_display_num = 1;

    //Input From User - includes sorting method and number of count of input numbers to be sorted
    START:
    printf("\n------------------------------------- START OF PROGRAM --------------------------------------------\n");
    printf("1 - Heap Sort\n"
                   "2 - Radix Sort\n\n");

    printf("Please Select Sorting Method Out Of 1, 2 \n:- ");
    int sorting_method;
    int count_number;
    char answer;

    scanf("%d", &sorting_method);
    //If user select appropriate sorting method then continue otherwise ask user again for input
    if (sorting_method != 1 && sorting_method != 2) {
        printf("\n***** Input entered is not valid. ***** \n\n"
                       "Do you want to continue? (y/n)\n:- ");
        scanf(" %c", &answer);
        //if user say yes to continue....continue the program
        if (toupper(answer) == 'Y') {
            counter = counter + 1;
            //if user give wrong input 3 times ....exit the program
            if (counter == 3) {
                printf("\n\nUser has exceeded number of chances....so exiting the program\n");
                return ZERO;
            }
            //go back to start to get correct input from user
            goto START;
        }
            // exit the program if user don't want to continue execution of program
        else {
            printf("\nExiting program....\n");
            printf("\n----------------------------------------------------------------------------\n\n");
            return ZERO;
        }
    } else {
        GET_COUNT:
        //take the count of numbers to be sorted from user. If input is between 1 to 1000 then continue ....else ask again to enter correct number
        printf("\n----------------------------------------------------------------------------\n");
        printf("\n Please enter count of numbers to be sorted between 1 to 1000\n:- ");
        scanf("%d", &count_number);
        if (count_number <= 0 || count_number >= 1001) {
            printf("\n***** Input count of numbers is not in range. Please enter number between 1 and 1000. *****\n"
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
        }

    }

    //Generating array of random numbers as per count given by user

    int input_array_m[count_number];

    //if count of numbers given by uuser is less than 20, set the flag of visual display to 1 (i.e. true) else keep it false
    if (count_number <= 20) {
        display = 1;
    } else {
        display = 0;
    }

    //need to clear random generator to null before generation of random number
    srand((unsigned) time(NULL));
    //generating random number using rand() function and adding the same into input array of integers
    for (int i = 0; i < count_number; i++) {
        // if count of numbers is less than 20, generating numbers between 1 to 15 --for visual representation
        if (display == 1) {
            input_array_m[i] = (rand() % max_display_num_15) + min_display_num;
        } else {
            // if count of numbers is greater than 20, generating number within the range of 0 to 999 for Radix Sort
            if (sorting_method == 2) {
                input_array_m[i] = (rand() % max_display_num_999) + min_display_num;
            }
                //if count of numbers is greater than 20, generating number within the range of SHORT for Heap Sort
            else {
                input_array_m[i] = (rand() % SHRT_MAX) + min_display_num;
            }
        }
    }

    //computing the size of input array
    int size_m = sizeof(input_array_m) / sizeof(int);

    //calling sorting function which will call required sorting method function as per input provided
    sorting(input_array_m, size_m, sorting_method);

    return 0;
}
/********************************* Main Function End *************************************/

/*
 This function invokes respective sorting algorithms as per user's input
*/
int sorting(int input_array_m[], int size_m, int sorting_method) {
    //int random_index;
    printf("\n----------------------------------------------------------------------------\n");
    printf("\nOriginal array is :- ");
    //printing original array to console before sorting
    for (int k = 0; k < size_m; k++) {
        printf("%d ", input_array_m[k]);
    }
    printf("\n");
    printf("\n----------------------------------------------------------------------------\n");

    //calling sorting method as per input provided.
    switch (sorting_method) {
        case 1:
            display_star(input_array_m, size_m);
            heap_sort(input_array_m, size_m);
            display_star(input_array_m, size_m);
            printf("\n----------------------------------------------------------------------------\n");
            printf("Sorted array using Heap Sort method is :- ");
            break;
        case 2:
            radix_sort(input_array_m, size_m);
            display_star(input_array_m, size_m);
            printf("\n----------------------------------------------------------------------------\n");
            printf("Sorted array using Radix Sort method is :- ");
            break;
    }

    //printing sorted array after completion of respective sorted function
    for (int k = 0; k < size_m; k++) {
        printf("%d ", input_array_m[k]);
    }
    printf("\n\n----------------------------------------------------------------------------\n");
    printf("\n");

    return 0;
}

/********************************* Heap Sort Code Start ******************************/
/*
 This function takes input_array and input  array size as input parameter
 First need to build max heap and then need to swap smallest number with root node and
 need to do the max_hepify
*/

int heap_sort(int input_array[], int input_array_size) {
    //calling function to build max heap
    build_max_heap(input_array, input_array_size);
    //Need to traverse through loop ranging from array_size -1 to 0
    for (int j = (input_array_size - 1); j >= 0; j--) {
        //calling visual representation if user input for number count is less than 20
        display_star(input_array, input_array_size);
        //swap root node with 0th node
        swap(input_array, 0, j);
        //max heapify complete structure except root node ....disconnecting root node
        max_heapify(input_array, 0, j - 1);
    }

    return 0;
}

/*
 This function built max heap ....parent node > child node structure
 At the end of function....highest element is at top/root node of the structure
 */
int build_max_heap(int input_array[], int input_array_size) {
    //calculating loop counter
    int loop_counter = floor(input_array_size / 2) - 1;
    //traverse through loop using counter
    for (int i = loop_counter; i >= 0; i--) {
        //calling max heapify function so that every parent node will be greater than child node
        max_heapify(input_array, i, input_array_size - 1);
    }
    return 0;
}

/*
 This function will create structure in which parent_node will be greater than child node
 */
int max_heapify(int input_array[], int root_index, int input_array_size) {
    //calculating child using root index
    int child_index1 = (2 * root_index) + 1;
    int child_index2 = (2 * root_index) + 2;
    //initial assignment of largest element index
    int largest_element_index = root_index;
    //if child index1 value is greater than rood index value....assign the same to largest element index
    if ((child_index1 <= input_array_size) && (input_array[root_index] < input_array[child_index1])) {
        largest_element_index = child_index1;
    }
    //if child index2 value is greater than largest element index value....assign the same to largest element index
    if ((child_index2 <= input_array_size) && (input_array[largest_element_index] < input_array[child_index2])) {
        largest_element_index = child_index2;
    }
    //swap largest element index with root index if needed.....so that root value is greater than it's respective children
    if (largest_element_index != root_index) {
        swap(input_array, largest_element_index, root_index);
        max_heapify(input_array, largest_element_index, input_array_size - 1);
    }
    return 0;
}
/********************************* Heap Sort Code End ******************************/

/********************************* Radix Sort Code Start ******************************/
/*
 This function takes input_array and input  array size as input parameter
 This function sort using digits. Considering base 10 for input numbers
 It uses stable sorting method i.e. counting-sort to sort every digit
*/

int radix_sort(int input_array[], int input_array_size) {
    //variable declaration
    int max_num;
    int no_of_digits;
    //finding out maximum number of array....so that number of digits can be calculated
    max_num = find_max_num(input_array, input_array_size);
    //calculate number of digits of maximum number using log10
    no_of_digits = log10(max_num) + 1;

    //traverse through numbers using digit position
    for (int j = 0; j < no_of_digits; j++) {
        //calling visual representation if user input for number count is less than 20
        display_star(input_array, input_array_size);
        //calling radix sort count function
        radix_sort_count(input_array, input_array_size, j);
    }
    return 0;
}

/*
 This function finds out maximum number in the array
 */
int find_max_num(int input_array[], int input_array_size) {
    //assignment of first element of array
    int max_num = input_array[0];
    //traverse through array and compare every element
    for (int i = 1; i < input_array_size; i++) {
        //if any array element is greater than current max number ...assign the same
        if (max_num < input_array[i]) {
            max_num = input_array[i];
        }
    }
    return max_num;
}

/*
 This function takes 3 input - input array, input array size and digit position eg - unit, tenth, hundredth as 0,1,2 resp.
 This function uses stable sorting - counting_sort method on every digit of number.
 So it's range of digits for base 10 is 0..9 (k)
 1) It count the number of frequency of every element in whole array
 2) It create offset array to calculate relative position of count array with that of total number of original array
 3) Sort original array and place separate sorted array
 4) Replace original array with sorted array
 */
int radix_sort_count(int input_array[], int input_array_size, int digit_position) {
    //local variable/array declaration
    int sorted_array[input_array_size];
    int range_lower_bound = 0;
    int count_array[10];
    int offset_array[10];
    int orig_array_digit;
    int element_sorted_position;
    //divisor is calculated which is used to get respective digit original array element
    int divisor = pow(10, digit_position);
    int input_array_index;

    //initialize array with 0
    for (int i = 0; i < 10; i++) {
        count_array[i] = 0;
    }

    //count keys by checking occurance of every element in original array....using digit of original array element
    for (int j = 0; j < input_array_size; j++) {
        //getting digit of original array element by dividing it with power of 10 (variable divisor) and taking mod with 10
        input_array_index = (input_array[j] / divisor) % 10;
        /*
         count and place it in appropriate index of count array using respective digit of original array element
         for eg - element 182 will increase the counter of index 2 when digit position is 0 i.e. unit digit
       */
        count_array[input_array_index] = count_array[input_array_index] + 1;
    }

    //create offset array to get relative position of array elements
    offset_array[0] = count_array[0];
    for (int m = 1; m < 10; m++) {
        offset_array[m] = count_array[m] + offset_array[m - 1];
    }

    /*
     sort array - this will sort array and place the element in new sorted array...it will start sorting from last
     element from original array, calculate it's digit  and will check it's relative position using offset array....
    */
    for (int n = input_array_size - 1; n >= 0; n--) {
        //getting digit of original array element by dividing it with power of 10 (variable divisor) and taking mod with 10
        orig_array_digit = (input_array[n] / divisor) % 10;
        //element sorted position is invoked from offset array
        element_sorted_position = offset_array[orig_array_digit] - 1;
        //place the original array element in sorted position in new sorted array
        sorted_array[element_sorted_position] = input_array[n];
        //reduce the offset by one as element is placed in sorted array
        offset_array[orig_array_digit]--;
    }

    //replace sorted array with input array
    for (int r = 0; r < input_array_size; r++) {
        input_array[r] = sorted_array[r];
    }
    return 0;
}

/********************************* Radix Sort Code End ******************************/
/*
 This function takes 3 inut - input array an 2 index
 It swap elements in input array using XOR bitwise operator using 2 index positions
 */
int swap(int input_array[], int index1, int index2) {
    if (index1 != index2) {
        input_array[index1] = input_array[index1] ^ input_array[index2];
        input_array[index2] = input_array[index1] ^ input_array[index2];
        input_array[index1] = input_array[index1] ^ input_array[index2];
    }
    return 0;
}

/********************************* Visualization of Sorting Start **********************/
/*
 Visualization function is created which will display sorting steps
 It will take input_array and it's size as input and display stars as per number if array
*/
int display_star(int input_array[], int size_input_array) {
    if (display == 1) {
        //loop to traverse size of array
        for (int i = 0; i < size_input_array; i++) {
            //loop to traverse value of every element so that respective number of * will be generated
            for (int k = 0; k < input_array[i]; k++) {
                //print the star as per value of array
                printf("*");
            }
            printf("\n");
        }
        printf("\n");
    }
    return 0;
}

/********************************* Visualization of Sorting End ***********************/
