# Lepikhina_Walton_CSCI2270_FinalProject

Name: Animal Guessing Game

Authors: Ksenia Lepikhina and Lindsay Walton

CSCI 2270 Final Project

This project is an animal guessing game. The program will guess which
animal the user is thinking of, by asking the user a series of yes or no
questions. 

The game will be developed as a binary search tree. Each question will be
included as a node in the binary search tree, with animals being included 
as the leaf nodes. As the user answers the questions, he/she will traverse 
through the tree, eventually resulting in an animal. If the animal that the
user was thinking of is not included in the tree, it can be added by the user.
The user can enter a new animal, along with a new question to differentiate 
the animal from the guessed animal. The new animal and question will be
added as nodes in the tree, so the tree grows as the user continues to play
the game. At the end of the game, the tree will be saved a .txt file. At the
start of the next game, the tree will be built from the .txt file, so that 
the program can guess a wider range of animals as the game is played more.
