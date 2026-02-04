#include "heap.hpp"
#include "random.hpp"

int main(){
    console_init();

    Min_Heap<int> minHeap;
    Max_Heap<int> maxHeap;

    auto vec = getRandomArr(0,100,20);

    printVector(vec,color::Type::Blue);

    for (auto &p : vec){
        minHeap.pq.push(p);
        maxHeap.pq.push(p);
    }

    minHeap.list();
    maxHeap.list();

    
    minHeap.pq.pop();
    maxHeap.pq.pop();

    minHeap.list();
    maxHeap.list();

}