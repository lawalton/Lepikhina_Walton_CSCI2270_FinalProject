#ifndef DECISIONTREE_H
#define DECISIONTREE_H
#include <string>

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

    Node(){};

    Node(std::string in_info)
    {
        info = in_info;
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
        void addQuestion(std::string question, std::string otherAnswer); // function to add a
        //new question
        Node *

    protected:
    private:
        Node *root; // pointer to the root of the tree
};

#endif // DECISIONTREE_H
