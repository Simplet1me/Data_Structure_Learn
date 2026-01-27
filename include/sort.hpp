#include "console.hpp"

template <typename T>
void swap(T *t1,T *t2){
    T temp;
    temp = *t1;
    *t1 = *t2;
    *t2 = temp;
}

/*
1.冒泡排序 时间复杂度O(n^2) 空间复杂度O(1)
两层循环，重复遍历
最外层循环用来控制次数
最内层循环用来实际排序
每次循环都会把最大的数排到最后面，因此内层循环到上层次数就可以了
-1是因为边界问题，会引用到数组长度+1这个不存在的数
所以内层索引为 j - i - 1

这是一种稳定排序，排序后各个元素之间相对位置不会太大变化
*/
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

/*
2.选择排序 时间复杂度O(n^2) 空间复杂度O(1)
两层循环，外层每次循环找出一个相对最小的值放到最前面，第一次找出的为绝对最小值
相对最小值索引每层推后一位
内层循环每次找出外层循环数外相对最小的值
*/
template <typename T>
void selectSort(std::vector<T> &arr){
    size_t min_index;
    for (size_t i = 0; i < arr.size(); i++){
        min_index = i;
        for (size_t j = i; j < arr.size(); j++){
            if(arr[min_index] > arr[j]){
                min_index = j;
            }
        }
        swap(&arr[min_index],&arr[i]);
    }
}


/*
3.插入排序 时间复杂度O(n^2) 空间复杂度O(1)
两层循环，外层每次循环控制索引移动
内层循环每次将左边变为有序，通过逆向冒泡的方法
*/
template <typename T>
void insertSort(std::vector<T> &arr){
    for (size_t i = 0; i < arr.size(); i++){
        for (size_t j = i; j > 0; j--){
            if(arr[j-1] > arr[j]){
                swap(&arr[j-1],&arr[j]);
            }else{
                //默认左边有序，可以优化时间
                break;
            }
        }
    }
}

/*
4.希尔排序 时间复杂度<O(n^2) 空间复杂度O(1)
先找个间隔，间隔隔出来后再通过插入排序进行相对调整
间隔逐个减小，，整个数组相对有序
直至间隔为1，整个数组相对有序，此时整个数组进行插入排序，时间最快
*/
template <typename T>
void seerSort(std::vector<T> &arr){
    int h = 1;
    while (h < arr.size()/3){
        h = 3 * h + 1;
    }

    for (; h >= 1; h = h / 3){
        for (size_t i = h; i < arr.size(); i++){
            for (size_t j = i; j >= h; j-=h){
                if(arr[j-1] > arr[j]){
                    swap(&arr[j-1],&arr[j]);
                }else{
                    //默认左边有序，可以优化时间
                    break;
                }
            }
        }
    }
}