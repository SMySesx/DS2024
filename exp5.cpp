#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <vector>
using namespace std;

// 1. 起泡排序
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// 2. 插入排序
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// 3. 选择排序
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}

// 4. 归并排序辅助函数，合并两个已排序的子数组
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; ++i) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; ++j) {
        R[j] = arr[mid + 1 + j];
    }
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }
    while (i < n1) {
        arr[k++] = L[i++];
    }
    while (j < n2) {
        arr[k++] = R[j++];
    }
}

// 4. 归并排序
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// 5. 快速排序辅助函数，划分操作
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// 5. 快速排序
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// 6. 堆排序辅助函数，维护最大堆性质
void maxHeapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && arr[l] > arr[largest]) {
        largest = l;
    }
    if (r < n && arr[r] > arr[largest]) {
        largest = r;
    }
    if (largest!= i) {
        swap(arr[i], arr[largest]);
        maxHeapify(arr, n, largest);
    }
}

// 6. 堆排序
void heapSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; --i) {
        maxHeapify(arr, n, i);
    }
    for (int i = n - 1; i > 0; --i) {
        swap(arr[0], arr[i]);
        maxHeapify(arr, i, 0);
    }
}

// 生成随机序列
vector<int> generateRandomArray(int size) {
    vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = rand();
    }
    return arr;
}

// 生成顺序序列
vector<int> generateAscendingArray(int size) {
    vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = i;
    }
    return arr;
}

// 生成逆序序列
vector<int> generateDescendingArray(int size) {
    vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = size - i;
    }
    return arr;
}

// 测试函数，计算排序花费时间
void testSortingAlgorithm(void (*sortFunc)(vector<int>&), const vector<int>& arr, string algoName) {
    vector<int> testArr = arr;
    clock_t start = clock();
    sortFunc(testArr);
    clock_t end = clock();
    double timeTaken = double(end - start) / CLOCKS_PER_SEC;
    cout << algoName << " took " << timeTaken << " seconds." << endl;
}

int main() {
    int arraySize = 10000;  // 可以调整数组大小来进一步观察性能差异

    // 顺序序列测试
    vector<int> ascendingArray = generateAscendingArray(arraySize);
    cout << "Testing on ascending array:" << endl;
    testSortingAlgorithm(bubbleSort, ascendingArray, "Bubble Sort");
    testSortingAlgorithm(insertionSort, ascendingArray, "Insertion Sort");
    testSortingAlgorithm(selectionSort, ascendingArray, "Selection Sort");
    vector<int> mergeSortAscending = ascendingArray;
    testSortingAlgorithm([](vector<int>& arr) { mergeSort(arr, 0, arr.size() - 1); }, mergeSortAscending, "Merge Sort");
    vector<int> quickSortAscending = ascendingArray;
    testSortingAlgorithm([](vector<int>& arr, int low = 0, int high = arr.size() - 1) { quickSort(arr, low, high); }, quickSortAscending, "Quick Sort");
    vector<int> heapSortAscending = ascendingArray;
    testSortingAlgorithm(heapSort, heapSortAscending, "Heap Sort");
    cout << endl;

    // 逆序序列测试
    vector<int> descendingArray = generateDescendingArray(arraySize);
    cout << "Testing on descending array:" << endl;
    testSortingAlgorithm(bubbleSort, descendingArray, "Bubble Sort");
    testSortingAlgorithm(insertionSort, descendingArray, "Insertion Sort");
    testSortingAlgorithm(selectionSort, descendingArray, "Selection Sort");
    vector<int> mergeSortDescending = descendingArray;
    testSortingAlgorithm([](vector<int>& arr) { mergeSort(arr, 0, arr.size() - 1); }, mergeSortDescending, "Merge Sort");
    vector<int> quickSortDescending = descendingArray;
    testSortingAlgorithm([](vector<int>& arr, int low = 0, int high = arr.size() - 1) { quickSort(arr, low, high); }, quickSortDescending, "Quick Sort");
    vector<int> heapSortDescending = descendingArray;
    testSortingAlgorithm(heapSort, heapSortDescending, "Heap Sort");
    cout << endl;

    // 随机序列测试
    vector<int> randomArray = generateRandomArray(arraySize);
    cout << "Testing on random array:" << endl;
    testSortingAlgorithm(bubbleSort, randomArray, "Bubble Sort");
    testSortingAlgorithm(insertionSort, randomArray, "Insertion Sort");
    testSortingAlgorithm(selectionSort, randomArray, "Selection Sort");
    vector<int> mergeSortRandom = randomArray;
    testSortingAlgorithm([](vector<int>& arr) { mergeSort(arr, 0, arr.size() - 1); }, mergeSortRandom, "Merge Sort");
    vector<int> quickSortRandom = randomArray;
    testSortingAlgorithm([](vector<int>& arr, int low = 0, int high = arr.size() - 1) { quickSort(arr, low, high); }, quickSortRandom, "Quick Sort");
    vector<int> heapSortRandom = randomArray;
    testSortingAlgorithm(heapSort, heapSortRandom, "Heap Sort");

    return 0;
}