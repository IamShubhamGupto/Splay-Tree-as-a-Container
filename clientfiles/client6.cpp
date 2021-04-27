#include <iostream>
#include <algorithm>
#include <utility>
#include "../src/splay_tree.h"
#include "../src/splay_tree.cpp"
using namespace std;

int main(){
    SplayTree<int, int> splaytree;
    //insert()
    //splayTheTree()
    splaytree.insert({1,10});
    splaytree.insert(pair<int,int>(2,20));

    splaytree.insert(pair<int,int>(3,30));
    splaytree.insert(pair<int,int>(4,40));
    
    auto first = splaytree.rbegin();
    auto last = splaytree.rend();
    
    while(first != last){
        cout<<(*first).first << " - " << (*first).second  << "\n";
        ++first;
    }
    return 0;
}