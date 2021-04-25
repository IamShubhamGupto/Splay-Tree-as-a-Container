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
    splaytree.insert(pair<int,int>(5,50));

    cout<< "\ndisplaying tree\n";
    splaytree.printTree();
    
    cout<< "\nPrinting first to last\n";
    {
        auto first = splaytree.begin();
        auto last = splaytree.end();
        while(first != last){
            cout << first->first << " - " << first->second  << "\n";
            ++first;
        }
    }
    
    cout<< "\nPrinting last to first\n";
    {
        auto first = splaytree.rbegin();
        auto last = splaytree.rend();
        while(first != last){
            cout << first->first << " - " << first->second  << "\n";
            ++first;
        }
    }

    cout << "splaytree[3] = " << splaytree[3] << "\n";

    splaytree[3] *= 2;

    cout << "splaytree[3] = " << splaytree[3] << "\n";

    cout<< "\ndisplaying tree\n";
    splaytree.printTree();

    return 0;
}