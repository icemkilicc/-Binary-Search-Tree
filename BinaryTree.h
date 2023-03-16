
#ifndef ASSIGMENT4_BINARYTREE_H
#define ASSIGMENT4_BINARYTREE_H


#include <string>

using namespace std;


class BinaryTree {

public:

    BinaryTree *rightNode = nullptr;
    BinaryTree *leftNode = nullptr;
    BinaryTree *SecondaryNode = nullptr;

    string names;
    string category;
    int price;
    bool color = true;


    BinaryTree *ifNodeExists(BinaryTree  **node, string names);
    BinaryTree* insert(BinaryTree **head, string category , string names , int price);
    BinaryTree* insertSecondary(BinaryTree **head, string names , int price);
    BinaryTree* remove(BinaryTree **head ,string names);
    void printAllItems(BinaryTree **head,ofstream &file1);
    void printAllItemsInCategory(BinaryTree **head, string category,ofstream &file1);
    void printItem(BinaryTree **head , string category , string names,ofstream &file1);
    void find(BinaryTree **head , string category , string names,ofstream &file1);
    void updateData(BinaryTree **head , string category , string names , int price);
    BinaryTree* insertRedBlack(BinaryTree **head, string names , int price);
    BinaryTree* removeRedBlack(BinaryTree **head, string names );
};


#endif
