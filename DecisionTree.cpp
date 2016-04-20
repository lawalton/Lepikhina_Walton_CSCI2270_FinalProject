#include "DecisionTree.h"

using namespace std;

DecisionTree::DecisionTree()
{
    //ctor
    //make initial node in the tree
    root = new Node("jellyfish");
}


DecisionTree::~DecisionTree()
{
    //dtor
}
