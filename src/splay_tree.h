#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H
#include <iostream>
using namespace std;
//template<typename T1, typename T2>
typedef struct splay_node splay_node_t;
template<class T1, class T2 > class SplayTree{
    private:
    struct splay_node{
        T1 key;
        T2 value;  
        struct splay_node* left;
        struct splay_node* right;
    };
    typedef struct splay_node splay_node_t;
    public:
    splay_node_t* st_;
    SplayTree();
    SplayTree(const SplayTree& rhs);
    void operator=(const SplayTree& rhs);
    ~SplayTree();
    template<class T3, class T4> friend ostream& operator<<(ostream&, const SplayTree<T3, T4>&);
    
};
#endif