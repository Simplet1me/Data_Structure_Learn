#include <vector>


template <typename T>
void swap(T *t1,T *t2){
    T temp;
    temp = *t1;
    *t1 = *t2;
    *t2 = temp;
}

//1.冒泡排序
template <typename T>
void bubbleSort(std::vector<T> &arr){
    for (size_t i = 0; i < arr.size(); i++){
        for (size_t j = 0; j < arr.size()-i-1; j++){
            if (arr[j] > arr[j+1]){
                swap(&arr[j],&arr[j+1]);
            }
        }
    }
}