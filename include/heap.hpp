#include <queue>
#include <vector>
#include "console.hpp"

template <typename T>
struct compareMin {
    bool operator()(T a, T b) {
        return a > b; // 这里定义了最小堆
    }
};

template <typename T>
struct compareMax {
    bool operator()(T a, T b) {
        return a < b; // 这里定义了最大堆
    }
};

template <typename T>
class Min_Heap{
public:
    std::priority_queue<T,std::vector<T>,compareMin<T>> pq;

    void list(){
        print("[");

        auto temp = pq;
        bool first = true;
        while (!temp.empty()){
            if (!first) { print(","); }
            print(temp.top(),color::Type::Green);
            first = false;
            temp.pop();
        }
        println("]");
    }
};



template <typename T>
class Max_Heap{
public:
    std::priority_queue<T,std::vector<T>,compareMax<T>> pq;

    void list(){
            print("[");

            auto temp = pq;
            bool first = true;
            while (!temp.empty()){
                if (!first) { print(","); }
                print(temp.top(),color::Type::Green);
                first = false;
                temp.pop();
            }
        println("]");
        }
};