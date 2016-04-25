#include <iostream>
#include <fstream>
#include <stdexcept>
#include "DecisionTree.h"

/*
    CSCI 2270 Final Project
    Ksenia Lepikhina and Lindsay Walton
*/

using namespace std;

int main(int arc, char *argv[])
{
    //add rules about yes or no questions in how to play
    //put instructions for playing in an external file and read it in
    //TOOD cite internet for try catch

    //make tree
    DecisionTree *gameTree = new DecisionTree();

    //current node
    Node *curr;

    string user;
    string question;
    string animal;

    //TODO ERROR CHECKING FOR USER INPUT EVERYWHERE
    string userInput = "";
    int menu = 0;
    bool correct = true; //flag to determine if the user put in correct input

    cout << "Welcome to Animal Guessing Game!" << endl;

    while (menu != 8)
    {
        //print menu
        cout << "===========Main Menu============" << endl;
        cout << "1. Play the Game" << endl;
        cout << "2. How to play" << endl;
        cout << "3. How many possible animals?" << endl;
        cout << "4. Display all the animals" << endl;
        cout << "5. How many possible questions?" << endl;
        cout << "6. Load" <<endl;
        cout << "7. Save" <<endl;
        cout << "8. Quit" << endl;
        cin >> userInput;

        // check if the user entered an integer
        try
        {
            //try to convert it to integer
            menu = stoi(userInput);
        }
        catch(invalid_argument&)
        {
            cout << "Please enter an integer for the menu options." << endl;
            correct = false;
        }
        catch(out_of_range&)
        {
            cout << "Please enter an integer that is in-range." << endl;
            correct = false;
        }

        //check if the user entered acceptable input
        if (correct)
        {
            switch(menu)
            {
                case 1:
                {
                    //get the root to the tree
                    curr = gameTree->getRoot();
                    //traverse through the tree
                    cout << "Let's play! Think of an animal." << endl;

                    //while the current node is a question
                    while (!curr->isAnimal)
                    {
                        curr = gameTree->askQuestion(curr);
                    }

                    //reached the end of the questions
                    cout << "Is it a " << curr->info << "?\n> ";
                    cin >> user;
                    //TODO add checking here to make sure that the user enters a valid response

                    if (user.compare("yes") == 0)
                    {
                        //guessed the correct animal
                        cout << "I win!" << endl;
                        //TOOD add loop so that they can play again
                    }
                    else
                    {
                        gameTree->userWon(curr);
                    }
                    break;
                }
                case 2:
                {
                    break;
                }
                case 3:
                {
                    int numAnimals = gameTree->countAnimals();
                    cout << "I currently know " << numAnimals << " animals. You'll never beat me!" << endl;
                    break;
                }
                case 4:
                {
                    cout << "If you haven't played yet, seeing all the animals is cheating." << endl;
                    cout << "Do you really want to display all animals?\n> ";
                    cin >> user;

                    if (user.compare("yes") == 0)
                        gameTree->displayAnimals();
                    else
                        cout << "Good choice. Look at the animals after you play!" << endl;

                    break;
                }
                case 5:
                {
                    int numQuestions = gameTree->countQuestions();
                    cout << "There are currently " << numQuestions << " possible questions that I could ask you." << endl;
                    cout << "You better know your stuff!" << endl;
                    break;
                }
                case 6:
                {
                    cout<< "Enter file path (/home/user/Documents/tree.txt)" << endl;
                    string path;
                    getline(cin,path);
                    gameTree->load(path);
                    break;
                }
                case 7:
                {
                    cout<< "Enter file path (/home/user/Documents/tree.txt)" << endl;
                    string path;
                    getline(cin,path);
                    gameTree->save(path);
                    break;
                }
                case 8:
                {
                    cout << "Thanks for playing!" << endl;
                    break;
                }
                default:
                {
                    cout << "Please enter an in-range integer for the menu options." << endl;
                    break;
                }
            }
        }
    }

    // gameTree->askQuestion();
    //gameTree->displayAnimals();

    cout << "See you next time!" << endl;
    return 0;
}
