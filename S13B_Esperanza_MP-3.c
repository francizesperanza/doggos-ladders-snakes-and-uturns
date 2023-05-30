/******************************************************************
This is to certify that this project is my own work, based on my personal efforts in studying and applying the concepts learned.
I have constructed the functions and their respective algorithm and corresponding code by myself. The program was run, tested, 
and debugged by my own efforts. I further certify that I have not copied in part or whole or otherwise plagiarized the work of
other students and/or persons. 

Franciz Emmanuelle Angelo L. Esperanza, DLSU ID# 12179922
******************************************************************/

/*
     Description: This program runs a game called Doggos, Ladders, Slides, and U-Turns. It is a game similar to Snakes and Ladders
     and it can be played by 2-5 players. Players need to roll a pair of 10-sided die to progress through the game and the chance
     to encounter objects is determined by another 10-sided die. The game ends when a player reaches tile 100.
     Programmed by: Franciz Emmanuelle Angelo L. Esperanza S13B
     Last modified: 06 Feb 2022
     Version: 1.2
     [Acknowledgements: https://developer.gnome.org/documentation/guidelines/programming/coding-style.html#whitespace
     			https://devdocs.io/c/
     			https://www.cplusplus.com/reference/cstdlib/strtol/
			https://www.geeksforgeeks.org/fgets-gets-c-language/
			https://www.geeksforgeeks.org/memset-c-example/
			
			edx's C Programming: Language Foundations]
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

// FUNCTION PROTOTYPES
int	roll10SidedDie ();

int	getSequence 		(int	playerCount);
int	updateSequence 		(int	nSequence,
				 int	playerCount);
int	getCurrentPlayer 	(int	nSequence,
				 int	playerCount);

int	getCurrentRow 		(int	row [],
				 int   *position);
int	getCurrentColumn 	(int	column [],
				 int   *position);
int	getTileNumber 		(int   *rowRoll,
				 int   *columnRoll,
				 int	row [],
				 int	column []);

int	isValidPlayerCount 	(int	playerCount);
int	isItDouble5 		(int	firstRoll,
				 int	secondRoll);
int	isItDouble3 		(int	firstRoll,
				 int	secondRoll);
int	getDouble3Tile 		(int   *firstRoll,
				 int   *secondRoll, 
				 int	row [], 
				 int	column [], 
				 int   *startTile);

int	getDoggoMovement 	(int   *rowRoll, 
				 int   *columnRoll, 
				 int	row [], 
				 int	column []);
int	getLadderMovement 	(int   *rowRoll,
				 int   *columnRoll,
				 int	row [], 
				 int	column [], 
				 int    position);
int	getSlideMovement 	(int   *rowRoll,
				 int   *columnRoll,
				 int	row [], 
				 int	column [], 
				 int    position);
int	getUTurnMovement 	(int    startTile);
int	getRow10Movement 	(int   *firstRoll,
				 int	startTile);

void	fillBoard 		(int	boardSpace []);
void	fillRow			(int	row []);
void	fillColumn 		(int	column []);

void 	getObjectCount		(int   *objectRoll,
				 int 	objectCount [],
				 int 	currentPlayer);
void	displayObjectMovement	(int   *objectRoll,
				 int   *position, 
				 int	rowRoll, 
				 int	columnRoll, 
				 int	row[], 
				 int	column [], 
				 int    startTile);
void	getFarthestObject 	(int	nFarthestObject [],
				 int	positionPreObject, 
				 int    position, 
				 int   *objectRoll, 
				 int	currentPlayer);
void	doObjectRoll 		(int	row [], 
				 int	column [],
				 int 	objectCount [],
				 int	nFarthestObject [], 
				 int	prevPosition [],
				 int   *objectRoll, 
				 int   *position, 
				 int	rowRoll, 
				 int	columnRoll, 
				 int	startTile, 
				 int	currentPlayer, 
				 int	positionPreObject);
				 
void	displayRow10Movement 	(int   *firstRoll,
				 int	startTile, 
				 int   *position,
				 int	row [],
				 int	column []);

void	checkIfDisplayBoard 	(char 	ifDisplayBoard,
				 int	boardSpace [], 
				 int	prevPosition []);
void	displayBoard 		(int	boardSpace [],
				 int	prevPosition []);

void	checkIfDisplayRank 	(char	ifDisplayRank,
				 int	prevPosition [], 
				 int	playerCount);
void	displayRanking 		(int	prevPosition [], 
				 int	playerCount);

void	checkIfWin 		(int   *position,
				 int	objectCount [], 
				 int	objectRoll, 
				 int	currentPlayer, 
				 int	nFarthestObject [],
				 int	prevPosition [],
				 int	firstRoll);
void	displayWin 		(int	objectCount [],
				 int	objectRoll, 
				 int	currentPlayer, 
				 int	nFarthestObject [],
				 int	prevPosition [],
				 int	firstRoll);

void	checkIfPlayAgain 	(char	ifPlayAgain,
				 int   *replay, 
				 int	prevPosition [], 
				 int	objectCount [], 
				 int	nFarthestObject [], 
				 int   *position);
void	resetValues 		(int	prevPosition [],
				 int	objectRoll [], 
				 int	nFarthestObject [], 
				 int   *position);
// MAIN
int main (void)
{
	int boardSpace [100];
	int row [100], column [100];
	int prevPosition [5] = {0,0,0,0,0};
	int objectCount [5] = {0,0,0,0,0};
	int nFarthestObject [5] = {0,0,0,0,0};
	
	int position = 0;
	int playerCount, nSequence, positionPreObject, firstPlayer, currentPlayer, startTile, replay;
	int firstRoll, secondRoll, objectRoll;
	int rowRoll = 0, columnRoll = 0;
	int i;
	
	char userInput [5];
	char* endPtr;
	
	char ifDisplayBoard = '*';
	char ifDisplayRank = '*';
	char ifPlayAgain = '*';
	
	srand (time (NULL));
	
	printf ("Welcome to Doggos, Ladders, Slides and U-Turns!\n");
	printf ("This game can be played by 2-5 players.\n");
	
	do {
		printf ("\nHow many players will play?: ");
		fgets (userInput,
		       5,
		       stdin);
		playerCount = strtol (userInput,
				     &endPtr,
				      0);
		if (isValidPlayerCount (playerCount) != 1)
			printf ("\nPlease input a valid number.");
	} while (playerCount < 2 || playerCount > 5);
	
	do {
	
		
		nSequence = getSequence (playerCount);
		firstPlayer = getCurrentPlayer (nSequence,
						playerCount);
						
		printf ("\n----------------------------------------");
		printf ("\n\nHere is the sequence of play: %d\n", nSequence);
		printf ("\nPlayer %d goes first,", firstPlayer);
		printf ("\nfollowed by ");
		for (i = 0; i < playerCount - 1; i++) {
			nSequence = updateSequence (nSequence,
						    playerCount);
			currentPlayer = getCurrentPlayer (nSequence,
						 	  playerCount);	
			if (i != playerCount - 2) {
				printf ("Player %d, ", currentPlayer);
			} else
				printf ("and Player %d.", currentPlayer);
			
		}
		printf ("\n\nPress ENTER to start!");
		nSequence = updateSequence (nSequence,
					    playerCount);
		
		getchar();
		
		//GAME START
		
		fillRow (row);
		fillColumn (column);
		
		firstPlayer = getCurrentPlayer (nSequence,		// to determine when a round ends
						playerCount); 
		
		do {
			currentPlayer = getCurrentPlayer (nSequence,
							  playerCount);
					  
			startTile = prevPosition [currentPlayer - 1];
			
			
			printf ("\n\nPlayer %d, you're currently on tile %d.", currentPlayer,
									       startTile);
			printf (" It's your turn to roll the pair of D10 dice!");
			printf ("\nPress ENTER to roll!");
			getchar();
			objectRoll = 0;				        // for winning move
			
			if (startTile >= 90) {
				displayRow10Movement (&firstRoll,
						       startTile,
						      &position,
						       row,
						       column);
				positionPreObject = position;
				
				checkIfWin (&position,
				 	     objectCount,
					     objectRoll, 
					     currentPlayer, 
					     nFarthestObject, 
					     prevPosition, 
					     firstRoll);
		
				if (position != 100) {
					doObjectRoll (row, 
						      column, 
						      objectCount, 
						      nFarthestObject, 
						      prevPosition,
				 		     &objectRoll, 
						     &position,
						      rowRoll,
						      columnRoll, 
						      startTile, 
						      currentPlayer, 
						      positionPreObject);
					
					checkIfWin (&position,
					 	     objectCount,
						     objectRoll, 
						     currentPlayer, 
						     nFarthestObject, 
						     prevPosition, 
						     firstRoll);
				}
			} else {
				firstRoll = roll10SidedDie();								//normal movement rolls
				secondRoll = roll10SidedDie();
			
				printf ("\n\nThe dice rolled %d and %d.", firstRoll, 
									  secondRoll);
				
				if (isItDouble5 (firstRoll,								// check for double-5
						 secondRoll) == 1) {							// if 1, skips object roll
					firstRoll = getCurrentRow (row,
								  &startTile);
					secondRoll = getCurrentColumn (column,
								      &startTile);
					printf ("\nSorry. You rolled a double-5. You stay on tile %d (row %d, col %d)", startTile,
															firstRoll,
															secondRoll);
					prevPosition [currentPlayer - 1] = startTile;
				} else {										// normal movement segment
					if (isItDouble3 (firstRoll,							// check for double-3
							 secondRoll) == 1) {
						if (startTile == 0) {
							printf ("\nUnfortunate. You rolled a double-3 on the starting tile.");
							printf (" You stay on tile 0 (row 0, col 0).");
							position = 0;
						} else {
							position = getDouble3Tile (&firstRoll, 
										   &secondRoll, 
										    row, 
										    column,
										   &startTile);
							printf ("\nWow! You rolled a double-3. ");
							printf ("\nYou move to tile %d (row %d, col %d).", position, 
													   firstRoll, 
													   secondRoll);
							positionPreObject = position;
						}
					} else {									// normal movement
						position = getTileNumber (&firstRoll,
								  	  &secondRoll, 
									   row, 
									   column);
						printf ("\nYou move to tile %d.", position);
						positionPreObject = position;
					}
							
					checkIfWin (&position,
					 	     objectCount,
						     objectRoll, 
						     currentPlayer, 
						     nFarthestObject, 
						     prevPosition, 
						     firstRoll);
							
					if (position != 0 && position != 100) {
						doObjectRoll (row, 
							      column, 
							      objectCount, 
							      nFarthestObject, 
							      prevPosition,
					 		     &objectRoll, 
							     &position,
							      rowRoll, 
							      columnRoll, 
							      startTile, 
							      currentPlayer, 
							      positionPreObject);	
					
						checkIfWin (&position,
						 	     objectCount,
							     objectRoll, 
							     currentPlayer, 
							     nFarthestObject, 
							     prevPosition, 
							     firstRoll);	
					} else
						prevPosition [currentPlayer - 1] = position;
				}
				
			}
			
			printf ("\n----------------------------------------");
			
			nSequence = updateSequence (nSequence,
						    playerCount);
			currentPlayer = getCurrentPlayer (nSequence, 
							  playerCount);
			
			if (currentPlayer == firstPlayer && position != 100) {
				checkIfDisplayBoard (ifDisplayBoard, 
						     boardSpace, 
						     prevPosition);	
				checkIfDisplayRank (ifDisplayRank, 
						    prevPosition, 
						    playerCount);
				getchar();
			}
		} while (position != 100);
		
		checkIfPlayAgain (ifPlayAgain,
				 &replay, 
				  prevPosition, 
				  objectCount, 
				  nFarthestObject, 
				 &position);
	} while (replay == 1);
	
	return 0;
}

// FUNCTIONS

/*   This function returns a random number from 1-10
     @return a random number from 1-10
*/

int
roll10SidedDie () 
{
	return rand () % 10 + 1; 
}

/*   This function returns a 2-5 digit integer that determines the sequence of players
     Precondition: the player count is 2-5
     @param playerCount is the number of players playing the game
     @return the 2-5 digit integer that determines the sequence of players
*/

int
getSequence 		(int	playerCount)
{
	int sequenceDigit, exponent, final = 0;
	int finalSequence [5];
	int i, j = 0, k, l = 1;
	
	sequenceDigit = rand () % playerCount + 1;					// initialize first digit of the sequence
	finalSequence [0] = sequenceDigit;
	
	do {
		for (i = 0; i < playerCount; i++) {					// this loop checks for duplicates
			if (sequenceDigit == finalSequence [j]) {			// if there is number in the array that is equal to
				sequenceDigit = rand () % playerCount + 1;		// random number, roll again and scan the array once again
				j=0;
				i=0;
			} else
				j++;
			
		}									// this loop can only be escaped when there is no dupes
		
		if (j == playerCount - 1) {						// initialize the next digit of the sequence
			finalSequence [l] = sequenceDigit;
			l++;
			j=0;
			i=0;
		}
			
	} while (l < playerCount);
	
	exponent = playerCount - 1;
	
	for (k = 0; k < playerCount; k++) {
		final += finalSequence [k] * pow (10, exponent);
		exponent--;
	}
	
	return final;
}

/*   This function puts the digit of the next player to the leftmost digit and the current player to the rightmost digit
     @param nSequence is the 2-5 digit number that determines the sequence of play
     @param playerCount is the number of players playing the game
     @return the updated 2-5 digit integer that determines the sequence of players
*/

int
updateSequence 		(int	nSequence,
			 int	playerCount)
{
	int prevFirst = 0, exponent = 0, update = 0;
	
	exponent = playerCount - 1;
	prevFirst = nSequence / pow (10, exponent);
	update = nSequence % (int) pow (10, exponent) * 10 + prevFirst;
	
	return update;
}

/*   This function computes for the player that is currently in play
     @param nSequence is the 2-5 digit number that determines the sequence of play
     @param playerCount is the number of players playing the game
     @return the 2-5 digit integer that determines the sequence of players
*/

int
getCurrentPlayer 	(int	nSequence,
			 int	playerCount)
{
	return nSequence / pow (10, playerCount - 1);
}

/*   This function computes for the row number that the player is currently in
     Precondition: row [] is correctly arranged
     @param row [] is an array filled with arranged row numbers
     @param *position is the player's position after an event
     @return the current row of the player based on their position
*/

int
getCurrentRow 		(int	row [],
			 int   *position)
{
	if (*position != 0)
		return row [*position - 1];
	else
		return 0;
}

/*   This function computes for the column number that the player is currently in
     Precondition: column [] is correctly arranged
     @param column [] is an array filled with arranged column numbers
     @param *position is the player's position after an event
     @return the current column of the player based on their position
*/
int
getCurrentColumn 	(int	column [],
			 int   *position)
{
	if (*position != 0)
		return column [*position - 1];
	else
		return 0;
}

/*   This function computes for the current tile that the player is on
     Precondition: row [] and column [] is correctly arranged, rowRoll and columnRoll is a number from 1 - 10
     @param *rowRoll is the 10-sided die roll that determines the row that the player is going to
     @param *columnRoll is the 10-sided die roll that determines the column that the player is going to
     @param row [] is an array filled with arranged row numbers
     @param column [] is an array filled with arranged column numbers
     @return the current tile of the player based on their position
*/

int
getTileNumber 		(int   *rowRoll,
			 int   *columnRoll,
			 int	row [],
			 int	column [])
{
	int sameRow [10], sameColumn [10];
	int i, j = 0, k = 0;
	int l = 0, m = 0;
		
	
	for (i = 0; i < 100; i++) {
		if(row [i] == *rowRoll) {			//stores the index of row[] if a value in row[] is equal to the rowRoll
			sameRow [j] = i;
			j++;
		}
		if(column [i] == *columnRoll) {			//stores the index of column[] if a value in column[] is equal to the columnRoll
			sameColumn [k] = i;
			k++;
		}
	}

	
	while (l != 10) {
		if(sameRow [l] == sameColumn [m])		//if the same number is found on both arrays, return it + 1
			return sameRow [l] + 1;
		
		else
			m++;					//compare the next number on sameColumn to sameRow
			if (m == 10) {				//compare the next number on sameRow to sameColumn 
				m = 0;
				l++;
			}
	}
	
	return 0;
}

/*   This function checks if the player count is a number from 2-5
     @param playerCount is the number of players playing the game
     @return 1 if the number is 2 - 5
     	     0 if not
*/

int
isValidPlayerCount 	(int	playerCount)
{
	switch (playerCount) {
	case 2:
	case 3:
	case 4:
	case 5: 
		return 1; 
		break;
	default:
		return 0;	
	}
}

/*   This function checks if the player rolled a double-5
     @param firstRoll is the 10-sided die roll that determines the row that the player is going to
     @param secondRoll is the 10-sided die roll that determines the column that the player is going to
     @return 1 if both rolls is equal to 5
     	     0 if not
*/

int
isItDouble5 		(int	firstRoll,
			 int	secondRoll)
{
	if (firstRoll == 5 && secondRoll == 5)
		return 1;
	else
		return 0;
}

/*   This function checks if the player rolled a double-3
     @param firstRoll is the 10-sided die roll that determines the row that the player is going to
     @param secondRoll is the 10-sided die roll that determines the column that the player is going to
     @return 1 if both rolls is equal to 3
     	     0 if not
*/

int	
isItDouble3 		(int	firstRoll,
			 int	secondRoll)
{
	if (firstRoll == 3 && secondRoll == 3)
		return 1;
	else
		return 0;
}

/*   This function returns the tile number that the player should proceed to when they roll a double-3
     Precondition: the player rolled a double-3 and the player's starting tile is not 0 and not on row 10
     @param *firstRoll is the 10-sided die roll that determines the row that the player is going to
     	    *firstRoll gets updated to the player's current row plus 3 if starting tile is not on row 8 and above
	     and 10 if it is
     @param *secondRoll is the 10-sided die roll that determines the column that the player is going to
     	    *secondRoll gets updated to the player's current column if starting tile is not on row 8 and above
	     and 2 if it is
     @param row [] is an array filled with arranged row numbers
     @param column [] is an array filled with arranged column numbers
     @param *startTile is the player's tile at the start of their turn
     @return the tile number that the player should proceed to when they roll a double-3
     	     99 if the player's current row is 8-10
*/

int
getDouble3Tile 		(int   *firstRoll,
			 int   *secondRoll, 
			 int	row [], 
			 int	column [], 
			 int   *startTile)
{
	if (getCurrentRow (row, 
			 *&startTile) < 8) {
		*firstRoll = getCurrentRow (row,
			  		  *&startTile) + 3;
		*secondRoll = getCurrentColumn (column, 
					      *&startTile);
		return getTileNumber (*&firstRoll,
				      *&secondRoll, 
				        row, 
					column);
	} else {
		*firstRoll = 10;
		*secondRoll = 2;
		return 99;
	}
}

/*   This function returns the tile number that the Doggo should proceed to. The Doggo
     can go to any valid tile
     Precondition: the objectRoll rolled a 1, the player is not on tile 0
     @param *rowRoll is the 10-sided die roll that determines the row that the player is going to
     	    *rowRoll gets updated to the random number generated by roll10SidedDie ()
     @param *columnRoll is the 10-sided die roll that determines the column that the player is going to
     	    *columnRoll gets updated to the random number generated by roll10SidedDie ()
     @param row [] is an array filled with arranged row numbers
     @param column [] is an array filled with arranged column numbers
     @return the tile number that the Doggo should proceed to
*/

int
getDoggoMovement 	(int   *rowRoll, 
			 int   *columnRoll, 
			 int	row [], 
			 int	column [])
{
	int dogTile;
	
	*rowRoll = roll10SidedDie ();
	*columnRoll = roll10SidedDie ();
	
	dogTile = getTileNumber (*&rowRoll,
				 *&columnRoll, 
				   row, 
				   column);

	return dogTile;
}

/*   This function returns the tile number where the top of the Ladder will go. The Ladder
     can go to any tile on a row that is greater than the player's current row.
     Precondition: the objectRoll rolled a 2, the player is not on tile 0 and not on row 10
     @param *rowRoll is the 10-sided die roll that determines the row that the player is going to
     	    *rowRoll gets updated to the random number generated by roll10SidedDie ()
     @param *columnRoll is the 10-sided die roll that determines the column that the player is going to
     	    *columnRoll gets updated to the random number generated by roll10SidedDie ()
     @param row [] is an array filled with arranged row numbers
     @param column [] is an array filled with arranged column numbers
     @param *position is the player's position after an event
     @return the tile number where the Ladder will take you
*/

int
getLadderMovement 	(int   *rowRoll,
			 int   *columnRoll,
			 int	row [], 
			 int	column [], 
			 int    position)
{
	int ladderTile, cRow;
	
	cRow = getCurrentRow (row, 
			     &position);
	
	do {
		*rowRoll = roll10SidedDie ();
		*columnRoll = roll10SidedDie ();
		
		ladderTile = getTileNumber (*&rowRoll,
					    *&columnRoll, 
					      row, 
					      column);
	} while (*rowRoll <= cRow);
	
	return ladderTile;
}

/*   This function returns the tile number where the bottom of the Slide will go. The Slide
     can go to any tile on a row that is less than the player's current row.
     Precondition: the objectRoll rolled a 3, the player is not on tile 0 and not on row 1
     @param *rowRoll is the 10-sided die roll that determines the row that the player is going to
     	    *rowRoll gets updated to the random number generated by roll10SidedDie ()
     @param *columnRoll is the 10-sided die roll that determines the column that the player is going to
     	    *columnRoll gets updated to the random number generated by roll10SidedDie ()
     @param row [] is an array filled with arranged row numbers
     @param column [] is an array filled with arranged column numbers
     @param *position is the player's position after an event
     @return the tile number where the Slide will take you
*/

int
getSlideMovement 	(int   *rowRoll,
			 int   *columnRoll,
			 int	row [], 
			 int	column [], 
			 int    position)
{
	int slideTile, cRow;
	
	cRow = getCurrentRow (row, 
			     &position);
	
	do {
		*rowRoll = roll10SidedDie ();
		*columnRoll = roll10SidedDie ();
	
		slideTile = getTileNumber (*&rowRoll, 
					   *&columnRoll, 
					     row, 
					     column);
	} while (*rowRoll >= cRow);
	
	return slideTile;
}

/*   This function returns the tile number that the UTurn should proceed to. The UTurn
     goes to the player's starting tile of the current turn
     Precondition: the objectRoll rolled a 4, the player is not on tile 0
     @param *startTile is the player's tile at the start of their turn
     @return the tile number that the UTurn should proceed to
*/

int
getUTurnMovement 	(int   startTile)
{
	int uTurnTile;
	
	uTurnTile = startTile;
	
	return uTurnTile;
}

/*   This function returns the tile number that the player should proceed to when the
     player is on tiles 90-99
     Precondition: the player is on tiles 90-99 at the start of their turn
     @param *firstRoll is the 10-sided die roll that gets added to the player's startTile
     	    *firstRoll gets updated to the random number generated by roll10SidedDie ()
     @param startTile is the player's tile at the start of their turn
     @return the tile number that the player should proceed to
*/

int
getRow10Movement 	(int   *firstRoll,
			 int	startTile)
{
	int row10Tile;
	
	*firstRoll = roll10SidedDie ();

	row10Tile = startTile + *firstRoll;
	
	return row10Tile;
}

/*   This function fills the boardSpace [] array with numbers 1-100
     ex. boardSpace [0] will have 1, boardSpace [1] will have 2, etc.
     @param boardSpace [] is an array containing numbers 1-100
     @return the boardSpace [] array with numbers 1-100
*/

void
fillBoard 		(int	boardSpace [])
{
	int i, numbers = 1;
	
	for (i = 0; i < 100; i++) {
		boardSpace [i] = numbers;
		numbers++;
	}
}

/*   This function fills the row [] array with appropriate row numbers
     ex. row [0] to row [9] will have 1-10, row [10] to row [19] will have 1-10, etc.
     @param row [] is an array containing appropriate row numbers
     @return the row [] array with correct row numbers
*/

void
fillRow 		(int	row [])
{
	int i = 0, j = 0;
	int end = 9, rowNumber = 1;
	
	for(i = 0; i < 10; i++) {
		while (j <= end) {
			row [j] = rowNumber;
			j++;
		}
		
		end += 10;
		rowNumber++;
	}
	
}

/*   This function fills the column [] array with appropriate column numbers
     ex. column [0] to column [9] will have 1-10, column [10] to column[19] will have 10-1, etc.
     @param column [] is an array containing appropriate column numbers
     @return the column [] array with correct column numbers
*/

void
fillColumn 		(int 	column [])
{
	int i = 0, j = 0, k = 19;
	int oddStart = 0, oddEnd = 9, evenStart = 19, evenEnd = 10, columnNumber = 1;
	
	for(i = 0; i < 5; i++) {
		while (j >= oddStart && j <= oddEnd) {
			column [j] = columnNumber;
			columnNumber++;
			j++;
		}
		
		columnNumber = 1;
		
		while (k <= evenStart && k >= evenEnd) {
			column [k] = columnNumber;
			columnNumber++;
			k--;
		}
		
		columnNumber = 1;
		
		oddStart += 20;
		oddEnd += 20;
		evenStart += 20;
		evenEnd += 20;
		
		j = oddStart;
		k = evenStart;
	}
	
}

/*   This function updates the objectCount [] array with a code that indicates the number of
     object encountered by a player
     ex. 3212 means the player has encountered 3 Doggos, 2 Ladders, 1 Slide, and 2 UTurns
     @param *objectRoll is a 10-sided die that determines the object encountered by a player on a tile
     @param objectCount [] is an array that contains the object count code of each player
     @param currentPlayer is the digit of the player that is currently playing
     @return the object count code of the current player
*/

void 
getObjectCount		(int *objectRoll,
			 int objectCount [],
			 int currentPlayer)
{
	switch (*objectRoll) {
	case 1: 
		objectCount [currentPlayer - 1] += 1000;
		break;
	case 2: 
		objectCount [currentPlayer - 1] += 100;
		break;
	case 3:
		objectCount [currentPlayer - 1] += 10;
		break;
	case 4:
		objectCount [currentPlayer - 1] += 1;
		break;
	}
}

/*   This function displays the movement that happened after rolling for an object encounter or when
     nothing is found
     @param *objectRoll is a 10-sided die that determines the object encountered by a player on a tile
     @param *position is the player's position after an event
     	    *position gets updated to the changes after the object encounter
     @param *rowRoll is the 10-sided die roll that determines the row that the player is going to
     @param *columnRoll is the 10-sided die roll that determines the column that the player is going to
     @param row [] is an array containing appropriate row numbers
     @param column [] is an array containing appropriate column numbers
     @param startTile is the player's tile at the start of their turn
*/

void
displayObjectMovement	(int   *objectRoll,
			 int   *position, 
			 int	rowRoll, 
			 int	columnRoll, 
			 int	row[], 
			 int	column [], 
			 int    startTile)
{
	int dogTile, ladderTile, slideTile, uTurnTile, uRow, uColumn;
	
	uRow = getCurrentRow (row, 
			     &startTile);
	uColumn = getCurrentColumn (column, 
				   &startTile);

	switch (*objectRoll) {
	case 1:
		dogTile = getDoggoMovement (&rowRoll, 
					    &columnRoll, 
					    row, 
					    column);
		printf("\nYou found a Doggo!");
		if (dogTile == *position)
			printf (" The Doggo did not move at all. You are still on tile %d (row %d col %d).", dogTile, 
												      	     rowRoll, 
												     	     columnRoll);
		else if (dogTile > *position)
			printf (" You followed the dog to tile %d (row %d col %d). What a good dog!", dogTile, 
												      rowRoll, 
												      columnRoll);
		else
			printf (" You followed the dog to tile %d (row %d col %d). Oh no...", dogTile, 
											      rowRoll, 
											      columnRoll);
		*position = dogTile;
		break;
	case 2:
		ladderTile = getLadderMovement (&rowRoll, 
						&columnRoll, 
						 row, 
						 column, 
						*position);
		printf ("\nYou found a Ladder! You climbed the ladder to tile %d (row %d col %d).", ladderTile, 
												    rowRoll, 
												    columnRoll);
		*position = ladderTile;
		break;
	case 3:
		slideTile = getSlideMovement (&rowRoll, 
					      &columnRoll, 
					       row, 
					       column, 
					      *position);
		printf ("\nUh-oh. You found a Slide. You rode the slide to tile %d (row %d col %d).", slideTile, 
												      rowRoll, 
												      columnRoll);
		*position = slideTile;
		break;
	case 4:
		uTurnTile = getUTurnMovement (startTile);
		printf ("\nYou found a U-Turn! You went back to tile %d (row %d col %d).", uTurnTile, 
											   uRow, 
											   uColumn);
		*position = uTurnTile;
		break;
	default:
		printf("\nHmm...you found nothing on this tile.");
	}

}

/*   This function forms a 3 digit code that determines the farthest distance covered by an object
     and what object it is
     ex. 390 means a SLide moved you 90 tiles in distance.
     @param nFarthestObject [] is an array containing the code of each player for the farthest distance
     covered by an object
     	    nFarthestObject [] gets updated to the farthest object code of the current player
     @param positionPreObject is the position of the player before encountering an object
     @param *position is the player's position after an event
     @param *objectRoll is a 10-sided die that determines the object encountered by a player on a tile
     @param currentPlayer is the digit of the player that is currently playing
*/

void
getFarthestObject 	(int	nFarthestObject [],
			 int	positionPreObject, 
			 int    position, 
			 int   *objectRoll, 
			 int	currentPlayer)
{
	int newDistance, movement, code, codeDistance;
	
	movement = position - positionPreObject;
	newDistance = abs (movement);
	
	if (*objectRoll >= 1 && *objectRoll <= 4) {
		codeDistance = nFarthestObject [currentPlayer - 1] % 100;
		
		if (newDistance >= codeDistance) {
			code = *objectRoll * 100 + newDistance;
			nFarthestObject [currentPlayer - 1] = code;
		}		
	}
}

/*   This function encapsulates every function that is needed when a player encounters an object
     Precondition: the player's position is not on tile 0
     @param row [] is an array containing appropriate row numbers
     @param column [] is an array containing appropriate column numbers
     @param objectcount [] is an array that contains the object count code of each player
     @param nFarthestObject [] is an array containing the code of each player for the farthest distance
     covered by an object
     @param prevPosition [] is an array that stores the movement that happens in player's turn
     	    prevPosition [] gets updated based on the position of the current player after the movements
     	    caused an object
     @param *objectRoll is a 10-sided die that determines the object encountered by a player on a tile
     	    *objectRoll gets updated to the appropriate random number
     @param *position is the player's position after an event
     @param *rowRoll is the 10-sided die roll that determines the row that the player is going to
     @param *columnRoll is the 10-sided die roll that determines the column that the player is going to
     @param startTile is the player's tile at the start of their turn
     @param currentPlayer is the digit of the player that is currently playing
     @param positionPreObject is the position of the player before encountering an object
*/

void
doObjectRoll 		(int	row [], 
			 int	column [], 
			 int	objectCount [],
			 int	nFarthestObject [], 
			 int	prevPosition [], 
			 int   *objectRoll, 
			 int   *position, 
			 int	rowRoll, 
			 int	columnRoll, 
			 int	startTile, 
			 int	currentPlayer, 
			 int	positionPreObject)
{
	int cRow;
	
	cRow = getCurrentRow (row, 
			    *&position);
	
	if (cRow == 1) {
		do {
			*objectRoll = roll10SidedDie ();	
		} while (*objectRoll == 3);
	} else if (cRow == 10) {
		do {
			*objectRoll = roll10SidedDie ();	
		} while (*objectRoll == 2);
	} else
		*objectRoll = roll10SidedDie ();
		
	getObjectCount (*&objectRoll, 
			  objectCount, 
			  currentPlayer);					
	displayObjectMovement (*&objectRoll, 
			       *&position, 
			       	 rowRoll, 
				 columnRoll, 
				 row, 
				 column, 
				 startTile);
	getFarthestObject (nFarthestObject, 
			   positionPreObject, 
			  *position, 
			 *&objectRoll, 
			   currentPlayer);					
	prevPosition [currentPlayer - 1] = *position;
}

/*   This function encapsulates every function that is needed when a player encounters an object
     Precondition: the player's starting tile is on 90-99
     @param *firstRoll is the 10-sided die roll that gets added to the player's startTile
     @param startTile is the player's tile at the start of their turn
     @param *position is the player's position after an event
     	    *position gets updated to the changes after rolling for movement
     @param row [] is an array containing appropriate row numbers
     @param column [] is an array containing appropriate column numbers
*/

void
displayRow10Movement 	(int   *firstRoll,
			 int	startTile, 
			 int   *position,
			 int	row [],
			 int	column [])
{
	int excess, row10Tile, cRow, cCol;
	
	row10Tile = getRow10Movement (*&firstRoll,
				        startTile);
	
		
	if (row10Tile > 100) {
		excess = row10Tile - 100;
		row10Tile = 100 - excess;
		cRow = getCurrentRow (row, &row10Tile);
		cCol = getCurrentColumn (column, &row10Tile);
		printf ("\nYou rolled %d. Sadly, you went over the finish line by %d step/s.", *firstRoll, 
												excess);
		printf (" You were sent back to %d (row %d col %d).", row10Tile,
								      cRow,
								      cCol);
		*position = row10Tile;
	} else {
		cRow = getCurrentRow (row, &row10Tile);
		cCol = getCurrentColumn (column, &row10Tile);
		printf ("\nYou rolled %d. You advanced to tile %d (row %d col %d).", *firstRoll, 
										      row10Tile,
										      cRow,
										      cCol);
		*position = row10Tile;
	}
}

/*   This function asks for valid input on whether the board should be displayed or not
     Precondition: the next player is the first player to take a turn
     @param ifDisplayBoard is the input of the player regarding whether to display the
     board or not
     @param boardSpace [] is an array containing numbers 1-100
     @param prevPosition [] is an array that stores the movement that happens in player's turn
*/

void
checkIfDisplayBoard 	(char 	ifDisplayBoard,
			 int	boardSpace [], 
			 int	prevPosition [])
{
	int escapeLoop = 0;
	do {
		printf ("\n\nA round has ended. Do you want to display the board? [Y/N]: ");
		scanf (" %c", &ifDisplayBoard);
		
		switch (ifDisplayBoard)	{
		case 'Y':
		case 'y': 
			displayBoard (boardSpace, 
				      prevPosition);
		 	escapeLoop = 1;
			break;
		case 'N': 
		case 'n':
			escapeLoop = 1;
			break;
		default :
			printf ("\nInvalid input.");	
		}	
	} while (escapeLoop != 1);
}

/*   This function displays the board and the current positions of every player
     Precondition: the board was prompted to be displayed
     @param boardSpace [] is an array containing numbers 1-100
     @param prevPosition [] is an array that stores the movement that happens in player's turn
*/

void
displayBoard 		(int	boardSpace [],
			 int	prevPosition [])
{
	int i = 0, j = 0, k = 0;
	int ifOccupied = 0, evenRowCounter = 99, oddRowCounter = 80;
	int evenLimit = 89, oddLimit = 90;
	char str [5] [10] = {"P1", "P2", "P3", "P4", "P5"};
	char display [10] = "";
	char erase [10] = "";

	fillBoard (boardSpace);
	
	printf("\n\n");
	while (i < 5) {
		while (evenRowCounter != evenLimit) {
			ifOccupied = 0;
			while (j < 5) {     // this loop checks all players' prevPosition to see if they are equal to the current boardSpace
				if(boardSpace [evenRowCounter] == prevPosition [j]) {
					strcat (display, str [j]);  // strcat connects display and str[j]. The newly formed string is now display.
					ifOccupied = 1;
				}
				j++;
			}
			
			if (ifOccupied == 1) {
				printf ("%11s", display);
				strcpy (display, erase); // cleans the display array	
			} else if (evenRowCounter != evenLimit)
				printf ("%11d", boardSpace [evenRowCounter]);

			evenRowCounter--;
			j = 0;
		}
		
		printf("\n\n");
	
		while (oddRowCounter != oddLimit) {
			ifOccupied = 0;
			while (k <= 4) {
				if (boardSpace [oddRowCounter] == prevPosition [k]) {
					strcat (display, str [k]);
					ifOccupied = 1;
				}
				k++;
			}
			
			if (ifOccupied == 1) {
				printf("%11s", display);
				strcpy (display, erase);
			} else if (oddRowCounter != oddLimit)
				printf("%11d", boardSpace [oddRowCounter]);

			oddRowCounter++;
			k = 0;
		}
		
		printf("\n\n");
		
		evenRowCounter -= 10;
		oddRowCounter -= 30;
		
		evenLimit -= 20;
		oddLimit -= 20;
		i++;	
	}
}

/*   This function asks for valid input on whether the board should be displayed or not
     Precondition: the next player is the first player to take a turn
     @param ifDisplayRank is the input of the player regarding whether to display the
     ranking or not
     @param prevPosition [] is an array that stores the movement that happens in player's turn
     @param playerCount is the number of players playing the game
*/

void
checkIfDisplayRank 	(char	ifDisplayRank,
			 int	prevPosition [], 
			 int	playerCount)
{
	int escapeLoop = 0;
	do {
		printf ("\n\nDo you want to display the current rankings? [Y/N]: ");
		scanf (" %c", &ifDisplayRank);
			
		switch (ifDisplayRank) {
		case 'Y':
		case 'y':
			displayRanking (prevPosition, 
					playerCount);
			escapeLoop = 1;
			break;
		case 'N': 
		case 'n': 
			escapeLoop = 1;
			break;
		default :
			printf ("\nInvalid input.");
		}
	} while (escapeLoop != 1);
}

/*   This function displays the ranking of every player
     @param prevPosition [] is an array that stores the movement that happens in player's turn
     @param playerCount is the number of players playing the game
*/

void
displayRanking 		(int	prevPosition [], 
			 int	playerCount)
{
	int i, j, k, l, m = 0, n = 0, o = 0, p, swap;
	int temp [5];
	int positionArranged [5];
	int nPlayer [5];
	int rank [5];
	int place = 1;
	
	for (i = 0; i < playerCount; i++) {
		temp [i] = prevPosition [i]; 			// a copy of prevPositions
		positionArranged [i] = prevPosition [i]; 	// a copy of PrevPositions that is going to be arranged
	}
	
	for (j = 0; j < playerCount-1; j++) { 			// bubble sorting positionArranged from largest to smallest
		for (k = 0; k < playerCount-1; k++) {
			if (positionArranged [k] < positionArranged [k+1]) {
				swap = positionArranged [k];
		                positionArranged [k] = positionArranged [k+1];
		                positionArranged [k+1] = swap;
			}
		}
	}
	
	for (l = 0; l < playerCount; l++) {				// determines the rank of players and checking for similar positions
		if (positionArranged [m] == positionArranged [m+1]){
			rank [m] = place;
			rank [m+1] = place;
		} else {
			rank [m] = place;
			place++;
		}
		m++;
	}
	
	while (n <= playerCount) {				// determines the player number of rank 1, rank 2, etc.
		if (positionArranged [n] == temp [o]) {		// comparing the arranged array to original order
			nPlayer [n] = o+1;
			if (positionArranged [n] == positionArranged [n+1])	// continue to search temp for similar position		
				o++;
			else
				o = 0;	
			n++;
		}
		else
			o++;
	}
	
	printf ("\n  Ranking     Player");
	for(p = 0; p < playerCount; p++)
		printf ("\n     %d%11s%d", rank [p], "P", nPlayer [p]);
}

/*   This function checks if the current player has reached tile 100
     @param *position is the player's position after an event
     @param objectCount [] is an array that contains the object count code of each player
     @param objectRoll is a 10-sided die that determines the object encountered by a player on a tile
     @param currentPlayer is the digit of the player that is currently playing
     @param nFarthestObject [] is an array containing the code of each player for the farthest distance
     covered by an object
     @param prevPosition [] is an array that stores the movement that happens in player's turn
     @param firstRoll is the 10-sided die roll that gets added to the player's startTile
*/

void
checkIfWin 		(int   *position,
			 int	objectCount [], 
			 int	objectRoll, 
			 int	currentPlayer, 
			 int	nFarthestObject [],
			 int	prevPosition [],
			 int	firstRoll)
{
	if (*position == 100)
		displayWin (objectCount,
			    objectRoll, 
			    currentPlayer, 
			    nFarthestObject, 
			    prevPosition, 
			    firstRoll);
}

/*   This function displays all the winning message, how many objects the winning player has encountered,
     the object that brought the winning player to the farthest tile, and the winning move.
     Precondition: *position is 100
     @param objectCount [] is an array that contains the object count code of each player
     @param objectRoll is a 10-sided die that determines the object encountered by a player on a tile
     @param currentPlayer is the digit of the player that is currently playing
     @param nFarthestObject [] is an array containing the code of each player for the farthest distance
     covered by an object
     @param prevPosition [] is an array that stores the movement that happens in player's turn
     @param firstRoll is the 10-sided die roll that gets added to the player's startTile
*/

void
displayWin 		(int	objectCount [],
			 int	objectRoll, 
			 int	currentPlayer, 
			 int	nFarthestObject [],
			 int	prevPosition [],
			 int	firstRoll)
{
	int nDoggo, 
	    nLadder, 
	    nSlide, 
	    nUTurn, 
	    nObject, 
	    diceRollWin = 0;
	/* slicing the objectCount [] code */
	nDoggo = objectCount [currentPlayer - 1] / 1000;
	nLadder = objectCount [currentPlayer - 1] / 100 % 10;
	nSlide = objectCount [currentPlayer - 1] / 10 % 10;
	nUTurn = objectCount [currentPlayer - 1] % 10;
	/* getting the object segment of the nFarthestObject [] code */
	nObject = nFarthestObject [currentPlayer - 1] / 100;
	
	printf ("\n----------------------------------------");
	printf ("\n\nCongratulations, Player %d! You won the game!", currentPlayer);
	
	printf ("\nYou have encountered %d Doggo", nDoggo);
	if (nDoggo != 1)
		printf ("s");
	
	printf ("\nYou have climbed %d Ladder", nLadder);
	if (nLadder != 1)
		printf ("s");
		
	printf ("\nYou have ridden %d Slide", nSlide);
	if (nSlide != 1)
		printf ("s");
		
	printf ("\nYou have taken %d UTurn", nUTurn);
	if (nUTurn != 1)
		printf ("s");
	
	switch (nObject) {
	case 1: 
		printf ("\nA Doggo took you to the farthest tile!");
		break;
	case 2: 
		printf ("\nA Ladder took you to the farthest tile!");
		break;
	case 3: 
		printf ("\nA Slide took you to the farthest tile!");
		break;
	case 4: 
		printf ("\nA U-Turn took you to the farthest tile!");
		break;
	default:
		printf ("\nYou did not find objects this game. Your luck carried you to victory!");
	}
	
	switch (objectRoll) {
	case 1: 
		printf ("\nThe winning move was when you followed a Doggo.");
		break;
	case 2: 
		printf ("\nThe winning move was when you climbed a Ladder.");
		break;
	default: 
		diceRollWin = 1;
	}
	
	if (diceRollWin == 1 && prevPosition [currentPlayer - 1] >= 90)
		printf ("\nThe winning move was when you rolled a %d to tile 100.", firstRoll);
	if (diceRollWin == 1 && prevPosition [currentPlayer - 1] == 61)
		printf ("\nThe winning move was when you rolled a double-3");
	else if (diceRollWin == 1 && prevPosition [currentPlayer - 1] < 90)
		printf ("\nThe winning move was when you rolled 10 and 1.");
	
	printf ("\nWell done!\n");
}

/*   This function asks for valid input on whether the players want to play again
     Precondition: a player has won / reached tile 100
     @param ifPlayAgain is the input of the player regarding whether to play again
     or not
     @param *replay is an integer that determines where to replay the game or not
     	    *replay's value is updated depending on the user's input
     @param prevPosition [] is an array that stores the movement that happens in player's turn
     @param objectCount [] is an array that contains the object count code of each player
     @param nFarthestObject [] is an array containing the code of each player for the farthest distance
     covered by an object
     @param *position is the player's position after an event
*/

void
checkIfPlayAgain 	(char	ifPlayAgain,
			 int   *replay, 
			 int	prevPosition [], 
			 int	objectCount [], 
			 int	nFarthestObject [], 
			 int   *position)
{
	int escapeLoop = 0;
	
	printf ("\nWould you like to play again? [Y/N]: ");
	scanf (" %c", &ifPlayAgain);
	
	do {
		switch (ifPlayAgain) {
		case 'Y':
		case 'y': 
			printf ("\n\n");
			*replay = 1;
			resetValues (prevPosition, 
				     objectCount, 
				     nFarthestObject, 
				   *&position);
			escapeLoop = 1;
			break;
		case 'N':
		case 'n':
			printf ("\nThank you for playing Doggos, Ladders, Slides and U-Turns!\nTill next time!");
			*replay = 0;
	  		escapeLoop = 1;
	  		break;
		default:
			printf ("\nInvalid input.");
		}	
	} while (escapeLoop != 1);
}

/*   This function resets the value of arrays to 0
     Precondition: the players want to play again
     @param prevPosition [] is an array that stores the movement that happens in player's turn
     	    prevPosition [] values will turn into 0
     @param objectCount [] is an array that contains the object count code of each player
     	    objectCount [] values will turn into 0
     @param nFarthestObject [] is an array containing the code of each player for the farthest distance
     covered by an object
     	    nFarthestObject [] values will turn into 0
     @param *position is the player's position after an event
*/

void
resetValues 		(int	prevPosition [],
			 int	objectCount [], 
			 int	nFarthestObject [], 
			 int   *position)
{
	memset (prevPosition, 0, 5*sizeof (int)); 			// memset sets all values of the array to 0
	memset (objectCount, 0, 5*sizeof (int));
	memset (nFarthestObject, 0, 5*sizeof (int));
	
	*position = 0;
}
