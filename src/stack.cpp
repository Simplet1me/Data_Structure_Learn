#include "stack.h"
#include <stdexcept>

Stack::Stack() : top_(-1) {}

Stack::~Stack() {}

void Stack::push(int value) {
    data_[++top_] = value;
}

void Stack::pop() {
    if (empty()) {
        throw std::runtime_error("stack is empty");
    }
    --top_;
}

int Stack::top() const {
    if (empty()) {
        throw std::runtime_error("stack is empty");
    }
    return data_[top_];
}

bool Stack::empty() const {
    return top_ == -1;
}
