/* Author: Angela To
 * Date: 11/27/14
 * File Name: minmax_sort.cpp
 * Description: Question 2
 */

#include <iostream>
using namespace std;


int find_min(int *a, int size);
int find_max(int *a, int size);
int count_max(int *a, int max, int size);
int count_min(int *a, int min, int size);
void minmax_sort(int*a, int*b, int size);


/* Moves the smallest integer (and its duplicates) to 
 * the front of the array and the largest to the end
 */
void minmax_sort(int*a, int*b, int size) {
  int max = find_max(a, size);
  int min = find_min(a, size);
  int num_max = count_max(a, max, size);
  int num_min = count_min(a, min, size);
  int i = 0; 

  // Replicate numbers of mins at front of temp array
  for (; i < num_min; i++) {
    b[i] = min;
  }

  // Copy over all other values excluding min and max values
  for (int j = 0; j < size; j++) {
    if ((a[j] != min) && (a[j] != max)) {
      b[i] = a[j];
      i++;
    }
  }

  // Replicate number of maxs at the end of the temp array
  for (int k = 0; k < num_max && i < size; k++, i++) {
    b[i] = max;
  }

  // Write the final sorted array to our original one
  for (int c = 0; c < size; c++) {
    a[c] = b[c];
  }
}


/* Find the max term in the array */
int find_max(int *a, int size) {
  int max = a[0];
  for (int i = 0; i < size; i++) 
    if (a[i] > max) max = a[i];
  return max;
}


/* Find the min term in the array */
int find_min(int *a, int size) {
  int min = a[0];
  for (int i = 0; i < size; i++) 
    if (a[i] < min) min = a[i];
  return min;
}


/* Count the number of max terms in array */
int count_max(int *a, int max, int size) {
  int num_max = 0;
  for (int i = 0; i < size; i++)
    if (a[i] == max) num_max++;
  return num_max;
}


/* Count the number of min terms in array */
int count_min(int *a, int min, int size) {
  int num_min = 0;
  for (int i = 0; i < size; i++)
    if (a[i] == min) num_min++;
  return num_min;
}




/* DRIVER to test sort minmax sort function 
 * Takes in command line input
 */
int main(int argc, char** argv) {
  cout << endl;
  int size;
  cout << "How many numbers do you want to sort? ";
  cin >> size;
  
  int a[size]; // Initialize with user input
  int b[size]; // Secondary array to hold values (temp store)

  cout << endl << "Please input numbers (one at a time): " << endl;
  // Take in user-input
  for (int i = 0; i < size; i++) {
    cout << (i + 1) << ": ";
    cin >> a[i];
  }

  // Start sort!
  minmax_sort(a, b, size);

  // Print the sorted array
  cout << endl << "Sorted!" << endl;
  for (int i = 0; i < size; i++) {
    cout << a[i] << " ";
  }
  cout << endl;

  // Done!
  return 0;
}
