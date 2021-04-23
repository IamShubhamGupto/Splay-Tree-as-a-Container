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
    //find()
    //Iterator()
    //splayTheTree()
    {
        cout << "------------------------------------------------------\n";
        auto it = splaytree.find(2);
        // operator*
        cout << (*it).first << " - " << (*it).second <<"\n";
        cout << "------------------------------------------------------\n";
        cout << "------------------------------------------------------\n";
        it = splaytree.find(10);
        //operator !=
        //end()
        if(it != splaytree.end()){
            cout << (*it).first << " - " << (*it).second  << "\n";
        }else{
            cout << "Element not found\n";
        }
        cout << "------------------------------------------------------\n";
    }
    {
        cout << "------------------------------------------------------\n";
        auto first = splaytree.begin();
        auto last = splaytree.end();

        auto mypair = pair<int,int>(2,20);
        while(first != last){
            if(*first == mypair)
                cout << "found == "<<(*first).first << " - " << (*first).second  << "\n";
            ++first;
        }
        cout << "------------------------------------------------------\n";
    }
    
    //dtor
    return 0;
}