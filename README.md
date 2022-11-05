# m,n,k-game in C++
A console implementation of a m,n,k-game in C++ between two players. With an added restriction of using (mostly) only standar headers and classes.

###Description
- m = number of columns
- n = number of rows
- k = number of consecutives to win
The first player to have align (vertically, horizontally or diagonally) *K* consecutive symbols in a *m*x*n* board wins!

e.g board of 4x5 with k = 3
___|___|_o_|_o_|___
___|_x_|_x_|_o_|___
___|___|_o_|_x_|_x_
___|___|___|___|_x_

Player 1 (x) wins!

##Undo movements
Any player can undo a movement by typing *undo* in the console. That way the player can return all the way back to the beginning of the game


