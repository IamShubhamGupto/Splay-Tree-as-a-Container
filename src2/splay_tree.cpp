#include <iostream>
#include <utility>
#include <cstring>
#include "splay_tree.h"
using namespace std;
#define DEBUG 1

template <class key_type, class mapped_type>
SplayTree<key_type, mapped_type>::Iterator::
Iterator()
  : node_ptr_(nullptr)
  , tree_(nullptr) {}

// private Iterator constructor
template <class key_type, class mapped_type>
inline
SplayTree<key_type, mapped_type>::Iterator::
Iterator(
  const splay_node *node_ptr_,
  const SplayTree<key_type, mapped_type> *tree_)
    : node_ptr_(node_ptr_)
    , tree_(tree_) {}

// Iterator operator==
#define DEBUG_OP 0
template <class key_type, class mapped_type>
bool 
SplayTree<key_type, mapped_type>::Iterator::operator==(const Iterator& rhs) const
{
  if(DEBUG_OP){
    cout << "called operator==\n";
    if(rhs.node_ptr_ != nullptr){
      cout << node_ptr_->data_.first << "-" << node_ptr_->data_.second << endl;
      cout << rhs.node_ptr_->data_.first  << "-" << rhs.node_ptr_->data_.second << endl;
    }else{
      cout << "comparing nulls\n";
    }
    
    cout << "-------------------\n";
  }
  if(node_ptr_== nullptr && rhs.node_ptr_ == nullptr){
    if(DEBUG_OP){
      cout << "both nulls\n";
    }
    return true;
  }else if((node_ptr_ && rhs.node_ptr_ == nullptr)){
    if(DEBUG_OP){
      cout << "rhs nulls\n";
    }
    return false;
  }else if((rhs.node_ptr_ && node_ptr_== nullptr)){
      if(DEBUG_OP){
      cout << "lhs nulls\n";
    }
      return false;
  }
  return node_ptr_->data_ == rhs.node_ptr_->data_;
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
  splay_node *p;
  
  if(node_ptr_ == nullptr)
  {
      // ++ from end(). get the root of the tree
      node_ptr_ = tree_->root_;
      
      // error! ++ requested for an empty tree
      //TODO: dont return NULL
      if(node_ptr_ == nullptr)
        return *this;
      
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
  splay_node *parent;
  
  if(node_ptr_ == nullptr)
  {
      // -- from end(). get the root of the tree
      node_ptr_ = tree_->root_;
      
      // error! -- requested for an empty tree
      //TODO: dont return NULL
      if(node_ptr_ == nullptr)
        return *this;
      
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
#define DEBUG_CTOR 0
template <class key_type, class mapped_type>
SplayTree<key_type, mapped_type>:: SplayTree()
    :root_(nullptr)
{
    if(DEBUG_CTOR){
        cout << "ctor called\n";
    }
}
//Destructor
#define DEBUG_DTOR 0
template <class key_type, class mapped_type>
SplayTree<key_type, mapped_type>::~SplayTree()
{
    makeEmpty();
    if(root_ != nullptr){
      delete root_;
    }
    root_ = nullptr;
    if(DEBUG_DTOR){
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
    splay_node* current = this->root_;
    splay_node* previous = nullptr;
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
  return Iterator(&getLeaftmostLeaf(root_), this);
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
pair<bool, typename SplayTree<key_type, mapped_type>::Iterator> 
SplayTree<key_type, mapped_type>::contains(const key_type& key)
{
  Iterator it = find(key);
  if(it == end()){
    return pair<bool, Iterator>(false,it);
  }
  return pair<bool, Iterator>(true,it);
}

#if 0
template <class key_type, class mapped_type>
void 
SplayTree<key_type, mapped_type>::printTree() const
{
  auto first = begin();
  auto last = end();
  while(first != last)
  {
    cout << (*first).first << " - " << (*first).second << "\n";
    ++first;
  }
}
#endif
#if 1
#define DEBUG_PT 0
template <class key_type, class mapped_type>
void 
SplayTree<key_type, mapped_type>::printTree() const
{
  splay_node* root = this->root_;
  if(DEBUG_PT){
    cout << "[printTree]current root is " << root_->data_.first << "\n";
  }
  printInorder(root, "", false);
}
#endif

#if 1
template <class key_type, class mapped_type>
void
SplayTree<key_type, mapped_type>::printInorder(splay_node* root, const string& prefix, bool isLeft) const
{
  if(root != nullptr){
    cout << prefix;
    cout << (isLeft ? "├──" : "└──");
    cout << root->data_.first << " : " << root->data_.second << "\n";
    printInorder(root->left_, prefix + (isLeft ? "│  " : "   "), true);
    printInorder(root->right_, prefix + (isLeft ? "│  " : "   "), false);
  }
}
#endif

#if 0
#define DEBUG_PIN 0
template <class key_type, class mapped_type>
void
SplayTree<key_type, mapped_type>::printInorder(splay_node* root) const
{
  if(root == nullptr)
  {
    return;
  }
  printInorder(root->left_);
  if(DEBUG_PIN){
    if(root->parent_){
      cout << "parent ";
      cout << root->parent_->data_.first << " - " << root->parent_->data_.second << "\n"; 
    }else{
      cout << root->data_.first << " has no parent "<< "\n";
    }
    
    cout << "root ";
  }
  
  cout << root->data_.first << " - " << root->data_.second << "\n"; 

  if(DEBUG_PIN){
    //left
    if(root->left_ != nullptr){
      cout << "left ";
      cout << root->left_->data_.first << " - " << root->left_->data_.second << "\n"; 
    }

    if(root->right_){
      cout << "right ";
      cout << root->right_->data_.first << " - " << root->right_->data_.second << "\n";
    }
    cout << "\n";
  }  
  printInorder(root->right_);
}
#endif
template <class key_type, class mapped_type>
void 
SplayTree<key_type, mapped_type>::makeEmpty()
{
  splay_node* root = this->root_;
  deleteNode(root->left_);
  deleteNode(root->right_);  
  root->left_ = nullptr;
  root->right_ = nullptr;
  
}
#define DEBUG_IN 0
template <class key_type, class mapped_type>
void 
SplayTree<key_type, mapped_type>::insert(const pair<key_type, mapped_type>& data)
{ 
    splay_node* current = root_;
    splay_node* previous = nullptr;

    while(current && current->data_.first != data.first){
        previous = current;
        
        if(data.first < current->data_.first){
            current = current->left_;
        }else{
            current = current->right_;
        }
    }
    if(DEBUG_IN && previous){
      cout << "[insert]previous == " << previous->data_.first << "\n";
    }
    splay_node* new_node = new splay_node(data);
    new_node->parent_ = previous;
    if(previous == nullptr){
        root_ = new_node;
        if(DEBUG_IN){
          cout << "[insert]root " << data.first << "\n";
        }
    }else if(current != nullptr && current->data_.first == data.first){
        if(DEBUG_IN){
          cout << "[insert]replacing node data " << data.first << "\n";
        }
        current->data_.second = data.second;
        splayTheTree( current);
        return;    
    }else if(new_node->data_.first < previous->data_.first){
        if(DEBUG_IN){
          cout << "[insert]left" << data.first << "\n";
        }
        previous->left_ = new_node;
    }else{
        if(DEBUG_IN){
          cout << "[insert]right " << data.first << "\n";
        }
        previous->right_ = new_node;
    }
    splayTheTree(new_node);
}
#define DEBUG_ERASE 0
template <class key_type, class mapped_type>
void 
SplayTree<key_type, mapped_type>::erase(const key_type& key)
{
    pair<bool, Iterator> ans = contains(key);
    if(!ans.first){
        printf("Node does not exist\n");
        return;
    }
    splay_node node = *ans.second.node_ptr_;
    splayTheTree(&node);
    SplayTree<key_type,mapped_type>* left_sub_tree;

    left_sub_tree->root_ = this->root_->left_;
    // node_t* lst_root = this->st_->root_->left_;
    if(left_sub_tree->root_ != nullptr){
        if(DEBUG_ERASE){
          cout << "[erase] making parent null of " << left_sub_tree->root_->data_.first << "\n";
        }
        
        left_sub_tree->root_->parent_ = nullptr;
    }

    splay_node* rst_root = this->root_->right_;
    if(rst_root != nullptr){
        rst_root->parent_ = nullptr;
    }

    if(left_sub_tree->root_ != nullptr){
        splay_node* max = &getRightmostLeaf(left_sub_tree->root_);
        left_sub_tree->splayTheTree(max);
        left_sub_tree->root_->right_ = rst_root;
        rst_root->parent_ = left_sub_tree->root_;
        root_ = left_sub_tree->root_;
    }else{
        this->root_ = rst_root;
    }
}

template <class key_type, class mapped_type>
typename SplayTree<key_type, mapped_type>::splay_node& 
SplayTree<key_type, mapped_type>::getLeaftmostLeaf(splay_node* root) const
{
  if(root == nullptr){
    root = root_;
  }
  while(root->left_ != nullptr){
    root = root->left_;
  }
  return *root;
}

template <class key_type, class mapped_type>
typename SplayTree<key_type, mapped_type>::splay_node& 
SplayTree<key_type, mapped_type>::getRightmostLeaf(splay_node* root) const
{
  if(root == nullptr){
    root = root_;
  }
  while(root->right_ != nullptr){
    root = root->right_;
  }
  //CHECK FOR NULL - DONE
  return *root;
}

template<typename key_type, typename mapped_type>
void 
SplayTree<key_type, mapped_type>::rotateRight(splay_node* node)
{
    // splay_tree_t* tree = this->st_;
    splay_node* leftChild = node->left_;
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
#define DEBUG_RL 0
template<typename key_type, typename mapped_type>
void 
SplayTree<key_type, mapped_type>::rotateLeft(splay_node* node)
{
    // splay_tree_t* tree = this->st_;
    splay_node* rightChild = node->right_;
    node->right_ = rightChild->left_;
    if(rightChild->left_ != nullptr){
        rightChild->left_->parent_ = node;
    }
        
    rightChild->parent_ = node->parent_;
    if(DEBUG_RL && node->parent_){
      cout << "[RL]setting parent of " << rightChild->data_.first << " to " << node->parent_->data_.first << "\n";
    }
    if(node->parent_ == nullptr){
        this->root_ = rightChild;
    }else if(node == node->parent_->left_){
        node->parent_->left_ = rightChild;
    }else{
        node->parent_->right_ = rightChild;
    }
    if(DEBUG_RL){
      cout << "[RL]splaying this " << node->data_.first << "\n";
    }
    rightChild->left_ = node;
    node->parent_ = rightChild;
}
#define DEBUG_STT 0
template<typename key_type, typename mapped_type>
void 
SplayTree<key_type, mapped_type>::splayTheTree(splay_node* new_node)
{
    // splay_tree_t* tree = this->st_;
    while(new_node->parent_ != nullptr){
        if(DEBUG_STT){
          cout << "[splaythetree]parent node === " << new_node->parent_->data_.first << "\n";
          cout << "[splaythetree]splaying node === " << new_node->data_.first << "\n";
        }
        if(new_node->parent_ == root_){
            if(new_node == root_->left_){
                rotateRight( new_node->parent_);
            }else{
                rotateLeft( new_node->parent_);
            }
        }else{
            splay_node* parent = new_node->parent_;
            splay_node* g_parent = parent->parent_;

            if(new_node->parent_->left_ == new_node && parent->parent_->left_ == parent){
                rotateRight( g_parent);
                rotateRight( parent);
            }else if(new_node->parent_->right_ == new_node && parent->parent_->right_ == parent){
                rotateLeft( g_parent);
                if(DEBUG_STT){
                  cout << "\n\n [splaythetree]print tree called\n";
                  printTree();
                  cout << "\n\n [splaythetree]print tree end\n";
                }
                
                rotateLeft( parent);
            }else if(new_node->parent_->right_ == new_node && parent->parent_->left_ == parent){
                rotateLeft( parent);
                rotateRight( g_parent);
            // }else if(new_node->parent_->left_ == new_node && parent->parent_->right_ == parent){
            }else{    
                rotateRight( parent);
                rotateLeft( g_parent);
            } 
        }
    }
}

template <class key_type, class mapped_type>
void 
SplayTree<key_type, mapped_type>::deleteNode(splay_node* root)
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
