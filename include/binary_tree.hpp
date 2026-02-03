#include <vector>
#include "queue.hpp"

template <typename T>
struct treenode{
    T value;
    treenode* left;
    treenode* right;
    treenode() : left(nullptr),right(nullptr){}
    treenode(T value) : value(value),left(nullptr),right(nullptr){}
    treenode(T value,treenode* left) : value(value),left(left),right(nullptr){}
    treenode(T value,treenode* left,treenode* right) : value(value),left(left),right(right){}
};

template <typename T>
class Binary_Tree{
public:
    Binary_Tree(T value){
        father_node = new treenode<T>(value);
        father_node->left = nullptr;
        father_node->right = nullptr;
    }

    std::vector<T> preOrder(){
        std::vector<T> vec;
        preOrder(father_node,vec);
        return vec;
    }


    std::vector<T> inOrder(){
        std::vector<T> vec;
        inOrder(father_node,vec);
        return vec;
    }
    
    std::vector<T> postOrder(){
        std::vector<T> vec;
        postOrder(father_node,vec);
        return vec;
    }

    //层序遍历 每层从左往右
    //基本思路，从上往下，从左往右依次入队，先进先出，每次提出来的值都是上层的左右子，直至最后一层
    std::vector<T> levelOrder(){
        Queue<treenode<T>*> queue;
        std::vector<T> vec;
        queue.push(father_node);
        while (!queue.isEmpty()){
            treenode<T>* node = queue.top();
            vec.push_back(node->value);
            queue.pop();
            if (node->left != nullptr){
                queue.push(node->left);
            }
            if (node->right != nullptr){
                queue.push(node->right);
            }
        }
        return vec;
    }


    


    void init(){
        father_node = new treenode<std::string>("A");
        treenode<std::string>* l = new treenode<std::string>("B");
        treenode<std::string>* r = new treenode<std::string>("C");
        treenode<std::string>* ll = new treenode<std::string>("D");
        treenode<std::string>* lr = new treenode<std::string>("E");
        treenode<std::string>* rl = new treenode<std::string>("F");
        treenode<std::string>* llr = new treenode<std::string>("H");

        father_node->left = l;
        father_node->left->left = ll;
        father_node->left->right = lr;
        father_node->left->left->right = llr;
        father_node->right = r;
        father_node->right->left = rl;
    }

private:
    treenode<T>* father_node;

    //前序遍历 根左右
    void preOrder(treenode<T>* root,std::vector<T> &vec){
        if (root != nullptr){
            vec.push_back(root->value);
            preOrder(root->left,vec);
            preOrder(root->right,vec);
        }
    }

    //中序遍历 左根右
    void inOrder(treenode<T>* root,std::vector<T> &vec){
        if(root != nullptr){
            inOrder(root->left,vec);
            vec.push_back(root->value);
            inOrder(root->right,vec);
        }
    }

    //后序遍历 左右根
    void postOrder(treenode<T>* root,std::vector<T> &vec){
        if(root != nullptr){
            postOrder(root->left,vec);
            postOrder(root->right,vec);
            vec.push_back(root->value);
        }
    }
};
