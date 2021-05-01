#include <iostream>
#include <algorithm>
#include <utility>
#include <cstring>
#include "../src/splay_tree.h"
#include "../src/splay_tree.cpp"
using namespace std;
int main()
{

    SplayTree<string, int> splaytree;

    splaytree.insert({"AB", 10});
    splaytree.insert(pair<string, int>("ab", 20));
    splaytree.insert(pair<string, int>("BC", 30));
    splaytree.insert(pair<string, int>("cd", 40));
    splaytree.insert(pair<string, int>("EF", 50));

    cout << "splaytree = \n";
    splaytree.printTree();
    //copy constructor
    SplayTree<string, int> splaytree2 = splaytree;

    //copy assignment
    SplayTree<string, int> splaytree3;
    splaytree3 = splaytree2;

    //move constructor
    SplayTree<string, int> splaytree4(move(splaytree3));

    //move assignment
    SplayTree<string, int> splaytree5;

    splaytree5 = move(splaytree);

    cout << "after assignments\n";
    splaytree.printTree();
    splaytree2.printTree();
    splaytree3.printTree();
    splaytree4.printTree();
    splaytree5.printTree();
}