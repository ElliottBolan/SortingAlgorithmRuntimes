// Elliott Bolan
// CS 3345.501 - Data Structures and Algorithms
// Project 1 - Sorting Algorithms
#include <iostream>  // for using cout to output
#include <fstream>   // for reading from a file and writing to a file
#include <chrono>    // for measuring runtime of sorting algorithm
//#include <cstdlib> // for generating random numbers
//#include <ctime>   // for seeding the random numbers

using namespace std;
int movements = 0;   // Initializing the movements counter as a global variable
int comparisons = 0; // Initializing the comparisons counter as a global variable

//Insertion sort provided with the professor with counter increments
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        comparisons++;
        while (j >= 0 && arr[j] > key) {
            comparisons++;
            arr[j + 1] = arr[j];
            movements++;
            j = j - 1;
        }
        arr[j + 1] = key;
        movements++;
    }
}

//Partition algorithm provided with the professor with modified pivot and counter increments
int partition(int arr[], int low, int high) {
    int pivot = (arr[high]+ arr[low])/2;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        comparisons++;
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
            movements += 3;
        }
    }
    swap(arr[i + 1], arr[high]);
    movements += 3;
    return i + 1;
}

// Implemented an iterative quicksort algorithm
void quicksort(int arr[], int low, int high) {
    int* stack = new int[high - low + 1];
    int top = -1;

    stack[++top] = low;
    stack[++top] = high;

    while (top >= 0) {
        high = stack[top--];
        low = stack[top--];

        int pi = partition(arr, low, high);

        if (pi - 1 > low) {
            stack[++top] = low;
            stack[++top] = pi - 1;
        }

        if (pi + 1 < high) {
            stack[++top] = pi + 1;
            stack[++top] = high;
        }
    }
    delete[] stack;
}

// Provided algorithm by professor with counter increments
void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;
    comparisons++;

    if (right < n && arr[right] > arr[largest])
        largest = right;
    comparisons++;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        movements += 3;
        heapify(arr, n, largest);
    }
}

// Provided algorithm by professor with counter increments
void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        movements += 3;
        heapify(arr, i, 0);
    }
}

// Provided algorithm by professor with counter increments
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
        movements++;
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
        movements++;
    }
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        comparisons++;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            movements++;
            i++;
        }
        else {
            arr[k] = R[j];
            movements++;
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        movements++;
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        movements++;
        j++;
        k++;
    }
    delete[] L;
    delete[] R;
}

// Provided algorithm by professor with counter increments
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int main() {
    cout << "PROJECT 1 - SORTING ALGORITHMS | By: Elliott Bolan " << endl; // Printing a header

    ifstream File("unsorted-list.txt");     // Opening file of unsorted numbers
    int* toSort = new int[50000];           // Allocate memory for an unsorted array of 50,000 integers
    int index = 0;                          // Initializing an index for the 
    while (File >> toSort[index]) {         // Read integers from the file into the array
        index++;                            // Increment Index
        if (index >= 50000) break;          // Finish reading at the 50000th index
    }File.close();                          // Close the file

    ifstream File2("sorted-list.txt");      // Opening a file of sorted numbers 
    int* sortedarr = new int[50000];        // Allocate memory for a sorted array of 50,000 integers
    int index2 = 0;                         // Initializing an index for 
    while (File2 >> sortedarr[index2]) {    // Read integers from the file into the array
        index2++;                           // Increment index
        if (index2 >= 50000) break;         // Finish reading at the 50000th index
    }File2.close();                         // Close the file

    // Making 3 duplicates of the unsorted array
    int* toSort1 = new int[50000];
    for (int i = 0; i < 50000; i++)
        toSort1[i] = toSort[i];
    int* toSort2 = new int[50000];
    for (int i = 0; i < 50000; i++)
        toSort2[i] = toSort[i];
    int* toSort3 = new int[50000];
    for (int i = 0; i < 50000; i++)
        toSort3[i] = toSort[i];
    // Making 3 duplicates of the sorted array
    int* sortedarr1 = new int[50000];
    for (int i = 0; i < 50000; i++) 
        sortedarr1[i] = sortedarr[i];
    int* sortedarr2 = new int[50000];
    for (int i = 0; i < 50000; i++)
        sortedarr2[i] = sortedarr[i];
    int* sortedarr3 = new int[50000];
    for (int i = 0; i < 50000; i++)
        sortedarr3[i] = sortedarr[i];

    // RUNNING AND PRINTING ALL SORTING ALGORITHMS BELOW
    cout << "PART 1: Passing unsorted array" << endl;
    // Run the sorting algorithm and time it with c++ library chrono
    auto start = chrono::high_resolution_clock::now();
    // Run the sorting algorithm here
    quicksort(toSort,0,49999);
    // End the timer
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    // Outputting the results
    std::cout << "Quick Sort\n Comparisons: " << comparisons << "\n Movements: " << movements << endl;
    std::cout << " Time taken: " << duration.count() << " seconds" << endl;
    // Resetting comparisons and movements
    comparisons = 0;
    movements = 0;

    // Run the sorting algorithm and time it with c++ library chrono
    auto start1 = chrono::high_resolution_clock::now();
    // Run the sorting algorithm here
    insertionSort(toSort1, 50000);
    // End the timer
    auto end1 = chrono::high_resolution_clock::now();
    duration = end1 - start1;
    // Outputting the results
    std::cout << "Insertion Sort\n Comparisons: " << comparisons << "\n Movements: " << movements << endl;
    std::cout << " Time taken: " << duration.count() << " seconds" << endl;
    // Resetting comparisons and movements
    comparisons = 0;
    movements = 0;
    
    // Run the sorting algorithm and time it with c++ library chrono
    auto start2 = chrono::high_resolution_clock::now();
    // Run the sorting algorithm here
    heapSort(toSort2, 50000);
    // End the timer
    auto end2 = chrono::high_resolution_clock::now();
    duration = end2 - start2;
    // Outputting the results
    std::cout << "Heap Sort\n Comparisons: " << comparisons << "\n Movements: " << movements << endl;
    std::cout << " Time taken: " << duration.count() << " seconds" << endl;
    // Resetting comparisons and movements
    comparisons = 0;
    movements = 0;

    // Run the sorting algorithm and time it with c++ library chrono
    auto start3 = chrono::high_resolution_clock::now();
    // Run the sorting algorithm here
    mergeSort(toSort3, 0, 50000);
    // End the timer
    auto end3 = chrono::high_resolution_clock::now();
    duration = end3 - start3;
    // Outputting the results
    std::cout << "Merge Sort\n Comparisons: " << comparisons << "\n Movements: " << movements << endl;
    std::cout << " Time taken: " << duration.count() << " seconds" << endl << endl;
    // Resetting comparisons and movements
    comparisons = 0;
    movements = 0;
    // DONE WITH THE UNSORTED LIST. 
    
    // RUNNING SORTING ALGORITHMS WITH SORTED LIST
    cout << "PART 2: Passing sorted array" << endl;
    
    // Run the sorting algorithm and time it with c++ library chrono
    auto start4 = chrono::high_resolution_clock::now();
    // Run the sorting algorithm here
    quicksort(sortedarr, 0, 49999);
    // End the timer
    auto end4 = chrono::high_resolution_clock::now();
    duration = end4 - start4;
    // Outputting the results
    std::cout << "Quick Sort\n Comparisons: " << comparisons << "\n Movements: " << movements << endl;
    std::cout << " Time taken: " << duration.count() << " seconds" << endl;
    // Resetting comparisons and movements
    comparisons = 0;
    movements = 0;

    // Run the sorting algorithm and time it with c++ library chrono
    auto start5 = chrono::high_resolution_clock::now();
    // Run the sorting algorithm here
    insertionSort(sortedarr1, 50000);
    // End the timer
    auto end5 = chrono::high_resolution_clock::now();
    duration = end5 - start5;
    // Outputting the results
    std::cout << "Insertion Sort\n Comparisons: " << comparisons << "\n Movements: " << movements << endl;
    std::cout << " Time taken: " << duration.count() << " seconds" << endl;
    // Resetting comparisons and movements
    comparisons = 0;
    movements = 0;

    // Run the sorting algorithm and time it with c++ library chrono
    auto start6 = chrono::high_resolution_clock::now();
    // Run the sorting algorithm here
    heapSort(sortedarr2, 50000);
    // End the timer
    auto end6 = chrono::high_resolution_clock::now();
    duration = end6 - start6;
    // Outputting the results
    std::cout << "Heap Sort\n Comparisons: " << comparisons << "\n Movements: " << movements << endl;
    std::cout << " Time taken: " << duration.count() << " seconds" << endl;
    // Resetting comparisons and movements
    comparisons = 0;
    movements = 0;

    // Run the sorting algorithm and time it with c++ library chrono
    auto start7 = chrono::high_resolution_clock::now();
    // Run the sorting algorithm here
    mergeSort(sortedarr3, 0, 50000);
    // End the timer
    auto end7 = chrono::high_resolution_clock::now();
    duration = end7 - start7;
    // Outputting the results
    std::cout << "Merge Sort\n Comparisons: " << comparisons << "\n Movements: " << movements << endl;
    std::cout << " Time taken: " << duration.count() << " seconds" << endl;
    // Resetting comparisons and movements
    comparisons = 0;
    movements = 0;

    // Deleting memory
    delete[] toSort;
    delete[] toSort1;
    delete[] toSort2;
    delete[] toSort3;
    delete[] sortedarr;
    delete[] sortedarr1;
    delete[] sortedarr2;
    delete[] sortedarr3;

    //Code that I used to generate the list's of random numbers. Used with libraries commented at top
    /*GENERATING RANDOM NUMBERS
    ofstream File;
    string filename = "unsorted-list.txt";
    File.open(filename);

    //Seed the random number generator
    srand(time(0));

    // Generate and write 50,000 random integers to the file
    for (int i = 0; i < 50000; i++) {
        int random_number = rand() % INT_MAX; // Generate a random integer between 0 and 99,999
        File << random_number << endl;       // Write the random number to the file
    }
    File.close();

    Opening file of sorted numbers to make sorted list
    ofstream outFile("sorted-list.txt");
    for (int i = 0; i < 50000; i++) {
        outFile << toSort[i] << endl;
    }
    outFile.close(); // Closing file of sorted numbers*/

    return 0;
}

