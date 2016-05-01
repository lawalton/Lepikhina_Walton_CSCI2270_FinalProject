#ifndef DECISIONTREE_H
#define DECISIONTREE_H
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>
#include <cstdlib>	//Changed to C++ version of <stdlib.h>	-KT
#include <cctype>	//Contains tolower and isupper	-KT

/*
    CSCI 2270 Final Project
    Ksenia Lepikhina and Lindsay Walton
*/

/*
Note: Maksim Lepikhina assisted with the SavedNode struct (line 37-82),
for the saving and loading the tree to and from a text file
*/

struct Node
{
    std::string info; // either the question or name of the animal
    Node *yes; //pointer to the yes answer
    Node *no; //pointer to the no answer
    bool isAnimal; //boolean value to tell if it's an animal or question

    Node(){};

    Node(std::string in_info)
    {
        info = in_info;
        isAnimal = true; //automatically set new nodes to animals
        yes = NULL;
        no = NULL;
    }
};
struct SavedNode
{
    std::string info; // either the question or name of the animal
    int yes; //"pointer" to the yes answer Can't save pointers to txt
    int no; //"pointer" to the no answer
    SavedNode()
    {
        info = "";
        yes = -1; //represents no children
        no = -1; //represents no children
    }
    std::string toString() //Node to string
    {
        std::ostringstream os; //output string stream
        os << info << ";" << yes << ";" << no;
        return os.str(); // return the output as string
    }
    void fromString(std::string line) //from string to Node
    {
        std::vector<std::string> tokens; //vector to push stuff on to
        std::istringstream ss(line);
        std::string token;
        tokens.clear(); //make sure theres nothing on there
        while (getline(ss,token, ';'))
        {
            tokens.push_back(token); // push to back of vector
        }
        if (tokens.size() != 3) //if there wasn't enough input (info, yes, no)
        {
            std::cout<< "You entered: " << line<< std::endl;
            std::cout<< "Error" << std::endl;
            return;
        }
        info = tokens[0]; //info is first token
        yes = atoi(tokens[1].c_str()); //yes is second token
        no = atoi(tokens[2].c_str()); //no is third token
    }
    SavedNode& operator=(const SavedNode& src) // called inside of push_back --> operator= = copy
    /*When we return a vector from a function it creates a new vector, in order to copy elements from the returned
    value to the one in the calling function stl calls operator= for all elements. - Maksim Lepikhin*/
    {
        info = src.info;
        yes = src.yes;
        no = src.no;
        return *this;
    } // search: implement operator= c++
};


class DecisionTree
{
    public:
        DecisionTree();
        ~DecisionTree();	//Works	-KT
        void load(std::string path); // load function
        void save(std::string path); //save function
        int countAnimals(); // function to count the number of animals in the tree	(changed so no memory leaks	-KT)
        int countQuestions(); // function to count all possible questions	(changed so no memory leaks	-KT)
        void displayAnimals(); //function to display all possible animals
        // Functions to add new questions:
        void addYesQuestion(Node *curr, std::string question, std::string otherAnswer);
        void addNoQuestion(Node *curr, std::string question, std::string otherAnswer);
        Node *askQuestion(Node *curr);
        void userWon(Node *curr); //function to handle the user winning (adding new animal)
        Node *getRoot();
        
        void printTree();	//Used for testing - delete if you want	-KT

    private:
        std::vector<SavedNode> NtoSN(); //Node to Saved Node -->
        void SNtoN(std::vector<SavedNode>& savedNodes); //Saved Node to Node -->	(changed so no memory leaks	-KT)
        void split(); //split text file
        Node *root; // pointer to the root of the tree
        void printAnimalNode(Node *node); //recursive function to print animals
        void countAnimalNodes(Node *node, int *c); //recursive function to count animal nodes
        void countQuestionNodes(Node *node, int *c);
        
        void removeNode(Node * r);	//Delete node	-KT
        void printTree(Node *node);	//Used for testing - delete if you want	-KT
};

#endif // DECISIONTREE_H
