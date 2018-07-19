//Including standard library
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define ZERO 0

/********************************* Function Declaration **********************************/
int Exchange_Sort(int input_array[], int size_input_array);

int Insertion_Sort(int input_array[], int size_input_array);

int Merge_Sort(int input_array[], int size_input_array);

int Merge_Sort_Divide(int input_array[], int size_input_array);

int Merge_Sort_Conquer(int input_array1[], int input_array2[], int input_array1_size, int input_array2_size,
                       int original_array[], int original_array_size);

int Randomized_Quicksort(int input_array[], int low, int high);

int Swap(int input_array[], int array_index1, int array_index2);

int Partition(int input_array[], int low, int high, int pivot_element);

int Sorting(int input_array_m[], int size_m, int sorting_method);

int Random_Pivot_Index(int low, int high);

int Display_star(int input_array[], int size_input_array);

/********************************* Global Variable Declaration **************************/
int display = 0; //false

/********************************* Main Function Start **********************************/
/*
 This function  will take input from user and will generate random number.
 As per user's input main will call sorting function
*/
int main() {
    //variable declaration
    int counter = ZERO;
    int max_display_num = 15;
    int min_display_num = 1;

    //Input From User - includes sorting method and number of count of input numbers to be sorted
    START:
    printf("\n------------------------------------- START OF PROGRAM --------------------------------------------\n");
    printf("1 - Insertion Sort\n"
                   "2 - Exchange Sort\n"
                   "3 - Merger Sort\n"
                   "4 - Randomized Quick Sort\n\n");

    printf("Please Select Sorting Method Out Of 1, 2, 3, 4 \n:- ");
    int sorting_method;
    int count_number;
    char answer;

    scanf("%d", &sorting_method);
    //If user select appropriate sorting method then continue otherwise ask user again for input
    if (sorting_method != 1 && sorting_method != 2 && sorting_method != 3 && sorting_method != 4) {
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
            input_array_m[i] = (rand() % max_display_num) + min_display_num;
        } else {
            // if count of numbers is greater than 20, generating number withing the range of SHORT
            input_array_m[i] = (rand() % SHRT_MAX) + min_display_num;
        }
    }

    //computing the size of input array
    int size_m = sizeof(input_array_m) / sizeof(int);

    //calling sorting function which will call required sorting method function as per input provided
    Sorting(input_array_m, size_m, sorting_method);

    return 0;
}
/********************************* Main Function End *************************************/

/*
 This function invokes respective sorting algorithms as per user's input
*/
int Sorting(int input_array_m[], int size_m, int sorting_method) {
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
            Insertion_Sort(input_array_m, size_m);
            printf("\n----------------------------------------------------------------------------\n");
            printf("Sorted array using Insertion Sort method is :- ");
            break;
        case 2:
            Exchange_Sort(input_array_m, size_m);
            printf("\n----------------------------------------------------------------------------\n");
            printf("Sorted array using Exchange Sort method is :- ");
            break;
        case 3:

            //if numbers are less that 20....need to call visualization function display_star()
            if (display == 1) {
                printf("\n ----- Visualization of Sorting Process ------ \n\n");
            }

            //we need to pass 2 input parameter - input_array and size of input array to Merge sort
            Merge_Sort(input_array_m, size_m);
            if (display == 1) {
                Display_star(input_array_m, size_m);
            }
            printf("\n----------------------------------------------------------------------------\n\n");
            printf("Sorted array using Merge Sort method is :- ");

            //if numbers are less that 20....need to call visualization function display_star()
            break;
        case 4:
            if (display == 1) {
                printf("\n ----- Visualization of Sorting Process ------ \n");
            }

            //Randomized quick sort need input array and low and high index
            Randomized_Quicksort(input_array_m, 0, size_m - 1);
            // if count of numbers is less than 20, generating numbers between 1 to 15 --for visual representation
            if (display == 1) {
                Display_star(input_array_m, size_m);
            }
            printf("\n----------------------------------------------------------------------------\n\n");
            printf("Sorted array using Randomized Quick Sort method is :- ");

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

/********************************* Exchange Sort Code Start ******************************/
/*
 This function takes input_array and input  array size as input parameter
 Every number will be compared with other numbers in sequence and get swapped if number is small
*/
int Exchange_Sort(int input_array[], int size_input_array) {

    if (display == 1) {
        printf("\n ----- Visualization of Sorting Process ------ \n\n");
    }

    for (int i = 0; i < size_input_array; i++) {
        //if numbers are less that 20....need to call visualization function display_star()
        if (display == 1) {
            Display_star(input_array, size_input_array);
        }
        //inner loop start from i+1 position so that it can be compared with number from previous loop
        for (int j = i + 1; j < size_input_array; j++) {
            if (input_array[j] < input_array[i]) {
                //swap number of ith index number is smaller than jth index number
                Swap(input_array, i, j);
            }
        }
    }

    return 0;
}
/********************************* Exchange Sort Code End ********************************/

/********************************* Insertion Sort Code Start *****************************/
/*
Insertion sort takes input array and size of input array as input parameter
Every number is compared with previous number and needs to be swapped and compared with
subsequent number only when current number is small
*/
int Insertion_Sort(int input_array[], int size_input_array) {
    if (display == 1) {
        printf("\n ----- Visualization of Sorting Process ------ \n\n");
    }

    for (int i = 1; i < size_input_array; i++) {
        //if numbers are less that 20....need to call visualization function display_star()
        if (display == 1) {
            Display_star(input_array, size_input_array);
        }
        //check if jth index number is less than (j-1)th index
        for (int j = i; j > 0 && input_array[j] < input_array[j - 1]; j--) {
            //swap position of numbers in original array
            Swap(input_array, j, j - 1);
        }
    }
    //if numbers are less that 20....need to call visualization function display_star()
    if (display == 1) {
        Display_star(input_array, size_input_array);
    }
    return 0;
}
/********************************* Insertion Sort Code End *******************************/

/********************************* Merge Sort Code Start *********************************/
/*Merge sort takes input array and size of input array as input parameter
First it splits the function into two part and keep on doing the same till it's size become 1
Then it combine/conquer divided elements. While combining it sort the position of elements
It calls function in recursive manner
*/
int Merge_Sort(int input_array[], int size_input_array) {

    Merge_Sort_Divide(input_array, size_input_array);
    return 0;
}

/*
 Divide array till it's size become 1
*/
int Merge_Sort_Divide(int input_array[], int size_input_array) {

    if (size_input_array > 1) {
        //split the array using floor function
        int num = floor(size_input_array / 2);
        int output_array[num];
        int output_array_2[size_input_array - num];
        //add data of ariginal array into two output array using index num
        for (int i = 0; i < num; i++) {
            output_array[i] = input_array[i];

        }
        for (int j = 0; j < (size_input_array - num); j++) {
            output_array_2[j] = input_array[num + j];
        }
        //recursive calling of divide and conquer function
        Merge_Sort_Divide(output_array, sizeof(output_array) / sizeof(int));
        Merge_Sort_Divide(output_array_2, sizeof(output_array_2) / sizeof(int));
        Merge_Sort_Conquer(output_array, output_array_2, sizeof(output_array) / sizeof(int),
                           sizeof(output_array_2) / sizeof(int), input_array, size_input_array);

        //if numbers are less that 20....need to call visualization function display_star()
        if (display == 1) {
            Display_star(input_array, size_input_array);
        }
    }
    return 0;
}

/*
 Sorting and combining divided arrays from previous function
*/
int Merge_Sort_Conquer(int input_array1[], int input_array2[], int input_array1_size, int input_array2_size,
                       int original_array[], int original_array_size) {
    //add the size of two array which needs to be combined....it gradually matches with size of original array
    int new_array_size = input_array1_size + input_array2_size;
    //check if newly combined array size is less than original size....need to cobine array till it has same size as that of original size
    if (new_array_size <= original_array_size) {
        int x = 0, y = 0, count = 0;
        while (count < new_array_size) {
            /*
            if array with xth index from array 1 is smaller than yth index of array 2....
            swap the position in original array and increase the counter of x
            it gradually sort original array through recursive calling
                        */
            if (x < input_array1_size && (y >= input_array2_size || input_array1[x] <= input_array2[y])) {
                original_array[count] = input_array1[x];
                x++;
                count++;
            }
                /*
                if array with yth index from array 2 is smaller than xth index of array 2....
                swap the position and increase the counter of y
                it gradually sort original array through recursive calling
                            */
            else if (y < input_array2_size && (x >= input_array1_size || input_array2[y] <= input_array1[x])) {
                original_array[count] = input_array2[y];
                y++;
                count++;
            }
        }
    }

    return 0;
}
/********************************* Merge Sort Code End *********************************/

/********************************* Randomized Quick Sort Code Start ********************/
/*
Randomized quick sort takes input array and size of input array as input parameter
It first  randomly select pivot position and swap with low position of array
For first call low position is 0 and high position is array_size
After first execution , all elements smaller than pivot element will be swapped to left of pivot element
and all higher elements than pivot are on right side of pivot element....
Process continues on sub arrays....till low index is lesser than higer index
*/
int Randomized_Quicksort(int input_array[], int low, int high) {
    //variable declaration
    int random_index;

    if (low < high) {
        //Random Index generation
        random_index = Random_Pivot_Index(low, high);
        //swap the position of random index with original pivot element position i.e. low
        Swap(input_array, low, random_index);

        int pivot_element = input_array[low];
        //if numbers are less that 20....need to call visualization function display_star()
        if (display == 1) {
            Display_star(input_array, high);
        }

        int pivot_location = Partition(input_array, low, high, pivot_element);
        //Recursive calling of till low index is greater than high index
        Randomized_Quicksort(input_array, low, pivot_location - 1);
        if (low <= pivot_location) {
            //if low index is lesser than pivot location....need to pass low index pivot_location +1
            Randomized_Quicksort(input_array, pivot_location + 1, high);
        } else {
            //if low index is greater than pivot position....need tp add low index value to pivot_location +1
            Randomized_Quicksort(input_array, low + pivot_location + 1, high + low);
        }

    }
    return 0;
}

/*
 Set the pivot location in such a way that original array is partitioned in a way that all smaller elements are at left of pivot
 and all higher elements are at right side of pivot....swap the position of elelemts of array accordingly
*/
int Partition(int input_array[], int low, int high, int pivot_element) {
    int pivot_location = low;
    //traverse through originial array using index position low and high
    for (int i = low + 1; i <= high; i++) {
        if (pivot_element >= input_array[i]) {
            //allocate position of pivot element consideting number of elelments smaller than pivot element
            pivot_location++;
            //swap array elements to newly calculated position
            Swap(input_array, i, pivot_location);
        }
    }

    //swap the position of pivot element to newly calculated position
    if (pivot_location >= 1) {
        Swap(input_array, low, pivot_location);
    }
    return pivot_location;
}

/*
 Function created to swap array elelments
 It takes 3 input - original array, and two index positions in which array needs to be swapped
 It performs binary XOR (^) operation to swap the position
 Array element will not be swapped if index is same
*/
int Swap(int input_array[], int array_index1, int array_index2) {
    if (array_index1 != array_index2) {
        input_array[array_index1] = input_array[array_index1] ^ input_array[array_index2];
        input_array[array_index2] = input_array[array_index1] ^ input_array[array_index2];
        input_array[array_index1] = input_array[array_index1] ^ input_array[array_index2];
    }
    return 0;
}

/*
 Function created to generate random pivot index using low and high index
 Appropriate conditions are handled when low and high are very close or have same index
 This function is used in randomized quick sort for swapping the position of pivot element
 with low position so that probability  pivot element selection is equally likely
*/
int Random_Pivot_Index(int low, int high) {
    int random_num;
    //if high index and low index are consecutive one or same ....return low index
    if ((high - low) <= 1) {
        return low;
    } else {
        //srand function is called to clear random generator
        srand(time(NULL));
        random_num = rand() % high;
        //if random number is greater than high index or smaller than low index ...return low index
        //as random index needs to be between low and high index
        if ((random_num > high) || (random_num < low)) {
            random_num = low;
        }
    }
    return random_num;
}

/********************************* Randomized Quick Sort Code End **********************/

/********************************* Visualization of Sorting Start **********************/
/*
 Visualization function is created which will display sorting steps
 It will take input_array and it's size as input and display stars as per number if array
*/
int Display_star(int input_array[], int size_input_array) {
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
    return 0;
}

/********************************* Visualization of Sorting End ***********************/
