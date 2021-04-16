#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H
#include <iostream>
#include <utility>
#include <exception>
#include <stdexcept>
#include <iterator>
using namespace std;
#define DEBUG 1

template <typename key_type, typename mapped_type>
class SplayTree
{
    private:
        class splay_node{
            private:
                pair<key_type, mapped_type> data_;
                splay_node* left_;
                splay_node* right_;
            	splay_node* parent_;
                friend class SplayTree<key_type, mapped_type>;
            public:
                splay_node (
                    const pair<key_type, mapped_type>& data_,
                    splay_node* left_ = nullptr,
                    splay_node* right_ = nullptr,
                    splay_node* parent_ = nullptr
                ) 
                : data_(data_ )
                , left_(left_)
                , right_(right_)
                , parent_(parent_) {}
        };
    public:
        class Iterator
            : public iterator<bidirectional_iterator_tag, key_type, mapped_type> {
            public:
            
                Iterator();
                
                // comparison operators. just compare node pointers
                //DONE
                bool operator==(const Iterator&) const;
                
                // DONE
                bool operator!=(const Iterator&) const;
                
                // dereference operator. return a reference to
                // the value pointed to by nodePtr
                //DONE
                const pair<key_type, mapped_type>& operator*() const;
                
                // preincrement 
                //DONE
                Iterator& operator++();
                // predecrement 
                //DONE
                Iterator& operator--();
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
                const splay_node* node_ptr_;
                const SplayTree<key_type, mapped_type>* tree_;
                
                // used to construct an iterator return value from
                // a node pointer
                // DONE
                Iterator(const splay_node* p, 
                    const SplayTree<key_type, mapped_type>* t);
        };

        // typedef Iterator const_iterator;
        // typedef const_iterator iterator;

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
        SplayTree(const SplayTree&);
        /**
        * Copy assignment
        * DONE
        */
        SplayTree& operator=(const SplayTree&);
        /**
        * Move constructor
        * DONE
        */
        SplayTree(SplayTree&&);
        /**
        * Move assignment
        * DONE
        */
        SplayTree& operator=(SplayTree&&);
        /**
            search for item. if found, return an iterator pointing
            at it in the tree; otherwise, return end()
            DONE
        */
        Iterator find(const key_type&);
        /**
        * return an iterator pointing to the first item (inorder)
        * DONE
        */
        Iterator begin() const;
        /**
        * return an iterator pointing just past the end of
        * DONE
        * the tree data
        */
        Iterator end() const;
        /**
        * Returns true if x is found in the tree.
        * DONE
        */
        bool contains(const key_type&) const;
        /**
        * Test if the tree is logically empty.
        * Return true if empty, false otherwise.
        * DONE
        */
        bool isEmpty() const {return root_ == nullptr; }
        /**
        * Print the tree contents in sorted order.
        */
        void printTree(ostream& out = cout) const;
        /**
        * Make the tree logically empty.
        * DONE
        */
        void makeEmpty();
        /**
        * Insert x into the tree; duplicates are ignored.
        * DONE
        */
        void insert(const pair<key_type, mapped_type>&);
        /**
         * Remove x from the tree. Nothing is done if x is not found.
         * DONE
        **/
        void erase(const key_type&);
        
        
    private:
        splay_node* root_;
        /**
        * Find the smallest item in the tree.
        * DONE
        */
        const splay_node& getLeaftmostLeaf(splay_node* root = nullptr) const;
        /**
        * Find the largest item in the tree.
        * Throw UnderflowException if empty.
        * DONE
        */
        const splay_node& getRightmostLeaf(splay_node* root = nullptr) const;
        /**
         * Rotate splay_node right
         * DONE
        **/
        void rotateRight(splay_node*);
        /**
         * Rotate splay_node left
         * DONE
        **/
        void rotateLeft(splay_node*);
        /**
         * Bring given node to root of tree
         * DONE
        **/
        void splayTheTree(splay_node*);

        /**
         * delete a node
         * DONE
        **/
        void deleteNode(splay_node*); 
};
#endif