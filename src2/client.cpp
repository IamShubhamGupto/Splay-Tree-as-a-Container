#include <iostream>
#include <algorithm>
#include <utility>
#include "splay_tree.h"
#include "splay_tree.cpp"
using namespace std;
int main(){
    //ctor
    SplayTree<int, int> splaytree;
    //insert()
    //splayTheTree()
    splaytree.insert({1,10});
    splaytree.insert(pair<int,int>(2,20));
    //find()
    //Iterator()
    //splayTheTree()
    auto it = splaytree.find(2);
    // operator*
    cout << (*it).first << " - " << (*it).second <<"\n";
    it = splaytree.find(10);
    //operator !=
    //end()
    if(it != splaytree.end()){
        cout << (*it).first << " - " << (*it).second  << "\n";
    }else{
        cout << "Element not found\n";
    }
    //operator--()
    --it;
    //operator*
    cout << (*it).first << " - " << (*it).second  << "\n";
    //dtor
    return 0;
}