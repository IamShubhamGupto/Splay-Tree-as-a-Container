#include <iostream>
#include <utility>
#include <stdexcept>
#include "splay_tree.h"
using namespace std;
#define DEBUG 1
//Constructor
template <class key_type, class mapped_type>
SplayTree<key_type, mapped_type>:: SplayTree()
    :root_(NULL){
    if(DEBUG){
        cout << "ctor called\n";
    }
}
//Destructor
template <class key_type, class mapped_type>
SplayTree<key_type, mapped_type>:: ~SplayTree()
{
    makeEmpty();
    delete root_;
    if(DEBUG){
        cout << "dtor called\n";
    }
}
//Copy Constructor
template <class key_type, class mapped_type>
SplayTree<key_type, mapped_type>::SplayTree(const SplayTree& rhs){
    root_ = rhs.root_;
}
//Copy Assignment
template <class key_type, class mapped_type>
SplayTree<key_type, mapped_type>& SplayTree<key_type, mapped_type>::operator=(const SplayTree& rhs){
    if(this != &rhs){
        makeEmpty();
        delete root_;
        root_ = rhs.root_;
    }
    return *this;
}
//Move Constructor
template <class key_type, class mapped_type>
SplayTree<key_type, mapped_type>::
    SplayTree(SplayTree&& rhs): root_(rhs.root_)
{   
    rhs.root_ = NULL;
}    

//Move Assignment
template <class key_type, class mapped_type>
SplayTree<key_type,mapped_type>& SplayTree<key_type, mapped_type>::
    operator=(SplayTree&& rhs)
{
    if(this != &rhs){
        makeEmpty();
        root_ = rhs.root_;
        rhs.root_ = NULL;
    }
}

// private Iterator constructor
template <class key_type, class mapped_type>
inline
SplayTree<key_type, mapped_type>::Iterator::
  Iterator(const splay_node<key_type, mapped_type> *node_ptr_,
   const SplayTree<key_type, mapped_type> *tree_)
    : node_ptr_(node_ptr_), tree_(tree_){}
/**
 * BEGIN
 * return an iterator pointing to the first item (inorder)
**/
template <class key_type, class mapped_type>
typename SplayTree<key_type, mapped_type>::const_iterator 
inline
SplayTree<key_type, mapped_type>::begin() const
{
  return const_iterator(findMin(root_), this);
}

/**
 * END
 * return an iterator pointing just past the end of
 * the tree data
 */
template <class key_type, class mapped_type>
typename SplayTree<key_type, mapped_type>::const_iterator 
inline
SplayTree<key_type, mapped_type>::end() const
{
  return Iterator(nullptr, this);
}

// preincrement. move forward to next larger value
// Operator++()
template <class key_type, class mapped_type>
typename SplayTree<key_type,mapped_type>::Iterator&
    SplayTree<key_type,mapped_type>::
        Iterator::operator++()
{
  splay_node<key_type,mapped_type> *p;
  
  if (node_ptr_ == nullptr)
    {
      // ++ from end(). get the root of the tree
      node_ptr_ = tree_->root_;
      
      // error! ++ requested for an empty tree
      //TODO: dont return NULL
      if (node_ptr_ == nullptr)
        return NULL;
      
      // move to the smallest value in the tree,
      // which is the first node inorder
      while (node_ptr_->left_ != nullptr) {
        node_ptr_ = node_ptr_->left_;
      }
    }
  else
    if (node_ptr_->right_ != nullptr)
      {
        // successor is the farthest left node of
        // right subtree
        node_ptr_ = node_ptr_->right_;
        
        while (node_ptr_->left_ != nullptr) {
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
  
  return *this;
}
// Operator++()
template <class key_type, class mapped_type>
typename SplayTree<key_type,mapped_type>::Iterator
    SplayTree<key_type,mapped_type>::
        Iterator::operator--()
{
  
}

// Operator++(int)
template <class key_type, class mapped_type>
typename SplayTree<key_type,mapped_type>::Iterator
    SplayTree<key_type,mapped_type>::
        Iterator::operator++(int n)
{
  Iterator temp(node_ptr_, tree_);
  ++*this;
  return temp;  
}

// Operator--(int)
template <class key_type, class mapped_type>
typename SplayTree<key_type,mapped_type>::Iterator
    SplayTree<key_type,mapped_type>::
        Iterator::operator--(int n)
{
  Iterator temp(node_ptr_, tree_);
  --*this;
  return temp;  
}

template <class key_type, class mapped_type>
void SplayTree<key_type, mapped_type>::makeEmpty(){

}