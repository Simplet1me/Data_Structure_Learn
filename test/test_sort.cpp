#include "console.hpp"
#include "sort.hpp"
#include "random.hpp"

int main(){
    console_init();
    auto arr = getRandomArr(0,30,10);

    // swap test

    // printVector(arr,color::Type::Blue);
    // swap(&arr[1],&arr[2]);
    // printVector(arr,color::Type::Green);
    
    
    // bubbleSort test

    // printVector(arr,color::Type::Blue);
    // bubbleSort(arr);
    // printVector(arr,color::Type::Green);


    // selectSort test
    
    // printVector(arr,color::Type::Blue);
    // selectSort(arr);
    // printVector(arr,color::Type::Green);


    // insertSort test

    // printVector(arr,color::Type::Blue);
    // insertSort(arr);
    // printVector(arr,color::Type::Green);

    // seerSort test
    // printVector(arr,color::Type::Blue);
    // seerSort(arr);
    // printVector(arr,color::Type::Green);

    // quickSort test
    printVector(arr,color::Type::Blue);
    quickSort(arr,0,arr.size()-1);
    printVector(arr,color::Type::Green);
}