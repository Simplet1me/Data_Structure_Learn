#pragma once

class Stack {
public:
    Stack();
    ~Stack();

    void push(int value);
    void pop();
    int top() const;
    bool empty() const;

private:
    int data_[100];
    int top_;
};
