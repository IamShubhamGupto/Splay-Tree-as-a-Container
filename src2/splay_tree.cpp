#include <iostream>
#include <utility>
#include "splay_tree.h"
using namespace std;
#define DEBUG 1

template <class key_type, class mapped_type>
SplayTree<key_type, mapped_type>::Iterator::
Iterator()
  : node_ptr_(nullptr)
  , tree_(nullptr)
{

}

// private Iterator constructor
template <class key_type, class mapped_type>
inline
SplayTree<key_type, mapped_type>::Iterator::
Iterator(
  const splay_node<key_type, mapped_type> *node_ptr_,
  const SplayTree<key_type, mapped_type> *tree_)
    : node_ptr_(node_ptr_)
    , tree_(tree_) 
{

}

// Iterator operator==
template <class key_type, class mapped_type>
bool 
SplayTree<key_type, mapped_type>::Iterator::operator==(const Iterator& rhs) const
{
  return tree_ == rhs.tree_ 
    && node_ptr_->data_->first = rhs.data_->first
    && node_ptr_->data_->second = rhs.data_->second; 
}

// Iterator operator!=
template <class key_type, class mapped_type>
bool 
SplayTree<key_type, mapped_type>::
  Iterator::operator!=(const Iterator& rhs) const
{
  return !(*this == rhs);
}

template <class key_type, class mapped_type>
const pair<key_type, mapped_type>& 
SplayTree<key_type,mapped_type>::Iterator::operator*() const
{
    return node_ptr_->data_;
}
// preincrement.
// Operator++()
template <class key_type, class mapped_type>
typename SplayTree<key_type,mapped_type>::Iterator&
SplayTree<key_type,mapped_type>::Iterator::operator++()
{
  splay_node<key_type,mapped_type> *p;
  
  if(node_ptr_ == nullptr)
  {
      // ++ from end(). get the root of the tree
      node_ptr_ = tree_->root_;
      
      // error! ++ requested for an empty tree
      //TODO: dont return NULL
      if(node_ptr_ == nullptr)
        return NULL;
      
      // move to the smallest value in the tree,
      // which is the first node inorder
      while(node_ptr_->left_ != nullptr) {
        node_ptr_ = node_ptr_->left_;
      }
  }else
  {
    if(node_ptr_->right_ != nullptr)
    {
        // successor is the farthest left node of
        // right subtree
        node_ptr_ = node_ptr_->right_;
        
        while(node_ptr_->left_ != nullptr)
        {
          node_ptr_ = node_ptr_->left_;
        }
    }else
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
typename SplayTree<key_type,mapped_type>::Iterator&
SplayTree<key_type,mapped_type>::Iterator::operator--()
{
  splay_node<key_type,mapped_type> *parent;
  
  if(node_ptr_ == nullptr)
  {
      // -- from end(). get the root of the tree
      node_ptr_ = tree_->root_;
      
      // error! -- requested for an empty tree
      //TODO: dont return NULL
      if(node_ptr_ == nullptr)
        return NULL;
      
      // move to the largest value in the tree
      while(node_ptr_->right_ != nullptr)
      {
        node_ptr_ = node_ptr_->right_;
      }
  }else
  {
    if (node_ptr_->left_ != nullptr)
    {
        node_ptr_ = node_ptr_->left_;
        
        while(node_ptr_->right_ != nullptr)
        {
          node_ptr_ = node_ptr_->right_;
        }
    }else
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
typename SplayTree<key_type,mapped_type>::Iterator
SplayTree<key_type,mapped_type>::Iterator::operator++(int n)
{
  Iterator temp(node_ptr_, tree_);
  ++*this;
  return temp;  
}

// Operator--(int)
template <class key_type, class mapped_type>
typename SplayTree<key_type,mapped_type>::Iterator
SplayTree<key_type,mapped_type>::Iterator::operator--(int n)
{
  Iterator temp(node_ptr_, tree_);
  --*this;
  return temp;  
}

//Constructor
template <class key_type, class mapped_type>
SplayTree<key_type, mapped_type>:: SplayTree()
    :root_(nullptr)
{
    if(DEBUG){
        cout << "ctor called\n";
    }
}
//Destructor
template <class key_type, class mapped_type>
SplayTree<key_type, mapped_type>::~SplayTree()
{
    makeEmpty();
    if(root_ != nullptr){
      delete root_;
    }
    root_ = nullptr;
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
    SplayTree(SplayTree&& rhs)
    : root_(rhs.root_)
{   
    rhs.root_ = nullptr;
}    

//Move Assignment
template <class key_type, class mapped_type>
SplayTree<key_type,mapped_type>& 
SplayTree<key_type, mapped_type>::operator=(SplayTree&& rhs)
{
    if(this != &rhs){
      // should I call moveEmpty ???yes
        makeEmpty();
        root_ = rhs.root_;
        rhs.root_ = NULL;
    }
}
template <class key_type, class mapped_type>
typename SplayTree<key_type,mapped_type>::Iterator
SplayTree<key_type, mapped_type>::find(const key_type& key )
{
    Iterator it;
    splay_node<key_type, mapped_type>* current = this->root_;
    splay_node<key_type, mapped_type>* previous = nullptr;
    while(current != nullptr && current->data_.first != key){
        previous = current;
        if(key < current->data_.first){
            current = current-> left_;
        }else{
            current = current->right_;
        }

    }
    //found    
    if(current && current->data_.first == key){
        it = Iterator(current, this);
        splayTheTree(current);
    //not found    
    }else{
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
typename SplayTree<key_type, mapped_type>::Iterator 
inline
SplayTree<key_type, mapped_type>::begin() const
{
  return Iterator(getLeaftmostLeaf(root_), this);
}

/**
 * END
 * return an iterator pointing just past the end of
 * the tree data
 */
template <class key_type, class mapped_type>
typename SplayTree<key_type, mapped_type>::Iterator 
inline
SplayTree<key_type, mapped_type>::end() const
{
  return Iterator(nullptr, this);
}

template <class key_type, class mapped_type>
bool 
SplayTree<key_type, mapped_type>::contains(const key_type& key) const
{
  Iterator it = find(key);
  if(it == end()){
    return false;
  }
  return true;
}

template <class key_type, class mapped_type>
void 
SplayTree<key_type, mapped_type>::printTree(ostream& out) const
{

}

template <class key_type, class mapped_type>
void 
SplayTree<key_type, mapped_type>::makeEmpty()
{
  splay_node<key_type, mapped_type>* root = this->root_;
  deleteNode(root->left_);
  deleteNode(root->right_);  
  root->left_ = nullptr;
  root->right_ = nullptr;
  
}

template <class key_type, class mapped_type>
void 
SplayTree<key_type, mapped_type>::insert(const pair<key_type, mapped_type>& data)
{ 
    splay_node<key_type, mapped_type>* current = this->root_;
    splay_node<key_type, mapped_type>* previous = nullptr;

    while(current != nullptr && current->data_.first != data.first){
        previous = current;
        if(data.first < current->data_.first){
            current = current->left_;
        }else{
            current = current->right_;
        }
    }
    splay_node<key_type, mapped_type>* new_node = new splay_node<key_type, mapped_type>(data);
    new_node->parent_ = previous;
    if(previous == nullptr){
        this->root_ = new_node;
        if(DEBUG){
          cout << "Insert at root " << data.first << "\n";
        }
    }else if(current != nullptr && current->data_.first == data.first){
        if(DEBUG){
          cout << "replacing node data " << data.first << "\n";
        }
        current->data_.second = data.second;
        splayTheTree( current);
        return;    
    }else if(new_node->data_.first < previous->data_.first){
        if(DEBUG){
          cout << "Inserting left" << data.first << "\n";
        }
        previous->left_ = new_node;
    }else{
        if(DEBUG){
          cout << "Inserting right " << data.first << "\n";
        }
        previous->right_ = new_node;
    }
    splayTheTree(new_node);
}

template <class key_type, class mapped_type>
void 
SplayTree<key_type, mapped_type>::erase(const key_type& key)
{
    bool present = contains(key);
    if(!present){
        printf("Node does not exist\n");
        return;
    }
    SplayTree<key_type,mapped_type> left_sub_tree;
    left_sub_tree->root_ = this->root_->left_;
    // node_t* lst_root = this->st_->root_->left_;
    if(left_sub_tree->root_ != nullptr){
        left_sub_tree->root_->parent_ = nullptr;
    }

    splay_node<key_type, mapped_type>* rst_root = this->root_->right_;
    if(rst_root != nullptr){
        rst_root->parent_ = nullptr;
    }

    if(left_sub_tree->root_ != nullptr){
        splay_node<key_type, mapped_type>* max = getRightmostLeaf(left_sub_tree->root_);
        left_sub_tree.splayTheTree(max);
        left_sub_tree->root_->right_ = rst_root;
        this->root_ = left_sub_tree->root_;
    }else{
        this->root_ = rst_root;
    }
}

template <class key_type, class mapped_type>
const splay_node<key_type, mapped_type>& 
SplayTree<key_type, mapped_type>::getLeaftmostLeaf(splay_node<key_type, mapped_type>* root) const
{
  if(root == nullptr){
    root = root_;
  }
  while(root != nullptr){
    root = root->left_;
  }
  return root;
}

template <class key_type, class mapped_type>
const splay_node<key_type, mapped_type>& 
SplayTree<key_type, mapped_type>::getRightmostLeaf(splay_node<key_type, mapped_type>* root) const
{
  if(root == nullptr){
    root = root_;
  }
  while(root != nullptr){
    root = root->right_;
  }
  //CHECK FOR NULL
  return root;
}

template<typename key_type, typename mapped_type>
void 
SplayTree<key_type, mapped_type>::rotateRight(splay_node<key_type,mapped_type>* node)
{
    // splay_tree_t* tree = this->st_;
    splay_node<key_type,mapped_type>* leftChild = node->left_;
    node->left_ = leftChild->right_;
    if(leftChild->right_ != nullptr){
        leftChild->right_->parent_ = node;
    }
        
    leftChild->parent_ = node->parent_;
    if(node->parent_ == nullptr){
        this->root_ = leftChild;
    }else if(node == node->parent_->right_){
        node->parent_->right_ = leftChild;
    }else{
        node->parent_->left_ = leftChild;
    }
    leftChild->right_ = node;
    node->parent_ = leftChild;
}

template<typename key_type, typename mapped_type>
void 
SplayTree<key_type, mapped_type>::rotateLeft(splay_node<key_type,mapped_type>* node)
{
    // splay_tree_t* tree = this->st_;
    splay_node<key_type,mapped_type>* rightChild = node->right_;
    node->right_ = rightChild->left_;
    if(rightChild->left_ != nullptr){
        rightChild->left_->parent_ = node;
    }
        
    rightChild->parent_ = node->parent_;
    if(node->parent_ == nullptr){
        this->root_ = rightChild;
    }else if(node == node->parent_->left_){
        node->parent_->left_ = rightChild;
    }else{
        node->parent_->right_ = rightChild;
    }
    rightChild->left_ = node;
    node->parent_ = rightChild;
}

template<typename key_type, typename mapped_type>
void 
SplayTree<key_type, mapped_type>::splayTheTree(splay_node<key_type,mapped_type>* new_node)
{
    // splay_tree_t* tree = this->st_;
    while(new_node->parent_ != nullptr){
        if(new_node->parent_ == this->root_){
            if(new_node == this->root_->left_){
                rotateRight( new_node->parent_);
            }else{
                rotateLeft( new_node->parent_);
            }
        }else{
            splay_node<key_type,mapped_type>* parent = new_node->parent_;
            splay_node<key_type,mapped_type>* g_parent = parent->parent_;

            if(new_node->parent_->left_ == new_node && parent->parent_->left_ == parent){
                rotateRight( g_parent);
                rotateRight( parent);
            }else if(new_node->parent_->right_ == new_node && parent->parent_->right_ == parent){
                rotateLeft( g_parent);
                rotateLeft( parent);
            }else if(new_node->parent_->right_ == new_node && parent->parent_->left_ == parent){
                rotateLeft( parent);
                rotateRight( g_parent);
            }else if(new_node->parent_->left_ == new_node && parent->parent_->right_ == parent){
                rotateRight( parent);
                rotateLeft( g_parent);
            } 
        }
    }
}

template <class key_type, class mapped_type>
void 
SplayTree<key_type, mapped_type>::deleteNode(splay_node<key_type, mapped_type>* root)
{
  if(root == nullptr)
  {
    return;
  }
  deleteNode(root->left_);
  root->left_ = nullptr;
  deleteNode(root->right_);
  root->right_ = nullptr;
  delete root;
  root = nullptr;  
}