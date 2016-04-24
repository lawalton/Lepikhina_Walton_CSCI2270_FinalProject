#include <iostream>
#include <fstream>
#include "DecisionTree.h"

/*
    CSCI 2270 Final Project
    Ksenia Lepikhina and Lindsay Walton
*/

using namespace std;

int main(int arc, char *argv[])
{
    //first command line argument will be the file name to read from

    //make tree
    DecisionTree gameTree;
    while(1)
    {
        cout << "======Main Menu======" << endl;
        cout << "1. Load: Think of an animal" << endl;
        cout << "2. Add Question and Animal" << endl;
        cout << "3. Save" << endl;
        cout << "4. Quit" << endl;
        char choice = -1;
        string str;
        getline(cin, str);
        if (str.length() == 1)
        {
            choice = str[0];
        }
        if (choice == '1') //Load
        {
            cout<< "Enter file path (/home/user/Documents/tree.txt)" << endl;
            string path;
            getline(cin,path);
            gameTree.load(path);
        }
        else if (choice == '2') //Add
        {

        }
        else if (choice == '3') //Save
        {
            cout<< "Enter file path (/home/user/Documents/tree.txt)" << endl;
            string path;
            getline(cin,path);
            gameTree.save(path);
        }
        else if (choice == '4') //Quit
        {
            cout<<"Thank you!"<<endl;
            break;
        }
        else
        {
            cout<< "Sorry, that is not a valid choice."<<endl;
            cout<< "Please try again."<<endl<<endl;
        }
    }

    return 0;
}
