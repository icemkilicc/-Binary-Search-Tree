
#include <iostream>
#include <vector>
#include "BinaryTree.h"
#include <fstream>

using namespace std;

BinaryTree *BinaryTree::ifNodeExists(BinaryTree **node, string names) {
    BinaryTree *first_node = *node;
    if (first_node == nullptr){
        return nullptr;
    }
    if ( first_node->category == names){
        return first_node;
    }
    if(first_node->names == names){
        return first_node;
    }
    BinaryTree *res1 = ifNodeExists(&first_node->leftNode, names);
    if(res1 != nullptr){
        return res1;
    }
    BinaryTree *res2 = ifNodeExists(&first_node->rightNode, names);

    return res2;
}

int height(BinaryTree **root){
    BinaryTree *copy = *root;

    if(copy == nullptr){
        return 0;
    }
    else{
        int right_height = height(&copy->rightNode);
        int left_height = height(&copy->leftNode);

        if (left_height > right_height) {
            return (left_height + 1);
        }
        else {
            return (right_height + 1);
        }
    }


}

int balance_number(BinaryTree **node){
    BinaryTree *copy = *node;

    if(copy == nullptr){
        return 0;
    }

    BinaryTree *left = copy->leftNode;
    BinaryTree *right = copy->rightNode;
    return height(&left) - height(&right);

}

BinaryTree *rotate_right(BinaryTree **head){
    BinaryTree *copy = *head;
    BinaryTree *copy1 = copy->leftNode;
    BinaryTree *copy2 = copy1->rightNode;

    copy1->rightNode = copy;
    copy->leftNode = copy2;

    return copy1;
}

BinaryTree *rotate_left(BinaryTree **head){
    BinaryTree *copy = *head;
    BinaryTree *copy1 = copy->rightNode;
    BinaryTree *copy2 = copy1->leftNode;

    copy1->leftNode = copy;
    copy->rightNode = copy2;

    return copy1;
}


BinaryTree* BinaryTree::insert(BinaryTree **head, string category,string names , int price) {

    BinaryTree *copy = *head;

    if (copy == nullptr){
        BinaryTree *new_Node = new BinaryTree;
        BinaryTree *new_Node2 = new BinaryTree;
        new_Node->category = category;
        new_Node2->names = names;
        new_Node2->price = price;
        new_Node->SecondaryNode = new_Node2;
        return new_Node;
    }
    if(category < copy->category){
        copy->leftNode = insert(&copy->leftNode, category, names,price);
    }
    else if (category > copy->category){
        copy->rightNode = insert(&copy->rightNode, category,names,price);
    }
    else{
        return copy;
    }

    return copy;

}
BinaryTree* BinaryTree::insertSecondary(BinaryTree **head, string names , int price) {

    BinaryTree *copy = *head;

    if (copy == nullptr){
        BinaryTree *new_Node = new BinaryTree;
        new_Node->names = names;
        new_Node->price = price;
        return new_Node;
    }
    if(names < copy->names){
        copy->leftNode = insertSecondary(&copy->leftNode, names,price);
    }
    else if (names > copy->names){
        copy->rightNode = insertSecondary(&copy->rightNode, names,price);
    }
    else{
        return copy;
    }
    int b_number = balance_number(&copy);

    if (b_number > 1 && names < copy->leftNode->names){
        return rotate_right(&copy);
    }

    if (b_number < -1 && names > copy->rightNode->names){
        return rotate_left(&copy);
    }

    if (b_number > 1 && names > copy->leftNode->names){
        copy->leftNode = rotate_left(&copy->leftNode);
        return rotate_right(&copy);
    }

    if (b_number < -1 && names < copy->rightNode->names){
        copy->rightNode = rotate_right(&copy->rightNode);
        return rotate_left(&copy);
    }

    return copy;

}

BinaryTree* BinaryTree::remove(BinaryTree **head, string names) {

    BinaryTree *copy = *head;

    if(copy == nullptr){
        return nullptr;
    }
    if(names < copy->names){
        copy->leftNode = remove(&copy->leftNode, names);
    }
    else if (names > copy->names){
        copy->rightNode = remove(&copy->rightNode, names);
    }
    else{
        if(copy->rightNode == nullptr && copy->leftNode == nullptr){
            return nullptr;
        }
        else if (copy->leftNode == nullptr ){
            BinaryTree *copy2 = copy->rightNode;
            free(copy);
            return  copy2;
        }
        else if ( copy->rightNode == nullptr){
            BinaryTree *copy2 = copy->leftNode;
            free(copy);
            return  copy2;
        }
        BinaryTree *right_min = copy->rightNode;

        while (right_min && right_min->leftNode != nullptr){
            right_min = right_min->leftNode;
        }
        copy->names = right_min->names;
        copy->price = right_min->price;

        copy->rightNode = remove(&copy->rightNode, right_min->names);
    }

    int b_number = balance_number(&copy);

    if (b_number > 1 && balance_number(&copy->leftNode) >= 0){
        return rotate_right(&copy);
    }

    if (b_number < -1 &&  balance_number(&copy->leftNode) < 0){
        return rotate_left(&copy);
    }

    if (b_number > 1 &&  balance_number(&copy->rightNode) <= 0){
        copy->leftNode = rotate_left(&copy->leftNode);
        return rotate_right(&copy);
    }

    if (b_number < -1 &&  balance_number(&copy->rightNode) > 0){
        copy->rightNode = rotate_right(&copy->rightNode);
        return rotate_left(&copy);
    }


    return copy;


}

void level_Print(BinaryTree **head , int len,ofstream &file1){
    BinaryTree *copy = *head;

    if(copy == nullptr){
        return;
    }
    else if ( len == 1){
        if(copy->category == ""){
            file1 <<  "\"" << copy->names  <<"\""<<":" << "\"" << copy->price  <<"\",";
        }
        else{
            file1 <<"\"" << copy->category  <<"\""<<":" ;
            int lenSecondary = height(&copy->SecondaryNode);
            if(lenSecondary ==0){
                file1 << "{}";
            }
            file1 <<"\n";
            for (int i = 1; i <= lenSecondary; ++i) {
                file1 << "        ";
                level_Print(&copy->SecondaryNode, i,file1);
                file1 << "\n";
            }
        }
    }
    else if ( len > 1){
        level_Print(&copy->leftNode, len-1,file1);
        level_Print(&copy->rightNode, len-1,file1);
    }

}

void BinaryTree::printAllItems(BinaryTree **head,ofstream &file1) {

    file1 << "command:printAllItems" << "\n";
    file1 << "{" << "\n";

    BinaryTree *copy = *head;
    int len = height(&copy);

    for (int i = 1; i <= len; ++i) {
        level_Print(&copy, i,file1);
    }
    file1 << "}" << "\n";

}

void BinaryTree::printAllItemsInCategory(BinaryTree **head, string category,ofstream &file1) {

    file1 << "command:printAllItemsInCategory" << "\t"<< category<<  "\n";
    file1 << "{" << "\n";

    BinaryTree *copy;
    copy = ifNodeExists(head, category);

    level_Print(&copy , 1,file1);

    file1 << "}" << "\n";

}

void BinaryTree::printItem(BinaryTree **head, string category, string names,ofstream &file1) {

    file1 << "command:printItem" << "\t"<< category<<"\t"<< names <<  "\n";
    file1 << "{" ;

    BinaryTree *copy = *head;
    copy = ifNodeExists(&copy , category);
    BinaryTree *item = nullptr;
    if(copy != nullptr){
        item = ifNodeExists(&copy->SecondaryNode, names);
    }

    if(item != nullptr){
        file1 << "\n";
        file1 <<"\"" << category  <<"\""<<":" << "\n";
        file1 << "        " << "\"" << item->names  <<"\""<<":" << "\"" << item->price  <<"\"" << "\n";
    }

    file1 << "}" << "\n";



}

void BinaryTree::find(BinaryTree **head, string category, string names,ofstream &file1) {

    file1 << "command:find" << "\t"<< category<<"\t"<< names <<  "\n";
    file1 << "{";

    BinaryTree *copy = *head;
    copy = ifNodeExists(&copy , category);
    BinaryTree *item = nullptr;
    if(copy != nullptr){
        item = ifNodeExists(&copy->SecondaryNode, names);
    }

    if(item != nullptr){
        file1 << "\n";
        file1 <<"\"" << category  <<"\""<<":" << "\n";
        file1 << "        " << "\"" << item->names  <<"\""<<":" << "\"" << item->price  <<"\"" << "\n";
    }


    file1 << "}" << "\n";

}

void BinaryTree::updateData(BinaryTree **head, string category, string names, int price) {

    BinaryTree *copy = *head;
    copy = ifNodeExists(&copy , category);
    BinaryTree *item;
    item = ifNodeExists(&copy->SecondaryNode, names);

    item->price = price;
}
int colorF(BinaryTree **myNode){
    BinaryTree *copy = *myNode;

    if (copy == nullptr)
        return 0;

    return copy->color;
}


BinaryTree *BinaryTree::insertRedBlack(BinaryTree **head, string names, int price) {

    BinaryTree *copy = *head;

    if (copy == nullptr){
        BinaryTree *new_Node = new BinaryTree;
        new_Node->names = names;
        new_Node->price = price;
        new_Node->color = true;
        return new_Node;
    }
    if(names < copy->names){
        copy->leftNode = insertRedBlack(&copy->leftNode, names,price);
    }
    else if (names > copy->names){
        copy->rightNode = insertRedBlack(&copy->rightNode, names,price);
    }
    else{
        return copy;
    }

    if(colorF(&copy->rightNode) && !colorF(&copy->leftNode)){
        copy = rotate_left(&copy);
        bool tf = copy->color;
        copy->color = copy->leftNode->color;
        copy->leftNode->color = tf;
    }
    if(colorF(&copy->leftNode) && colorF(&copy->leftNode->leftNode)){
        copy = rotate_right(&copy);
        bool tf = copy->color;
        copy->color = copy->rightNode->color;
        copy->rightNode->color = tf;
    }
    if(colorF(&copy->leftNode) && colorF(&copy->rightNode)){
        copy->color = !copy->color;
        copy->rightNode->color = false;
        copy->leftNode->color = false;
    }

    return copy;

}
void FlipC(BinaryTree **head){
    BinaryTree *copy = *head;
    copy->color = !copy->color;
    if(copy->leftNode != nullptr){
        copy->leftNode->color = !copy->leftNode->color;
    }
    if(copy->rightNode != nullptr){
        copy->rightNode->color = !copy->rightNode->color;
    }
}
BinaryTree *moveRedLeft(BinaryTree **head){
    BinaryTree *copy = *head;
    FlipC(&copy);
    if(copy->rightNode != nullptr){
        if (colorF(&copy->rightNode->leftNode))
        {
            copy->rightNode = rotate_right(&copy->rightNode);
            copy = rotate_left(&copy);
            FlipC(&copy);
        }
    }
    return copy;
}
BinaryTree *moveRedRight(BinaryTree **head){
    BinaryTree *copy = *head;
    FlipC(&copy);
    if(copy->leftNode != nullptr){
        if (colorF(&copy->leftNode->leftNode))
        {
            copy = rotate_right(&copy);
            FlipC(&copy);
        }
    }
    return copy;
}
BinaryTree *find_min(BinaryTree ** head){
    BinaryTree *copy = *head;
    while(copy->leftNode != nullptr){
        copy = copy->leftNode;
    }
    return copy;
}
BinaryTree *fix_up(BinaryTree ** head){
    BinaryTree *copy = *head;

    if(colorF(&copy->rightNode)){
        copy = rotate_left(&copy);
    }
    if(colorF(&copy->leftNode)&& colorF(&copy->leftNode->leftNode)){
        copy = rotate_right(&copy);
    }
    if(colorF(&copy->leftNode)&& colorF(&copy->rightNode)){
        FlipC(&copy);
    }
    return copy;
}


BinaryTree *delete_min(BinaryTree ** head){
    BinaryTree *copy = *head;

    if(copy->leftNode == nullptr){
        free(copy);
        return nullptr;
    }
    if(colorF(&copy->leftNode) == false && colorF(&copy->leftNode->leftNode)== false){
        copy = moveRedLeft(&copy);
    }
    copy->leftNode = delete_min(&copy->leftNode);

    return fix_up(&copy);
}



BinaryTree *BinaryTree::removeRedBlack(BinaryTree **head, string names) {

    BinaryTree *copy = *head;

    if (names < copy->names){
        if(copy->leftNode != nullptr){
            if (!colorF(&copy->leftNode) && !colorF(&copy->leftNode->leftNode)){
                copy = moveRedLeft(&copy);
            }
            copy->leftNode = removeRedBlack(&copy->leftNode, names);
        }
    }
    else{
        if(colorF(&copy->leftNode)){
            copy = rotate_right(&copy);
        }
        if(names == copy->names && copy->rightNode == nullptr){
            free(copy);
            return nullptr;
        }
        if(!colorF(&copy->rightNode) && !colorF(&copy->rightNode->leftNode)){
            copy = moveRedRight(&copy);
        }
        if(copy->rightNode != nullptr){
            if(names == copy->names ){
                copy = find_min(&copy->rightNode);
                copy->rightNode = delete_min(&copy->rightNode);
            }
            else{
                copy->rightNode = removeRedBlack(&copy->rightNode,names);
            }
        }
    }
    return fix_up(&copy);
}








