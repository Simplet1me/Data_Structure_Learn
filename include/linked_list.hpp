#include "console.hpp"

template <typename T>
struct node{
    T value;
    node* next;
    node() : next(nullptr){}
    node(T t) : value(t),next(nullptr){}
    node(T t,node* node) : value(t),next(node){}
};


template <typename T>
class linked_list{
public:
    linked_list() : head(){};
    linked_list(T t) : head(new node<T>(t)){};
    ~linked_list(){
        while (head != nullptr){
            node<T>* temp = head;
            head = head->next;
            delete temp;
        }
        
    }

    void setHead(T t){
        head->value = t;
    }

    void push_back(T t){
        node<T>* newNode = new node<T>(t);

        // 创建临时变量p，向后遍历链表，跑完循环即找到末尾节点，此时末尾节点指向为空
        node<T>* p = head;
        while (p->next != nullptr){
            p = p->next;
        }

        p->next = newNode;
        
    }

    void push_front(T t){
        node<T>* newNode = new node<T>(t,head);
        head = newNode;
    }

    void list(){
        node<T>* p = head;
        //跑完循环p为nullptr
        while (p != nullptr){
            print(p->value,color::Type::Green);
            print("->");
            p = p->next;
        }
        println("nullptr",color::Type::Blue);
    }

private:
    node<T>* head;

};

