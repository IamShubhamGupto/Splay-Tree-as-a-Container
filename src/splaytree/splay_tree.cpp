#include <iostream>
#include <utility>
#include <cstring>
#include <stdexcept>
#include "splay_tree.h"
using namespace std;
#define DEBUG 0

template <class key_type, class mapped_type>
SplayTree<key_type, mapped_type>::
    Iterator::
        Iterator()
    : node_ptr_(nullptr), tree_(nullptr)
{
}

template <class key_type, class mapped_type>
SplayTree<key_type, mapped_type>::
    ConstIterator::
        ConstIterator()
    : node_ptr_(nullptr), tree_(nullptr) {}
// private Iterator constructor
template <class key_type, class mapped_type>
SplayTree<key_type, mapped_type>::
    Iterator::
        Iterator(splay_node *node_ptr_, SplayTree<key_type, mapped_type> *tree_)
    : node_ptr_(node_ptr_), tree_(tree_) {}

template <class key_type, class mapped_type>
SplayTree<key_type, mapped_type>::
    ConstIterator::
        ConstIterator(const splay_node *node_ptr_, const SplayTree<key_type, mapped_type> *tree_)
    : node_ptr_(node_ptr_), tree_(tree_) {}

#define DEBUG_OP 0
template <class key_type, class mapped_type>
bool SplayTree<key_type, mapped_type>::
    Iterator::
    operator==(const Iterator &rhs) const
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
}

template <class key_type, class mapped_type>
bool SplayTree<key_type, mapped_type>::
    ConstIterator::
    operator==(const ConstIterator &rhs) const
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
}

// Iterator operator!=
template <class key_type, class mapped_type>
bool SplayTree<key_type, mapped_type>::
    Iterator::
    operator!=(const Iterator &rhs) const
{
  return !(*this == rhs);
}

template <class key_type, class mapped_type>
bool SplayTree<key_type, mapped_type>::
    ConstIterator::
    operator!=(const ConstIterator &rhs) const
{
  return !(*this == rhs);
}

template <class key_type, class mapped_type>
pair<const key_type, mapped_type> &
SplayTree<key_type, mapped_type>::
    Iterator::
    operator*()
{
  // SplayTree<key_type,mapped_type>temp;
  tree_->splayTheTree(node_ptr_);

  return node_ptr_->data_;
}

template <class key_type, class mapped_type>
const pair<const key_type, mapped_type> &
SplayTree<key_type, mapped_type>::
    Iterator::
    operator*() const
{
  return node_ptr_->data_;
}
template <class key_type, class mapped_type>
const pair<const key_type, mapped_type> &
SplayTree<key_type, mapped_type>::
    ConstIterator::
    operator*() const
{
  return node_ptr_->data_;
}

template <class key_type, class mapped_type>
pair<const key_type, mapped_type> *
SplayTree<key_type, mapped_type>::
    Iterator::
    operator->()
{
  // SplayTree<key_type,mapped_type>temp;
  tree_->splayTheTree(node_ptr_);
  //opertree_->printTree();
  return &node_ptr_->data_;
}
// preincrement.
// Operator++()
template <class key_type, class mapped_type>
typename SplayTree<key_type, mapped_type>::Iterator &
SplayTree<key_type, mapped_type>::
    Iterator::
    operator++()
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
}

template <class key_type, class mapped_type>
typename SplayTree<key_type, mapped_type>::ConstIterator &
SplayTree<key_type, mapped_type>::
    ConstIterator::
    operator++()
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
}
// Operator--()
template <class key_type, class mapped_type>
typename SplayTree<key_type, mapped_type>::Iterator &
SplayTree<key_type, mapped_type>::
    Iterator::
    operator--()
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
}
template <class key_type, class mapped_type>
typename SplayTree<key_type, mapped_type>::ConstIterator &
SplayTree<key_type, mapped_type>::
    ConstIterator::
    operator--()
{
  splay_node *parent;

  if (node_ptr_ == nullptr)
  {
    throw new logic_error("Decrementing NULL iterator!!\n");
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
}
// Operator++(int)
template <class key_type, class mapped_type>
typename SplayTree<key_type, mapped_type>::Iterator
SplayTree<key_type, mapped_type>::
    Iterator::
    operator++(int n)
{
  Iterator temp(node_ptr_, tree_);
  ++*this;
  return temp;
}
// Operator++(int)
template <class key_type, class mapped_type>
typename SplayTree<key_type, mapped_type>::ConstIterator
SplayTree<key_type, mapped_type>::
    ConstIterator::
    operator++(int n)
{
  ConstIterator temp(node_ptr_, tree_);
  ++*this;
  return temp;
}
// Operator--(int)
template <class key_type, class mapped_type>
typename SplayTree<key_type, mapped_type>::Iterator
SplayTree<key_type, mapped_type>::
    Iterator::
    operator--(int n)
{
  Iterator temp(node_ptr_, tree_);
  --*this;
  return temp;
}
template <class key_type, class mapped_type>
typename SplayTree<key_type, mapped_type>::ConstIterator
SplayTree<key_type, mapped_type>::
    ConstIterator::
    operator--(int n)
{
  ConstIterator temp(node_ptr_, tree_);
  --*this;
  return temp;
}

template <typename T1, typename T2>
bool lesserThan(T1 lhs, T2 rhs)
{
  if (lhs->node_ptr_ == nullptr || rhs.node_ptr_ == nullptr)
  {
    return false;
  }
  return lhs->node_ptr_->data_ < rhs.node_ptr_->data_;
}
template <typename T1, typename T2>
bool greaterThan(T1 lhs, T2 rhs)
{
  if (lhs->node_ptr_ == nullptr || rhs.node_ptr_ == nullptr)
  {
    return false;
  }
  return lhs->node_ptr_->data_ > rhs.node_ptr_->data_;
}
#define DEBUG_LTEQ 0
template <typename T1, typename T2>
bool lesserThanEqualTo(T1 lhs, T2 rhs)
{
  if (DEBUG_LTEQ)
  {
    cout << "lesser than equal to op\n";
    cout << (*lhs == rhs) << "\n";
    cout << lesserThan(lhs, rhs) << "\n";
  }

  return lesserThan(lhs, rhs) || (*lhs == rhs);
}
#define DEBUG_GTEQ 0
template <typename T1, typename T2>
bool greaterThanEqualTo(T1 lhs, T2 rhs)
{
  if (DEBUG_GTEQ)
  {
    cout << "greater than equal to op\n";
    cout << (*lhs == rhs) << "\n";
    cout << greaterThan(lhs, rhs) << "\n";
  }
  return greaterThan(lhs, rhs) || (*lhs == rhs);
}
template <class key_type, class mapped_type>
bool SplayTree<key_type, mapped_type>::Iterator::
operator<(const Iterator &rhs) const
{
  return lesserThan(this, rhs);
}

template <class key_type, class mapped_type>
bool SplayTree<key_type, mapped_type>::Iterator::
operator>(const Iterator &it) const
{
  return greaterThan(this, it);
}

template <class key_type, class mapped_type>
bool SplayTree<key_type, mapped_type>::Iterator::
operator<=(const Iterator &it) const
{
  return lesserThanEqualTo(this, it);
}

template <class key_type, class mapped_type>
bool SplayTree<key_type, mapped_type>::Iterator::
operator>=(const Iterator &it) const
{
  if (DEBUG_GTEQ)
  {
    if (node_ptr_ == nullptr)
      cout << "lhs null";
    if (it.node_ptr_ == nullptr)
      cout << "rhs null";
  }
  return greaterThanEqualTo(this, it);
}
template <class key_type, class mapped_type>
bool SplayTree<key_type, mapped_type>::ConstIterator::
operator<(const ConstIterator &it) const
{
  return lesserThan(this, it);
}

template <class key_type, class mapped_type>
bool SplayTree<key_type, mapped_type>::ConstIterator::
operator>(const ConstIterator &it) const
{
  return greaterThan(this, it);
}

template <class key_type, class mapped_type>
bool SplayTree<key_type, mapped_type>::ConstIterator::
operator<=(const ConstIterator &it) const
{
  return lesserThanEqualTo(this, it);
}

template <class key_type, class mapped_type>
bool SplayTree<key_type, mapped_type>::ConstIterator::
operator>=(const ConstIterator &it) const
{
  return greaterThanEqualTo(this, it);
}
//end of iterator functions
template <class key_type, class mapped_type>
SplayTree<key_type, mapped_type>::
    ReverseIterator::
        ReverseIterator()
    : node_ptr_(nullptr), tree_(nullptr) {}

template <class key_type, class mapped_type>
SplayTree<key_type, mapped_type>::
    ConstReverseIterator::
        ConstReverseIterator()
    : node_ptr_(nullptr), tree_(nullptr) {}
// private ReverseIterator constructor
template <class key_type, class mapped_type>
inline SplayTree<key_type, mapped_type>::
    ReverseIterator::
        ReverseIterator(
            splay_node *node_ptr_,
            SplayTree<key_type, mapped_type> *tree_)
    : node_ptr_(node_ptr_), tree_(tree_)
{ //cout << "ri ctor called\n"; if(node_ptr_)cout << "ri" << node_ptr_->data_.first << "\n";
}

template <class key_type, class mapped_type>
inline SplayTree<key_type, mapped_type>::
    ConstReverseIterator::
        ConstReverseIterator(
            const splay_node *node_ptr_,
            const SplayTree<key_type, mapped_type> *tree_)
    : node_ptr_(node_ptr_), tree_(tree_)
{ //cout << "ri ctor called\n"; if(node_ptr_)cout << "ri" << node_ptr_->data_.first << "\n";
}
// Iterator operator==
#define DEBUG_OP_2 0
template <class key_type, class mapped_type>
bool SplayTree<key_type, mapped_type>::
    ReverseIterator::
    operator==(const ReverseIterator &rhs) const
{
  if (node_ptr_ == nullptr && rhs.node_ptr_ == nullptr)
  {
    if (DEBUG_OP_2)
    {
      cout << "both nulls\n";
    }
    return true;
  }
  else if ((node_ptr_ && rhs.node_ptr_ == nullptr))
  {
    if (DEBUG_OP_2)
    {
      cout << "rhs nulls\n";
    }
    return false;
  }
  else if ((rhs.node_ptr_ && node_ptr_ == nullptr))
  {
    if (DEBUG_OP_2)
    {
      cout << "lhs nulls\n";
    }
    return false;
  }
  return node_ptr_->data_ == rhs.node_ptr_->data_;
  // return Iterator::operator==(rhs);
}
template <class key_type, class mapped_type>
bool SplayTree<key_type, mapped_type>::
    ConstReverseIterator::
    operator==(const ConstReverseIterator &rhs) const
{
  if (node_ptr_ == nullptr && rhs.node_ptr_ == nullptr)
  {
    if (DEBUG_OP_2)
    {
      cout << "both nulls\n";
    }
    return true;
  }
  else if ((node_ptr_ && rhs.node_ptr_ == nullptr))
  {
    if (DEBUG_OP_2)
    {
      cout << "rhs nulls\n";
    }
    return false;
  }
  else if ((rhs.node_ptr_ && node_ptr_ == nullptr))
  {
    if (DEBUG_OP_2)
    {
      cout << "lhs nulls\n";
    }
    return false;
  }
  return node_ptr_->data_ == rhs.node_ptr_->data_;
  // return ReverseIterator::operator==(rhs);
}
// Iterator operator!=
template <class key_type, class mapped_type>
bool SplayTree<key_type, mapped_type>::
    ReverseIterator::
    operator!=(const ReverseIterator &rhs) const
{
  return !(*this == rhs);
}

template <class key_type, class mapped_type>
bool SplayTree<key_type, mapped_type>::
    ConstReverseIterator::
    operator!=(const ConstReverseIterator &rhs) const
{
  return !(*this == rhs);
}

template <class key_type, class mapped_type>
pair<const key_type, mapped_type> &
SplayTree<key_type, mapped_type>::
    ReverseIterator::
    operator*()
{
  tree_->splayTheTree(node_ptr_);
  return node_ptr_->data_;
}

template <class key_type, class mapped_type>
const pair<const key_type, mapped_type> &
SplayTree<key_type, mapped_type>::
    ReverseIterator::
    operator*() const
{
  return node_ptr_->data_;
}
template <class key_type, class mapped_type>
const pair<const key_type, mapped_type> &
SplayTree<key_type, mapped_type>::
    ConstReverseIterator::
    operator*() const
{
  return node_ptr_->data_;
}
template <class key_type, class mapped_type>
pair<const key_type, mapped_type> *
SplayTree<key_type, mapped_type>::
    ReverseIterator::
    operator->()
{
  tree_->splayTheTree(node_ptr_);
  return &node_ptr_->data_;
}

// preincrement.
// Operator++()
template <class key_type, class mapped_type>
typename SplayTree<key_type, mapped_type>::ReverseIterator &
SplayTree<key_type, mapped_type>::
    ReverseIterator::
    operator++()
{
  splay_node *parent;

  if (node_ptr_ == nullptr)
  {
    throw new logic_error("Incrementing NULL iterator!!\n");
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
}
template <class key_type, class mapped_type>
typename SplayTree<key_type, mapped_type>::ConstReverseIterator &
SplayTree<key_type, mapped_type>::
    ConstReverseIterator::
    operator++()
{
  splay_node *parent;

  if (node_ptr_ == nullptr)
  {
    throw new logic_error("Incrementing NULL iterator!!\n");
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
}
// Operator--()
template <class key_type, class mapped_type>
typename SplayTree<key_type, mapped_type>::ReverseIterator &
SplayTree<key_type, mapped_type>::
    ReverseIterator::
    operator--()
{
  splay_node *p;

  if (node_ptr_ == nullptr)
  {
    // ++ from end(). get the root of the tree
    node_ptr_ = tree_->root_;

    // error! ++ requested for an empty tree
    if (node_ptr_ == nullptr)
      throw new logic_error("Decrementing NULL iterator!!\n");

    // move to the smallest value in the tree,
    // which is the first node inorder
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
}
template <class key_type, class mapped_type>
typename SplayTree<key_type, mapped_type>::ConstReverseIterator &
SplayTree<key_type, mapped_type>::
    ConstReverseIterator::
    operator--()
{
  splay_node *parent;

  if (node_ptr_ == nullptr)
  {
    throw new logic_error("Decrementing NULL iterator!!\n");
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
      parent = node_ptr_->parent_;
      while (parent != nullptr && node_ptr_ == parent->right_)
      {
        node_ptr_ = parent;
        parent = parent->parent_;
      }

      // if we were previously at the right-most node in
      // the tree, nodePtr = nullptr, and the iterator specifies
      // the end of the list
      node_ptr_ = parent;
    }
  }
  return *this;
}
// Operator++(int)
template <class key_type, class mapped_type>
typename SplayTree<key_type, mapped_type>::ReverseIterator
SplayTree<key_type, mapped_type>::
    ReverseIterator::
    operator++(int n)
{
  reverse_iterator temp(node_ptr_, tree_);
  ++*this;
  return temp;
}

template <class key_type, class mapped_type>
typename SplayTree<key_type, mapped_type>::ConstReverseIterator
SplayTree<key_type, mapped_type>::
    ConstReverseIterator::
    operator++(int n)
{
  ConstReverseIterator temp(node_ptr_, tree_);
  ++*this;
  return temp;
}

// Operator--(int)
template <class key_type, class mapped_type>
typename SplayTree<key_type, mapped_type>::ReverseIterator
SplayTree<key_type, mapped_type>::
    ReverseIterator::
    operator--(int n)
{
  reverse_iterator temp(node_ptr_, tree_);
  --*this;
  return temp;
}
template <class key_type, class mapped_type>
typename SplayTree<key_type, mapped_type>::ConstReverseIterator
SplayTree<key_type, mapped_type>::
    ConstReverseIterator::
    operator--(int n)
{
  ConstReverseIterator temp(node_ptr_, tree_);
  --*this;
  return temp;
}

template <class key_type, class mapped_type>
bool SplayTree<key_type, mapped_type>::ReverseIterator::
operator<(const ReverseIterator &it) const
{
  return lesserThan(this, it);
}

template <class key_type, class mapped_type>
bool SplayTree<key_type, mapped_type>::ReverseIterator::
operator>(const ReverseIterator &it) const
{
  return greaterThan(this, it);
}

template <class key_type, class mapped_type>
bool SplayTree<key_type, mapped_type>::ReverseIterator::
operator<=(const ReverseIterator &it) const
{
  return lesserThanEqualTo(this, it);
}

template <class key_type, class mapped_type>
bool SplayTree<key_type, mapped_type>::ReverseIterator::
operator>=(const ReverseIterator &it) const
{
  return greaterThanEqualTo(this, it);
}
template <class key_type, class mapped_type>
bool SplayTree<key_type, mapped_type>::ConstReverseIterator::
operator<(const ConstReverseIterator &it) const
{
  return lesserThan(this, it);
}

template <class key_type, class mapped_type>
bool SplayTree<key_type, mapped_type>::ConstReverseIterator::
operator>(const ConstReverseIterator &it) const
{
  return greaterThan(this, it);
}

template <class key_type, class mapped_type>
bool SplayTree<key_type, mapped_type>::ConstReverseIterator::
operator<=(const ConstReverseIterator &it) const
{
  return lesserThanEqualTo(this, it);
}

template <class key_type, class mapped_type>
bool SplayTree<key_type, mapped_type>::ConstReverseIterator::
operator>=(const ConstReverseIterator &it) const
{
  return greaterThanEqualTo(this, it);
}
//end of reverse iterator
//Constructor
#define DEBUG_CTOR 0
template <class key_type, class mapped_type>
SplayTree<key_type, mapped_type>::
    SplayTree()
    : root_(nullptr)
{
  if (DEBUG_CTOR)
  {
    cout << "ctor called\n";
  }
}
//Destructor
#define DEBUG_DTOR 0
template <class key_type, class mapped_type>
SplayTree<key_type, mapped_type>::~SplayTree()
{
  clear();
  //delete root_;
  root_ = nullptr;
  if (DEBUG_DTOR)
  {
    cout << "dtor called\n";
  }
}
//Copy Constructor
template <class key_type, class mapped_type>
SplayTree<key_type, mapped_type>::
    SplayTree(const SplayTree &rhs)
{
  root_ = deep_tree_copy(rhs.root_);
}
//Copy Assignment
template <class key_type, class mapped_type>
SplayTree<key_type, mapped_type> &
SplayTree<key_type, mapped_type>::
operator=(const SplayTree &rhs)
{
  if (this != &rhs)
  {
    clear();
    //root_ = nullptr;
    root_ = deep_tree_copy(rhs.root_);
  }
  return *this;
}
//Move Constructor
template <class key_type, class mapped_type>
SplayTree<key_type, mapped_type>::
    SplayTree(SplayTree &&rhs)
    : root_(rhs.root_)
{
  cout << "move ctor called\n";
  rhs.root_ = nullptr;
}

//Move Assignment
template <class key_type, class mapped_type>
SplayTree<key_type, mapped_type> &
SplayTree<key_type, mapped_type>::
operator=(SplayTree &&rhs)
{
  if (this != &rhs)
  {
    clear();
    root_ = rhs.root_;
    rhs.root_ = nullptr;
  }
  cout << "move assignment called\n";
  return *this;
}
#define DEBUG_OP3 0
template <class key_type, class mapped_type>
mapped_type &
SplayTree<key_type, mapped_type>::
operator[](const key_type &key)
{
  pair<bool, iterator> ans = contains(key);
  if (!ans.first)
  {
    iterator new_it = insert(pair<key_type, mapped_type>(key, mapped_type()));
    return new_it->second;
  }
  return (ans.second)->second;
}

template <class key_type, class mapped_type>
const mapped_type &
SplayTree<key_type, mapped_type>::
operator[](const key_type &key) const
{
  pair<bool, iterator> ans = contains(key);
  if (!ans.first)
  {
    throw out_of_range("Key does not exist in map!!");
  }
  return (ans.second)->second;
}

template <class key_type, class mapped_type>
mapped_type &
SplayTree<key_type, mapped_type>::
    at(const key_type &key)
{
  pair<bool, iterator> ans = contains(key);
  if (!ans.first)
  {
    throw out_of_range("Key does not exist in map!!");
  }
  return (ans.second)->second;
}
template <class key_type, class mapped_type>
const mapped_type &
SplayTree<key_type, mapped_type>::
    at(const key_type &key) const
{
  pair<bool, iterator> ans = contains(key);
  if (!ans.first)
  {
    throw out_of_range("Key does not exist in map!!");
  }
  return (ans.second)->second;
}
template <class key_type, class mapped_type>
typename SplayTree<key_type, mapped_type>::iterator
SplayTree<key_type, mapped_type>::
    find(const key_type &key)
{
  if (isEmpty())
  {
    return end();
  }
  iterator it;
  splay_node *current = root_;
  splay_node *previous = nullptr;
  while (current != nullptr && current->data_.first != key)
  {
    previous = current;
    if (key < current->data_.first)
    {
      current = current->left_;
    }
    else
    {
      current = current->right_;
    }
  }
  //found
  if (current && current->data_.first == key)
  {
    it = iterator(current, this);
    splayTheTree(current);
    //not found
  }
  else
  {
    it = end();
    splayTheTree(previous);
  }
  return it;
}
/**
 * BEGIN
 * return an iterator pointing to the first item (inorder)
**/
template <class key_type, class mapped_type>
typename SplayTree<key_type, mapped_type>::iterator inline SplayTree<key_type, mapped_type>::
    begin()
{
  return iterator(&getLeftmostLeaf(root_), this);
}

template <class key_type, class mapped_type>
// template <class node_type, class tree_type>
typename SplayTree<key_type, mapped_type>::const_iterator inline SplayTree<key_type, mapped_type>::
    cbegin() const
{
  return const_iterator(&getLeftmostLeaf(root_), this);
}

template <class key_type, class mapped_type>
// template <class node_type, class tree_type>
typename SplayTree<key_type, mapped_type>::const_reverse_iterator inline SplayTree<key_type, mapped_type>::
    crbegin() const
{
  return const_reverse_iterator(&getRightmostLeaf(root_), this);
}

template <class key_type, class mapped_type>
// template <class node_type, class tree_type>
typename SplayTree<key_type, mapped_type>::const_reverse_iterator inline SplayTree<key_type, mapped_type>::
    crend() const
{
  return const_reverse_iterator(nullptr, this);
}
/**
 * END
 * return an iterator pointing just past the end of
 * the tree data
 */
template <class key_type, class mapped_type>
// template <class node_type, class tree_type>
typename SplayTree<key_type, mapped_type>::const_iterator inline SplayTree<key_type, mapped_type>::
    cend() const
{
  return const_iterator(nullptr, this);
}

template <class key_type, class mapped_type>
typename SplayTree<key_type, mapped_type>::iterator inline SplayTree<key_type, mapped_type>::
    end()
{
  return iterator(nullptr, this);
}

template <class key_type, class mapped_type>
typename SplayTree<key_type, mapped_type>::reverse_iterator inline SplayTree<key_type, mapped_type>::
    rbegin()
{
  return reverse_iterator(&getRightmostLeaf(root_), this);
}

template <class key_type, class mapped_type>
typename SplayTree<key_type, mapped_type>::reverse_iterator inline SplayTree<key_type, mapped_type>::
    rend()
{
  return reverse_iterator(nullptr, this);
}

template <class key_type, class mapped_type>
pair<bool, typename SplayTree<key_type, mapped_type>::iterator>
SplayTree<key_type, mapped_type>::contains(const key_type &key)
{
  iterator it = find(key);
  if (it == end())
  {
    return pair<bool, iterator>(false, it);
  }
  return pair<bool, iterator>(true, it);
}

#if 1
#define DEBUG_PT 0
template <class key_type, class mapped_type>
void SplayTree<key_type, mapped_type>::
    printTree() const
{
  if (isEmpty())
  {
    cout << "Empty tree !!\n";
    return;
  }
  splay_node *root = this->root_;
  if (DEBUG_PT)
  {
    cout << "[printTree]current root is " << root_->data_.first << "\n";
  }
  printInorder(root, "", false);
}
#endif

#if 1
template <class key_type, class mapped_type>
void SplayTree<key_type, mapped_type>::
    printInorder(splay_node *root, const string &prefix, bool isLeft) const
{
  if (root != nullptr)
  {
    cout << prefix;
    cout << (isLeft ? "├──" : "└──");
    cout << root->data_.first << " : " << root->data_.second << "\n";
    printInorder(root->left_, prefix + (isLeft ? "│  " : "   "), true);
    printInorder(root->right_, prefix + (isLeft ? "│  " : "   "), false);
  }
}
#endif

template <class key_type, class mapped_type>
void SplayTree<key_type, mapped_type>::
    clear()
{
  deleteNode(root_);
  root_ = nullptr;
}
#define DEBUG_IN 0
template <class key_type, class mapped_type>
typename SplayTree<key_type, mapped_type>::iterator
SplayTree<key_type, mapped_type>::
    insert(const pair<key_type, mapped_type> &data)
{
  splay_node *current = root_;
  splay_node *previous = nullptr;

  while (current && current->data_.first != data.first)
  {
    previous = current;

    if (data.first < current->data_.first)
    {
      current = current->left_;
    }
    else
    {
      current = current->right_;
    }
  }
  if (DEBUG_IN && previous)
  {
    cout << "[insert]previous == " << previous->data_.first << "\n";
  }
  splay_node *new_node = new splay_node(data);
  new_node->parent_ = previous;
  if (previous == nullptr)
  {
    if (current && current->data_.first == data.first)
    {
      current->data_.second = data.second;
      //cout << "replacing current\n";
      delete new_node;
      new_node = nullptr;
      return iterator(root_, this);
    }
    root_ = new_node;
    if (DEBUG_IN)
    {
      cout << "[insert]root " << data.first << "\n";
    }
  }
  else if (current && current->data_.first == data.first)
  {
    if (DEBUG_IN)
    {
      cout << "[insert]replacing node data " << data.first << "\n";
    }
    current->data_.second = data.second;
    splayTheTree(current);
    delete new_node;
    new_node = nullptr;
    return iterator(current, this);
  }
  else if (new_node->data_.first < previous->data_.first)
  {
    if (DEBUG_IN)
    {
      cout << "[insert]left" << data.first << "\n";
    }
    previous->left_ = new_node;
  }
  else
  {
    if (DEBUG_IN)
    {
      cout << "[insert]right " << data.first << "\n";
    }
    previous->right_ = new_node;
  }
  splayTheTree(new_node);
  return iterator(new_node, this);
}
#define DEBUG_ERASE 0
#if 0
template <class key_type, class mapped_type>
void SplayTree<key_type, mapped_type>::
    erase(const key_type &key)
{
  pair<bool, iterator> ans = contains(key);
  if (!ans.first)
  {
    if (DEBUG_ERASE)
      printf("Node does not exist\n");
    return;
  }
  splay_node *node = ans.second.node_ptr_;
  SplayTree<key_type, mapped_type> left_sub_tree;
  left_sub_tree.root_ = root_->left_;
  // node_t* lst_root = this->st_->root_->left_;
  if (left_sub_tree.root_ != nullptr)
  {
    if (DEBUG_ERASE)
    {
      cout << "[erase] making parent null of " << left_sub_tree.root_->data_.first << "\n";
    }

    left_sub_tree.root_->parent_ = nullptr;
  }

  splay_node *rst_root = root_->right_;
  if (rst_root != nullptr)
  {
    rst_root->parent_ = nullptr;
  }

  if (left_sub_tree.root_ != nullptr)
  {
    splay_node *max = &getRightmostLeaf(left_sub_tree.root_);
    left_sub_tree.splayTheTree(max);
    left_sub_tree.root_->right_ = rst_root;
    if (rst_root)
      rst_root->parent_ = left_sub_tree.root_;
    root_ = left_sub_tree.root_;
  }
  else
  {
    this->root_ = rst_root;
  }
  delete node;
  node = nullptr;
}
#endif
#if 1
template <class key_type, class mapped_type>
void SplayTree<key_type, mapped_type>::
    erase(const key_type &key)
{
  pair<bool, iterator> ans = contains(key);
  if (!ans.first)
  {
    if (DEBUG_ERASE)
      printf("Node does not exist\n");
    return;
  }
  splay_node *node = ans.second.node_ptr_;
  SplayTree<key_type, mapped_type> *left_sub_tree = new SplayTree<key_type, mapped_type>();
  SplayTree<key_type, mapped_type> *right_sub_tree = new SplayTree<key_type, mapped_type>();

  left_sub_tree->root_ = root_->left_;
  // node_t* lst_root = this->st_->root_->left_;
  if (left_sub_tree->root_ != nullptr)
  {
    if (DEBUG_ERASE)
    {
      cout << "[erase] making parent null of " << left_sub_tree->root_->data_.first << "\n";
    }

    left_sub_tree->root_->parent_ = nullptr;
  }

  right_sub_tree->root_ = root_->right_;
  if (right_sub_tree->root_ != nullptr)
  {
    right_sub_tree->root_->parent_ = nullptr;
  }

  if (left_sub_tree->root_ != nullptr)
  {
    splay_node *max = &left_sub_tree->getRightmostLeaf();
    left_sub_tree->splayTheTree(max);
    left_sub_tree->root_->right_ = right_sub_tree->root_;
    if (right_sub_tree->root_)
      right_sub_tree->root_->parent_ = left_sub_tree->root_;
    root_ = left_sub_tree->root_;
  }
  else
  {
    this->root_ = right_sub_tree->root_;
  }
  delete node;
  node = nullptr;
}
#endif
template <class key_type, class mapped_type>
typename SplayTree<key_type, mapped_type>::splay_node *
SplayTree<key_type, mapped_type>::deep_tree_copy(const splay_node *rhs)
{
  splay_node *new_root = new splay_node(rhs);
  if (rhs->left_)
  {
    new_root->left_ = deep_tree_copy(rhs->left_);
    new_root->left_->parent_ = new_root;
  }
  if (rhs->right_)
  {
    new_root->right_ = deep_tree_copy(rhs->right_);
    new_root->right_->parent_ = new_root;
  }
  return new_root;
}
template <class key_type, class mapped_type>
typename SplayTree<key_type, mapped_type>::splay_node &
SplayTree<key_type, mapped_type>::
    getLeftmostLeaf(splay_node *root) const
{
  if (root == nullptr)
  {
    root = root_;
  }
  while (root->left_ != nullptr)
  {
    root = root->left_;
  }
  return *root;
}

#define DEBUG_GRL 0
template <class key_type, class mapped_type>
typename SplayTree<key_type, mapped_type>::splay_node &
SplayTree<key_type, mapped_type>::
    getRightmostLeaf(splay_node *root) const
{

  if (root == nullptr)
  {
    root = root_;
  }
  while (root->right_ != nullptr)
  {
    root = root->right_;
  }
  //CHECK FOR NULL - DONE
  if (DEBUG_GRL)
  {
    if (root == nullptr)
    {
      cout << "returning null\n";
    }
    cout << "[grl]" << root->data_.first << "\n";
  }

  return *root;
}

template <typename key_type, typename mapped_type>
void SplayTree<key_type, mapped_type>::
    rotateRight(splay_node *node)
{
  // splay_tree_t* tree = this->st_;
  splay_node *leftChild = node->left_;
  node->left_ = leftChild->right_;
  if (leftChild->right_ != nullptr)
  {
    leftChild->right_->parent_ = node;
  }

  leftChild->parent_ = node->parent_;
  if (node->parent_ == nullptr)
  {
    this->root_ = leftChild;
  }
  else if (node == node->parent_->right_)
  {
    node->parent_->right_ = leftChild;
  }
  else
  {
    node->parent_->left_ = leftChild;
  }
  leftChild->right_ = node;
  node->parent_ = leftChild;
}
#define DEBUG_RL 0
template <typename key_type, typename mapped_type>
void SplayTree<key_type, mapped_type>::
    rotateLeft(splay_node *node)
{
  if (node == nullptr)
    return;
  // splay_tree_t* tree = this->st_;
  splay_node *rightChild = node->right_;
  node->right_ = rightChild->left_;
  if (rightChild->left_ != nullptr)
  {
    rightChild->left_->parent_ = node;
  }

  rightChild->parent_ = node->parent_;
  if (DEBUG_RL && node->parent_)
  {
    cout << "[RL]setting parent of " << rightChild->data_.first << " to " << node->parent_->data_.first << "\n";
  }
  if (node->parent_ == nullptr)
  {
    this->root_ = rightChild;
  }
  else if (node == node->parent_->left_)
  {
    node->parent_->left_ = rightChild;
  }
  else
  {
    node->parent_->right_ = rightChild;
  }
  if (DEBUG_RL)
  {
    cout << "[RL]splaying this " << node->data_.first << "\n";
  }
  rightChild->left_ = node;
  node->parent_ = rightChild;
}
#define DEBUG_STT 0
#define DEBUG_STT_OLD 0
template <typename key_type, typename mapped_type>
void SplayTree<key_type, mapped_type>::
    splayTheTree(splay_node *new_node)
{
  if (new_node == nullptr)
  {
    if (DEBUG_STT_OLD)
      cout << "Already root\n";
    return;
  }
  // splay_tree_t* tree = this->st_;
  while (new_node->parent_ != nullptr)
  {
    if (new_node->parent_ == root_)
    {
      if (new_node == root_->left_)
      {
        if (DEBUG_STT)
        {
          cout << "Before rotating\n";
          printTree();
          cout << "===calling right/zig rotation on " << new_node->parent_->data_.first << " ===\n";
        }
        rotateRight(new_node->parent_);
        if (DEBUG_STT)
        {
          cout << "After rotating\n";
          printTree();
          cout << "\n";
        }
      }
      else
      {
        if (DEBUG_STT)
        {
          cout << "Before rotating\n";
          printTree();
          cout << "===calling left/zag rotation on " << new_node->parent_->data_.first << " ===\n";
        }
        rotateLeft(new_node->parent_);
        if (DEBUG_STT)
        {
          cout << "After rotating\n";
          printTree();
          cout << "\n";
        }
      }
    }
    else
    {
      splay_node *parent = new_node->parent_;
      splay_node *g_parent = parent->parent_;

      if (parent && new_node->parent_->left_ == new_node && parent->parent_ && parent->parent_->left_ == parent)
      {
        if (DEBUG_STT)
        {
          cout << "Before rotating\n";
          printTree();
          cout << "===calling right-right rotation on " << g_parent->data_.first << " and " << parent->data_.first << " ===\n";
        }
        rotateRight(g_parent);
        rotateRight(parent);
        if (DEBUG_STT)
        {
          cout << "After rotating\n";
          printTree();
          cout << "\n";
        }
      }
      else if (new_node->parent_->right_ == new_node && parent->parent_->right_ == parent)
      {
        if (DEBUG_STT)
        {
          cout << "Before rotating\n";
          printTree();
          cout << "===calling left-left rotation on " << g_parent->data_.first << " and " << parent->data_.first << " ===\n";
        }
        rotateLeft(g_parent);
        if (DEBUG_STT_OLD)
        {
          cout << "\n\n [splaythetree]print tree called\n";
          printTree();
          cout << "\n\n [splaythetree]print tree end\n";
        }

        rotateLeft(parent);

        if (DEBUG_STT)
        {
          cout << "After rotating\n";
          printTree();
          cout << "\n";
        }
      }
      else if (new_node->parent_->right_ == new_node && parent->parent_->left_ == parent)
      {
        if (DEBUG_STT)
        {
          cout << "Before rotating\n";
          printTree();
          cout << "===calling left-right rotation on " << g_parent->data_.first << " and " << parent->data_.first << " ===\n";
        }
        rotateLeft(parent);
        rotateRight(g_parent);
        if (DEBUG_STT)
        {
          cout << "After rotating\n";
          printTree();
          cout << "\n";
        }
        // }else if(new_node->parent_->left_ == new_node && parent->parent_->right_ == parent){
      }
      else
      {
        if (DEBUG_STT)
        {
          cout << "Before rotating\n";
          printTree();
          cout << "===calling right-left rotation on " << g_parent->data_.first << " and " << parent->data_.first << " ===\n";
        }
        rotateRight(parent);
        rotateLeft(g_parent);
        if (DEBUG_STT)
        {
          cout << "After rotating\n";
          printTree();
          cout << "\n";
        }
      }
    }
  }
}

template <class key_type, class mapped_type>
void SplayTree<key_type, mapped_type>::
    deleteNode(splay_node *root)
{
  if (root)
  {
    deleteNode(root->left_);
    deleteNode(root->right_);
    delete root;
    root = nullptr;
  }
}
