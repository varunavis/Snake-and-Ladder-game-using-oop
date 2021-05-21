/* Program to set the snakes and the info about
   the snakes head or tail
   */

#include<iostream>
#include <bits/stdc++.h>
#include<string.h>
#include "Board.h"
using namespace std;

class Snakes: virtual public Board
{
	public:
		Snakes();
		void setSnake(int, int);
		void printBoardwithInfo();
};



void Snakes::setSnake(int head, int tail)
{
	static int funcCounter = 0; // keeps tab of how many times func is called, that is how many snakes are there
	funcCounter++;
	stringstream ss;	// uses bits/stdc++.h 
	ss<<funcCounter;	// is converting int to string
	string strfuncounter;
	ss>>strfuncounter;
	
	int *rch, *rct;	// row-column-head, row-column-tail
	
	// this function is from board.h
	rch = find_board_coordinates(head);		// 2 values are stored in rch; rch[0] is row info, rch[1] is column info
	board[rch[0]][rch[1]][1] = snakehead;	// enum value of snakehead will be replaced here
	snakeorladderhere[rch[0]][rch[1]] = "S" + strfuncounter + "*";
	
	
	rct = find_board_coordinates(tail);
	board[rct[0]][rct[1]][1] = snaketail;	// enum value of snaketail will be replaced here
	snakeorladderhere[rct[0]][rct[1]] = "S" + strfuncounter;
	
}

void Snakes::printBoardwithInfo()
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

Snakes::Snakes()	// ONLY 3 SNAKES TILL NOW
{
	//setBoard_with_initializing_info();	// initiate the board numbers and set object info to zero
	
	// now to set the actual snakes
	setSnake(94, 78);	//snake1; gonna have to set snake number manually
	setSnake(55, 40);
	setSnake(27, 6);
	// print the info in array
	//printBoardwithInfo();
	
	
	//fancyprintboard();
}

