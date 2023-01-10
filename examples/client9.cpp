#include <iostream>
#include <algorithm>
#include <utility>
#include "../src/splay_tree.h"
using namespace std;

/**
 * test insertion 
 * test constant reverse iterators
 **/
int main()
{
    SplayTree<int, int> splaytree;
    cout << "inserting 5\n";
    splaytree.insert({5, 50});
    cout << "inserting 1\n";
    splaytree.insert({1, 10});
    cout << "inserting 6\n";
    splaytree.insert(pair<int, int>(6, 60));
    cout << "inserting 2\n";
    splaytree.insert(pair<int, int>(2, 20));
    cout << "inserting 7\n";
    splaytree.insert(pair<int, int>(7, 70));
    cout << "deleting 5\n";
    splaytree.erase(5);
    cout << "inserting 3\n";
    splaytree.insert(pair<int, int>(3, 30));
    cout << "inserting 4\n";
    splaytree.insert(pair<int, int>(4, 40));
    return 0;
}