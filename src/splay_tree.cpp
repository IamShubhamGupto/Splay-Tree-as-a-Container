#include<iostream>
#include<algorithm>
#include <ostream>
#include "splay_tree.h"
#include <iostream>
using namespace std;
#define DEBUG 1
// template<typename T1, typename T2>
// struct splay_node{
//     T1 key;
//     T2 value;  
//     struct splay_node* left;
//     struct splay_node* right;
// };
// typedef struct splay_node splay_node_t;

template<class T1, class T2>
SplayTree<T1, T2>:: SplayTree(): st_(new splay_node_t){
    st_->key = T1();
    st_->value = T2();
    st_->left = NULL;
    st_->right = NULL;
    if(DEBUG){
        cout << "ctor called\n";
    }
    
}
template<class T1, class T2>
SplayTree<T1, T2>:: ~SplayTree(){
    delete st_;
    if(DEBUG){
        cout << "dtor called\n";
    }   
}

template<class T1, class T2>
ostream& operator<<(ostream& o, const SplayTree<T1, T2>& splaytree){
    return o << splaytree.st_->key << " - " << splaytree.st_->value << "\n";
}
