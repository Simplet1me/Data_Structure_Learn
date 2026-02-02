#include "hash_table.hpp"
#include "console.hpp"

Hash_Table::Hash_Table(){
    hash_table = std::vector<pair *>(100);
}

Hash_Table::~Hash_Table(){
    for (const auto& p : hash_table){
        delete p;
    }
    hash_table.clear();
}

void Hash_Table::put(int key,std::string value){
    pair* p = new pair(key,value);
    hash_table[key] = p;
}

std::string Hash_Table::get(int key){
    pair* p = hash_table[key];
    if (p == nullptr){
        return "";
    }
    return p->value;
}

void Hash_Table::del(int key){
    delete hash_table[key];
    hash_table[key] = nullptr;
}

void Hash_Table::listKey(){
    for(const auto& p : hash_table){
        if(p != nullptr)
        println(p->key,color::Type::Blue);
    }
}

void Hash_Table::listVal(){
    for(const auto& p : hash_table){
        if(p != nullptr)
        println(p->value,color::Type::Green);
    }
}

void Hash_Table::listTable(){
    for(const auto& p : hash_table){
        if(p != nullptr){
            print(p->key,color::Type::Blue);
            print(" = ");
            println(p->value,color::Type::Green);
        }
    }
}

