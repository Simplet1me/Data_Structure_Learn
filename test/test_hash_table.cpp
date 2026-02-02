#include "hash_table.hpp"
#include "console.hpp"

int main(){
    console_init();

    Hash_Table ht;

    ht.put(1,"a");
    ht.put(2,"b");
    ht.put(3,"c");
    ht.put(4,"d");
    ht.put(5,"e");
    ht.put(7,"r");
    ht.put(9,"g");
    ht.put(11,"h");

    ht.listTable();

    println(ht.get(5));

    ht.del(5);

    println(ht.get(5));

    ht.listTable();
}