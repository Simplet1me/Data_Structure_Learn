#include "linked_list.hpp"

int main(){
    console_init();

    Linked_List<int> linklist(1);

    linklist.list();

    linklist.push_back(2);
    linklist.push_back(3);
    linklist.push_back(4);

    linklist.list();

    linklist.push_back(6);

    linklist.list();

    println(linklist.find(2),color::Type::Red);

    linklist.insert(linklist.find(2),114514);

    linklist.list();

    linklist.pop_front();
    linklist.list();

    linklist.pop_back();
    linklist.list();



}