#include "bstree.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

// constructor
BSTNode::BSTNode(int d){
    count = 1;
    value = d;
    left = right = NULL;
    
}

// destructor
BSTNode::~BSTNode() {
    
}

// constructor for BST
BSTree::BSTree(){
    root = NULL;
    n_elem = 0;

}

// destructor for BST
BSTree::~BSTree(){

}

// helper methods


void BSTree::rangeSearchHelper(BSTNode *p, int low, int high, std::vector<int> *range){
    if (p == NULL) return;
    if(p->value <=high && p->value>=low){
        range->push_back(p->value);
    }
    rangeSearchHelper(p->left,low,high,range);
    rangeSearchHelper(p->right,low,high,range);
    
}


unsigned int BSTree::getSize(BSTNode *ptr){
   if( ptr == NULL){
       return 0;
   }   
   else{
    if(ptr->left == NULL && ptr->right == NULL){
        return 1;
    }
    else{
        return(1 + (getSize(ptr->left) + getSize(ptr->right)));
    }
    }
}


void BSTree::clearAll(BSTNode *ptr){
    if ( ptr == NULL ){
        return;
    }
    clearAll( ptr->left );
    clearAll( ptr->right );
    delete ptr;
    root = NULL;
    n_elem=0;
}

void BSTree::print_allPrivate(BSTNode *ptr){
    if(root != NULL){
        if(ptr->left != NULL){
            print_allPrivate(ptr->left);
        }
        std::cout<< ptr->value <<" "<< ptr->count<<std::endl;
        if(ptr->right != NULL){
            print_allPrivate(ptr->right);
        }
    }
    else{
        
    }
}

int BSTree::findSmallestPrivate(BSTNode *temp){
    
    if(root == NULL){
        
    }
    else{
       if(temp->left != NULL){
           findSmallestPrivate(temp->left);
       }
       else{
           return temp->value;
       }
    }
}

void BSTree::removeMatch(BSTNode *parent , BSTNode *match , bool left){
        if(root != NULL){
        BSTNode* temp;
        int matchKey = match->value;
        int smallestInRightSubtree;
        
        if(match->left ==NULL && match->right == NULL){
           if(match->count > 1){
               match->count--;
           }
           else{
           temp = match;
           left == true ? parent->left = NULL : parent->right = NULL;
           delete temp;
           }
        }
        else if(match->left == NULL && match->right != NULL){
            if(match->count > 1){
               match->count--;
           }
            else{
            left == true ? parent->left = match->right : parent->right = match->right;
            match->right = NULL;
            temp = match;
            delete temp;
            }
        }
        else if(match->left != NULL && match->right == NULL){
            if(match->count > 1){
               match->count--;
           }
            else{
            left == true ? parent->left = match->left : parent->right = match->left;
            match->left = NULL;
            temp = match;
            delete temp;
            }
        }
        else{
            if(match->count > 1){
               match->count--;
           }
            else{
            smallestInRightSubtree = findSmallestPrivate(match->right);
            removePrivate(smallestInRightSubtree , match);
            match->value = smallestInRightSubtree;
            }
        }
    }
    else{
        return;
    }
}

void BSTree::removeRootMatch(){
    if(root != NULL){
        BSTNode *temp = root;
        int rootVal = root->value;
        int smallestInRightSubtree;
        // case 0 children
        if(root->left == NULL && root->right == NULL){
            if(root->count >1){
                root->count--;
            }
            else{
                root = NULL;
                delete temp;
            }
        }
        // case with 1 child
        else if(root ->left == NULL && root->right != NULL){
            if(root->count >1){
                root->count--;
            }
            else{
                root = root->right;
                temp->right = NULL;
                delete temp;
            }
        }
        else if(root ->left != NULL && root->right == NULL){
            if(root->count >1){
                root->count--;
            }
            else{
                root = root->left;
                temp->left = NULL;
                delete temp;
            }
        }
        else{
            if(root->count >1){
                root->count--;
            }
            else{
                smallestInRightSubtree = findSmallestPrivate(root->right);
                removePrivate(smallestInRightSubtree , root);
                root->value = smallestInRightSubtree;
                
            }
        
            
        }
        
    }
}


void BSTree::removePrivate(const int num , BSTNode *parent){
    if(root != NULL){
        if(root-> value == num){
            removeRootMatch();
        }
        else{
            if(num < parent->value && parent->left != NULL){
                parent->left->value == num ?
                removeMatch(parent,parent->left,true) :
                removePrivate(num , parent->left);
            }
            else if(num > parent->value && parent->right != NULL){
                parent->right->value == num ?
                removeMatch(parent,parent->right,false) :
                removePrivate(num , parent->right);
            }
            else{
                return;
            }
        }
    }
}


/*
void BSTree::theRemove(BSTNode *node, int item)  //private
{
    if(node == NULL)
    {
        return;
    }
    else if(item < node->value)
    {
        theRemove(node->left, item);
    }
    else if(item > node->value)
    {
        theRemove(node->right, item);
    }
    else    //item == node->data
    {
        if(node->count>1){
            node->count--;
        }
        else{
            BSTNode *temp = node;
            if(node->right == NULL)
            {
                node = node->left
                
            }
            else if(node->left == NULL)
            {
                node = node->right;
                
            }
            else{
                int min_val = findSmallestPrivate(node->right);
                theRemove(node->right, min_val);
                node->value = min_val;
                return;
                
            }
            delete temp;
            
        }
        
    }   
}
*/
void BSTree::insertPrivate(const int num , BSTNode *temp){
    if(root == NULL){
        root = new BSTNode(num);
        
    }
    else if(num < temp->value){
        if(temp->left != NULL){
            insertPrivate(num , temp->left);
        }
        else{
            temp->left = new BSTNode(num);
            n_elem++;
        }
        
    }
    else if(num > temp->value){
        if(temp->right != NULL){
            insertPrivate(num , temp->right);
        }
        else{
            temp->right = new BSTNode(num);
            n_elem++;
        }
        
    }
    else{
        temp->count++;
    }    
}
// insert method
void BSTree::insert(const int num){
    
    insertPrivate(num , root);
    
}


// contains method
int BSTree::contains(const int num){
    BSTNode *temp = root;

    while (temp != NULL)
    {
        if (temp->value == num){
            break;
        }
        if (num > temp->value){
            temp = temp->right;
        }    
        else{                
        if (num < temp->value){
            temp = temp->left;
        }
    }    
}

    if (temp == NULL){
        return 0;
    }    

    if (temp->value == num){
        return 1;
    }    
    return 0;
}

//delete method
void BSTree::remove(const int num){
    removePrivate(num,root);
}

//checks if bst is empty
int BSTree::empty(){
    if(root == NULL){
        return 1;
    }
    else{
        return 0;
    }
}

//checks the size of the bst
unsigned int BSTree::size(){
    return getSize(root);
}

//deletes all nodes from bst
void BSTree::clear(){
    clearAll(root);
}

// checks if there are values in bst within a certain range
void BSTree::range_search(const int l, const int r, std::vector<int> *range){
    rangeSearchHelper(root, l, r, range);
}

// prints all elements in bst
void BSTree::print_all(){
    print_allPrivate(root);
}