#ifndef DECISIONTREE_H
#define DECISIONTREE_H
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>
#include <stdlib.h>

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
struct SavedNode
{
    std::string info; // either the question or name of the animal
    int yes; //pointer to the yes answer
    int no; //pointer to the no answer
    SavedNode()
    {
        info = "";
        yes = -1;
        no = -1;
    }
    std::string toString()
    {
        std::ostringstream os;
        os << info << ";" << yes << ";" << no;
        return os.str();
    }
    void fromString(std::string line)
    {
        std::vector<std::string> tokens;
        std::istringstream ss(line);
        std::string token;
        tokens.clear();
        while (getline(ss,token, ';'))
        {
            tokens.push_back(token);
        }
        if (tokens.size() != 3)
        {
            std::cout<< "You entered: " << line<< std::endl;
            std::cout<< "Error" << std::endl;
            return;
        }
        info = tokens[0];
        yes = atoi(tokens[1].c_str());
        no = atoi(tokens[2].c_str());
    }
    SavedNode& operator=(const SavedNode& src)
    {
        info = src.info;
        yes = src.yes;
        no = src.no;
        return *this;
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
        void load(const std::string& path);
        void save(const std::string& path);

    protected:
    private:
        std::vector<SavedNode> NtoSN();
        void SNtoN(std::vector<SavedNode>& savedNodes);
        void split(); //split text file
        Node *root; // pointer to the root of the tree
};

#endif // DECISIONTREE_H
