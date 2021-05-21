/* this code would include the navigation part of the game
   that is, the main controller of where the game should 
   lead to if something happens
   like if snake is encountered, code should execute snake part
   or if game ends, then what should happen*/

#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <bits/stdc++.h>
#ifndef BASICINFO_H
#define BASICINFO_H

// when including user defined headers, use quotations intead of <>
#include "Dice.h"	// importing the class Dice that we created through the header file

using namespace std;

class BasicInfo: public Dice	// to inherit diceNum and rolltheDice function
{
	void creditsStartPage();
	void gameStartPage();
	string generateInitials(string);	
	void getInitials();
	void chooseWhoGoesFirst(); 	// Dice functions would be used here
	
	char cg;
	//string playernamesarr[4];
	int largestnamelength=30;
	
	public:	// variables
		int numberofplayers;
		char playernametoinput[4][30];	// space for 4 names to be entered with max capacity of 30 characters
		//char playerinitials[4][2];		// space for 4 initials with max length 2 chars
		string playerinitials[4];
		string namesinstring[4];
		int orderofplay[];
		
		
	public:	//functions
		BasicInfo();  // constructor
};

void CoutCentered(std::string text) {
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

void BasicInfo::creditsStartPage()
{
	cout<<"\n";
	CoutCentered("############################## \n");
	CoutCentered("THE SNAKE AND LADDER GAME \n");
	CoutCentered("############################## \n");
	CoutCentered("Game design by: \n");
	CoutCentered("# Varunavi Shettigar # ");
}

void BasicInfo::gameStartPage()
{
	
	cout<<"\n";
	/*do  // will execute atleast once
	{
		cout<<"(2 to 4 players allowed) \nNumber of players? ";
		cin>>numberofplayers;
	} while(numberofplayers<2 || numberofplayers>4); */  // if user enters 1 player or 5 players etc
	
	cout<<"(2 to 4 players allowed) \nNumber of players? ";
	cin>>numberofplayers;
	switch(numberofplayers)
	{
		case 2:
		case 3:
		case 4:
			break;
		
		default:
			cout<<"Sorry, a minimum 2 players and maximum 4 players are allowed. \nBy default 2 players have been chosen.";
			numberofplayers = 2;
			break;
	}
	
	cin.ignore();		// to ignore the \n still waiting to be read by cin>>numberofplayers
	// otherwise it does not input player 1's name
	int playernumber = 0;
	while(playernumber<numberofplayers)
	{
		cout<<"\nEnter name of player "<<playernumber+1<<": ";
		
		cin.getline(playernametoinput[playernumber], largestnamelength);
		//cout.write(playernametoinput[playernumber], strlen(playernametoinput[playernumber]));		// was for testing purpose
		
		namesinstring[playernumber] = (string)playernametoinput[playernumber];
		
		playernumber+=1;	// playernumber++
	}
	
}

string BasicInfo::generateInitials(string playername)
{
	string playini; 	// to not get confused with similar names
	int initials = 0;
	playini = toupper(playername[0]);	// the first character should be initial
	initials++;
	for(int i=1; i<playername.length(); i++)
	{
		if(initials>2)		
			break;	// exit the loop if number of initials are more than 2
		
		if(playername[i]==' ')
		{
			playini += toupper(playername[i+1]);
			initials++;
		}
	}
	if(initials==1)	// meaning no whitespace was found in the text
		playini += toupper(playername[1]);		// second initial would be the second letter
	
	return playini;
}


void BasicInfo::getInitials()
{
	cout<<"\nInitials will be placed in the game to track players positions \nDo you want to enter your initials or generate them? (C/G)";
	cin>>cg;
	for(int playernumber=0; playernumber<numberofplayers; playernumber++)
	{
		string & temp = playerinitials[playernumber];	// using a substitute, reference variable
		switch(cg)
		{
			case 'C':
			case 'c':
				do {
					cout<<"\nInitials of 2 letters only! No space!";
					cout<<"\nPlayer "<<playernumber+1<<" initials: ";
					cin>>playerinitials[playernumber];		// player will enter initials as per their choice
				} while(playerinitials[playernumber].length() > 2 || playerinitials[playernumber].length() < 1);	
				// would repeat if the initials are more than 2 or one letter initials
				
				// using transform() function and ::toupper in STL
    			transform(temp.begin(), temp.end(), temp.begin(), ::toupper);
				break;
			
			case 'G':
			case 'g':
			default:	// to not stress the user, the default 'generate' option should work
				//cout<<"\nPlayer "<<playernumber<<" initials: ";
				//playerinitials[playernumber] = generateInitials(playernametoinput[playernumber]);
				playerinitials[playernumber] = generateInitials(namesinstring[playernumber]);
				//cout<<playerinitials[playernumber];
				break;
				
		}
	}
	//checkifInitialSame(playerinitials);
	
	for(int i=0; i<numberofplayers; i++)	// making sure the players know what initials they have
	{
		cout<<"\nPlayer "<<i+1<<" ("<<playernametoinput[i]<<") initials: "<<playerinitials[i];
	}
}

void BasicInfo::chooseWhoGoesFirst()	// this function uses the Dice header
{
	int numberOnDice[numberofplayers];
	cout<<"\n";
	CoutCentered("############################## \n");
	CoutCentered("LET THE GAME BEGIN!! \n");
	CoutCentered("############################## \n");
	cout<<"\nTime to choose the first player!"<<endl;
	
	for(int i=0; i<numberofplayers; i++)	// to roll the dice, player by player
	{
		system("pause");
		cout<<"Player "<<i+1<<" "<<playerinitials[i]<<" gets number ";
		numberOnDice[i] = rolltheDice();
		cout<<numberOnDice[i]<<" on the dice"<<endl;
	}
	
	for(int i=0; i<numberofplayers; i++)	// to store the order in the orderofplay array
	{
		// returns the max element index from the array
		orderofplay[i] = max_element(numberOnDice, numberOnDice + numberofplayers) - numberOnDice;		
		numberOnDice[orderofplay[i]] = 0;	// so that next maximum can be found
	}
	
	cout<<"\nOrder of play:"<<endl;
	for(int i=0; i<numberofplayers; i++)	// to print the order of play to players
		cout<<"PLayer "<<orderofplay[i] + 1<<" "<<playerinitials[orderofplay[i]]<<endl;
	
//	order[0] = *max_element(numberOnDice, numberOnDice + numberofplayers);	// returns the max element from the array
//	maxpos = max_element(numberOnDice, numberOnDice + numberofplayers) - numberOnDice + 1;	// for the index of the max; +1 coz it starts from 0
//	cout<<order[0]<<"  "<<maxpos;

}

BasicInfo::BasicInfo()  // constructor
{
	creditsStartPage();   // calling the functions from within the constructor
	gameStartPage();	  // as wouldn't have to call it separately 
	
	getInitials();	// giving user choice of choosing initials, or generating them
	chooseWhoGoesFirst();
	
}

//int main()
//{
//	BasicInfo bi;  // contructor gets intitailaized when object is created
//	return 0;
//}
#endif
