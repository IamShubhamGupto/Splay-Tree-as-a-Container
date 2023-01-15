#include <iostream>
#include <algorithm>
#include <utility>
#include "../src/splay_tree.hpp"
using namespace std;

/**
 * insertion
 * print tree
 * find pair in tree
 * iterator dereferencing
 **/
int main()
{

    splay_tree<int, int> splaytree;

    splaytree.insert({1, 10});
    splaytree.insert(pair<int, int>(2, 20));
    splaytree.insert(pair<int, int>(3, 30));
    splaytree.insert(pair<int, int>(4, 40));

    {
        cout << "------------------------------------------------------\n";
        auto it = splaytree.find(2);
        if (it != splaytree.end())
        {
            cout << (*it).first << " - " << (*it).second << "\n";
        }
        else
        {
            cout << "Element not found\n";
        }

        it = splaytree.find(10);
        if (it != splaytree.end())
        {
            cout << (*it).first << " - " << (*it).second << "\n";
        }
        else
        {
            cout << "Element not found\n";
        }
        cout << "------------------------------------------------------\n";
    }
    {
        cout << "------------------------------------------------------\n";
        auto first = splaytree.begin();
        auto last = splaytree.end();

        auto mypair = pair<int, int>(2, 20);
        while (first != last)
        {
            if (first->first == mypair.first && first->second == mypair.second)
                cout << "found == " << (*first).first << " - " << (*first).second << "\n";
            ++first;
        }
        cout << "------------------------------------------------------\n";
    }
    {
        cout << "------------------------------------------------------\n";
        splaytree.printTree();
        cout << "------------------------------------------------------\n";
    }
    //dtor
    return 0;
}