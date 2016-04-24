#ifndef DECISIONTREE_H
#define DECISIONTREE_H
#include <string>
#include <iostream>

/*
    CSCI 2270 Final Project
    Ksenia Lepikhina and Lindsay Walton
*/

struct Node
{
    std::string info; // either the question or name of the animal
    Node *yes; //pointer to the yes answer
    Node *no; //pointer to the no answer
    //TODO would a boolean be helpful here to tell if it's an
    //animal or a question?
    bool isAnimal;

    Node(){};

    Node(std::string in_info)
    {
        info = in_info;
        isAnimal = true; //automatically set new nodes to animals
        yes = NULL;
        no = NULL;
    }
};

class DecisionTree
{
    public:
        DecisionTree();
        ~DecisionTree();
        int countAnimals(); // function to count the number of animals in the tree
        int countQuestions(); // function to count all possible questions
        void displayAnimals(); //function to display all possible animals
        //TOOD add function to search for an animal
        void addYesQuestion(Node *curr, std::string question, std::string otherAnswer); // function to add a
        //new question
        void addNoQuestion(Node *curr, std::string question, std::string otherAnswer);
        Node *askQuestion(Node *curr);
       // void playGame(Node *curr);
        void userWon(Node *curr);
        Node *getRoot();

    private:
        Node *root; // pointer to the root of the tree
        void printAnimalNode(Node *node); //recursive function to print animals
        void countAnimalNodes(Node *node, int *c); //recursive function to count animal nodes
        void countQuestionNodes(Node *node, int *c);
};

#endif // DECISIONTREE_H
