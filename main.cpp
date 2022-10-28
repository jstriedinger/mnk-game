#include <iostream>
#include <cmath>
#include <string>
#include <stack>
#include <stdio.h>

using namespace std;

struct Movement
{	
	string mark;
	string pos;
	int coordX;
	int coordY;
};

class mnkGame
{
private:
	int stones;
	int columns;
	int rows;
	int winCondition;
	string** board;
	bool p1Turn;
	bool gameOver;
	bool draw;
	stack<Movement> moves;

	
public:
	mnkGame(int n, int m, int k)
	{
		p1Turn = true;
		winCondition = k;
		rows = n;
		columns = m;

		board = new string*[rows];
		for (int i = 0; i < rows; i++)
			board[i] = new string[columns];

		//quickly populate the board with placeholders 
		int tempNum = 0;
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				board[i][j] = to_string(tempNum);
				tempNum += 1;
			}
		}
		
	}

	/**
	 * Backtrack move by jus savnng the moves on a stack and removing them, putting the number back on the board
	 * 
	 */
	void backtrackMove() 
	{
		if(!moves.empty())
		{
			Movement* lastMove = &moves.top();
			board[lastMove->coordX][lastMove->coordY] = lastMove->pos;
			moves.pop();
			cout << "--- Movement backtracked ---" << endl;

			p1Turn = !p1Turn;
		}
	}

	/**
	 * Checks for vertical win. Meaning k consecutives cells with X or O depending on current player
	 * To be optimal and in cases where m and n iw way bigger than k, I decided to just get the surronding area.
	 * E.G
	 * If m = n = 10 and k = 3. And the player puts X on say [5,5] I do not need to start searching starting from [5,0]
	 * but from [5,3]
	 *
	 * @param row
	 * @param col
	 * @param check
	 */
	bool checkBoardHorizontal(int *row, int *col, string *check, string** pBoard) {
		// horizontal
		int initialCol = *col - winCondition + 1 < 0 ? 0 : *col - winCondition + 1;
		int finalCol = *col + winCondition - 1 >= columns ? (columns - 1 ) : *col + winCondition - 1;

		bool foundMatch = true;
		for (int j = initialCol; j <= finalCol; j++)
		{
			if (j + winCondition - 1 >= columns)
				break;

			foundMatch = true;
			for (int k = j; k < j + winCondition -1; k++)
			{
				if (pBoard[*row][k] == *check)
				{
					if (pBoard[*row][k] != pBoard[*row][k + 1])
					{
						foundMatch = false;
						break;
					}
				}
				else
					foundMatch = false;
			}
			if( foundMatch)
				return foundMatch;
			
		}
		return foundMatch;
	}

	/**
	 * Checks for vertical win. Meaning k consecutives cells with X or O depending on current player
	 * To be optimal and in cases where m and n iw way bigger than k, I decided to just get the surronding area.
	 * E.G
	 * If m = n = 10 and k = 3. And the player puts X on say [5,5] I do not need to start searching starting from [0,5]
	 * but from [3,5]
	 * 
	 * @param row 
	 * @param col 
	 * @param check 
	 */
	bool checkBoardVertical(int *row, int *col, string *check, string** pBoard) {
	
		int initialRow = *row - winCondition + 1 < 0 ? 0 : *row - winCondition + 1;
		int finalRow = *row + winCondition - 1 >= rows ? (rows - 1) : *row + winCondition - 1;

		bool foundMatch = true;
		for (int i = initialRow; i <= finalRow; i++)
		{
			if (i + winCondition - 1 >= rows)
				break;

			foundMatch = true;
			for (int k = i; k < i + winCondition - 1; k++)
			{
				if (pBoard[k][*col] == *check)
				{
					if (pBoard[k][*col] != pBoard[k+1][*col])
					{
						foundMatch = false;
						break;
					}
				}
				else
					foundMatch = false;
			}
			if (foundMatch)
				return foundMatch;
		}
		return foundMatch;
	}
	/**
	 * Check for diagonal wins using an extra parameter to different directions
	 *
	 * @param row
	 * @param col
	 * @param check
	 * @return true
	 * @return false
	 */
	bool checkBoardDiagonalRight(int *row, int *col, string *check, string** pBoard)
	{
		int initRow, initCol, finalRow, finalCol;
		if(*row + *col >= rows ) {
			//We are in this corner:
			// ? ? ? ?
			// ? ? x x
			// ? x x x
			initRow = *row + winCondition - 1 >= rows ? (rows - 1) : *row + winCondition - 1;
			initCol = *col - (initRow - *row);

			finalCol = *col + winCondition - 1 >= columns ? (columns - 1) : *col + winCondition - 1;
			finalRow = *row - (finalCol - *col);
		} 
		else {
			// We are in this corner:
			//  x x x ?
			//  x x ? ?
			//  x ? ? ?
			initCol = *col - winCondition + 1 < 0 ? 0 : *col - winCondition + 1;
			initRow = *row + (*col -  initCol);

			finalRow = *row - winCondition + 1 < 0 ? 0 : *row - winCondition + 1;
			finalCol = *col + (*row - finalRow);
		}

		//cout << "cdr Checking diagonal from  [" << initRow << "],[" << initCol << "] to [" << finalRow << "],[" << finalCol << "]" << endl;

		bool foundMatch = false;
		for (int i = initRow, j = initCol; i >= finalRow; i--, j++)
		{
			if (i - winCondition + 1 < 0)
				break;

			foundMatch = true;
			for (int k = i, l = j; k > i - winCondition + 1; k--, l++)
			{
				if (pBoard[k][l] == *check)
				{

					if (pBoard[k][l] != pBoard[k - 1][l + 1])
					{
						foundMatch = false;
						break;
					}
				}
				else
					foundMatch = false;
			}
			if (foundMatch)
				return foundMatch;
		}
		return foundMatch;
	}

	/**
	 * Check for diagonal wins using an extra parameter to different directions
	 *
	 * @param row
	 * @param col
	 * @param check
	 * @return true
	 * @return false
	 */
	bool checkBoardDiagonalLeft(int *row, int *col, string *check, string** pBoard)
	{
		int initRow, initCol, finalRow, finalCol;
		if(*row >= *col) {
			// We are in this corner:
			//  x ? ? ?
			//  x x ? ?
			//  x x x ?
			initCol = *col - winCondition + 1 < 0 ? 0 : *col - winCondition + 1;
			initRow = *row - (*col - initCol);

			finalRow = *row + winCondition - 1 >= rows ? (rows - 1) : *row + winCondition - 1;
			finalCol = *col + (finalRow - *row);
		} else
		{
			// We are in this corner:
			//  ? x x x
			//  ? ? x x
			//  ? ? ? x
			initRow = *row - winCondition + 1 < 0 ? 0 : *row - winCondition + 1;
			initCol = *col - (*row - initRow);

			finalCol = *col + winCondition - 1 >= columns ? (columns - 1) : *col + winCondition - 1;
			finalRow = *row + (finalCol - *col);
		}

		bool foundMatch = false;
		for (int i = initRow, j = initCol; i <= finalRow; i++, j++)
		{
			if ((i + winCondition - 1 >= rows) || (j + winCondition - 1 >= columns)  )
				break;

			foundMatch = true;
			for (int k = i, l = j; k < i + winCondition - 1; k++, l++)
			{
				if (pBoard[k][l] == *check)
				{

					if (pBoard[k][l] != pBoard[k + 1][l + 1])
					{
						foundMatch = false;
						break;
					}
				}
				else
					foundMatch = false;
			}
			if (foundMatch)
				return foundMatch;
		}
		return foundMatch;
	}

	/**
	 * Check if there is a winner 
	 * @param row 
	 * @param col 
	 */
	void checkForWinner(int* row, int* col) {

		string check = p1Turn ? "X" : "O";
		gameOver = checkBoardHorizontal(row, col, &check, board) || checkBoardVertical(row, col, &check, board) || checkBoardDiagonalRight(row, col, &check, board) || checkBoardDiagonalLeft(row, col, &check, board);
	}

	/**
	 * @brief Detect if there is a draw
	 * By working on a copy board, it will try to fill that copy board until it finds a possible winning outcome
	 * Do this for both players. If the answer is no, then is a draw
	 * 
	 */
	bool detectDraw()
	{
		//lets make a copy of the board
		string** copyB1 = new string*[rows];
		string** copyB2 = new string*[rows];
		for (int i = 0; i < rows; i++) {
			copyB1[i] = new string[columns];
			copyB2[i] = new string[columns];

		}

		//populate the copyboard
		bool canWin = false;
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				copyB1[i][j] = board[i][j];
				copyB2[i][j] = board[i][j];
			}
		}

		//lets test p1 win
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				string check = "X";
				if(copyB1[i][j] != "O")
					copyB1[i][j] = "X";
				if(copyB1[i][j] == "X")
				{
					canWin = checkBoardHorizontal(&i, &j, &check, copyB1) || checkBoardVertical(&i, &j, &check, copyB1) || checkBoardDiagonalRight(&i, &j, &check, copyB1) || checkBoardDiagonalLeft(&i, &j, &check, copyB1);
					if( canWin)
						return true;
				}

				if (copyB2[i][j] != "X")
					copyB2[i][j] = "O";
				if (copyB2[i][j] == "O")
				{
					string check = "O";
					canWin = checkBoardHorizontal(&i, &j, &check, copyB2) || checkBoardVertical(&i, &j, &check, copyB2) || checkBoardDiagonalRight(&i, &j, &check, copyB2) || checkBoardDiagonalLeft(&i, &j, &check, copyB2);
					if (canWin)
						return true;
				}
			}
		}
		return false;
		
	}
	
	/**
	 * Captures the players move
	 */
	void playerMove() {
		
		string move;
		int numMove, rowMove, colMove;
		while (true)
		{
			cin.clear();
			int c, i = 0;
			cout << "Player " << (p1Turn ? "1" : "2") << " -  Where would you like to play? (write 'undo' to backtrack)";
			cin >> move;
			if (move != "") {
				try
				{
					//tries to convert it to a number
					numMove = stoi(move);
					rowMove = numMove / columns;
					colMove = numMove % columns;
					if (board[rowMove][colMove] != "X" && board[rowMove][colMove] != "O")
					{
						// lets take that value
						board[rowMove][colMove] = p1Turn ? 'X' : 'O';
						checkForWinner(&rowMove, &colMove);

						if (!gameOver) {
							if(!detectDraw())
							{
								draw = true;
								gameOver = true;
								break;	
							}
							//if game is not over, save the move on a stack and go to the other player
							Movement newMove;
							newMove.coordX = rowMove;
							newMove.coordY = colMove;
							newMove.pos = move;
							moves.push(newMove);
							p1Turn = !p1Turn;

						}
						break;
					}
					else
					{
						cout << "Space occupied. Please select another one" << endl;	
					}
				}
				catch (exception &err)
				{
					// is not a number, therefore it should be 'undo' or is invalid
					if (move == "undo")
					{
						if (moves.empty()) 
						{
							cout << "No moves to backtrack" << endl;
						}
						else
						{
							backtrackMove(); break;
						}
					}
					else
						cout << "Please select a valid opton" << endl;
				}
			}
			else
				cout << "Please select an option" << endl;
		}
		
	}

	/**
	 * Prints the board on the console
	 * 
	 */
	void printBoard() {
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				
				if(j < columns - 1 )
				{
					cout << " " << board[i][j];
					if(board[i][j].length() < 2 )
						cout << " ";
					cout << "|";

				}
				else
				{
					cout << " " << board[i][j] << endl;
				}
			}
			cout << string((columns * 4) - 1, '-') << endl;			
		}
		
	}

	void playGame() {

		p1Turn = true;
		gameOver = false;
		draw = false;
		printBoard();
		while (!gameOver)
		{
			playerMove();
			printBoard();
		}
		if(draw)
			cout << "Its a draw! *dramatic music*" << endl;
		else
			cout << "winner winner chicken dinner! Player " << (p1Turn ? "1" : "2") << " wins!";
	}
};


int main() {
	int m;
	int n;
	int k;
	bool winner = false;

	cout << "Please select number of rows (n):";
	cin >> n;

	cout << "Please select number of columns (m):";
	cin >> m;

	cout << "Please select number of repetitions to win (k):";
	cin >> k;

	cout << "Lets play a m-n-k game! Player 1 is X, player 2 is O" << endl;
	mnkGame game(n,m,k);
	game.playGame();

	return 0;
} 