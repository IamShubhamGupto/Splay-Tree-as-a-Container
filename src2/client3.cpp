#include <iostream>
#include <algorithm>
#include <utility>
#include "splay_tree.h"
#include "splay_tree.cpp"
using namespace std;
int main(){

    SplayTree<int, int> splaytree;

    splaytree.insert({1,10});
    splaytree.insert(pair<int,int>(2,20));
    splaytree.insert(pair<int,int>(3,30));
    splaytree.insert(pair<int,int>(4,40));
    

    cout << "Tree after insertions\n";

    splaytree.printTree();

    auto first = splaytree.cbegin();
    auto last = splaytree.cend();
    while(first != last){
        cout << (*first).first << " - " << (*first).second  << "\n";
        ++first;
    }

    return 0;
}