#include <iostream>
#include <algorithm>
#include <utility>
#include <cstring>
#include "../src/splay_tree.hpp"

using namespace std;
/**
 * This clientfile is to test:
 * Constructors
 * Destructors
 * iterator relational operators
 **/
int main()
{

    splay_tree<string, int> splaytree;

    splaytree.insert({"AB", 10});
    splaytree.insert(pair<string, int>("ab", 20));
    splaytree.insert(pair<string, int>("BC", 30));
    splaytree.insert(pair<string, int>("cd", 40));
    splaytree.insert(pair<string, int>("EF", 50));

    cout << "splaytree = \n";
    splaytree.printTree();

    {
        auto first = splaytree.begin();
        auto last = splaytree.end();

        cout << "less than\n";
        while (first < last)
        {
            cout << first->first << " - " << first->second << "\n";
            ++first;
        }
    }

    {
        auto first = splaytree.begin();
        auto last = splaytree.end();

        cout << "greater than\n";
        while (last > first)
        {
            cout << first->first << " - " << first->second << "\n";
            ++first;
        }
    }

    {
        auto first = splaytree.begin();
        auto last = splaytree.end();
        --last;
        cout << "less than equal to\n";
        while (first <= last)
        {
            cout << first->first << " - " << first->second << "\n";
            ++first;
        }
    }

    {
        auto first = splaytree.begin();
        auto last = splaytree.end();
        --last;
        cout << "greater than equal to\n";
        while (last >= first)
        {
            cout << first->first << " - " << first->second << "\n";
            ++first;
        }
    }
}
