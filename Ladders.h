/* program to set the ladders and store
   info about where it starts and ends
   */

#include<iostream>
#include <bits/stdc++.h>
#include<string.h>
#include "Board.h"
using namespace std;

class Ladders: virtual public Board
{
	public:
		Ladders();
		void setLadder(int, int);
		void printBoardwithInfo();
		
};

void Ladders::setLadder(int start, int end)	// this code is same as the one in Snakes.cpp
{
	static int funcCounter = 0; // keeps tab of how many ladders are there
	funcCounter++;
	stringstream ss;	// uses bits/stdc++.h 
	ss<<funcCounter;	// is converting int to string
	string strfuncounter;
	ss>>strfuncounter;
	
	int *rcs, *rce;	// row-column-start, row-column-end
	
	// this function is from board.h
	rcs = find_board_coordinates(start);		// 2 values are stored in rch; rch[0] is row info, rch[1] is column info
	board[rcs[0]][rcs[1]][1] = ladderstart;	// enum value of snakehead will be replaced here
	snakeorladderhere[rcs[0]][rcs[1]] = "L" + strfuncounter + "*";
	
	
	rce = find_board_coordinates(end);
	board[rce[0]][rce[1]][1] = ladderend;	// enum value of snaketail will be replaced here
	snakeorladderhere[rce[0]][rce[1]] = "L" + strfuncounter;
	
}

void Ladders::printBoardwithInfo()
{
	for(int i=0; i<10; i++)
	{
		for(int j=0; j<10; j++)
		{
			cout<<board[i][j][0]<<" "<<board[i][j][1]<<" "<<board[i][j][2]<<"\t";
		}
		cout<<"\n";
	}
}

Ladders::Ladders()	// 3 LADDERS TILL NOW
{
	setLadder(2, 18);
	setLadder(32, 53);
	setLadder(45, 77);
	//printBoardwithInfo();
	//fancyprintboard();
}

