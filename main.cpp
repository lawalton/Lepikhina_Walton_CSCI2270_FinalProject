#include <iostream>
#include <fstream>
#include <stdexcept>
#include <stdlib.h>
#include <string>
#include "DecisionTree.h"

/*
    CSCI 2270 Final Project
    Ksenia Lepikhina and Lindsay Walton
*/

/*
Note: the exception names for the try catch statements, lines 59-70,
were found on the internet, from cplusplus.com
http://www.cplusplus.com/reference/stdexcept/invalid_argument/
http://www.cplusplus.com/reference/stdexcept/out_of_range/
*/

using namespace std;

int main(int arc, char *argv[])
{
    //make tree
    DecisionTree *gameTree = new DecisionTree();

    //current node
    Node *curr;

    string user;
    string question;
    string animal;
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

        //reset value of correct
        correct = true;

        // check if the user entered an integer
        try
        {
            //try to convert it to integer
            //menu = stoi(userInput);
            menu = atoi(userInput.c_str());
        }
        catch(invalid_argument&)
        {
            //if stoi failed, user didn't input an integer
            cout << "Please enter an integer for the menu options." << endl;
            correct = false;
        }
        catch(out_of_range&)
        {
            //user entered a number that is too large for the memory
            cout << "Please enter an integer that is in-range." << endl;
            correct = false;
        }

        //check if the user entered acceptable input
        if (correct)
        {
            switch(menu)
            {
                case 1: //play the game
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

                    if (user.compare("yes") == 0)
                    {
                        //guessed the correct animal
                        cout << "I win!" << endl;
                    }
                    else
                    {
                        gameTree->userWon(curr);
                    }
                    break;
                }
                case 2: //how to play
                {
                    cout << "Here's how to play!" << endl;
                    cout << "Think of an animal, and I'll try to guess what animal it is." << endl;
                    cout << "I'll ask you yes or no questions about your animal, so know your stuff!" << endl;
                    cout << "When I ask a question, only answer with 'yes' or 'no' (don't capitalize them)." << endl;
                    cout << "If I guess your animal, I win. If I don't, you win!" << endl;
                    cout << "Ready to play?" << endl;
                    break;
                }
                case 3: //how many animals
                {
                    int numAnimals = gameTree->countAnimals();
                    cout << "I currently know " << numAnimals << " animals. You'll never beat me!" << endl;
                    break;
                }
                case 4: //show all animals
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
                case 5: //how many questions
                {
                    int numQuestions = gameTree->countQuestions();
                    cout << "There are currently " << numQuestions << " possible questions that I could ask you." << endl;
                    cout << "You better know your stuff!" << endl;
                    break;
                }
                case 6: //load
                {
                    cout<< "Enter file path (/home/user/Documents/tree.txt)" << endl;
                    string path;
                    cin.ignore();
                    getline(cin,path);
                    gameTree->load(path);
                    break;
                }
                case 7: //save
                {
                    cout<< "Enter file path (/home/user/Documents/tree.txt)" << endl;
                    string path;
                    cin.ignore();
                    getline(cin,path);
                    gameTree->save(path);
                    break;
                }
                case 8: //quit
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

    cout << "See you next time!" << endl;
    return 0;
}
