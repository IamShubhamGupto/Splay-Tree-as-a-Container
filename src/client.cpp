#include <iostream>
#include "splay_tree.h"
#include "splay_tree.cpp"
#include <algorithm>
#include <ostream>
using namespace std;

int main(){
    SplayTree<int, double> splaytree;
    splaytree.insert(1,6.66);
    splaytree.insert(2,9.9999);
    splaytree.display();
    splaytree.insert(10,43.2);
    cout << splaytree.find(2) << "\n";
    splaytree.insert(5,123.1);
    splaytree.display();
    return 0;
}