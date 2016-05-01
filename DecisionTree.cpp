#include "DecisionTree.h"

/*
Note: Maksim Lepikhin assisted with the algorithm for loading and saving of the tree
to and from a text file.
*/


/*
 * Kian Tanner - changes made:
 * Added code to make yes or no answers lower case so that user may enter "Yes" or "No"
 * Added code to check if user said not my animal but later said it was
 * Added code to disallow any answer but yes or no for what is the answer to a new question
 * Created destructor mem leaks reduced from 219 bytes to 4 bytes (tested with valgrind)
 * Deleted pointer in count animals and count questions, now no memory leaks!! YAY!!
 * Loading works, before, every line was marked as an animal
 * Loading now doesn't leak memory
 * No memory leaks at all (tested with valgrind)
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


DecisionTree::~DecisionTree() {	//Call using 'delete gameTree'	-KT
    removeNode(root);	
}

void DecisionTree::removeNode(Node * r) {
	if (r) {	//If r exists	-KT
		if (r->yes) {	//If r->yes exists, Delete yes	-KT
			removeNode(r->yes);
		}
		if (r->no) {	//Delete no	-KT
			removeNode(r->no);
		}
		delete r;		
	}
}

void DecisionTree::printTree() {	//Testing/debugging	-KT
	printTree(root);
}

void DecisionTree::printTree(Node *node) {
	if (node == NULL) {
		return;
	}
	printTree(node->yes);
    cout << "--" << node->info << " - " << node->isAnimal << endl;
    printTree(node->no);
    return;
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
        file.close();	//Close file	-KT
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
    file.close();
}

void DecisionTree::SNtoN(vector<SavedNode>& savedNodes) // Saved Node to Node
{
    vector<Node*> nodePointers; //mapping from node index to node pointer
    
    removeNode(root);	//Clear old tree	-KT
    
    for (int i = 0; i < (int)savedNodes.size(); i++)
    {
        Node* node = new Node(savedNodes[i].info);
        nodePointers.push_back(node);
    } // allocate nodes of tree
    for (int i = 0; i < (int)savedNodes.size(); i++)
    {
        Node* node = nodePointers[i];
        SavedNode savedNode = savedNodes[i];
        
        if (isupper(savedNode.info[0])) {	//Uppercase first letter only occurs for questions	-KT
			node->isAnimal = false;
		} else {
			node->isAnimal = true;
		}
		
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
    
    for (int i = 0; i < user.length(); i++) {	//Convert to lower case so that user can input "Yes" or "No"	-KT
		user[i] = tolower(user[i]);
	}

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

	string in;
	
    cout << "You win! What animal were you thinking of?\n> ";
    cin.ignore();
    getline(cin, animal);
    
    in = animal;
    for (int i = 0; i < animal.length(); i++) {	//Convert to lower case so no cheating	-KT
		animal[i] = tolower(animal[i]);
	}
	if (animal == curr->info) {	//User cheated by thinking of capitalized version of animal	-KT
		cout << "You cheated! I actually won that game. I guessed " << curr->info << ", and you thought of " << in << ". Those are the same thing!" << endl;
		return;
	}
	
    cout << "I'm adding that animal to my knowledge so I can beat you next time!" << endl;
    cout << "What question distinguishes that animal from my guess (a " << curr->info << ")?\n> ";
    getline(cin,question);
    
    question[0] = toupper(question[0]);	//Capitalize first letter	-KT
    if (question[question.length() - 1] != '?') {	//Add question mark if needed	-KT
		question += "?";
	}
	
    user = "";
    while (user != "yes" && user != "no") {
		cout << "For a " << animal << ", is the answer to that question 'yes' or 'no'?\n> ";
		cin >> user;
		
		in = user;
		
		for (int i = 0; i < user.length(); i++) {	//Convert to lower case so that user can input "Yes" or "No"	-KT
			user[i] = tolower(user[i]);
		}

		if (user == "yes") {
			addYesQuestion(curr, question, animal);
		} else if (user == "no") {
			addNoQuestion(curr, question, animal);
		} else {
			cout << in << "is not a valid input. Please enter \"yes\" or \"no\"." << endl;
		}
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
    int a = *c;	//Need to be able to delete pointer c	-KT
    delete c;
    return a;
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
    int a = *c;	//Need to be able to delete pointer c	-KT
    delete c;
    return a;
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
