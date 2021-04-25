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
    
    #if 0
    cout << "\nConstant Iterator demo\n";
    auto first = splaytree.cbegin();
    auto last = splaytree.cend();
    while(first != last){
        (*first).second += 2;
        ++first;
    }
    #endif
    #if 0
    cout << "\nConstant Iterator demo\n";
    auto first = splaytree.cbegin();
    auto last = splaytree.cend();
    while(first != last){
        cout << (*first).first << " - " << (*first).second  << "\n";
        ++first;
    }
    #endif
    #if 1
    cout << "\nConstant Reverse Iterator demo\n";
    auto first = splaytree.crbegin();
    auto last = splaytree.crend();
    while(first != last){
        cout << (*first).first << " - " << (*first).second  << "\n";
        ++first;
    }
    #endif
    return 0;
}