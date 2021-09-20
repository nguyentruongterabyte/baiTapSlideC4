#include <stdio.h>      /* printf */
#include <stdlib.h> /* qsort */
#include <iostream>
#include<utility>

using namespace std;


int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int left = 0;
    int right = high - 1;
    while (true) {
        while (left <= right && arr[left] < pivot) left++;
        while (right >= left && arr[right] > pivot) right--; if (left >= right) break;
        swap(arr[left], arr[right]);
        left++;
        right--;
    }
    swap(arr[left], arr[high]);
    return left;
}


void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
void printArray(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        cout <<*(arr + i) <<" ";
    }
}

int compare(const void* p1, const void* p2) {
    return (*(int*)p2 - *(int*)p1);
}
int main() {
   
    int values[] = { 1, 10, 9, 4, 8, 7, 6, 7, 5, 4 };
    qsort(values, 10, sizeof(int), compare);
    
    printArray(values, 10);
    return 0;
}