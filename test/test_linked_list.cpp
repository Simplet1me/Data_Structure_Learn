#include "linked_list.hpp"

int main(){
    console_init();

    linked_list<int> linklist(1);

    linklist.list();

    linklist.push_back(2);
    linklist.push_back(3);
    linklist.push_back(4);

    linklist.list();

    linklist.push_front(6);

    linklist.list();


}