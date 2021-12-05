#include "Rope.h"

#include <iostream>
#include <vector>
#include <string>
#include <memory>

using namespace std;

Rope::Rope(){
    
shared_ptr<rope_node> root_ptr_(NULL);

}

Rope::~Rope(){
    
}

//Initialize a rope node
shared_ptr<rope_node> Rope::InitNode(string text){
    
    shared_ptr<rope_node> newone(new rope_node);
    newone->input = text;
    newone->left = NULL;
    newone->right = NULL;
    newone->is_leaf = false;
    newone->length = text.size();
    newone->weight = 0;
    newone->parent = NULL;

    return newone;
}

//***********************************************************************************

//MakeTree is unfinished, began it right after initNode then realized I 
//need some helper functions built before implementing this (concatenate, split, balance)
shared_ptr<rope_node> Rope::MakeTree(shared_ptr<rope_node> root_ptr, string input){
    
    shared_ptr<rope_node> curNode(new rope_node);
    shared_ptr<rope_node> leafNode(new rope_node);
    string blank = "";
    
    curNode = root_ptr;

    //Set up the leaf with the string and the weight
    //so the info can then be passed to the new root node
    leafNode = InitNode(input);
    leafNode->is_leaf = true;
    leafNode->weight = leafNode->length;

    //If root is Null this will be the beginning of the tree
    if(curNode == NULL){

        curNode = InitNode(blank);
        curNode->left = leafNode;
        curNode->weight = leafNode->weight;

    }

    else{
        //If no left node, insert it here
        if(curNode->left == NULL){

            curNode->left = leafNode;
            curNode->weight = leafNode->weight;

        }

        //if a left node exists but no right node, insert it here
        if(curNode->left != NULL && curNode->right == NULL){

            curNode->right = leafNode;
            curNode->weight = leafNode->weight;
        }
        
        //root has 2 children
        if(curNode->left != NULL && curNode->right != NULL){
            shared_ptr<rope_node> newtop(new rope_node);
            shared_ptr<rope_node> temp(new rope_node);

            temp = curNode;

            newtop = InitNode(blank);
            newtop->left = temp;
            newtop->right = leafNode;
            newtop->weight = temp->weight + leafNode->weight;

            curNode = newtop;
        }
    }
    return curNode;
}

//***********************************************************************************

//This concatenate is specific to concatenating 2 string nodes, Take the freshly
//Initialized nodes and set then as leaves with correct weights then concatenate
//put together with a non-leaf node as the root
shared_ptr<rope_node> Rope::Concatenate(shared_ptr<rope_node> a, shared_ptr<rope_node> b){

    shared_ptr<rope_node> newtop(new rope_node);
    string blank = "";

    newtop = InitNode(blank);
    newtop->left = a;
    newtop->left->is_leaf = true;
    newtop->left->weight = newtop->left->length;
    newtop->right = b;
    newtop->right->is_leaf = true;
    newtop->right->weight = newtop->right->length;
    newtop->left->parent = newtop;
    newtop->right->parent = newtop;

    newtop->weight = newtop->left->weight;

    return newtop;
}

//***********************************************************************************

//Index string, receives a rope node's root node then searches for the stored
//string of int i, basically if you were looking for what is saved 8 char's in
//because this is storing strings as immutable objects it will return the whole
//string not the char at that specified location

void Rope::Index_string(shared_ptr<rope_node> root_ptr, int i, string& output){

    shared_ptr<rope_node> curNode(new rope_node);
    curNode = root_ptr;

    if(curNode->is_leaf){
        output = curNode->input;
        return;
    }

    if(curNode->right != NULL && curNode->weight < i ){
        //cout << "I'm in right" << endl;
        i = i - curNode->weight;
        Index_string(curNode->right, i, output);
        curNode = curNode->right;
        if(!curNode->is_leaf){
            return;
        }
    }

    if(curNode->left != NULL  ){
        //cout << "I'm in left" << endl;
        Index_string(curNode->left, i, output);
        curNode = curNode->left;
        if(!curNode->is_leaf){
            return;
        }
    } 
  return;
}

//***********************************************************************************

//Similar to index string but updates your pointer to the node with the 
//number within the string you are searching for - to be utilized in split
//function
void Rope::Index_location(shared_ptr<rope_node>& root_ptr, int i){

    if(root_ptr->is_leaf){
        return;
    }

    if(root_ptr->right != NULL && root_ptr->weight < i ){
        //cout << "I'm in right" << endl;
        i = i - root_ptr->weight;
        Index_location(root_ptr->right, i);
        root_ptr = root_ptr->right;
        if(!root_ptr->is_leaf){
            return;
        }
    }

    if(root_ptr->left != NULL  ){
        //cout << "I'm in left" << endl;
        Index_location(root_ptr->left, i);
        root_ptr = root_ptr->left;
        if(!root_ptr->is_leaf){
            return;
        }
    } 
  return;
}

//***********************************************************************************

//Take a basic rope structure a split it returning the left most root to the
//new node and update the reference node with the new right node root, set the
//leaf nodes in the left pointer locations
shared_ptr<rope_node> Rope::Split(shared_ptr<rope_node>& root_ptr, int i){

    shared_ptr<rope_node> parent;
    shared_ptr<rope_node> newParent;
    string blank = "";

    newParent = InitNode(blank);
    SetRoot(root_ptr);

    Index_location(root_ptr,i);
    parent = root_ptr->parent;

    if(parent->right == root_ptr){
        newParent->left = root_ptr;
        newParent->weight = newParent->left->length;
        newParent->left->parent = newParent;
        parent->right = NULL;
        root_ptr = newParent;
        return parent;
    }

    else{
        newParent->left = parent->left;
        newParent->weight = newParent->left->length;
        newParent->left->parent = newParent;
        parent->left = parent->right;
        parent->right = NULL;
        root_ptr = parent;
        return newParent;
    }

}


//***********************************************************************************

// This function is implemented for you
// Returns the root pointer
shared_ptr<rope_node> Rope::GetRoot(){
  return root_ptr_;
}

// This function is implemented for you
// sets a given pointer as the top pointer
void Rope::SetRoot(shared_ptr<rope_node> root_ptr){
  root_ptr_ = root_ptr;
}