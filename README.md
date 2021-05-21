# Snake and Ladder game using OOP concepts in C++ language
## Introduction
Snake and Ladders is a board game in which there are around 2-4 players on a board numbered 1 to 100. The aim of the game is to reach the last number, 100 by avoiding as many snakes and chancing upon ladders, and faster than the other players. The games ends when any of the players reaches a score of 100. The number of spaces a player can move is decide by a single dice. Each player gets a chance in the decided order. Order is decided at the start; players roll the dice and the one who gets the highest number on the dice starts first, followed by the other players in descending order of the number on the dice. If a player encounter a snake's head, they have to follow it down to the tail - that is the new position of the particular player. If a player chances upon a ladder start, they have to climb it up till the end and that would be their new position. So in short, if you land on a number which has a snake head, you have to go down some spaces, and if you land on a ladder, you go up some spaces. This is how the board looks like: 

![image](https://user-images.githubusercontent.com/70715821/119087076-20fd6b00-ba24-11eb-8b13-6ed92076caff.png)

## Game nomenclature
<strong>L*</strong> means the ladder start, and the number after it (L1*) means ladder 1. So its corresponding end must be found, L1. 
The start of any ladder/snake is indicated by an asterisk*. 
Similarly <strong>S*</strong> signifies snake head, from where the player must travel down to its respective snake tail a few spaces. 

<strong>Example:</strong>

If player 2 lands on number 18 (ladder 1 end), it won't matter since ladders are used to climb up, not down (in this game). So no change in score.

If player 4 lands on number 55 (snake 2 head), they would slither down to number 40, as that is snake 2's tail. It would not go down to number 6 as that is snake 3's tail.

if player 3 lands on number 32 (ladder 2 start), they would climb up and land on square 53, ladder 2's end. Going up till 77 is not allowed since that is ladder 3's end.
