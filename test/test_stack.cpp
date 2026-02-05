#include "console.hpp"
#include "stack.hpp"

int main() {
    console_init();
    Stack<std::string> s;
    s.push("aaa");
    s.push("bbb");
    s.push("ccc");
    s.push("ddd");

    s.list();

    println(s.top());

    println("pop");
    s.pop();

    s.list();
    println(s.top());

    println(s.isEmpty());

    s.pop();
    s.pop();
    s.pop();

    println(s.isEmpty());

}
