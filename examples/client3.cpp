#include <iostream>
#include <algorithm>
#include <utility>
#include <cstring>
#include "../src/splaytree/splay_tree.h"
#include "../src/splaytree/splay_tree.cpp"
using namespace std;

/**
 * This client file tests
 * insertion
 * print tree
 * iterators and increment op
 * reverse iterators and increment(reverse) op
 * operator[]
 * insertion using operator[]
 * at()
 * accessing not inserted pair using at()
 **/
int main()
{

    SplayTree<string, int> splaytree;

    splaytree.insert({"AB", 10});
    splaytree.insert(pair<string, int>("ab", 20));
    splaytree.insert(pair<string, int>("BC", 30));
    splaytree.insert(pair<string, int>("cd", 40));
    splaytree.insert(pair<string, int>("EF", 50));

    cout << "\ndisplaying tree\n";
    splaytree.printTree();

    cout << "\nPrinting first to last\n";
    {
        auto first = splaytree.begin();
        auto last = splaytree.end();
        while (first != last)
        {
            cout << first->first << " - " << first->second << "\n";
            ++first;
        }
    }

    cout << "\nPrinting last to first\n";
    {
        auto first = splaytree.rbegin();
        auto last = splaytree.rend();
        while (first != last)
        {
            cout << first->first << " - " << first->second << "\n";
            ++first;
        }
    }

    splaytree["BC"] *= 2;

    cout << "splaytree[\"BC\"] = " << splaytree["BC"] << "\n";

    cout << "\ndisplaying tree\n";
    splaytree.printTree();

    cout << "\ninsert using operator[]\n";
    splaytree["ABCD"] = 100;
    cout << "splaytree[\"ABCD\"] = " << splaytree.at("ABCD") << "\n";

    cout << "\ndisplaying tree\n";
    splaytree.printTree();

    splaytree.at("ABCDE") = 9090;

    return 0;
}