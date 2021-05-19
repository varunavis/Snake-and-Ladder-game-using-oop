#include<iostream>
#include<stdlib.h>
#include<time.h>
#ifndef DICE_H
#define DICE_H
using namespace std;

class Dice
{
	public:
		int diceNum;
		int rolltheDice()
		{
			// Use current time as seed for random generator
			srand(time(0) * rand());  // if not used, rand() would produce same number everytime
			// srand(time(0)) was also starting off with the same number because it was called at the same time
			// so multiplied that too with rand()
			
			diceNum = (rand() % 6) + 1;
			//cout<<"Number on the dice: ";
			//cout <<diceNum<<endl;
			return diceNum;
		}
};

#endif
