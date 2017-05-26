/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: G. Taylor McClamroch
 * Purpose: Test AVL Tree
 * Created on May 25, 2017, 10:44 AM
 */

#include <cstdlib>
#include <iostream>
#include <time.h>
#include "AVL_Tree.h"

using namespace std;

int main(int argc, char** argv) 
{
    srand(time(0));
    Tree<int> test_tree1;
    
    //Randomly fill test tree with values 0-99
    for(int i = 0; i < 10; i++)
    {
        test_tree1.Insert(rand()%100);
    }
    
    //Print test tree in order
    cout << "Randomly filled Tree Printed in order: " << endl;
    test_tree1.PrintInOrder();
    cout << endl << endl;
    
    //New Tree
    cout << "Create new tree." << endl;
    Tree<int> test_tree2;
    
    //Refill tree with values 1 to 10
    cout << "Fill tree from 1 to 10." << endl << endl;
    for(int i = 1; i < 11; i++)
    {
        test_tree2.Insert(i);
    }
    
    //Print with 3 traversals
    cout << "Print inOrder: " << endl;
    test_tree2.PrintInOrder();
    cout << endl;
    
    cout << "Print preOrder: " << endl;
    test_tree2.PrintPreOrder();
    cout << endl;
    
    cout << "Print postOrder: " << endl;
    test_tree2.PrintPostOrder();
    cout << endl << endl;

    //Test Delete Function
    cout << "Delete 1: " << endl;
    test_tree2.Delete(1);
    test_tree2.PrintInOrder();
    cout << endl;
    
    cout << "Delete 10: " << endl;
    test_tree2.Delete(10);
    test_tree2.PrintInOrder();
    cout << endl;
    
    cout << "Delete 5: " << endl;
    test_tree2.Delete(5);
    test_tree2.PrintInOrder();
    cout << endl;
        
    return 0;
}

