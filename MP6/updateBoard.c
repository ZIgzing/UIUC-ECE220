/*----------------------------------------------------------------------------------------------------------------------------
The Game of Life

Written by Marc Harvey
UIUC ECE 220 MP6
030818

The game of life consists of a board of any dimensions, with any amount of alive and dead cells is any positions.
During each iteration of the game, it applies a set of rules to update the board, killing off or "birthing" new
cells at anay positions. The rules are: if a cell is dead and has 3 neighbors, the cell becomes alive. If the 
cell is alive and has less than 2 or more than 3 neighbors then the cell dies.  

This file holds the functions used in the actual game (written by Lumetta), which is located in main.c. The
functions are countLiveNeighbor, updateBoard, and aliveStable.

The countLiveNeighbor function is the bread and butter of this game. It returns how many live cells surround 
a user given cell. The way I made it makes it use a nested for loop method to check all 8 neighbors around the 
cell, and add up the values of each neighbor ( due to 1 = alive and 0 = dead ). It uses an if statement to make
sure that the neighbor in question exists ( in that it isn't off the edge of the board ).

The updateBoard function is fairly simple in that it basically iterated through the entirety of the board, and 
appleis the countLiveNeighbor function to every cell. It then forms a new board with that information and the 
given rules of live and death of cells to uodate tehe board according to those rules.

The aliveStable function uses the same conditionals and loops as the updateBoard function, but instead of 
updating the according to the conditionals, it instead returns 0 if the board would be changed by the rules of 
updatBoard. It returns 1 if the board is "stable" in that it won't ever change.

----------------------------------------------------------------------------------------------------------------------------*/


/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */


int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){

    int liveNeighbors = 0;
    int curValue;
    int curIndex;

    int i, j;

    for (i = row - 1; i <= row + 1; i++) {  // This loop iterates through every row
        
        for (j = col - 1; j <= col + 1; j++) {  // This loop iterates through every column of the specified row

            if ( ( (i >= 0 && i < boardRowSize) && (j >= 0 && j < boardColSize) ) &&  // Checks if cell exists (not past edge)
                  !(i == row && j == col) ) {                                         // Checks if cell is not the center cell
                
                curIndex = boardColSize * i + j;
                curValue = board[ curIndex ];
                liveNeighbors += curValue;
            }
        }
    }

    return liveNeighbors;
}

//----------------------------------------------------------------------------------------------------------------------------


/*
 * Update the game board to the next step.
 * Input: 
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */


void updateBoard(int* board, int boardRowSize, int boardColSize) {

    int curIndex;
    int curValue;
    int curNeighbors;
    int newBoard[ boardRowSize * boardColSize ];

    int i, j;

    for (i = 0; i < boardRowSize; i++) {  // This loop iterates through every row
    
        for (j = 0; j < boardColSize; j++) {  // This loop iterates through every column of the specified row
        
            curIndex = boardColSize * i + j;
            curValue = board[ curIndex ];
            curNeighbors = countLiveNeighbor(board, boardRowSize, boardColSize, i, j);

            newBoard[ curIndex ] = curValue;

            if ( curValue == 0 && curNeighbors == 3) {  // Checks if cell should come to life
            
                newBoard[ curIndex ] = 1;  // cell becomes alive

            }

            if ( curValue == 1 && ( (curNeighbors < 2 ) || (curNeighbors > 3) ) ) {  // Checks if cell should die
    
                newBoard[ curIndex ] = 0;  //cell dies

            }

        }
    }

    for (i = 0; i < boardRowSize; i++) {  // This loop iterates through every row
        for (j = 0; j < boardColSize; j++) {  // This loop iterates through every column of the specified row

            curIndex = boardColSize * i + j;
            board[ curIndex ] = newBoard[ curIndex ];
        }
    }

}

//----------------------------------------------------------------------------------------------------------------------------


/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with 
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */ 
int aliveStable(int* board, int boardRowSize, int boardColSize){

    int curIndex;
    int curValue;
    int curNeighbors;

    int i, j;

    for (i = 0; i < boardRowSize; i++) {  // This loop iterates through every row

        for (j = 0; j < boardColSize; j++) {  // This loop iterates through every column of the specified row

            curIndex = boardColSize * i + j;
            curValue = board[ curIndex ];
            curNeighbors = countLiveNeighbor(board, boardRowSize, boardColSize, i, j);

            if ( curValue == 0 && curNeighbors == 3) {  // Checks if cell will come to life

                return 0;

            }

            if ( curValue == 1 && ( (curNeighbors < 2 ) || (curNeighbors > 3) ) ) {  // Checks if cell will die

                return 0;

            }
        }
    }

    return 1;
}

//----------------------------------------------------------------------------------------------------------------------------

				
				
			

