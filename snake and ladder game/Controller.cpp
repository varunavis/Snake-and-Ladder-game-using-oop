#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <string>
#include <bits/stdc++.h>
#include <stdbool.h>

//including the classes we created
//#include "Dice.h"
//#include "Board.h"
#include "Snakes.h"
#include "Ladders.h"
#include "BasicInfo.h"

using namespace std;

class Controller: virtual public Snakes, virtual public Ladders, virtual public BasicInfo, virtual public Board
{
	void gameends(int);
	void endCredits();
	public:
		bool gameOngoing = true;
		
	public: 
		Controller();
		void gameplay();
};

void coutCentered(std::string text) {	// since it couldn't get inherited
	// This function will only center the text if it is less than the length of the console!
	// Otherwise it will just display it on the console without centering it.
	
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Get the console handle.
	PCONSOLE_SCREEN_BUFFER_INFO lpScreenInfo = new CONSOLE_SCREEN_BUFFER_INFO(); // Create a pointer to the Screen Info pointing to a temporal screen info.
	GetConsoleScreenBufferInfo(hConsole, lpScreenInfo); // Saves the console screen info into the lpScreenInfo pointer.
	COORD NewSBSize = lpScreenInfo->dwSize; // Gets the size of the screen
	if (NewSBSize.X > text.size()) {
	    int newpos = ((NewSBSize.X - text.size()) / 2); // Calculate the number of spaces to center the specific text.
	    for (int i = 0; i < newpos; i++) std::cout << " "; // Prints the spaces
	}
	std::cout << text << std::endl; // Prints the text centered :]
}

void Controller::gameplay()
{
	int numberOnDice[numberofplayers];
	int score[numberofplayers] = {0};
	int previousscore[numberofplayers] = {0};	
	while(gameOngoing)
	{
		for(int i=0; i<numberofplayers; i++)
		{
			cout<<"\nPlayer "<<orderofplay[i] + 1<<"'s chance: "<<endl;
			system("pause");
			numberOnDice[i] = rolltheDice();
			cout<<"Player "<<orderofplay[i] + 1<<" "<<playerinitials[orderofplay[i]]<<" gets "<<numberOnDice[i]<<endl;
			
			if((score[i]+numberOnDice[i]) > 100)	// else it would go out of bounds
			{
				cout<<namesinstring[i]<<" NEEDS TO GET "<<100-score[i]<<" TO WIN"<<endl;
				continue; // don't add score if result equals greater than 100
			}
			
			score[i] += numberOnDice[i]; 
			score[i] = updateScore(orderofplay[i], score[i]);
			cout<<"Score is "<<score[i]<<endl;
			
			if(score[i]==100)	// check if player has reached the end
			{
				gameends(orderofplay[i]);		// game is terminated
				break;
			}
			if(previousscore[i]!=0)	// it won't work if previous is just at the beginning of the game, since score is 0, and 0 is not on the board
				deletePlay(previousscore[i]);	// delete player from previous position
			printPlayers(playerinitials[orderofplay[i]], orderofplay[i], score[i]);
			//updatePlayer(orderofplay[i], score[i]);  // put players initials on the board
			fancyprintboard();	// print the board with updated info
			
			
//			objecthere[rc[0]][rc[1]] = " "; // segmentation error
//			cout<<objecthere[rc[0]][rc[1]].length(); // segmentation error
			previousscore[i] = score[i];	// at the last, we'll change previous score to current score so that this updated one can be used next time as previous
		}
	}
}

void Controller::gameends(int playerno)
{
	gameOngoing = false;
	switch(playerno)
	{
		case 0:	// starts from 0 since we are passing an array, and array numbering starts from 0
			coutCentered("~~~~~Player 1 has won the game~~~~~");
			coutCentered(namesinstring[playerno]);
			break;
		case 1:
			coutCentered("~~~~~Player 2 has won the game~~~~~");
			coutCentered(namesinstring[playerno]);
			break;
		case 2:
			coutCentered("~~~~~Player 3 has won the game~~~~~");
			coutCentered(namesinstring[playerno]);
			break;
		case 3:
			coutCentered("~~~~~Player 4 has won the game~~~~~");
			coutCentered(namesinstring[playerno]);
			break;
	}
	coutCentered("CONGRATULATIONS");
//	cout.width(50);
//	cout<<namesinstring[playerno]<<" WON!";
	endCredits();
}

void Controller::endCredits()
{
	coutCentered("");
	coutCentered("############################## \n");
	coutCentered("THANKS FOR PLAYING");
	coutCentered("SEE YOU SOON!\n");
	coutCentered("############################## \n");
}


Controller::Controller()
{
	//BasicInfo bi;
	//Board b;
	Snakes s;
	Ladders l;
	fancyprintboard();
	gameplay();
	//gameends(2);	//for testing purpose
}

int main()
{
	Controller c;
	return 0;
}
