#include <vector>

template <typename T>
class Stack{
public:

    void push(T a){
        stack.push_back(a);
    }

    void pop(){
        stack.pop_back();
    }

    void list(){
        printVector(stack);
    }

    T top(){
        return stack[stack.size() - 1];
    }

    bool isEmpty(){
        return stack.empty();
    }

private:
    std::vector<T> stack;
};
