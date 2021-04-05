#include <iostream>
#include "splay_tree.h"
#include "splay_tree.cpp"
#include <algorithm>
#include <ostream>
#include<cstring>
using namespace std;

int main(){
    {
        SplayTree<int, double> splaytree;
        splaytree.insert(1,6.66);
        splaytree.insert(2,9.9999);
        splaytree.display();
        splaytree.insert(10,43.2);
        cout << splaytree.find(2) << "\n";
        cout << splaytree.find(6) << "\n";
        splaytree.insert(5,123.1);
        splaytree.display();
    }

    {
        SplayTree<int, int> splaytree;
        splaytree.insert(1,6);
        splaytree.insert(2,9);
        splaytree.display();
        splaytree.insert(10,43);
        cout << splaytree.find(2) << "\n";
        cout << splaytree.find(6) << "\n";
        splaytree.insert(5,123);
        splaytree.display();
    }
    
    {
        SplayTree<string, int> splaytree;
        splaytree.insert("hi",1);
        splaytree.insert("there",2);
        splaytree.display();
        splaytree.insert("hey",2);
        cout << splaytree.find("there") << "\n";
        cout << splaytree.find("hola") << "\n";
        splaytree.insert("hello",5);
        splaytree.display();
    }

    {
        SplayTree<int, string> splaytree;
        splaytree.insert(1,"h");
        splaytree.insert(2,"there");
        splaytree.display();
        splaytree.insert(10,"hey");
        cout << splaytree.find(2) << "\n";
        cout << splaytree.find(6) << "\n";
        splaytree.insert(5,"hello");
        splaytree.display();
    }
    return 0;
}