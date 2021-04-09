#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H
#include <iostream>
#include <utility>
using namespace std;
//template<typename T1, typename T2>
//typedef struct splay_node node_t;
template<class T1, class T2 > class SplayTree{
    private:
    struct splay_node{
        pair<T1, T2> data_;
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

    class Iterator{
        Iterator();
        bool operator==(const Iterator& rhs) const;
        bool operator!=(const Iterator& rhs) const;
        //TODO fix this
        // const Comparable& operator* () const;

        // preincrement
        Iterator& operator++ ();
        // predecrement.
        Iterator operator--();
        // postincrement
        Iterator operator++(int);
        // postdecrement
        Iterator operator--(int);
    };
    typedef Iterator const_iterator;
    typedef const_iterator iterator;
    //Constructor
    SplayTree();
    //Destructor
    ~SplayTree();
    //Copy constructor
    SplayTree(const SplayTree& rhs);
    //Copy assignment
    SplayTree& operator=(const SplayTree& rhs);
    //Move constructor 
    SplayTree(SplayTree && rhs);
    //Move Assignment
    SplayTree& operator=(SplayTree && rhs);

    node_t* makeNewNode(const pair<T1, T2>&);
    node_t* maximum(node_t*);
    void rotateRight( node_t*);
    void rotateLeft( node_t*);
    void splayTheTree( node_t*);
    void insert(const pair<T1, T2>&);
    void delete_node(const T1 key);
    //find should return an Iterator object
    //TODO:
    T2 find(const T1 key);
    // temprorary function
    void display();
    // temprorary function
    void in_order_traverser(node_t*);
    

    // delete this
    // template<typename T3, typename T4> friend ostream& operator<<(ostream&, const SplayTree<T3, T4>&);
    
};
#endif