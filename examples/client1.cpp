#include <iostream>
#include <algorithm>
#include <utility>
#include "../src/splaytree/splay_tree.h"
#include "../src/splaytree/splay_tree.cpp"
using namespace std;

/**
 * This client code tests the following
 * Insertion
 * printTree
 * iterators increment
 * Splaying the tree while using iterators
 **/
int main()
{

    SplayTree<char, int> splaytree;

    splaytree.insert({'1', 10});
    splaytree.insert(pair<char, int>('2', 20));
    splaytree.insert(pair<char, int>('3', 30));
    splaytree.insert(pair<char, int>('4', 40));

    cout << "Tree after insertions\n";

    splaytree.printTree();

    cout << "\nDemo iterator\n";

    auto first = splaytree.begin();
    auto last = splaytree.end();
    while (first != last)
    {
        first->second += 2;
        ++first;
    }

    cout << "Tree after modifications\n";
    splaytree.printTree();
    //dtor
    return 0;
}