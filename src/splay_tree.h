#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H
#include <iostream>
using namespace std;
//template<typename T1, typename T2>
//typedef struct splay_node node_t;
template<class T1, class T2 > class SplayTree{
    private:
    struct splay_node{
        T1 key_;
        T2 value_;  
        struct splay_node* left_;
        struct splay_node* right_;
        struct splay_node* parent_;
    };
    typedef struct splay_node node_t;
    struct splay_tree{
        node_t* root_;
    };
    typedef struct splay_tree splay_tree_t;
    public:
    splay_tree_t* st_;
    
    SplayTree();
    ~SplayTree();
    SplayTree(const SplayTree& rhs);

    node_t* makeNewNode(T1 key, T2 value);
    node_t* maximum(node_t*);
    void rotateRight( node_t*);
    void rotateLeft( node_t*);
    void splayTheTree( node_t*);
    void insert( T1 key, T2 value);
    void delete_node(T1 key);
    T2 find( T1 key);
    // temprorary function
    void display();
    // temprorary function
    void in_order_traverser(node_t*);
    void operator=(const SplayTree& rhs);
    
    template<typename T3, typename T4> friend ostream& operator<<(ostream&, const SplayTree<T3, T4>&);
    
};
#endif