#include <vector>
#include "console.hpp"

template <typename T>
class Queue{
public:
    void push(T a){
        queue.push_back(a);
    }

    void pop(){
        queue.erase(queue.begin() + 0);
    }

    void list(){
        printVector(queue,color::Type::Blue);
    }

    T top(){
        return queue[0];
    }

    bool isEmpty(){
        return queue.empty();
    }
private:
    std::vector<T> queue;
};
