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

    splaytree.insert(pair<int,int>(3,30));
    splaytree.insert(pair<int,int>(4,40));
    {
        cout << "------------------------------------------------------\n";
        auto first = begin(splaytree);
        auto last = end(splaytree);

        auto mypair = pair<int,int>(2,20);
        while(first != last){
            if(*first == mypair)
                cout << "found == "<<(*first).first << " - " << (*first).second  << "\n";
            ++first;
        }
        cout << "------------------------------------------------------\n";
    }
    {
        cout << "------------------------------------------------------\n";
        auto first = begin(splaytree);
        auto last = end(splaytree);

        auto mypair = pair<int,int>(2,20);

        auto it = find(first, last, mypair);
        if(it == last){
            cout << "Element not found\n";
        }else{
            cout<<(*it).first << " - " << (*it).second  << "\n";
        }
        cout << "------------------------------------------------------\n";
    }
    {
        cout << "------------------------------------------------------\n";
        splaytree.erase(2);
        auto first = begin(splaytree);
        auto last = end(splaytree);

        auto mypair = pair<int,int>(2,20);

        auto it = find(first, last, mypair);
        if(it == last){
            cout << "Element not found\n";
        }else{
            cout<<(*it).first << " - " << (*it).second  << "\n";
        }
        cout << "------------------------------------------------------\n";
    }
    //dtor
    return 0;
}