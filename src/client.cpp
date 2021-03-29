#include <iostream>
#include "splay_tree.h"
#include "splay_tree.cpp"
#include <algorithm>
#include <ostream>
using namespace std;

int main(){
    SplayTree<int, int> splaytree;
    cout << splaytree;
    return 0;
}