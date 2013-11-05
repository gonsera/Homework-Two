//Michael Mayer
//CS 162 Homework #2
//October 29, 2013

#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

void game(); //The main game function, from which game essential functions are called and the game is run
void printMessage(char letters[]);
void printScore(int score);

bool checkValid(char input[], char letters[]); //Checks if the user input is a valid word
bool checkVowel(char input[]); //checks if the user inputed an extra vowel, for the purposes of being valid

int userInput(char letters[]); //Gets user input, return net score

int scoreGained(char input[]); //calulates the score gained from the word entered
int scoreLost(char input[], char letters[]); //calculates the score lost from the word entered

bool checkWin(int totalScore); //checks to see if the user has won the game
bool checkLoss(int totalScore); //checks to see if the user has lost the game

static int SCORE_LOSS = -1; //score to lose
static int SCORE_WIN = 21; //Score to win
static char VOWELS[6] = {'a','e','i','o','u'}; //Vowels, to be checked against so that score can be subtracted

int main()
{
	bool playAgain;

	do
	{
		game();

		bool playAgainError;
		do
		{
			char awnser;

			cout << "Would you like to play again? (y/n) " << endl;
			cin >> awnser;
			cin.ignore(100,'\n');

			if (awnser == 'y')
			{
				playAgain = true;
				playAgainError = false;
			}
			else if (awnser == 'n')
			{
				playAgain = false;
				playAgainError = false;
			}
			else
			{
				playAgainError = true;

				cout << "I don't think you understood the question..." << endl;
			}
		} while (playAgainError);
	} while (playAgain);
}

void game()
{
	bool gameWon;
	bool gameLost;
	int totalScore = 0;
	srand(time(0));

	char letters[6];

	for (int i = 0; i < 6; i++) //Gets 6 random chars
	{
		letters[i] = (rand() % 26) + 'a';
	}

	do //All of the game is done here
	{
		printScore(totalScore);
		printMessage(letters);
		totalScore = totalScore + userInput(letters);

		gameWon = checkWin(totalScore);
		gameLost = checkLoss(totalScore);
	} while (!gameWon && !gameLost); //While the game is not lost or won

	if (gameWon)
	{
		cout << "You Won! Your final score was: " << totalScore << endl;
	}
	else
	{
		cout << "You Lost! Your final score was: " << totalScore << endl;
	}
}

void printMessage(char letters[])
{
	for (int i = 0; i < 6; i++)
	{
		cout << letters[i];
	}

	cout << endl << "Please enter a word (Up to 6 letters) from the letters above " << endl; 
}

void printScore(int score)
{
	cout << "Your score is: " << score << endl;
}

bool checkValid(char input[], char letters[])
{
	bool letterValid[6];
	bool allValid = true; //default is true, checks if false

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (input[i] == letters[j])
			{
				letterValid[i] = true;
			}
			else
			{
				for (int k = 0; k < 6; k++)
				{
					if (input[i] == VOWELS[k])
					{
						letterValid[i] = true;
					}
				}

				for (int k = 0; k < 6; k++)
				{
					if (input[i] == '\0') //I could find no other fix for this
					{
						letterValid[i] = true;
					}
				}
			}
		}
	}

	for (int i = 0; i < 6; i++)
	{
		if (letterValid[i] != true)
		{
			allValid = false;
		}
	}

	return allValid;
}

int userInput(char letters[])//Problem
{
	bool validWord;
	int netScore = 0;

	do
	{
		char input[7];
		cin >> input;
		cin.ignore(100,'\n');

		validWord = checkValid(input, letters);

		if (validWord)
		{
			netScore = scoreGained(input) - scoreLost(input, letters);
		}
		else
		{
			cout << "Your word is not valid! Try again!" << endl;
			printMessage(letters);
		}
	} while (!validWord);

	return netScore;
}

int scoreGained(char input[])//Problem
{
	int scoreGained = 0;

	for (int i = 0; i < 6; i++)
	{
		if (input[i] > 'a' && input[i] < 'z')
		{
			scoreGained++;
		}
	}

	return scoreGained;
}

int scoreLost(char input[], char letters[])//Problem
{
	int scoreLost = 0;
	bool inList[6];

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (input[i] == letters[j])
			{
				inList[i] = true;
			}
			else
			{
				inList[i] = false;
			}
		}

		for (int j = 0; j < 6; j++)
		{
			if (input[i] == VOWELS[j] && !inList[i])
			{
				scoreLost++;
			}
		}
	}

	return scoreLost;
}

bool checkLoss(int totalScore)
{
	if (totalScore <= SCORE_LOSS)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool checkWin(int totalScore)
{
	if (totalScore >= SCORE_WIN)
	{
		return true;
	}
	else
	{
		return false;
	}
}
