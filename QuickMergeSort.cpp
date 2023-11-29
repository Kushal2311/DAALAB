// Assignment 1 , 2 :- 

#include<bits/stdc++.h>
using namespace std;
using namespace std::chrono;

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[low];
    int i = low;
    int j = high;

    while (i < j) {
        while (arr[i] <= pivot && i <= high - 1) {
            i++;
        }

        while (arr[j] > pivot && j >= low + 1) {
            j--;
        }
        if (i < j) swap(arr[i], arr[j]);
    }
    swap(arr[low], arr[j]);
    return j;
}


void quicksort(vector<int> &arr, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high);

        quicksort(arr, low, pivotIndex - 1);
        quicksort(arr, pivotIndex + 1, high);
    }
}

// Mergesort implementation
void merge(vector<int> &arr, int low, int mid, int high) {
    vector<int> temp; 
    int left = low;      
    int right = mid + 1;   

    

    while (left <= mid && right <= high) {
        if (arr[left] <= arr[right]) {
            temp.push_back(arr[left]);
            left++;
        }
        else {
            temp.push_back(arr[right]);
            right++;
        }
    }

   

    while (left <= mid) {
        temp.push_back(arr[left]);
        left++;
    }

    while (right <= high) {
        temp.push_back(arr[right]);
        right++;
    }

    
    for (int i = low; i <= high; i++) {
        arr[i] = temp[i - low];
    }
}

void mergeSort(vector<int> &arr, int low, int high) {
    if (low >= high) return;
    int mid = (low + high) / 2 ;
    mergeSort(arr, low, mid);  
    mergeSort(arr, mid + 1, high); 
    merge(arr, low, mid, high);  
}

int main() {
   
    vector<int> values_to_sort;
    srand(static_cast<unsigned>(time(0)));
    for (int i = 0; i < 500; ++i) {
        values_to_sort.push_back(rand() % 1000);
    }

   
    vector<int> values_for_mergesort = values_to_sort;

 
    auto start_time_quicksort = high_resolution_clock::now();
    quicksort(values_to_sort, 0, values_to_sort.size() - 1);
    auto end_time_quicksort = high_resolution_clock::now();
    auto duration_quicksort = duration_cast<nanoseconds>(end_time_quicksort - start_time_quicksort);

    
    auto start_time_mergesort = high_resolution_clock::now();
    mergeSort(values_for_mergesort, 0, values_for_mergesort.size() - 1);
    auto end_time_mergesort = high_resolution_clock::now();
    auto duration_mergesort = duration_cast<nanoseconds>(end_time_mergesort - start_time_mergesort);

    
    cout << "Quicksort - Sorted values: ";
    for (int val : values_to_sort) {
        cout << val << " ";
    }
    cout << "\nTime taken for Quicksort: " << duration_quicksort.count() << " nanoseconds" << endl;

    cout << "\nMergesort - Sorted values: ";
    for (int val : values_for_mergesort) {
        cout << val << " ";
    }
    cout << "\nTime taken for Mergesort: " << duration_mergesort.count() << " nanoseconds" << endl;
   
    return 0;
}

