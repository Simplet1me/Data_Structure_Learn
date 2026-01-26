#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>


int getRand(int min, int max);

std::vector<int> getRandomArr(int min,int max,int length){
    std::vector<int> arr;
    srand(0);
    for(int i = 0;i<length;i++){
        arr.push_back(getRand(min,max));
    }
    return arr;
}

int getRand(int min,int max){
    return (rand() % (max - min + 1) + min);
}