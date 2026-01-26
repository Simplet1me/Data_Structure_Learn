#include "console.hpp"
#include "sort.hpp"
#include "random.hpp"

int main(){
    console_init();

    // swap test

    // std::vector<int> arr = {1,2,3,4};
    // printVector(arr);
    // swap(&arr[1],&arr[2]);
    // printVector(arr);
    
    
    // bubbleSort test

    auto arr = getRandomArr(0,20,10);
    printVector(arr);
    bubbleSort(arr);
    printVector(arr);

}