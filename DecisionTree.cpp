#include "DecisionTree.h"

using namespace std;

DecisionTree::DecisionTree()
{
    //ctor
    //make initial node in the tree
    root = new Node("jellyfish");
    root->yes = new Node("cat");
    root->yes->yes = new Node("whale");
    root->yes->no = new Node("bug");

}


DecisionTree::~DecisionTree()
{
    //dtor
}

int DecisionTree::countAnimals()
{

}

void DecisionTree::addQuestion(string question, string otherAnswer)
{

}

void DecisionTree::load(const string& path)
{
    vector<SavedNode> savedNodes;
    ifstream file(path.c_str());
    if (file.good())
    {
        string line;
        while (getline(file, line))
        {
            SavedNode sn;
            sn.fromString(line);
            savedNodes.push_back(sn);
        }
        SNtoN(savedNodes);
    }
    else
    {
        cout<< "File doesn't exist."<< endl;
    }
}

void DecisionTree::save(const string& path)
{
    vector<SavedNode> savedNodes = NtoSN();
    ofstream file(path.c_str());
    for (int i = 0; i < (int)savedNodes.size(); i++)
    {
        file << savedNodes[i].toString() << endl;
    }
}

void DecisionTree::SNtoN(vector<SavedNode>& savedNodes)
{
    vector<Node*> nodePointers;
    for (int i = 0; i < (int)savedNodes.size(); i++)
    {
        Node* node = new Node(savedNodes[i].info);
        nodePointers.push_back(node);
    }
    for (int i = 0; i < (int)savedNodes.size(); i++)
    {
        Node* node = nodePointers[i];
        SavedNode savedNode = savedNodes[i];
        if (savedNode.yes < 0)
        {
            node->yes = NULL;
        }
        else
        {
            node->yes = nodePointers[savedNode.yes];
        }
        if (savedNode.no < 0)
        {
            node->no = NULL;
        }
        else
        {
            node->no = nodePointers[savedNode.no];
        }
    }
    if (root != NULL)
    {
        //TODO destroy tree
        //create function destroy tree
        //call from destructor and here
    }
    root = nodePointers[0];
}

int findNodeIndex(const vector<Node*>& v, Node* node)
{
    for (size_t i=0;i<v.size();i++)
    {
        if (v[i] == node)
        {
            return i;
        }
    }
    return -1; // should never happen
}

void traverse(Node* node,vector<Node*>& nodePointers)
{
    nodePointers.push_back(node);
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
    vector<Node*> nodePointers;
    traverse(root, nodePointers); //filled node pointers and map and map of Node* to index
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
        savedNodes.push_back(savedNode);
    }
    return savedNodes;
}
