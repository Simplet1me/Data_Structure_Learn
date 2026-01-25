#include "console.h"
#include "stack.h"
#include <iostream>
#include <string>

int main() {
    console_init();

    Stack s;
    s.push(1);
    s.push(2);

    
    print(s.top(),color::Type::Green);
    std::cout << "\033[32m" << s.top() << "\033[0m\n";
    s.pop();
    std::cout << s.top() << "\n";

    return 0;
}
