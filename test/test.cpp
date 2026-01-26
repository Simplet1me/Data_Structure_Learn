#include <iostream>
#include "console.hpp"
#include "random.hpp"

int main(){
    console_init();
    // int arr_in[] = {5,6,7,8,9,5,3,2,1};
    // int arr_in_leng = std::size(arr_in);
    std::vector<int> arr = getRandomArr(0,100,50);

    printVector(arr);

    int max = arr[0];
    for(auto &p : arr){
        if (max <= p){
            max = p;
        }
    }

    println(max,color::Type::Green);
}