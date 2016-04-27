# Lepikhina_Walton_CSCI2270_FinalProject

Name: Animal Guessing Game

Authors: Ksenia Lepikhina and Lindsay Walton

CSCI 2270 Final Project

1) Project Summary:
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

2) How To Run:
Run the main.cpp file. When the game starts, a menu will be displayed. 
The user can choose to play the game, learn how to play, count the number
of animals in the game, and count the number of possible questions in the game.
Select the appropriate number for the option that you want. If you do not 
select an acceptable number, you will continue to be prompted until you select
an acceptable number. 

Once the game starts, you will be asked a series of yes or no questions to 
determine the animal that you are thinking of. For each question, only the
responses 'yes' or 'no' will be accepted. Capitalized answers, different 
spellings, or shorthand (such as 'y' or 'n') will not be accepted. You will
continue to be prompted until you enter 'yes' or 'no'. 

You will be asked questions until the game reaches an animal. It will ask if
that is the animal that you were thinking of. If it was, you will be taken
back to the main menu to either play again, or choose one of the other options
in the menu.

If the game did not correctly guess your animal, you will be asked to enter
the name of the correct animal. You will also be asked for a question to 
distinguish it from the animal that the game guessed, so that the new animal
can be added to the game. After you enter the new animal and new question, 
you will be asked if the answer to the new question for your new animal is
'yes' or 'no'. For example, if the game guessed 'jellyfish' but the correct
animal was 'shark', a new question might be 'Does it have fins?". The answer
to that question for a shark would be 'yes'. Another possible question is
'Does it have tentacles?". The answer to that question for a shark is "no".
The new question and animal will be added to the game's knowledge based on
those answers. After this, the user will be taken back to the main menu.

3) Dependencies:
There are no external libraries that the user must have. The user only needs
main.cpp, DecisionTree.h, DecisionTree.cpp, and the optional text file to
build an existing tree.

4) System Requirements:
There are no system requirements for this game. The user only needs to have
a C++ compiler to compile and run the code. 

5) Group Members:
The Animal Guessing Game development team consists of Ksenia Lepikhina and 
Lindsay Walton.

6) Contributors:
The development team has received assistance from Maksim Lepikhina, as he 
assisted with saving the tree to a text file and then re-constructing the
tree from a text file.

7) Known Issues:
a) A user could answer a question about the animal incorrectly (either by
accident or lack of knowledge), and the program would "think" that the user
won the game with a new animal, and the animal would be added to the tree
a second tree, with an incorrect answer leading to it. This could be resolved
by adding a search function for animals. When a user has won and entered the
animal he/she was thinking of, the program searches the tree for that animal.
If the animal is found, the program could display a message stating that that
animal is already in the tree, and the user must have answered a question
incorrectly.  
