#include <iostream>
#include <utility>
#include "splay_tree.h"
#include "splay_tree.cpp"
#include <algorithm>
#include <ostream>
#include <cstring>
using namespace std;

int main(){
    {
        SplayTree<int, double> splaytree;
        splaytree.insert({1,6.66});
        splaytree.insert({2,9.9999});
        splaytree.display();
        splaytree.insert({10,43.2});
        cout << splaytree.find(2) << "\n";
        cout << splaytree.find(6) << "\n";
        splaytree.insert({5,123.1});
        cout << "deleting 5" << "\n";
        splaytree.delete_node(5);
        splaytree.display();
    }

    {
        SplayTree<int, int> splaytree;
        splaytree.insert(make_pair(1,6));
        splaytree.insert(make_pair(2,9));
        splaytree.display();
        splaytree.insert(make_pair(10,43));
        cout << splaytree.find(2) << "\n";
        cout << splaytree.find(6) << "\n";
        splaytree.insert(make_pair(5,123));
        cout << "deleting 1" << "\n";
        splaytree.delete_node(1);
        splaytree.display();
    }
    
    {
        SplayTree<string, int> splaytree;
        splaytree.insert(make_pair("hi",1));
        splaytree.insert(make_pair("there",2));
        splaytree.display();
        splaytree.insert(make_pair("hey",2));
        cout << splaytree.find("there") << "\n";
        cout << splaytree.find("hola") << "\n";
        splaytree.insert(make_pair("hello",5));
        splaytree.display();
    }

    {
        SplayTree<int, string> splaytree;
        splaytree.insert(make_pair(1,"h"));
        splaytree.insert(make_pair(2,"there"));
        splaytree.display();
        splaytree.insert(make_pair(10,"hey"));
        cout << splaytree.find(2) << "\n";
        cout << splaytree.find(6) << "\n";
        splaytree.insert(make_pair(5,"hello"));
        splaytree.display();
    }
    return 0;
}