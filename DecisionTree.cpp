#include "DecisionTree.h"

using namespace std;

DecisionTree::DecisionTree()
{
    //ctor
    //make initial node in the tree
    root = new Node("cat");

    //add another question
    addYesQuestion(root, "Does it live underwater?", "jellyfish");
}


DecisionTree::~DecisionTree()
{
    //dtor
}

Node* DecisionTree::askQuestion(Node *curr)
{
    string user;
    //ask the question
    cout << curr->info << "\n> ";
    cin >> user;

    while (user.compare("yes") != 0 && user.compare("no") != 0)
    {
        cout << "Please enter a valid response, either 'yes' or 'no'\n> ";
        cin >> user;
    }

    if (user.compare("yes") == 0)
    {
        //if user answered yes
        //advance to the yes node
        curr = curr->yes;
    }
    else
    {
        //if user answered no
        //advance to the no node
        curr = curr->no;
    }

    return curr;
}

void DecisionTree::addYesQuestion(Node *curr, string question, string otherAnswer)
{
    //this function adds a new animal where the new animal is "yes" response
    // to new question
    //TODO need to handle if it's the root?

    //move current node to child position, add parent node, add other answer
    //copy current node to new child node
    Node *copyChild = new Node(curr->info);

    //move current to the no position
    curr->no = copyChild;

    //change info in current node
    curr->info = question;

    //change it to a question
    curr->isAnimal = false;

    //add the other node
    Node *newNode = new Node(otherAnswer);

    //link it to the root
    curr->yes = newNode;

}

void DecisionTree::addNoQuestion(Node *curr, string question, string otherAnswer)
{
    //this function adds a new animal where the new animal is "no" response
    // to new question

    //move current node to child position, add parent node, add other answer
    //copy current node to new child node
    Node *copyChild = new Node(curr->info);

    //move current to the no position
    curr->yes = copyChild;

    //change info in current node
    curr->info = question;

    //change it to a question
    curr->isAnimal = false;

    //add the other node
    Node *newNode = new Node(otherAnswer);

    //link it to the root
    curr->no = newNode;

}

void DecisionTree::userWon(Node* curr)
{
    string user;
    string question;
    string animal;

    cout << "You win! What animal were you thinking of?\n> ";
    cin.ignore();
    getline(cin, animal);
    cout << "I'm adding that animal to my knowledge so I can beat you next time!" << endl;
    cout << "What question distinguishes that animal from my guess (a " << curr->info << ")?\n> ";
    getline(cin,question);
    cout << "For a " << animal << ", is the answer to that question 'yes' or 'no'?\n> ";
    cin >> user;

    if(user.compare("yes") == 0)
    {
        //add yes question
        addYesQuestion(curr, question, animal);
    }
    else
    {
        addNoQuestion(curr, question, animal);
    }

    cout << "Got it! I'll beat you next time!" << endl;
}

Node* DecisionTree::getRoot()
{
    return root;
}

//function to print all animals
void DecisionTree::displayAnimals()
{
    //call recursive function
    printAnimalNode(root);
}

//recursive function to print all animal nodes
void DecisionTree::printAnimalNode(Node *node)
{
    //recursive function to print node
    if (node->no != NULL)
    {
        printAnimalNode(node->no);
    }
    //only print it if it's an animal
    if (node->isAnimal)
        cout<<node->info<<endl;
    if (node->yes != NULL)
    {
        printAnimalNode(node->yes);
    }

}

//function to count all the animals in the tree
int DecisionTree::countAnimals()
{
    int *c = new int;
    *c = 0;
    countAnimalNodes(root, c);
    return *c;
}

//recursive function to count all the animals in the tree
void DecisionTree::countAnimalNodes(Node *node, int *c)
{
    //recursive function to print node
    if (node->no != NULL)
    {
        countAnimalNodes(node->no, c);
    }
    //only count this node if its an animal
    if (node->isAnimal)
        *c = *c+1;
    if (node->yes != NULL)
    {
        countAnimalNodes(node->yes, c);
    }
}

//function to count all the animals in the tree
int DecisionTree::countQuestions()
{
    int *c = new int;
    *c = 0;
    countQuestionNodes(root, c);
    return *c;
}

//recursive function to count all the animals in the tree
void DecisionTree::countQuestionNodes(Node *node, int *c)
{
    //recursive function to print node
    if (node->no != NULL)
    {
        countQuestionNodes(node->no, c);
    }
    //only count this node if its an animal
    if (!node->isAnimal)
        *c = *c+1;
    if (node->yes != NULL)
    {
        countQuestionNodes(node->yes, c);
    }
}
