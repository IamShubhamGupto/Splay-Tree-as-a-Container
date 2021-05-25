#include <iostream>
#include <algorithm>
#include <utility>
#include "../src/splaytree/splay_tree.h"
#include "../src/splaytree/splay_tree.cpp"
using namespace std;

/**
 * test insertion 
 * test constant reverse iterators
 **/
int main()
{
    SplayTree<int, int> splaytree;
    splaytree.insert({1, 10});
    splaytree.insert(pair<int, int>(2, 20));

    splaytree.insert(pair<int, int>(3, 30));
    splaytree.insert(pair<int, int>(4, 40));

    auto first = splaytree.crbegin();
    auto last = splaytree.crend();

    while (first != last)
    {
        cout << (*first).first << " - " << (*first).second << "\n";
        ++first;
    }
    return 0;
}