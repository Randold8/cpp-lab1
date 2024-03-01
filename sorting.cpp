#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

// Функция для обмена двух элементов
template <typename T>
void swap(T* a, T* b) {
    T t = *a;
    *a = *b;
    *b = t;
}
template <typename T>
void generateRandomVector(std::vector<T>& arr, int size) {
    arr.clear(); 
    arr.reserve(size); // Резервируем память для улучшения производительности
    for (int i = 0; i < size; i++) {
        arr.push_back(rand() % 100000);
    }
}

// Функция для рандомизированного выбора опорного элемента
template <typename T>
int randomizedPartition(std::vector<T>& arr, int low, int high) {
    srand(time(NULL));
    int randomIndex = low + rand() % (high - low);

    swap(&arr[randomIndex], &arr[high]);

    T pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++; 
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// Функция для реализации QuickSort
template <typename T>
void quickSort(std::vector<T>& arr, int low, int high) {
    if (low < high) {
        int pi = randomizedPartition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
// Функция для реализации selectionSort
template <typename T>
void selectionSort(std::vector<T>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        swap(&arr[min_idx], &arr[i]);
    }
}
// Функция для сортировки Bucket Sort
template <typename T>
void bucketSort(std::vector<T>& arr) {
    T maxVal = *max_element(arr.begin(), arr.end());
    T minVal = *min_element(arr.begin(), arr.end());
    T bucketRange = (maxVal - minVal) / arr.size() + 1; 

    std::vector<std::vector<T>> buckets(arr.size());

    for (int i = 0; i < arr.size(); i++) {
        int bucketIdx = (arr[i] - minVal) / bucketRange;
        buckets[bucketIdx].push_back(arr[i]);
    }
    int idx = 0;
    for (int i = 0; i < buckets.size(); i++) {
        std::sort(buckets[i].begin(), buckets[i].end()); 
        for (int j = 0; j < buckets[i].size(); j++) {
            arr[idx++] = buckets[i][j];
        }
    }
}

// Вспомогательная функция для вывода массива на экран
template <typename T>
void printArray(const std::vector<T>& arr) {
    for (const T& val : arr) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

int main() {
    srand(time(NULL));

    // Размеры массивов для тестирования
    std::vector<int> sizes = {10, 100, 1000, 10000, 100000};
    for (int size : sizes) {
        std::vector<int> arr;
        generateRandomVector(arr, size);

        // Создаем копии массива для каждого алгоритма сортировки
        std::vector<int> arrForQuickSort = arr;
        std::vector<int> arrForSelectionSort = arr;
        std::vector<int> arrForBucketSort = arr;

        // QuickSort
        clock_t startQuickSort = clock();
        quickSort(arrForQuickSort, 0, arrForQuickSort.size() - 1);
        clock_t endQuickSort = clock();
        double elapsedQuickSort = double(endQuickSort - startQuickSort) / CLOCKS_PER_SEC;

        // SelectionSort
        clock_t startSelectionSort = clock();
        selectionSort(arrForSelectionSort);
        clock_t endSelectionSort = clock();
        double elapsedSelectionSort = double(endSelectionSort - startSelectionSort) / CLOCKS_PER_SEC;

        // BucketSort
        clock_t startBucketSort = clock();
        bucketSort(arrForBucketSort);
        clock_t endBucketSort = clock();
        double elapsedBucketSort = double(endBucketSort - startBucketSort) / CLOCKS_PER_SEC;

        // Выводим размер массива и время выполнения для каждого алгоритма
        std::cout << "Array size: " << size << std::endl;
        std::cout << "QuickSort Time: " << elapsedQuickSort << " seconds." << std::endl;
        std::cout << "SelectionSort Time: " << elapsedSelectionSort << " seconds." << std::endl;
        std::cout << "BucketSort Time: " << elapsedBucketSort << " seconds." << std::endl;
        std::cout << "---------------------------------" << std::endl;
    }

    return 0;
}