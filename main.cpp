#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "BinaryTree.h"


using namespace std;

int main(int argc, char** argv) {

    string input = argv[1];
    string out1 = argv[2];
    string out2 = argv[3];

    ifstream infile;
    infile.open(input.c_str());

    vector<string> list;
    string line;

    BinaryTree *head = nullptr;
    BinaryTree function;



    if(infile.is_open()){
        string x;
        ofstream file1;
        file1.open(out1.c_str());

        while (getline(infile, line))
        {
            istringstream iss(line);
            string word;

            while(getline(iss, word, '\t')) {
                list.push_back(word);
            }

            if(list[0] == "insert"){
                int band; stringstream  ss; ss << list[3]; ss >> band; ss.clear();
                BinaryTree *search = function.ifNodeExists(&head,list[1]);
                if(search == nullptr){
                    head = function.insert(&head, list[1],list[2], band);
                }
                else{
                    search->SecondaryNode = function.insertSecondary(&search->SecondaryNode, list[2], band);
                }
            }
            else if (list[0] == "remove"){
                BinaryTree *category_root;
                category_root = function.ifNodeExists(&head, list[1]);
                category_root->SecondaryNode = function.remove(&category_root->SecondaryNode,list[2]);

            }
            else if (list[0] == "printAllItems"){
                function.printAllItems(&head,file1);
            }
            else if (list[0] == "printAllItemsInCategory"){
                function.printAllItemsInCategory(&head , list[1],file1);
            }
            else if (list[0] == "printItem"){
                function.printItem(&head , list[1],list[2],file1);
            }
            else if (list[0] == "find"){
                function.find(&head , list[1],list[2],file1);
            }
            else if (list[0] == "updateData"){
                int band; stringstream  ss; ss << list[3]; ss >> band; ss.clear();
                function.updateData(&head , list[1],list[2],band);
            }

            list.clear();
        }

        infile.close();
    }

    else{
        cout << "The file is not found";
    }
    infile.close();


    BinaryTree *head2 = nullptr;
    infile.open(input.c_str());

    if(infile.is_open()){
        string x;
        ofstream file1;
        file1.open(out2.c_str());

        while (getline(infile, line))
        {
            istringstream iss(line);
            string word;

            while(getline(iss, word, '\t')) {
                list.push_back(word);
            }

            if(list[0] == "insert"){
                int band; stringstream  ss; ss << list[3]; ss >> band; ss.clear();
                BinaryTree *search = function.ifNodeExists(&head2,list[1]);
                if(search == nullptr){
                    head2 = function.insert(&head2, list[1],list[2], band);
                }
                else{
                    search->SecondaryNode = function.insertRedBlack(&search->SecondaryNode, list[2], band);
                    search->SecondaryNode->color = false;
                }
            }
            else if (list[0] == "remove"){
                BinaryTree *category_root;
                category_root = function.ifNodeExists(&head2, list[1]);
                category_root->SecondaryNode = function.removeRedBlack(&category_root->SecondaryNode,list[2]);

            }
            else if (list[0] == "printAllItems"){
                function.printAllItems(&head2,file1);
            }
            else if (list[0] == "printAllItemsInCategory"){
                function.printAllItemsInCategory(&head2 , list[1],file1);
            }
            else if (list[0] == "printItem"){
                function.printItem(&head2 , list[1],list[2],file1);
            }
            else if (list[0] == "find"){
                function.find(&head2 , list[1],list[2],file1);
            }
            else if (list[0] == "updateData"){
                int band; stringstream  ss; ss << list[3]; ss >> band; ss.clear();
                function.updateData(&head2 , list[1],list[2],band);
            }

            list.clear();
        }

        infile.close();
    }

    else{
        cout << "The file is not found";
    }
    infile.close();



    return 0;
}
