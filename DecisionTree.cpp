#include "DecisionTree.h"

/*
Note: Maksim Lepikhina assisted with the algorithm for loading and saving of the tree
to and from a text file.
*/
using namespace std;

DecisionTree::DecisionTree()
{
    //ctor
    //make initial node in the tree
    root = new Node("cat");

    //add additional question
    addYesQuestion(root, "Does it live underwater?", "jellyfish");
}


DecisionTree::~DecisionTree()
{
    //dtor
}

void DecisionTree::load(string path)
{
    vector<SavedNode> savedNodes; //create a vector of saved nodes ex: ("cat", -1, -1) where -1 represents no children
    ifstream file(path.c_str()); //input stream
    if (file.good()) // checks to see if file exists
    {
        string line; //
        while (getline(file, line))
        {
            SavedNode sn;
            sn.fromString(line); //from string to Node
            savedNodes.push_back(sn); // push to back of vector
        }
        SNtoN(savedNodes); //Saved Node to Node: takes savedNodes, parses it into tokens and then assigns tokens to the fields
    }
    else
    {
        cout<< "File doesn't exist."<< endl;
    }
}

void DecisionTree::save(string path)
{
    vector<SavedNode> savedNodes = NtoSN(); //vector of savedNodes = Node to Saved Nodes -> Copying result of NtoSN to savedNodes
    ofstream file(path.c_str()); //output stream
    for (int i = 0; i < (int)savedNodes.size(); i++) //makes sure it saves all of the savedNodes
    {
        file << savedNodes[i].toString() << endl;
    }
}

void DecisionTree::SNtoN(vector<SavedNode>& savedNodes) // Saved Node to Node
{
    vector<Node*> nodePointers; //mapping from node index to node pointer
    for (int i = 0; i < (int)savedNodes.size(); i++)
    {
        Node* node = new Node(savedNodes[i].info);
        nodePointers.push_back(node);
    } // allocate nodes of tree
    for (int i = 0; i < (int)savedNodes.size(); i++)
    {
        Node* node = nodePointers[i];
        SavedNode savedNode = savedNodes[i];
        if (savedNode.yes < 0) //if savedNode.yes = -1 then there are no children
        {
            node->yes = NULL;
        }
        else
        {
            node->yes = nodePointers[savedNode.yes];
        }
        if (savedNode.no < 0) //if savedNode.no = -1 then there are no children
        {
            node->no = NULL;
        }
        else
        {
            node->no = nodePointers[savedNode.no];
        }
    } //build tree
    root = nodePointers[0];
}

int findNodeIndex(const vector<Node*>& nodePointers, Node* node) //find index of Node*
{
    for (int i=0;i<(int)nodePointers.size();i++)
    {
        if (nodePointers[i] == node)
        {
            return i;
        }
    }
    return -1; // should never happen
}

void traverse(Node* node,vector<Node*>& nodePointers) //recursive function that goes through all nodes and collects all nodePointers
{
    nodePointers.push_back(node); // do this first so you push root back first
    if (node->yes != NULL)
    {
        traverse(node->yes, nodePointers);
    }
    if (node->no != NULL)
    {
        traverse(node->no, nodePointers);
    }
}
vector<SavedNode> DecisionTree::NtoSN()
{
    vector<Node*> nodePointers; //mapping from node index to node pointer
    traverse(root, nodePointers); //map of Node* to index
    vector<SavedNode> savedNodes;
    for (int i = 0; i < (int)nodePointers.size(); i++)
    {
        Node* node = nodePointers[i];
        SavedNode savedNode;
        savedNode.info = node->info;
        if (node->yes == NULL)
        {
            savedNode.yes = -1;
        }
        else
        {
            savedNode.yes = findNodeIndex(nodePointers, node->yes);
        }
        if (node->no == NULL)
        {
            savedNode.no = -1;
        }
        else
        {
            savedNode.no = findNodeIndex(nodePointers, node->no);
        }
        savedNodes.push_back(savedNode); //copy saved node to back of vectosr
    }
    return savedNodes;
}

//function to ask the user a question
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

//Function to add new question
void DecisionTree::addYesQuestion(Node *curr, string question, string otherAnswer)
{
    //this function adds a new animal where the new animal is "yes" response
    // to new question

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

//Function to add new question
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

//Function to handle the user winning the game
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

//Function to return root
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
