#include <vector>
#include <string>

struct pair{
    int key;
    std::string value;
    pair(int key,std::string value) : key(key),value(value){}
};

class Hash_Table{
    public:
    Hash_Table();
    ~Hash_Table();

    void put(int key,std::string value);
    std::string get(int key); 
    void del(int key);
    void listKey();
    void listVal();
    void listTable();
    
    private:
    std::vector<pair *> hash_table;
};
