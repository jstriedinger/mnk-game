# m,n,k-game in C++
A console implementation of a m,n,k-game in C++ between two players. With an added restriction of using (mostly) only standar headers and classes.

###Description
- m = number of columns
- n = number of rows
- k = number of consecutives to win
The first player to have align (vertically, horizontally or diagonally) *K* consecutive symbols in a *n*x*m* board wins!

e.g board of 4x5 with k = 3  

 --| - | o | o | -  
 --| x | x | o | -  
 --| - | o | x | x    
 --| - | - | - | x

Player 1 (x) wins!

##Undo movements
Any player can undo a movement by typing *undo* in the console. That way the player can return all the way back to the beginning of the game


