#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H
#include <iostream>
#include <utility>
#include <cstring>
#include <iterator>
#define DEBUG 0
using namespace std;

template <typename key_type, typename mapped_type>
class SplayTree
{
private:
    class splay_node
    {
    private:
        template <class T1, class T2>
        friend bool lesserThan(T1, T2);
        template <class T1, class T2>
        friend bool greaterThan(T1, T2);
        template <class T1, class T2>
        friend bool lesserThanEqualTo(T1, T2);
        template <class T1, class T2>
        friend bool greaterThanEqualTo(T1, T2);
        pair<const key_type, mapped_type> data_;
        splay_node *left_;
        splay_node *right_;
        splay_node *parent_;
        friend class SplayTree<key_type, mapped_type>;

    public:
        /**
         *splay_node constructor
        **/
        splay_node(
            const pair<const key_type, mapped_type> &data_,
            splay_node *left_ = nullptr,
            splay_node *right_ = nullptr,
            splay_node *parent_ = nullptr)
            : data_(data_), left_(left_), right_(right_), parent_(parent_) {}

        splay_node(const splay_node *rhs)
            : data_(rhs->data_), left_(rhs->left_), right_(rhs->right_), parent_(rhs->parent_)
        {
        }
    };

public:
    class Iterator
        : public iterator<bidirectional_iterator_tag, pair<const key_type, mapped_type>>
    {
    public:
        /**
         * iterator constructor, assign members to null
        **/
        Iterator(): node_ptr_(nullptr), tree_(nullptr) {};

        // operator functions
        #define DEBUG_OP 0
        bool operator==(const Iterator &rhs) const
        {
            if (DEBUG_OP)
            {
                cout << "called operator==\n";
                if (rhs.node_ptr_ != nullptr)
                {
                    cout << node_ptr_->data_.first << "-" << node_ptr_->data_.second << "\n";
                    cout << rhs.node_ptr_->data_.first << "-" << rhs.node_ptr_->data_.second << "\n";
                }
                else
                {
                    cout << "comparing nulls\n";
                }

                cout << "-------------------\n";
            }
            if (node_ptr_ == nullptr && rhs.node_ptr_ == nullptr)
            {
                if (DEBUG_OP)
                {
                    cout << "both nulls\n";
                }
                return true;
            }
            else if ((node_ptr_ && rhs.node_ptr_ == nullptr))
            {
                if (DEBUG_OP)
                {
                    cout << "rhs nulls\n";
                }
                return false;
            }
            else if ((rhs.node_ptr_ && node_ptr_ == nullptr))
            {
                if (DEBUG_OP)
                {
                    cout << "lhs nulls\n";
                }
                return false;
            }
            return node_ptr_->data_ == rhs.node_ptr_->data_;
        };
        bool operator!=(const Iterator &rhs) const
        {
            return !(*this == rhs);
        };
        bool operator<(const Iterator &) const;
        bool operator>(const Iterator &) const;
        bool operator<=(const Iterator &) const;
        bool operator>=(const Iterator &) const;

        /*
                 * dereference operator. return a reference to
                 * the value pointed to by node_ptr_
                **/
        pair<const key_type, mapped_type> &operator*()
        {
            // SplayTree<key_type,mapped_type>temp;
            tree_->splayTheTree(node_ptr_);

            return node_ptr_->data_;
        };
        const pair<const key_type, mapped_type> &operator*() const
        {
            return node_ptr_->data_;
        };
        pair<const key_type, mapped_type> *operator->()
        {
            // SplayTree<key_type,mapped_type>temp;
            tree_->splayTheTree(node_ptr_);
            //opertree_->printTree();
            return &node_ptr_->data_;
        };

        // preincrement
        Iterator &operator++()
        {
            splay_node *p;

            if (node_ptr_ == nullptr)
            {
                // ++ from end(). get the root of the tree
                node_ptr_ = tree_->root_;

                // error! ++ requested for an empty tree
                //TODO: dont return NULL
                if (node_ptr_ == nullptr)
                    return *this;

                // move to the smallest value in the tree,
                // which is the first node inorder
                //remove ???? test
                while (node_ptr_->left_ != nullptr)
                {
                    node_ptr_ = node_ptr_->left_;
                }
            }
            else
            {
                if (node_ptr_->right_ != nullptr)
                {
                    // successor is the farthest left node of
                    // right subtree
                    node_ptr_ = node_ptr_->right_;

                    while (node_ptr_->left_ != nullptr)
                    {
                        node_ptr_ = node_ptr_->left_;
                    }
                }
                else
                {
                    // have already processed the left subtree, and
                    // there is no right subtree. move up the tree,
                    // looking for a parent for which nodePtr is a left child,
                    // stopping if the parent becomes NULL. a non-NULL parent
                    // is the successor. if parent is NULL, the original node
                    // was the last node inorder, and its successor
                    // is the end of the list
                    p = node_ptr_->parent_;
                    while (p != nullptr && node_ptr_ == p->right_)
                    {
                        node_ptr_ = p;
                        p = p->parent_;
                    }

                    // if we were previously at the right-most node in
                    // the tree, nodePtr = nullptr, and the iterator specifies
                    // the end of the list
                    node_ptr_ = p;
                }
            }
            return *this;
        };
        // predecrement
        Iterator &operator--()
        {
            splay_node *parent;

            if (node_ptr_ == nullptr)
            {
                // -- from end(). get the root of the tree
                node_ptr_ = tree_->root_;

                // error! -- requested for an empty tree
                //TODO: dont return NULL
                if (node_ptr_ == nullptr)
                    return *this;

                // move to the largest value in the tree
                while (node_ptr_->right_ != nullptr)
                {
                    node_ptr_ = node_ptr_->right_;
                }
            }
            else
            {
                if (node_ptr_->left_ != nullptr)
                {
                    node_ptr_ = node_ptr_->left_;

                    while (node_ptr_->right_ != nullptr)
                    {
                        node_ptr_ = node_ptr_->right_;
                    }
                }
                else
                {
                    parent = node_ptr_->parent_;
                    while (parent != nullptr && node_ptr_ == parent->left_)
                    {
                        node_ptr_ = parent;
                        parent = parent->parent_;
                    }
                    node_ptr_ = parent;
                }
            }
            return *this;
        };
        // postincrement
        Iterator operator++(int)
        {
            Iterator temp(node_ptr_, tree_);
            ++*this;
            return temp;
        };
        // postdecrement
        Iterator operator--(int)
        {
            Iterator temp(node_ptr_, tree_);
            --*this;
            return temp;
        };

    private:
        friend class SplayTree<key_type, mapped_type>;
        friend class splay_node;
        template <class T1, class T2>
        friend bool lesserThan(T1 lhs, T2 rhs)
        {
            if (lhs->node_ptr_ == nullptr || rhs.node_ptr_ == nullptr)
            {
                return false;
            }
            return lhs->node_ptr_->data_ < rhs.node_ptr_->data_;
        };

        template <class T1, class T2>
        friend bool greaterThan(T1 lhs, T2 rhs)
        {
            if (lhs->node_ptr_ == nullptr || rhs.node_ptr_ == nullptr)
            {
                return false;
            }
            return lhs->node_ptr_->data_ > rhs.node_ptr_->data_;
        };

        #define DEBUG_LTEQ 0
        template <class T1, class T2>
        friend bool lesserThanEqualTo(T1 lhs, T2 rhs)
        {
            if (DEBUG_LTEQ)
            {
                cout << "lesser than equal to op\n";
                cout << (*lhs == rhs) << "\n";
                cout << lesserThan(lhs, rhs) << "\n";
            }

            return lesserThan(lhs, rhs) || (*lhs == rhs);
        };

        #define DEBUG_GTEQ 0
        template <class T1, class T2>
        friend bool greaterThanEqualTo(T1 lhs, T2 rhs)
        {
            if (DEBUG_GTEQ)
            {
                cout << "greater than equal to op\n";
                cout << (*lhs == rhs) << "\n";
                cout << greaterThan(lhs, rhs) << "\n";
            }
            return greaterThan(lhs, rhs) || (*lhs == rhs);
        };
        /**
                 * nodePtr is the current location in the tree. we can move
                 * freely about the tree using left, right, and parent.
                 * tree is the address of the stree object associated
                 * with this iterator. it is used only to access the
                 * root pointer, which is needed for ++ and --
                 * when the iterator value is end()
                **/
        splay_node *node_ptr_;
        SplayTree<key_type, mapped_type> *tree_;

        /**
                 * used to construct an iterator return value from
                 * a node pointer
                **/
        Iterator(splay_node *node_ptr_, SplayTree<key_type, mapped_type> *tree_): node_ptr_(node_ptr_), tree_(tree_) {}
    };

    class ConstIterator : public Iterator
    {
    public:
        ConstIterator(): node_ptr_(nullptr), tree_(nullptr) {}

        // comparison operators.
        bool operator==(const ConstIterator &rhs) const
        {
            if (DEBUG_OP)
            {
                cout << "called operator==\n";
                if (rhs.node_ptr_ != nullptr)
                {
                    cout << node_ptr_->data_.first << "-" << node_ptr_->data_.second << endl;
                    cout << rhs.node_ptr_->data_.first << "-" << rhs.node_ptr_->data_.second << endl;
                }
                else
                {
                    cout << "comparing nulls\n";
                }

                cout << "-------------------\n";
            }
            if (node_ptr_ == nullptr && rhs.node_ptr_ == nullptr)
            {
                if (DEBUG_OP)
                {
                    cout << "both nulls\n";
                }
                return true;
            }
            else if ((node_ptr_ && rhs.node_ptr_ == nullptr))
            {
                if (DEBUG_OP)
                {
                    cout << "rhs nulls\n";
                }
                return false;
            }
            else if ((rhs.node_ptr_ && node_ptr_ == nullptr))
            {
                if (DEBUG_OP)
                {
                    cout << "lhs nulls\n";
                }
                return false;
            }
            return node_ptr_->data_ == rhs.node_ptr_->data_;
        };
        bool operator!=(const ConstIterator &rhs) const
        {
            return !(*this == rhs);
        };

        bool operator<(const ConstIterator &) const;
        bool operator>(const ConstIterator &) const;
        bool operator<=(const ConstIterator &) const;
        bool operator>=(const ConstIterator &) const;

        const pair<const key_type, mapped_type> &operator*() const
        {
            return node_ptr_->data_;
        };

        // preincrement
        ConstIterator &operator++()
        {
            splay_node *p;

            if (node_ptr_ == nullptr)
            {
                throw new logic_error("Incrementing NULL iterator!!\n");
            }
            else
            {
                if (node_ptr_->right_ != nullptr)
                {
                    // successor is the farthest left node of
                    // right subtree
                    node_ptr_ = node_ptr_->right_;

                    while (node_ptr_->left_ != nullptr)
                    {
                        node_ptr_ = node_ptr_->left_;
                    }
                }
                else
                {
                    // have already processed the left subtree, and
                    // there is no right subtree. move up the tree,
                    // looking for a parent for which nodePtr is a left child,
                    // stopping if the parent becomes NULL. a non-NULL parent
                    // is the successor. if parent is NULL, the original node
                    // was the last node inorder, and its successor
                    // is the end of the list
                    p = node_ptr_->parent_;
                    while (p != nullptr && node_ptr_ == p->right_)
                    {
                        node_ptr_ = p;
                        p = p->parent_;
                    }

                    // if we were previously at the right-most node in
                    // the tree, nodePtr = nullptr, and the iterator specifies
                    // the end of the list
                    node_ptr_ = p;
                }
            }
            return *this;
        };
        // predecrement
        ConstIterator &operator--();
        // postincrement
        ConstIterator operator++(int);
        // postdecrement
        ConstIterator operator--(int);

    private:
        friend class SplayTree<key_type, mapped_type>;
        friend class splay_node;
        template <class T1, class T2>
        friend bool lesserThan(T1, T2);
        template <class T1, class T2>
        friend bool greaterThan(T1, T2);
        template <class T1, class T2>
        friend bool lesserThanEqualTo(T1, T2);
        template <class T1, class T2>
        friend bool greaterThanEqualTo(T1, T2);
        /**
         * nodePtr is the current location in the tree. we can move
         * freely about the tree using left, right, and parent.
         * tree is the address of the stree object associated
         * with this iterator. it is used only to access the
         * root pointer, which is needed for ++ and --
         * when the iterator value is end()
        **/
        const splay_node *node_ptr_;
        const SplayTree<key_type, mapped_type> *tree_;

        /**
         * used to construct an iterator return value from
         * a node pointer
        **/
        ConstIterator(const splay_node *, const SplayTree<key_type, mapped_type> *): node_ptr_(node_ptr_), tree_(tree_) {}
    };
    typedef ConstIterator const_iterator;
    typedef Iterator iterator;

    //template<typename node_type, typename tree_type>
    class ReverseIterator
        : public Iterator
    {
    public:
        /**
         * reverse iterator constructor, assign members to null
        **/
        ReverseIterator(): node_ptr_(nullptr), tree_(nullptr) {};

        bool operator==(const ReverseIterator &) const;
        bool operator!=(const ReverseIterator &) const;
        bool operator<(const ReverseIterator &) const;
        bool operator>(const ReverseIterator &) const;
        bool operator<=(const ReverseIterator &) const;
        bool operator>=(const ReverseIterator &) const;
        /*
         * dereference operator. return a reference to
         * the value pointed to by node_ptr_
        **/
        pair<const key_type, mapped_type> &operator*();
        const pair<const key_type, mapped_type> &operator*() const;
        pair<const key_type, mapped_type> *operator->();

        // preincrement
        ReverseIterator &operator++();
        // predecrement
        ReverseIterator &operator--();
        // postincrement
        ReverseIterator operator++(int);
        // postdecrement
        ReverseIterator operator--(int);

    private:
        friend class SplayTree<key_type, mapped_type>;
        friend class splay_node;
        template <class T1, class T2>
        friend bool lesserThan(T1, T2);
        template <class T1, class T2>
        friend bool greaterThan(T1, T2);
        template <class T1, class T2>
        friend bool lesserThanEqualTo(T1, T2);
        template <class T1, class T2>
        friend bool greaterThanEqualTo(T1, T2);
        splay_node *node_ptr_;
        SplayTree<key_type, mapped_type> *tree_;

        /**
         * used to construct an iterator return value from
         * a node pointer
        **/
        ReverseIterator(splay_node *, SplayTree<key_type, mapped_type> *);
    };

    class ConstReverseIterator
        : public ReverseIterator
    {
    public:
        /**
         * reverse iterator constructor, assign members to null
        **/
        ConstReverseIterator(): node_ptr_(nullptr), tree_(nullptr) {};

        bool operator==(const ConstReverseIterator &) const;
        bool operator!=(const ConstReverseIterator &) const;
        bool operator<(const ConstReverseIterator &) const;
        bool operator>(const ConstReverseIterator &) const;
        bool operator<=(const ConstReverseIterator &) const;
        bool operator>=(const ConstReverseIterator &) const;
        /*
         * dereference operator. return a reference to
         * the value pointed to by node_ptr_
        **/
        const pair<const key_type, mapped_type> &operator*() const;

        // preincrement
        ConstReverseIterator &operator++();
        // predecrement
        ConstReverseIterator &operator--();
        // postincrement
        ConstReverseIterator operator++(int);
        // postdecrement
        ConstReverseIterator operator--(int);

    private:
        friend class SplayTree<key_type, mapped_type>;
        friend class splay_node;
        template <class T1, class T2>
        friend bool lesserThan(T1, T2);
        template <class T1, class T2>
        friend bool greaterThan(T1, T2);
        template <class T1, class T2>
        friend bool lesserThanEqualTo(T1, T2);
        template <class T1, class T2>
        friend bool greaterThanEqualTo(T1, T2);
        const splay_node *node_ptr_;
        const SplayTree<key_type, mapped_type> *tree_;

        /**
         * used to construct an iterator return value from
         * a node pointer
        **/
        ConstReverseIterator(const splay_node *, const SplayTree<key_type, mapped_type> *): 
            node_ptr_(node_ptr_), tree_(tree_){};
    };
    typedef ConstReverseIterator const_reverse_iterator;
    typedef ReverseIterator reverse_iterator;

    /** Constructor **/
    SplayTree();
    /** Destructor **/
    ~SplayTree();
    /** Copy constructor **/
    SplayTree(const SplayTree &);
    /** Copy assignment **/
    SplayTree &operator=(const SplayTree &);
    /** Move constructor **/
    SplayTree(SplayTree &&);
    /** Move assignment **/
    SplayTree &operator=(SplayTree &&);
    /** indexing operator **/
    mapped_type &operator[](const key_type &);
    const mapped_type &operator[](const key_type &) const;

    /** at operator **/
    mapped_type &at(const key_type &);
    const mapped_type &at(const key_type &) const;
    /**
     * search for item. if found, return an iterator pointing
     * at it in the tree; otherwise, return end()
    **/
    iterator find(const key_type &);
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
    iterator insert(const pair<key_type, mapped_type> &);
    /**
         * Remove key,value pair from the tree 
        **/
    void erase(const key_type &);

private:
    splay_node *root_;

    splay_node *deep_tree_copy(const splay_node *);
    /**
        * Test if the tree is logically empty.
        * Return true if empty, false otherwise.
        * DONE
        */
    bool isEmpty() const
    {
        return root_ == nullptr;
    }
    /**
        * Returns true if x is found in the tree.
        * DONE
        */
    pair<bool, iterator> contains(const key_type &);

    void printInorder(splay_node *, const string &prefix, bool isLeft) const;
    /**
        * Find the smallest item in the tree.
        * DONE
        */
    splay_node &getLeftmostLeaf(splay_node *root = nullptr) const;
    /**
        * Find the largest item in the tree.
        * Throw UnderflowException if empty.
        * DONE
        */
    splay_node &getRightmostLeaf(splay_node *root = nullptr) const;
    /**
         * Rotate splay_node right
         * DONE
        **/
    void rotateRight(splay_node *);
    /**
         * Rotate splay_node left
         * DONE
        **/
    void rotateLeft(splay_node *);
    /**
         * Bring given node to root of tree
         * DONE
        **/
    void splayTheTree(splay_node *);

    /**
         * delete a node
         * DONE
        **/
    void deleteNode(splay_node *);
};
#endif