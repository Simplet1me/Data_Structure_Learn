#include <string>
#include "queue.hpp"
#include "console.hpp"

int main(){
    console_init();

    Queue<std::string> q;
    q.push("aaa");
    q.push("bbb");
    q.push("ccc");
    q.push("ddd");

    printVector(q.list(),color::Type::Green);

    println(q.top(),color::Type::Red);

    println("pop",color::Type::Yellow);

    q.pop();

    printVector(q.list(),color::Type::Green);

    println(q.top(),color::Type::Red);

    q.pop();
    q.pop();
    q.pop();

    println(q.isEmpty());


}