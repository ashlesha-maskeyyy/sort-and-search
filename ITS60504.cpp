#include <iostream>
#include <algorithm>
#include <chrono>
#include <cstdlib>  
#include <ctime>   

using namespace std;
using namespace chrono;

// function to generate random array with allowed repetition


void generateRandomArray(int arr[], int n){

    srand(time(0));  
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 99 + 1; 
    }
}

// Merge Sort

// Function to create merge
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int L[150], R[150];

    for (int i = 0; i < n1; i++) 
    L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) 
    R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Quick Sort
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high){
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Binary Search
int binarySearch(int arr[], int n, int key) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (arr[mid] == key) return mid;
        else if (arr[mid] < key) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

// Exponential Search
int exponentialSearch(int arr[], int n, int key) {
    if (arr[0] == key) return 0;

    int i = 1;
    while (i < n && arr[i] <= key)
        i = i * 2;

    int low = i / 2;
    int high = min(i, n - 1);
    while (low <= high) {
        int mid = (low + high) / 2;
        if (arr[mid] == key) return mid;
        else if (arr[mid] < key) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

// Display Array
void displayArray(int arr[], int n) {
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
}

// MAIN
int main() {
    int n;
    cout << "Enter number of elements (max 150): ";
    cin >> n;
    if (n < 1 || n > 150) {
        cout << "Invalid input!" << endl;
        return 1;
    }

    int arr[150];
    generateRandomArray(arr, n);

    cout << "\nRandom array:\n";
    displayArray(arr, n);

    // Merge Sort
    int mergeArr[150];
    copy(arr, arr + n, mergeArr);
    auto start = high_resolution_clock::now();
    mergeSort(mergeArr, 0, n - 1);
    auto stop = high_resolution_clock::now();
    cout << "\nArray after Merge Sort:\n";
    displayArray(mergeArr, n);
    cout << "\nMerge Sort time: " << duration_cast<nanoseconds>(stop - start).count() << " nanoseconds\n";

    // Quick Sort
    int quickArr[150];
    copy(arr, arr + n, quickArr);
    start = high_resolution_clock::now();
    quickSort(quickArr, 0, n - 1);
    stop = high_resolution_clock::now();
    cout << "\nArray after Quick Sort:\n";
    displayArray(quickArr, n);
    cout << "\nQuick Sort time: " << duration_cast<nanoseconds>(stop - start).count() << " nanoseconds\n";

    // Search key input
    int key;
    cout << "\nEnter number to search: ";
    cin >> key;

    // Binary Search
    start = high_resolution_clock::now();
    int binaryIndex = binarySearch(quickArr, n, key);
    stop = high_resolution_clock::now();
    cout << "\nBinary Search result: ";
    if (binaryIndex != -1)
        cout << "Found at index " << binaryIndex << endl;
    else
        cout << "Not found.\n";
    cout << "\nBinary Search time: " << duration_cast<nanoseconds>(stop - start).count() << " nanoseconds\n";

    // Exponential Search
    start = high_resolution_clock::now();
    int expoIndex = exponentialSearch(quickArr, n, key);
    stop = high_resolution_clock::now();
    cout << "\nExponential Search result: ";
    if (expoIndex != -1)
        cout << "Found at index " << expoIndex << endl;
    else
        cout << "Not found.\n";
    cout << "\nExponential Search time: " << duration_cast<nanoseconds>(stop - start).count() << " nanoseconds\n";

    return 0;
}



