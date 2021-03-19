#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>




/* ANSI 3-bit and 4-bit color with escaped sequences.
 * According to specification, it produces 8 colors.
 * Later terminals started supporting background(BG) colors.
 */
#define R0     "\033[0;0m"
#define BLK    "\033[0;30m"
#define RED    "\033[0;31m"
#define GRN    "\033[0;32m"
#define YLW    "\033[0;33m"
#define BLU    "\033[0;34m"
#define MGN    "\033[0;35m"
#define CYN    "\033[0;36m"
#define REDBG  "\033[0;41m"
#define GRNBG  "\033[0;42m"




/* Given a variable name,
 * Returns the type.
 */
#define TYPE_CHAR    2
#define TYPE_STR     3

#define TYPE_INT     1
#define TYPE_LONG    4
#define TYPE_DOUBLE  5
#define TYPE_FLOAT   6

#define TYPE_UNKNOWN 0
//add more data types at will when needed.
//we're gonna use `TYPE_dataTypeName` anyway.

#define type(var) _Generic(var, \
	int: TYPE_INT, char: TYPE_CHAR, char*: TYPE_STR, \
	long: TYPE_LONG, double: TYPE_DOUBLE, float: TYPE_FLOAT,\
	default: TYPE_UNKNOWN)










/* Given an array,
 * Returns the len of the array.
 */
#define len(arr) sizeof(arr)/sizeof(arr[0])




/* Given a C expression,
 * asserts it.
 */
#define assert(expression) \
	(expression) ? printf(GRNBG "True" R0) : printf(REDBG "False" R0); \
	printf("\n");




/* Given a filename,
 * reads a file. 
 * Returns the contents of the file.
 */
char* file_read(char* filename) {
	FILE *file = fopen(filename, "r");
	char *buffer = 0;
	long length;
	if (file) {
		fseek(file, 0, SEEK_END);
		length = ftell(file);
		fseek(file, 0, SEEK_SET);
		buffer = (char*)malloc(length);
		if (buffer) { fread(buffer, 1, length, file); }
		fclose(file);
	}
	return buffer;
}





/* Given a string, and a substring,
 * searches the substring in the string
 * Returns up to what is matched.
 */
char*  substr(char* string, char* substr) {		
	static char matched[1000000];	
	int i = 0;    // counter for substr
	int j = 0;    // counter for string

	for(j = 0; j < strlen(string); j++) {
		if (substr[i] == string[j]) {
			strcat(matched, &substr[i]);    //substr[i] matched!
			i++; 
		}
		if (strcmp(matched, substr)==0) { break; }
	}
	return matched;
}




/* Given an array of numbers, and len of the array,
 * determines the sum of the array
 * Returns the sum.
 */
double sum(double numbers[], int arrlen) { 
	double sum = 0;
	for (int i=0; i < arrlen; i++) { 
		sum += numbers[i];
	} 
	return sum;
}




/* Given an array of numbers, and length of the array,
 * determines the maximum value of the array
 * Returns the maximum item.
 */

double max (double numbers[], int arrlen) {
	double maxitem = numbers[0];
	for(int i=1; i<arrlen; i++) {
		if (numbers[i] > maxitem) {
			maxitem = numbers[i];
		}
	}
	return maxitem;
}




/* Given an array of numbers, and length of the array,
 * determines the minimum value of the array
 * Returns the minimum item.
 */

double min(double numbers[], int arrlen) {
	double minitem = numbers[0];
	for(int i=1; i < arrlen; i++) {
		if (numbers[i] < minitem) {
			minitem = numbers[i];
		}
	}
	return minitem;
}



int str_index(char *str, char item){
    for(int i = 0; i < strlen(str); i++){
        if(str[i] == item){
            return 0;
        }
    }

    return -1;
}


// This function sorts array from left index to
// to right index which is of size atmost RUN
void insertionSort(int arr[], int left, int right)
{
    for (int i = left + 1; i <= right; i++)
    {
        int temp = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > temp)
        {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = temp;
    }
}


// Merge function merges the sorted runs
void merge(int arr[], int l, int m, int r)
{
     
    // Original array is broken in two parts
    // left and right array
    int len1 = m - l + 1, len2 = r - m;
    int left[len1], right[len2];
    for (int i = 0; i < len1; i++)
        left[i] = arr[l + i];
    for (int i = 0; i < len2; i++)
        right[i] = arr[m + 1 + i];
 
    int i = 0;
    int j = 0;
    int k = l;
 
    // After comparing, we 
    // merge those two array
    // in larger sub array
    while (i < len1 && j < len2)
    {
        if (left[i] <= right[j])
        {
            arr[k] = left[i];
            i++;
        }
        else
        {
            arr[k] = right[j];
            j++;
        }
        k++;
    }
 
    // Copy remaining elements of left, if any
    while (i < len1)
    {
        arr[k] = left[i];
        k++;
        i++;
    }
 
    // Copy remaining element of right, if any
    while (j < len2)
    {
        arr[k] = right[j];
        k++;
        j++;
    }
}
 
// Iterative Timsort function to sort the
// array[0...n-1] (similar to merge sort)
void timSort(int arr[], int n)
{
     
    // Sort individual subarrays of size RUN
    for (int i = 0; i < n; i+=RUN)
        insertionSort(arr, i, min((i+RUN-1), 
                                    (n-1)));
 
    // Start merging from size RUN (or 32). 
    // It will merge
    // to form size 64, then 128, 256 
    // and so on ....
    for (int size = RUN; size < n; 
                             size = 2*size)
    {
         
        // pick starting point of 
        // left sub array. We
        // are going to merge 
        // arr[left..left+size-1]
        // and arr[left+size, left+2*size-1]
        // After every merge, we 
        // increase left by 2*size
        for (int left = 0; left < n; 
                             left += 2*size)
        {
             
            // find ending point of 
            // left sub array
            // mid+1 is starting point 
            // of right sub array
            int mid = left + size - 1;
            int right = min((left + 2*size - 1), 
                                            (n-1));
 
            // merge sub array arr[left.....mid] &
            // arr[mid+1....right]
              if(mid < right)
                merge(arr, left, mid, right);
        }
    }
}



void printArray(int arr[], int size) { 
    int i; 
    for (i=0; i < size; i++) 
        printf("%d ", arr[i]); 
    printf("\n"); 
}



int* sorted(int *arr, int size){
    timSort(arr, size);

    return arr;
}
