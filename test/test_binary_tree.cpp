// #include "raylib.h"
#include "binary_tree.hpp"
#include "console.hpp"
#include <string>

int main(){

    Binary_Tree<std::string> bt("A");

    bt.init();

    auto pre = bt.preOrder();

    printVector(pre,color::Type::Blue);

    auto in = bt.inOrder();

    printVector(in,color::Type::Green);

    auto post = bt.postOrder();

    printVector(post,color::Type::Yellow);

    auto level = bt.levelOrder();

    printVector(level,color::Type::Red);
}