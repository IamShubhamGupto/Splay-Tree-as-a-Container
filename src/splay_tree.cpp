#include <iostream>
#include <algorithm>
#include <utility>
#include "splay_tree.h"
using namespace std;
#define DEBUG 1

template<typename T1, typename T2>
typename SplayTree<T1, T2>::node_t* SplayTree<T1, T2>::makeNewNode(const pair<T1, T2>& data){
    node_t* temp = new node_t;
    temp->data_.first = data.first;
    temp->data_.second = data.second;
    temp->left_ = NULL;
    temp->right_ = NULL;
    temp->parent_ = NULL;
    return temp;
}
template<typename T1, typename T2>
typename SplayTree<T1, T2>::node_t* SplayTree<T1, T2>::maximum(node_t* node){
    while(node->right_ != NULL){
        node = node->right_;
    }
    return node;
}
template<typename T1, typename T2>
SplayTree<T1, T2>:: SplayTree(): st_(new splay_tree_t){
    st_->root_ = NULL;
    if(DEBUG){
        cout << "ctor called\n";
    }
    
}
template<typename T1, typename T2>
SplayTree<T1, T2>:: ~SplayTree(){
    delete st_;
    if(DEBUG){
        cout << "dtor called\n";
    }   
}
template<typename T1, typename T2>
void SplayTree<T1, T2>::rotateRight(node_t* node){
    splay_tree_t* tree = this->st_;
    node_t* leftChild = node->left_;
    node->left_ = leftChild->right_;
    if(leftChild->right_ != NULL){
        leftChild->right_->parent_ = node;
    }
        
    leftChild->parent_ = node->parent_;
    if(node->parent_ == NULL){
        tree->root_ = leftChild;
    }else if(node == node->parent_->right_){
        node->parent_->right_ = leftChild;
    }else{
        node->parent_->left_ = leftChild;
    }
    leftChild->right_ = node;
    node->parent_ = leftChild;
}

template<typename T1, typename T2>
void SplayTree<T1, T2>::rotateLeft(node_t* node){
    splay_tree_t* tree = this->st_;
    node_t* rightChild = node->right_;
    node->right_ = rightChild->left_;
    if(rightChild->left_ != NULL){
        rightChild->left_->parent_ = node;
    }
        
    rightChild->parent_ = node->parent_;
    if(node->parent_ == NULL){
        tree->root_ = rightChild;
    }else if(node == node->parent_->left_){
        node->parent_->left_ = rightChild;
    }else{
        node->parent_->right_ = rightChild;
    }
    rightChild->left_ = node;
    node->parent_ = rightChild;
}

template<typename T1, typename T2>
void SplayTree<T1, T2>::splayTheTree( node_t* new_node){
    splay_tree_t* tree = this->st_;
    while(new_node->parent_ != NULL){
        if(new_node->parent_ == tree->root_){
            if(new_node == tree->root_->left_){
                rotateRight( new_node->parent_);
            }else{
                rotateLeft( new_node->parent_);
            }
        }else{
            node_t* parent = new_node->parent_;
            node_t* g_parent = parent->parent_;

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

template<typename T1, typename T2>
void SplayTree<T1, T2>::insert(const pair<T1, T2>& data){
    splay_tree_t* tree = this->st_;
    node_t* current = tree->root_;
    node_t* previous = NULL;

    while(current != NULL && current->data_.first != data.first){
        previous = current;
        if(data.first < current->data_.first){
            current = current->left_;
        }else{
            current = current->right_;
        }
    }
    node_t* new_node = makeNewNode(data);
    new_node->parent_ = previous;
    if(previous == NULL){
        tree->root_ = new_node;
    }else if(current != NULL && current->data_.first == data.first){
        current->data_.second = data.second;
        splayTheTree( current);
        return;    
    }else if(new_node->data_.first < previous->data_.first){
        previous->left_ = new_node;
    }else{
        previous->right_ = new_node;
    }
    splayTheTree( new_node);
}

template<typename T1, typename T2>
T2 SplayTree<T1, T2>::find(const T1 key){
    splay_tree_t* tree = this->st_;
    T2 val = T2();
    node_t* current = tree->root_;
    node_t* previous = NULL;
    while(current != NULL && current->data_.first != key){
        previous = current;
        if(key < current->data_.first){
            current = current-> left_;
        }else{
            current = current->right_;
        }

    }
    
    if(current == NULL){
        splayTheTree( previous);
    }else if(current->data_.first == key){
        val = current->data_.second;
        splayTheTree( current);
    }else{
        val = T2();
        splayTheTree( previous);
    }
    return val;
}

template<typename T1, typename T2>
void SplayTree<T1, T2>::delete_node(const T1 key){
    T2 val = find(key);
    if(val == T2()){
        printf("Node does not exist\n");
        return;
    }
    SplayTree<T1,T2> left_sub_tree;
    left_sub_tree.st_->root_ = this->st_->root_->left_;
    // node_t* lst_root = this->st_->root_->left_;
    if(left_sub_tree.st_->root_ != NULL){
        left_sub_tree.st_->root_->parent_ = NULL;
    }

    node_t* rst_root = this->st_->root_->right_;
    if(rst_root != NULL){
        rst_root->parent_ = NULL;
    }

    if(left_sub_tree.st_->root_ != NULL){
        node_t* m = maximum(left_sub_tree.st_->root_);
        left_sub_tree.splayTheTree(m);
        left_sub_tree.st_->root_->right_ = rst_root;
        this->st_->root_ = left_sub_tree.st_->root_;
    }else{
        this->st_->root_ = rst_root;
    }
}
//inorder traversal
template<typename T1, typename T2>
void SplayTree<T1,T2>::in_order_traverser(node_t* root){
    if(root == NULL){
        return;
    }
    in_order_traverser(root->left_);
    cout << root->data_.first << " - " << root->data_.second << "\n";
    in_order_traverser(root->right_);
}

template<typename T1, typename T2>
void SplayTree<T1,T2>::display(){
    splay_tree_t* tree = this->st_;
    node_t* root = tree->root_;
    in_order_traverser(root);

}
//delete this
// template<typename T1, typename T2>
// ostream& operator<<(ostream& o, const SplayTree<T1, T2>& splaytree){
//     return o << splaytree.st_->root_->key_ << " - " << splaytree.st_->root_->key_ << "\n";
// }
