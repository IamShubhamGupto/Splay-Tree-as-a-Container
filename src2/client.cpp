#include <iostream>
#include <algorithm>
#include "splay_tree.h"
#include "splay_tree.cpp"
using namespace std;
int main(){
    SplayTree<int, int> splaytree;
    splaytree.insert({1,10});
    splaytree.insert({2,20});

    auto it = splaytree.find(2);
    cout << (*it).first << " - " << (*it).second <<"\n";
    it = splaytree.find(10);
    cout << (*it).first << " - " << (*it).second  << "\n";
    return 0;
}