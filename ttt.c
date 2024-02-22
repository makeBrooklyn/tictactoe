// definitions

// The Software Version
#define __VERSION "1.0.0"

// Some things that are different for windows vs nix
#ifdef _WIN32
// The console clear command for windows
#define _CLR_CMD_ "cls"
#else
// The console clear command for linux and most
// everything else
#define _CLR_CMD_ "clear"
#endif

// Include required for the functions / libraries
// we are using.
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ttt.h"

// Global variables

// Player one name
char pOne[128];
// Player Two name
char pTwo[128];
// Player one marker
char pOneChar = 'X';
// Player two marker
char pTwoChar = 'O';
// The array to hold the board values
char board[3][3];
// Any error messages that need to be displayed
char error[256];
// Keep track of whos turn it is
char turn = 1;
// The number of turns taken so far.
int turns = 0;
// The name of the current player
char player[128];
// The current marker to use
char marker = 'X';
// The name of the winner
char winner[128];
// The marker of the winner
char winnerMark = '-';

// Function Definitions

// Function:	isMatch(char a, char b, char c)
// Parms:		requires three chars. The three
// 				elements in any column, row, or
//					diagonal on a Tic-Tac-Toe board.
// Return:		Returns a 1 (true) if a winner
// 				has been detected. It also sets
// 				the winner name and mark for
// 				later display
int isMatch(char a, char b, char c)
{
	// If a = b and b = c we have a match
	if ((a == b) && (b == c))
	{
		// if it's an X, the winner is player one
		if (a == 'X')
		{
			// set the winner name
			strcpy(winner, pOne);
			// set the winner mark
			winnerMark = 'X';
			// return true
			return 1;
		} // if not, player two is the winner
		else
		{
			// set the winner name
			strcpy(winner, pTwo);
			// set the winner mark
			winnerMark = 'O';
			// return true
			return 1;
		}
	}
	// If we had no match, return false
	return 0;
}

// Function:	gameOver()
// Parms: 		none
// Return:		Returns a 1 (true) if the game is
// 				ended and a 0 if it is not.
int gameOver()
{
	// Just a counter
	int i = 0;

	// Check the rows and cols
	for (i = 0; i < 3; i++)
	{
		// Check row i and column i to see if all three elements match
		if (isMatch(board[i][0], board[i][1], board[i][2]) ||
			 isMatch(board[0][i], board[1][i], board[2][i]))
		{
			// They all match! Return a 1
			return 1;
		}
	}
	// Check the two diagonals to see if all three elements match.
	if (isMatch(board[0][0], board[1][1], board[2][2]) ||
		 isMatch(board[0][2], board[1][1], board[2][0]))
	{
		// They all match! Return a 1
		return 1;
	}

	if (turns >= 9)
	{
		// There is no winner but the game is over
		return 1;
	}
	// If we've made it this far, there's no match. Return a 0.
	return 0;
}

// Function:	squareFill(int num)
// Parms: 		require one integer indicating the
// 				square to fill from 1-9
// Return:		Returns a 1 (true) if the game is
int squareFill(int num)
{
	int row = 0; // The row coordinate of the square
	int col = 0; // The column coordinate of the square
	int ret = 0; // The return value. Default to false (0)

	// If num is a valid square number (1-9) try to fill the square
	if (num >= 1 && num <= 9)
	{

		// Since array indicies start at zero, not one
		// we shift the number back by one.
		num--;

		// Set the row index to the absolute value
		// (just the whole number part without any decimal
		// or remainder) of the number divided by three to
		// be the row index
		row = abs(num / 3);

		// Set the column index to the remainder of the
		// above by subtracting the row index times three
		// from the original number.
		col = num - (row * 3);

		// Before placing the current players marker on the
		// square, check to see that it is not already used.
		if (board[row][col] != 'X' && board[row][col] != 'O')
		{
			// Set the current players marker to the
			// board elemnt indicated.
			board[row][col] = marker;

			// count the turn
			turns++;

			// Set the return value to true (1).
			ret = 1;
		}
	}

	// Return the return value
	return ret;
}

// Function:	renderBoard()
// Parms: 		none
// Return:		Draws the board and messages then returns 0
int renderBoard()
{
	// Clear the screen
	system(_CLR_CMD_);

	// Print the welcome message
	printf("Hello %s (%c) and %s (%c), lets play Tic-tac-toe...\n", pOne, pOneChar, pTwo, pTwoChar);

	// Print the basic instructions
	printf("Choose an unoccupied square 1-9 to place your marker on.\n\n");

	// Print the Tic-tac-toe board
	printf(" %c | %c | %c \n-----------\n", board[0][0], board[0][1], board[0][2]);
	printf(" %c | %c | %c \n-----------\n", board[1][0], board[1][1], board[1][2]);
	printf(" %c | %c | %c \n", board[2][0], board[2][1], board[2][2]);

	// Print any error messages
	printf("\n%s\n", error);

	// return 0
	return 0;
}

// Function:	main()
// Parms: 		none
// Return:		Sets up the variables and then
//             executes the loop that runs the game
int main()
{
	// This is the array that holds the values for
	// the board. It's a 3x3 array of chars.
	board[0][0] = '1';
	board[0][1] = '2';
	board[0][2] = '3';
	board[1][0] = '4';
	board[1][1] = '5';
	board[1][2] = '6';
	board[2][0] = '7';
	board[2][1] = '8';
	board[2][2] = '9';

	// A char to accept user input
	char userinput = ' ';

	// Another char to absoarb the rest of stdin
	char altchar = ' ';

	// Set the name of the first player to "Player One"
	strcpy(pOne, "Player One");
	// Set the name of the second player to "Player Two"
	strcpy(pTwo, "Player Two");

	// Prepopulating the error message with a space as a placeholder.
	strcpy(error, " ");

	// Copy player ones info to the current player variables
	strcpy(player, pOne);
	marker = pOneChar;

	// Loop until there is a winner a draw or a Q
	while (userinput != 'q' && userinput != 'Q')
	{
		// reset the alt char to a space.
		altchar = ' ';
		// Draw the board in it's curent state
		renderBoard();

		// Promt the players for the next input
		printf("%s, Enter the square you want or Q to quit >", player);

		// Get the next move
		userinput = getchar();

		// Empty stdin
		while (altchar != '\n' && altchar != EOF)
		{
			altchar = getchar();
		}

		// Check for a quit command
		if (userinput == 'q' || userinput == 'Q')
		{
			// Say goodbye
			sprintf(error, "\n\nAll done. You pressed: %c\n\n", userinput);
			// Draw the board and then exit
			renderBoard();
			exit(0);
		}
		else if (userinput >= '1' && userinput <= '9')
		{
			// If a move has been attempted try to implement it
			if (squareFill(((int)userinput - 48)))
			{
				// Check to see if this move has ended the game
				if (gameOver())
				{
					// Check to see if there is a winner
					if (winnerMark != '-')
					{
						// Congratulate the winer
						sprintf(error, "\n\nWinner!\n\n%s (%c) wins!!\n\n", player, marker);
					}
					else
					{
						// Let the players know that it's a draw
						sprintf(error, "\n\nDraw. No winner this time.\n\n");
					}
					// Draw the board and then exit
					renderBoard();
					exit(0);
				}
				else
				{
					// The game continues
					if (turn == 1)
					{
						// update the turn tracker
						turn = 2;
						// Copy the player 2 info into the current player variables
						strcpy(player, pTwo);
						marker = pTwoChar;
					}
					else
					{
						// update the turn tracker
						turn = 1;
						// Copy the player 1 info into the current player variables
						strcpy(player, pOne);
						marker = pOneChar;
					}
				}
			}
		}
		else
		{
			// A character thats not a valid square number
			sprintf(error, "\n\nInvalid character on last input: %c\n\n", userinput);
		}
	}
	// Say goodbye
	printf("\nBye!");
	// Return a zero
	return 0;
}
