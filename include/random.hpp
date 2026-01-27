#include <vector>
#include <random>

int getRand(int min,int max){
    // return (rand() % (max - min + 1) + min);
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> distrib(min, max);
    return distrib(gen);
}



std::vector<int> getRandomArr(int min,int max,int length){
    std::vector<int> arr;
    for(int i = 0;i<length;i++){
        arr.push_back(getRand(min,max));
    }
    return arr;
}
