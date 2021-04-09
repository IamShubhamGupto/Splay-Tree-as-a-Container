#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H
#include <iostream>
#include <utility>
using namespace std;
#define DEBUG 1
template <typename key_type, typename mapped_type>
struct splay_node
{
	pair<key_type, mapped_type> element_;
	splay_node *left_;
	splay_node *right_;
	splay_node *parent_;

	splay_node(const pair<key_type, mapped_type>& element_, splay_node *left_, splay_node *right_,
			splay_node *parent_)
	: element_{ element_ }, left_{ left_ }, right_{ right_ }, parent_{ parent_ } { }

};

template <typename key_type, typename mapped_type>
class SplayTree
{
    public:
        class Iterator
            : public iterator<bidirectional_iterator_tag, key_type, mapped_type> {
            public:
                Iterator();
                
                // comparison operators. just compare node pointers
                bool operator==(const Iterator& rhs) const;
                
                bool operator!=(const Iterator& rhs) const;
                
                // dereference operator. return a reference to
                // the value pointed to by nodePtr
                const pair<key_type, mapped_type>& operator*() const;
                
                // preincrement 
                //DONE
                Iterator& operator++();
                // predecrement
                //DONE 
                Iterator operator--();
                // postincrement
                //DONE
                Iterator operator++(int);
                // postdecrement
                //DONE
                Iterator operator--(int);
                
            private:
                friend class SplayTree<key_type, mapped_type>;
                
                // nodePtr is the current location in the tree. we can move
                // freely about the tree using left, right, and parent.
                // tree is the address of the stree object associated
                // with this iterator. it is used only to access the
                // root pointer, which is needed for ++ and --
                // when the iterator value is end()
                const splay_node<key_type, mapped_type> *node_ptr_;
                const SplayTree<key_type, mapped_type> *tree_;
                
                // used to construct an iterator return value from
                // a node pointer
                // DONE
                Iterator(const splay_node<key_type, mapped_type>* p, 
                    const SplayTree<key_type, mapped_type>* t);
        };

        typedef Iterator const_iterator;
        typedef const_iterator iterator;

        /**
        * Constructor
        * DONE
        */
        SplayTree();
        /**
        * Destructor
        * DONE
        */
        ~SplayTree();  
        /**
        * Copy constructor
        * DONE
        */
        SplayTree(const SplayTree& rhs );
        /**
        * Copy assignment
        * DONE
        */
        SplayTree& operator=(const SplayTree & rhs );
        /**
        * Move constructor
        * DONE
        */
        SplayTree(SplayTree&& rhs );
        /**
        * Move assignment
        * DONE
        */
        SplayTree& operator=(SplayTree && rhs );
        /**
            search for item. if found, return an iterator pointing
            at it in the tree; otherwise, return end()
        */
        const_iterator find(const pair<key_type, mapped_type>& ) const;
        /**
        * return an iterator pointing to the first item (inorder)
        * DONE
        */
        const_iterator begin() const;
        /**
        * return an iterator pointing just past the end of
        * DONE
        * the tree data
        */
        const_iterator end() const;
        /**
        * Find the smallest item in the tree.
        */
        const pair<key_type, mapped_type>& findMin() const;
        /**
        * Find the largest item in the tree.
        * Throw UnderflowException if empty.
        */
        const pair<key_type, mapped_type>& findMax() const;
        /**
        * Returns true if x is found in the tree.
        */
        bool contains(const pair<key_type, mapped_type>& ) const;
        /**
        * Test if the tree is logically empty.
        * Return true if empty, false otherwise.
        */
        bool isEmpty() const {return root_ == nullptr; }
        /**
        * Print the tree contents in sorted order.
        */
        void printTree(ostream& out = cout ) const;
        /**
        * Make the tree logically empty.
        */
        void makeEmpty();
        /**
        * Insert x into the tree; duplicates are ignored.
        */
        void insert(const pair<key_type, mapped_type>& );
        /**
        * Remove x from the tree. Nothing is done if x is not found.
        TODO:
        *
        * void remove(const pair<key_type, mapped_type>& x );
        */
    private:
        splay_node<key_type, mapped_type> *root_;
};
#endif