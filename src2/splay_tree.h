#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H
#include <iostream>
#include <utility>
#include <cstring>
#include <iterator>
using namespace std;

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
                friend class Iterator;
                friend class ReverseIterator;
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
        template<typename node_type, typename tree_type>
        class Iterator
            : public iterator<bidirectional_iterator_tag, key_type, mapped_type> 
        {
            public:
            
                Iterator();
                
                // comparison operators. just compare node pointers
                //DONE
                bool operator==(const Iterator<node_type, tree_type>&) const;
                
                // DONE
                bool operator!=(const Iterator<node_type, tree_type>&) const;
                
                //bool operator==() const;
                // dereference operator. return a reference to
                // the value pointed to by nodePtr
                //DONE

                pair<key_type, mapped_type> operator*();
                pair<key_type, mapped_type> operator*() const;
                pair<key_type, mapped_type>* operator->();
                
                // preincrement 
                //DONE
                Iterator<node_type, tree_type>& operator++();
                // predecrement 
                //DONE
                Iterator<node_type, tree_type>& operator--();
                // postincrement
                //DONE
                Iterator<node_type, tree_type> operator++(int);
                // postdecrement
                //DONE
                Iterator<node_type, tree_type> operator--(int);
                
            private:
                friend class SplayTree<key_type, mapped_type>;
                friend class splay_node;
                // nodePtr is the current location in the tree. we can move
                // freely about the tree using left, right, and parent.
                // tree is the address of the stree object associated
                // with this iterator. it is used only to access the
                // root pointer, which is needed for ++ and --
                // when the iterator value is end()
                node_type node_ptr_;
                tree_type tree_;
                
                // used to construct an iterator return value from
                // a node pointer
                // DONE
                Iterator(node_type node_ptr_, tree_type tree_);
                // Iterator(const splay_node* p, 
                    // const SplayTree<key_type, mapped_type>* t);
        };
        typedef Iterator<const splay_node*, const SplayTree<key_type, mapped_type>*> const_iterator;
        typedef Iterator<splay_node*, SplayTree<key_type, mapped_type>*> iterator;

        template<typename node_type, typename tree_type>
        class ReverseIterator 
            : public Iterator<node_type, tree_type>
        {
            public:
                ReverseIterator();

                bool operator==(const ReverseIterator<node_type, tree_type>&) const;
                
                bool operator!=(const ReverseIterator<node_type, tree_type>&) const;

                pair<key_type, mapped_type> operator*();
                pair<key_type, mapped_type> operator*() const;
                pair<key_type, mapped_type>* operator->();

                // preincrement 
                //UNDONE
                ReverseIterator<node_type, tree_type>& operator++();
                // predecrement 
                //UNDONE
                ReverseIterator<node_type, tree_type>& operator--();
                // postincrement
                //UNDONE
                ReverseIterator<node_type, tree_type> operator++(int);
                // postdecrement
                //UNDONE
                ReverseIterator<node_type, tree_type> operator--(int);

            private:
                friend class SplayTree<key_type, mapped_type>;
                friend class splay_node;
                // friend class Iterator;
                node_type node_ptr_;
                tree_type tree_;

                ReverseIterator(node_type p, tree_type t);
        };
        typedef ReverseIterator<const splay_node*, const SplayTree<key_type, mapped_type>*> const_reverse_iterator;
        typedef ReverseIterator<splay_node*, SplayTree<key_type, mapped_type>*> reverse_iterator;
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

        mapped_type& operator[](const key_type&);

        //void operator[](const key_type&)(const mapped_type&);
        /**
            search for item. if found, return an iterator pointing
            at it in the tree; otherwise, return end()
            DONE
        */
        iterator find(const key_type&);
        /**
        * return an iterator pointing to the first item (inorder)
        * DONE
        */
        //Iterator begin();
        iterator begin();

        const_iterator cbegin() const;

        reverse_iterator rbegin();

        const_reverse_iterator crbegin() const;

        const_reverse_iterator crend() const;

        reverse_iterator rend();

        const_iterator cend() const;
        /**
        * return an iterator pointing just past the end of
        * DONE
        * the tree data
        */
        iterator end();
        
        /**
        * Print the tree contents inorder.
        */
        void printTree() const;
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
        * Test if the tree is logically empty.
        * Return true if empty, false otherwise.
        * DONE
        */
        bool isEmpty() const {return root_ == nullptr; }
        /**
        * Returns true if x is found in the tree.
        * DONE
        */
        pair<bool, iterator> contains(const key_type&);
        // friend iterator;
        // friend const_iterator;
        // friend reverse_iterator;
        // friend const_reverse_iterator;
        void printInorder(splay_node*,const string& prefix, bool isLeft) const;
        /**
        * Find the smallest item in the tree.
        * DONE
        */
        splay_node& getLeftmostLeaf(splay_node* root = nullptr) const;
        /**
        * Find the largest item in the tree.
        * Throw UnderflowException if empty.
        * DONE
        */
        splay_node& getRightmostLeaf(splay_node* root = nullptr) const;
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