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

    int find(T t){
        node<T>* p = head;
        int index = 0;
        while (p != nullptr){
            if(p->value == t){
                return index;
            }
            p = p->next;
            index++;
        }
        return -1;
    }

    void insert(int index,T t){
        node<T>* p = head;
        for (size_t i = 0; i < index; i++){
            p = p->next;
        }
        node<T>* newNode = new node<T>(t,p->next);
        p->next = newNode;
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

    void pop_back(){
        node<T>* p = head;
        // 跑完为倒数第二节点
        while (p->next->next != nullptr){
            p = p->next;
        }

        // 从倒数第二节点自闭合
        p->next = nullptr;
        // 删除倒数第一节点
        delete p->next;

    }

    void pop_front(){
        node<T>* p = head->next;
        delete head;
        head = p;

    }
private:
    node<T>* head;

};

