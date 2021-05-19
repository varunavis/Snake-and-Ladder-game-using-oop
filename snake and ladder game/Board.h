#include<iostream>
#include <windows.h>
#ifndef BOARD_H
#define BOARD_H
using namespace std;

class Board
{
	public:	// variables
		int numberfilling;
		int mainboard[10][10];
		int board[10][10][3];
		string objecthere[10][10];
		string snakeorladderhere[10][10];
		enum object {
			nothing=0,
			player1,
			player2,
			player3,
			player4,
			snakehead=11,	// just like that, no reason for 11
			snaketail,
			ladderstart,
			ladderend
		};
		
	public: // functions
		Board();
		void printboard();
		void fancyprintboard();
		void setBoard_with_initializing_info();
		int* find_board_coordinates(int boardnumber);
		int updateScore(int, int);
		void printPlayers(string, int, int);
		void deletePlay(int);
};

Board::Board()
{
	numberfilling=0;
	for(int i=0; i<10; i++)
	{
		if(i%2==0)
		{
			for(int j=9; j>=0; j--)
			{
				numberfilling++;
				mainboard[9-i][9-j] = numberfilling;
				snakeorladderhere[9-i][9-j] = " ";
			}
		}
		else
		{
			for(int j=0; j<10; j++)
			{
				numberfilling++;
				mainboard[9-i][9-j] = numberfilling;
				snakeorladderhere[9-i][9-j] = " ";
			}
		}
	}
	
	setBoard_with_initializing_info();
}

void Board::printboard()
{
	for(int i=0; i<10; i++)
	{
		for(int j=0; j<10; j++)
		{
			cout.width(3);
			cout<<mainboard[i][j]<<" ";
		}
		cout<<"\n";
	}
}

void Board::fancyprintboard()	// has spaces in between so that snake or ladder or player position can be showed
{
    int row, column, lbofmainboard=10, continuousdotsrow, numberrow, snakeladderrow;
    int noofdotscolumn = lbofmainboard*(8+2);   // coz 8 dots and 2 spaces
    
    for(row=0, numberrow=1; row<lbofmainboard; row++, continuousdotsrow+=3, numberrow+=3) 
    {
        // first the dots row
        for(continuousdotsrow=0; continuousdotsrow<lbofmainboard; continuousdotsrow++)
        {
            cout<<"~~~~~~~~"<<"  ";   // 8 dots then 2 spaces
        }
        cout<<"\n"; // 1st row to next
        
        // then the number row - to print the numbers inside the square of dots
        for(column = 0; column<lbofmainboard; column++) 
        {
            cout<<"|";
            cout.width(6);
            cout<<right;
			cout<<mainboard[row][column];
            cout<<"|  ";
        }
        cout<<"\n"; // 2nd row to next
        
        // next the info showing snake or ladder here
        for(snakeladderrow=0; snakeladderrow<lbofmainboard; snakeladderrow++)
        {
            cout<<"|";
            cout.width(4);
            cout<<left;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);	//changing color for snake/ladder - red
			cout<<snakeorladderhere[row][snakeladderrow];
			cout.width(2);
            //cout<<left;
            if(objecthere[row][snakeladderrow] == " " || objecthere[row][snakeladderrow] == "")	// otherwise blank gets highlighted
            	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
            else
            	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 243);	//changing color for player - white and teal
			cout<<objecthere[row][snakeladderrow]; // snake or ladder or player position
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);	// making it dull white again
            cout<<"|  ";
        }
        cout<<"\n"; // 3rd row to next
        
        
        if(row==9)
        {
        	for(continuousdotsrow=0; continuousdotsrow<lbofmainboard; continuousdotsrow++)
	        {
	            cout<<"~~~~~~~~"<<"  ";   // 8 dots then 2 spaces
	        }
	        cout<<"\n";
		}
    }
}


void Board::setBoard_with_initializing_info()
{
	for(int i=0; i<10; i++)
	{
		for(int j=0; j<10; j++)
		{
			board[i][j][0] = mainboard[i][j];
			board[i][j][1] = nothing;	// 0 zero; for snake or ladder or player(if no snake or ladder) info
			board[i][j][2] = nothing;	// 0 zero; for other player info (suppose 2 players are present in same spot)
			
			//cout<<board[i][j][0]<<" "<<board[i][j][snake]<<" "<<board[i][j][ladder]<<"\t";
		}
		//cout<<"\n";
	}
}

int* Board::find_board_coordinates(int boardnumber) // optimized finding of coordinates of the board where the number is located
{
	int rcinfo[2], row=9, column=9;
	if(boardnumber<=10)	// remember, [0, 0] is 100, [1, 0] is 81, [2, 0] is 80
		row=9;
	else if(boardnumber<=20 && boardnumber>10)
		row=8; // go to the row 7
	else if(boardnumber<=30 && boardnumber>20)
		row=7;
	else if(boardnumber<=40 && boardnumber>30)
		row=6;
	else if(boardnumber<=50 && boardnumber>40)
		row=5;
	else if(boardnumber<=60 && boardnumber>50)
		row=4;
	else if(boardnumber<=70 && boardnumber>60)
		row=3;
	else if(boardnumber<=80 && boardnumber>70)
		row=2;
	else if(boardnumber<=90 && boardnumber>80)
		row=1;
	else if(boardnumber<=100 && boardnumber>90)
		row=0;
	
	for(column=0; column<10; column++)
	{
		if(boardnumber == mainboard[row][column])
		{
			rcinfo[0] = row;
			rcinfo[1] = column;
			break;
		}
	}
	
	return rcinfo;
}

int Board::updateScore(int playerno, int score)
{
	int *rc = find_board_coordinates(score);
	
	if(board[rc[0]][rc[1]][1] == snakehead)	// ONLY 3 SNAKES TILL NOW
	{
		switch(score)	// checking which snake it is, correspondingly player would be moved down
		{
			case 94:
				score = 78;
				cout<<"Oops! You've encountered a SNAKE. You slither down to 78"<<endl;
				break;
			
			case 55:
				score = 40;
				cout<<"Oops! You've encountered a SNAKE. You slither down to 40"<<endl;
				break;
			
			case 27:
				score = 6;
				cout<<"Oops! You've encountered a SNAKE. You slither down to 6"<<endl;
				break;
			
		}
	}
	
	else if(board[rc[0]][rc[1]][1] == ladderstart)
	{
		switch(score)	// checking which ladder it is
		{
			case 2:
				score = 18;
				cout<<"Yayy! You've found a LADDER. You climb up to 18"<<endl;
				break;
			
			case 32:
				score = 53;
				cout<<"Yayy! You've found a LADDER. You climb up to 53"<<endl;
				break;
			
			case 45:
				score = 77;
				cout<<"Yayy! You've found a LADDER. You climb up to 77"<<endl;
				break;
		}
	}
	return score;
}

void Board::printPlayers(string playername, int playerno, int score)
{
	int *rc = find_board_coordinates(score);
	//objecthere[rc[0]][rc[1]] = " ";
	if(board[rc[0]][rc[1]][1] == nothing)	// first slot is meant for snake or ladder (player later), if that is not there, then we are clear
		board[rc[0]][rc[1]][1] = playerno;
	
	else if (board[rc[0]][rc[1]][2] == nothing)	// if slot 1 is occupied, then we'll add the player
		board[rc[0]][rc[1]][2] = playerno;
		
	
	objecthere[rc[0]][rc[1]] = playername; 
	
	//fancyprintboard();
	//cout<<"Oui";
	//objecthere[rc[0]][rc[1]] = " ";
}

void Board::deletePlay(int previousscore)
{
	int *rc = find_board_coordinates(previousscore);
	objecthere[rc[0]][rc[1]] = " ";
}

//int main()
//{
//	Board b;
//	system("Color F9");
//	b.printboard();
//	b.fancyprintboard();
//	return 0;
//}
#endif
