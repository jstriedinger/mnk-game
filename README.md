# m,n,k-game in C++
A console implementation of a m,n,k-game in C++ between two players. With an added restriction of using only standar headers and classes. Just run the .cpp 

## Description
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

## Undo movements
Any player can undo a movement by typing *undo* in the console. That way the player can return all the way back to the beginning of the game
A vector witht he movemet information is used to be able to bactrack the game to the previous state.

## Detect possible *k* matches ONLY on the proximity
Let's assume we have a 100x100 board with k = 20. A player puts his X on the board [20][50] and we want to check if there is horizontal match. We do not need to start checking on [20][0], we should start checking on [20][50 - 19] =  [20][31]. Because that is the "farthest" possible starting point for an horizontal match. 

**A simple equation would be**. If player chooses [X][Y], on a n x m board with k stones. Then we should start looking for horizontal matches in 
[X][Y - k - 1] with a min value of 0 (first column) of course. Similar logics is used to check vertical and diagonal matches.


