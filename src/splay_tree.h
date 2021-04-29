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
                pair<const key_type, mapped_type> data_;
                splay_node* left_;
                splay_node* right_;
            	splay_node* parent_;
                friend class SplayTree<key_type, mapped_type>;
                // friend class Iterator;
                // friend class ReverseIterator;
            public:
                /**
                 *splay_node constructor
                **/
                splay_node (
                    const pair<const key_type, mapped_type>& data_,
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
                /**
                 * iterator constructor, assign members to null
                **/
                Iterator();
                
                // comparison operators. 
                bool operator==(const Iterator<node_type, tree_type>&) const;
                bool operator!=(const Iterator<node_type, tree_type>&) const;
                
                /*
                 * dereference operator. return a reference to
                 * the value pointed to by node_ptr_
                **/
                pair<const key_type, mapped_type> operator*();
                pair<const key_type, mapped_type> operator*() const;
                pair<const key_type, mapped_type>* operator->();
                
                // preincrement 
                Iterator<node_type, tree_type>& operator++();
                // predecrement 
                Iterator<node_type, tree_type>& operator--();
                // postincrement
                Iterator<node_type, tree_type> operator++(int);
                // postdecrement
                Iterator<node_type, tree_type> operator--(int);
                
            private:
                friend class SplayTree<key_type, mapped_type>;
                friend class splay_node;
                /**
                 * nodePtr is the current location in the tree. we can move
                 * freely about the tree using left, right, and parent.
                 * tree is the address of the stree object associated
                 * with this iterator. it is used only to access the
                 * root pointer, which is needed for ++ and --
                 * when the iterator value is end()
                **/ 
                node_type node_ptr_;
                tree_type tree_;
                
                /**
                 * used to construct an iterator return value from
                 * a node pointer
                **/
                Iterator(node_type, tree_type);
        };
        typedef Iterator<const splay_node*, const SplayTree<key_type, mapped_type>*> const_iterator;
        typedef Iterator<splay_node*, SplayTree<key_type, mapped_type>*> iterator;

        template<typename node_type, typename tree_type>
        class ReverseIterator 
            : public Iterator<node_type, tree_type>
        {
            public:
                /**
                 * reverse iterator constructor, assign members to null
                **/
                ReverseIterator();
                /*
                 * dereference operator. return a reference to
                 * the value pointed to by node_ptr_
                **/
                bool operator==(const ReverseIterator<node_type, tree_type>&) const;
                bool operator!=(const ReverseIterator<node_type, tree_type>&) const;

                /*
                 * dereference operator. return a reference to
                 * the value pointed to by node_ptr_
                **/
                pair<const key_type, mapped_type> operator*();
                pair<const key_type, mapped_type> operator*() const;
                pair<const key_type, mapped_type>* operator->();

                // preincrement 
                ReverseIterator<node_type, tree_type>& operator++();
                // predecrement 
                ReverseIterator<node_type, tree_type>& operator--();
                // postincrement
                ReverseIterator<node_type, tree_type> operator++(int);
                // postdecrement
                ReverseIterator<node_type, tree_type> operator--(int);

            private:
                friend class SplayTree<key_type, mapped_type>;
                friend class splay_node;

                node_type node_ptr_;
                tree_type tree_;
                /**
                 * used to construct an iterator return value from
                 * a node pointer
                **/
                ReverseIterator(node_type, tree_type);
        };
        typedef ReverseIterator<const splay_node*, const SplayTree<key_type, mapped_type>*> const_reverse_iterator;
        typedef ReverseIterator<splay_node*, SplayTree<key_type, mapped_type>*> reverse_iterator;

        /** Constructor **/
        SplayTree();
        /** Destructor **/
        ~SplayTree();  
        /** Copy constructor **/
        SplayTree(const SplayTree&);
        /** Copy assignment **/
        SplayTree& operator=(const SplayTree&);
        /** Move constructor **/
        SplayTree(SplayTree&&);
        /** Move assignment **/
        SplayTree& operator=(SplayTree&&);
        /** indexing operator **/
        mapped_type& operator[](const key_type&);
        const mapped_type& operator[](const key_type&) const;

        /** at operator **/
        mapped_type& at(const key_type&);
        const mapped_type& at(const key_type&) const;
        /**
         * search for item. if found, return an iterator pointing
         * at it in the tree; otherwise, return end()
        **/
        iterator find(const key_type&);
        /**
         * return an iterator pointing to the first item (inorder)
        **/
        iterator begin();
        /**
        * return an iterator pointing to beyond-last-element item.
        * this element acts as a placeholder
        * attempting to access it results in undefined behavior.
        */
        iterator end();
        /**
         * return an constant iterator pointing to the first item (inorder).
         * member pointed to by the iterator is a constant and cannot be modified
        **/
        const_iterator cbegin() const;
        /**
         * return an constant iterator pointing to the beyond-first-element item.
         * member pointed to by the iterator is a constant and cannot be modified.
         * this element acts as a placeholder
         * attempting to access it results in undefined behavior.
        **/
        const_iterator cend() const;
        /**
         * return an iterator pointing to the last item (inorder)
        **/
        reverse_iterator rbegin();
        /**
         * return an iterator pointing to the beyond-first-element item.
         * this element acts as a placeholder
         * attempting to access it results in undefined behavior.
        **/
        reverse_iterator rend();
        /**
         * return an constant iterator pointing to the last item (inorder).
         * member pointed to by the iterator is a constant and cannot be modified
        **/
        const_reverse_iterator crbegin() const;
        /**
         * return an constant iterator pointing to the beyond-first-element item.
         * member pointed to by the iterator is a constant and cannot be modified.
         * this element acts as a placeholder
         * attempting to access it results in undefined behavior.
        **/
        const_reverse_iterator crend() const;
        
        /**
         * Print the tree contents inorder.
        **/
        void printTree() const;
        /**
         * Make the tree logically empty.
        **/
        void clear();
        /**
         * Insert key,value pair into the tree
         * Duplicate keys are updated to newly inserted value
        **/
        iterator insert(const pair<key_type, mapped_type>&);
        /**
         * Remove key,value pair from the tree 
        **/
        void erase(const key_type&);
        
        
    private:
        // friend class Iterator<splay_node*, SplayTree<key_type,mapped_type>*>;
        // friend class Iterator<const splay_node*, const SplayTree<key_type,mapped_type>*>;
        // friend class ReverseIterator<splay_node*, SplayTree<key_type,mapped_type>*>;
        // friend class ReverseIterator<const splay_node*, const SplayTree<key_type,mapped_type>*>;
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