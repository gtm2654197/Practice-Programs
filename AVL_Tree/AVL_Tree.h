/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AVL_Tree.h
 * Author: G. Taylor McClamroch
 * Purpose: AVL Tree definition and implementation
 * Created on May 25, 2017, 10:44 AM
 */


#include <cstdlib>
#include <iostream>

using namespace std;

#ifndef AVL_TREE_H
#define AVL_TREE_H

template<class T>
struct node
{
    int height = 0;
    T record;
    node* left = NULL;
    node* right = NULL;
    node* parent = NULL;
};

template<class T>
class Tree
{
    public:
        Tree();
        ~Tree();
        void Clear(node<T>* nodeptr);
        node<T>* getRoot();
        void Insert(T data);
        void Insert(T data, node<T>* nodeptr);  
        void fixRoot();
        void Delete(T data);
        void Delete(node<T>* nodeptr);
        int Number_of_Children(node<T>* nodeptr);
        node<T>* findSmallest(node<T>* nodeptr);
        void Balance(node<T>* nodeptr);
        void Left_Rotate(node<T>* nodeptr);
        void Right_Rotate(node<T>* nodeptr);
        int Height_Diff(node<T>* nodeptr);
        int height(node<T>* nodeptr);
        node<T>* Search(T data);
        void PrintInOrder();
        void PrintInOrder(node<T>* nodeptr);
        void PrintPreOrder();
        void PrintPreOrder(node<T>* nodeptr);
        void PrintPostOrder(); 
        void PrintPostOrder(node<T>* nodeptr); 
        
    private:
        node<T>* root;            
};

template<class T>
Tree<T>::Tree()
{
    root = NULL;
}

template<class T>
Tree<T>::~Tree()
{    
    Clear(root);    
}

template<class T>
void Tree<T>::Clear(node<T>* nodeptr)
{
    if(nodeptr == NULL) return;
    Clear(nodeptr->left);
    Clear(nodeptr->right);
    delete nodeptr;
    nodeptr = NULL;
}

template<class T>
node<T>* Tree<T>::getRoot()
{
    return root;
}

template<class T>
void Tree<T>::Insert(T data)  //User uses this function, not requiring root node
{
    if(root == NULL)
    {
        root = new node<T>;
        root->record = data;
    }
    else
    {
        Insert(data, root);   
        fixRoot();
    }
}

template<class T>
void Tree<T>::Insert(T data, node<T>* nodeptr)  //User insert function calls this recursive function
{    
    if(data < nodeptr->record)
    {
        //If left height is >= right height, increment height of root
        if(height(nodeptr->left) >= height(nodeptr->right)) nodeptr->height++;
        if(nodeptr->left != NULL)
        {
            Insert(data, nodeptr->left);
        }
        else
        {
            nodeptr->left = new node<T>;
            nodeptr->left->parent = nodeptr;
            nodeptr->left->record = data;
            node<T>* walker = nodeptr;
            while(walker->parent != NULL)
            {                
                Balance(walker->parent);                
                walker = walker->parent;                
                if(walker == NULL) return;
            }     
        }
    }
    else
    {
        //If right height is >= left height, increment height of root
        if(height(nodeptr->right) >= height(nodeptr->left)) nodeptr->height++;
        if(nodeptr->right != NULL)
        {
            Insert(data, nodeptr->right);
        }
        else
        {
            nodeptr->right = new node<T>;
            nodeptr->right->parent = nodeptr;
            nodeptr->right->record = data;
            node<T>* walker = nodeptr;
            while(walker->parent != NULL)
            {                
                Balance(walker->parent);                
                walker = walker->parent;                
                if(walker == NULL) return;
            }          
        }
    }
}

template<class T>
void Tree<T>::fixRoot()
{
    while(root->parent != NULL)
    {
        root = root->parent;
    }
}

template<class T>
void Tree<T>::Delete(T data)
{
    node<T>* deleteMe = Search(data);
    if(deleteMe != NULL) Delete(deleteMe);
}

template<class T>
void Tree<T>::Delete(node<T>* nodeptr)
{
    if(nodeptr == NULL) return;
    int children = Number_of_Children(nodeptr);
    if(children == 0)
    {
        if(nodeptr->parent != NULL)
        {                
            node<T>* parent = nodeptr->parent;           
            if(parent->left == nodeptr)
            {
                parent->left = NULL;
                parent->height = height(parent->right) + 1;
            }
            else
            {
                parent->right = NULL;   
                parent->height = height(parent->left) + 1;
            }            
            delete nodeptr;            
            node<T>* walker = parent;
            while(walker->parent != NULL)
            {                 
                Balance(walker->parent);                
                walker = walker->parent;                
                if(walker == NULL) return;
            }     
        }
        else
        {
            delete nodeptr;
            root = NULL;
        }
    }
    else if(children == 1)
    { 
        if(nodeptr->parent == NULL)
        {
            if(nodeptr->left != NULL) root = nodeptr->left;            
            else root = nodeptr->right;
            root->parent = NULL;
            delete nodeptr;
        }
        else
        {
            node<T>* temp;
            if(nodeptr->left != NULL) temp = nodeptr->left;
            else temp = nodeptr->right;
            if(nodeptr->parent == NULL)
            {
                root = temp;
                temp->parent = NULL;
                delete nodeptr;
            }
            else
            {
                if(nodeptr->parent->left == nodeptr) nodeptr->parent->left = temp;            
                else nodeptr->parent->right = temp;
                temp->parent = nodeptr->parent;
                delete nodeptr;
                node<T>* walker = temp->parent;
                while(walker->parent != NULL)
                {                
                    Balance(walker->parent);                
                    walker = walker->parent;                
                    if(walker == NULL) return;
                }    
            }
        }
    } 
    else if(children == 2)
    {
        node<T>* smallest = findSmallest(nodeptr->right);
        nodeptr->record = smallest->record;        
        Delete(smallest);
    }
    fixRoot();
}

template<class T>
int Tree<T>::Number_of_Children(node<T>* nodeptr)
{
    if(nodeptr->left == NULL && nodeptr->right == NULL) return 0;
    else if(nodeptr->left != NULL && nodeptr->right != NULL) return 2;
    else return 1;
}

template<class T>
node<T>* Tree<T>::findSmallest(node<T>* nodeptr)
{
    while(nodeptr->left != NULL)
    {
        nodeptr = nodeptr->left;
    }    
    return nodeptr;
}

template<class T>
void Tree<T>::Balance(node<T>* nodeptr)
{
    int bal_diff = Height_Diff(nodeptr);
    if(bal_diff > 1)
    {        
        if(Height_Diff(nodeptr->left) > 0)
        {
            Right_Rotate(nodeptr);
            return;
        }
        else
        {
            Left_Rotate(nodeptr->left);
            Right_Rotate(nodeptr);
            return;
        }
    }
    else if(bal_diff < -1)
    {       
        if(Height_Diff(nodeptr->right) < 0)
        {
            Left_Rotate(nodeptr);
            return;
        }
        else
        {
            Right_Rotate(nodeptr->right);
            Left_Rotate(nodeptr);
            return;
        }
    }
}

template<class T>
void Tree<T>::Left_Rotate(node<T>* nodeptr)
{    
    node<T>* temp = nodeptr->right;    
    nodeptr->right = temp->left;    
    if(nodeptr->right != NULL) nodeptr->right->parent = nodeptr;    
    temp->left = nodeptr;    
    temp->parent = nodeptr->parent;     
    if(temp->parent != NULL)
    {
        if(temp->parent->left == nodeptr) temp->parent->left = temp;
        else temp->parent->right = temp;   
    }    
    nodeptr->parent = temp;    
    //Fix heights after rotation
    if(height(nodeptr->left) >= height(nodeptr->right)) nodeptr->height = height(nodeptr->left) + 1;
    else nodeptr->height = height(nodeptr->right) + 1;
    if(height(temp->left) >= height(temp->right)) temp->height = height(temp->left) + 1;
    else temp->height = height(temp->right) + 1;    
    if(temp->parent != NULL)
    {
        if(height(temp->parent->left) >= height(temp->parent->right)) temp->parent->height = height(temp->parent->left) + 1;
        else temp->parent->height = height(temp->parent->right) + 1;
    }    
}

template<class T>
void Tree<T>::Right_Rotate(node<T>* nodeptr)  //Right rotate of nodeptr when left height > right height
{    
    node<T>* temp = nodeptr->left;
    nodeptr->left = temp->right;
    temp->right = nodeptr;
    temp->parent = nodeptr->parent;
    if(temp->parent != NULL)
    {
        if(temp->parent->left == nodeptr) temp->parent->left = temp;
        else temp->parent->right = temp;   
    }
    nodeptr->parent = temp;
    //Fix heights after rotation
    if(height(nodeptr->left) >= height(nodeptr->right)) nodeptr->height = height(nodeptr->left) + 1;
    else nodeptr->height = height(nodeptr->right) + 1;
    if(height(temp->left) >= height(temp->right)) temp->height = height(temp->left) + 1;
    else temp->height = height(temp->right) + 1;
    if(temp->parent != NULL)
    {
        if(height(temp->parent->left) >= height(temp->parent->right)) temp->parent->height = height(temp->parent->left) + 1;
        else temp->parent->height = height(temp->parent->right) + 1;
    }
}

template<class T>
int Tree<T>::Height_Diff(node<T>* nodeptr)
{
    return (height(nodeptr->left) - height(nodeptr->right));
}

template<class T>
int Tree<T>::height(node<T>* nodeptr)
{
    if(nodeptr == NULL) return -1;
    else return nodeptr->height;
}

template<class T>
node<T>* Tree<T>::Search(T data)
{
    bool found = false;
    node<T>* walker = root;
    while(!found && walker != NULL)
    {
        if(walker->record == data) found = true;
        else
        {
            if(data < walker->record) walker = walker->left;
            else walker = walker->right;
        }
    }
    return walker;
}

template<class T>
void Tree<T>::PrintInOrder()
{
    PrintInOrder(root);
}

template<class T>
void Tree<T>::PrintInOrder(node<T>* nodeptr)
{    
    if(nodeptr == NULL) return;
    PrintInOrder(nodeptr->left);
    cout << nodeptr->record << " ";
    PrintInOrder(nodeptr->right);
}

template<class T>
void Tree<T>::PrintPreOrder()
{
    PrintPreOrder(root);
}

template<class T>
void Tree<T>::PrintPreOrder(node<T>* nodeptr)
{
    if(nodeptr == NULL) return;
    cout << nodeptr->record << " ";
    PrintPreOrder(nodeptr->left);
    PrintPreOrder(nodeptr->right);
}

template<class T>
void Tree<T>::PrintPostOrder()
{
    PrintPostOrder(root);
}

template<class T>
void Tree<T>::PrintPostOrder(node<T>* nodeptr)
{
    if(nodeptr == NULL) return;
    PrintPostOrder(nodeptr->left);
    PrintPostOrder(nodeptr->right);
    cout << nodeptr->record << " ";
}

#endif /* AVL_TREE_H */

