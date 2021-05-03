#include <iostream>
#include <algorithm>
#include <utility>
#include "../src/splay_tree.h"
#include "../src/splay_tree.cpp"
using namespace std;

/**
 * insertion
 * iterators
 * test find() algorithm
 * test begin() algorithm
 * test end() algorithm
 * test double insertion
 * print tree
 **/
int main()
{
    //ctor
    SplayTree<int, int> splaytree;
    splaytree.insert({1, 10});
    splaytree.insert(pair<int, int>(2, 20));

    splaytree.insert(pair<int, int>(3, 30));
    splaytree.insert(pair<int, int>(4, 40));
    splaytree.insert(pair<int, int>(5, 50));
    {
        cout << "------------------------------------------------------\n";
        auto first = begin(splaytree);
        auto last = end(splaytree);

        auto mypair = pair<int, int>(2, 20);
        while (first != last)
        {
            if (first->first == mypair.first && first->second == mypair.second)
                cout << "found == " << (*first).first << " - " << (*first).second << "\n";
            ++first;
        }
        cout << "------------------------------------------------------\n";
    }
#if 0
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
#endif
    splaytree.printTree();
    {
        cout << "------------------------------------------------------\n";
        splaytree.erase(2);
        auto first = begin(splaytree);
        auto last = end(splaytree);

        pair<const int, int> mypair = pair<const int, int>(2, 20);

        auto it = find(first, last, mypair);
        if (it == last)
        {
            cout << "Element not found\n";
        }
        else
        {
            cout << (*it).first << " - " << (*it).second << "\n";
        }
        cout << "------------------------------------------------------\n";
    }
    {
        cout << "------------------------------------------------------\n";
        splaytree.printTree();
        cout << "------------------------------------------------------\n";
    }
    splaytree.insert({5, 50});
    {
        cout << "------------------------------------------------------\n";
        splaytree.printTree();
        cout << "------------------------------------------------------\n";
    }
    //dtor
    return 0;
}