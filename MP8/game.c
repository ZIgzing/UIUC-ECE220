/*----------------------------------------------------------------------------------------------------------------------------
2048

Written by Marc Harvey
UIUC ECE 220 MP8
032718

The functions in this file are used in main.c to play the popular game 2048. The ones I wrote are make_game, remake_game,
get_cell, move_w, move_s, move_a, move_d, and legal_move_check

The make game function takes the number of rows and columns and then creates a new game struct, with rows, cols, score, and 
a cells array initialized.

The remake game function takes a game struct and a new amount of rows and columns, and overwrites the old game to hold a new
game with the specified amount of rows and columns.

The get_cell function takes a row and column and returns a pointer to the given cell that is being referred to.

The move function are the meat of this assignment, and move the cells in the specified direction, combining them when they
move into a cell with the same value. All the move functions work the same way, which uses a triple nested for loop 
technique to move cells and then compare them to the cells above, below, or to the side of them, depending on which button
is pressed.

The legal_move_check determines if there are any moves left. It does that by checking if there are any empty cells, and then
checking if there are any neighbor cells with the same value, and returns 1 if either is true. 

----------------------------------------------------------------------------------------------------------------------------*/

#include "game.h"


game * make_game(int rows, int cols)
/*! Create an instance of a game structure with the given number of rows
    and columns, initializing elements to -1 and return a pointer
    to it. (See game.h for the specification for the game data structure) 
    The needed memory should be dynamically allocated with the malloc family
    of functions.
*/
{
    //Dynamically allocate memory for game and cells (DO NOT modify this)
    game * mygame = malloc(sizeof(game));
    mygame->cells = malloc(rows*cols*sizeof(cell));

    // Initializing cells array of struct to have every cell equal to -1
    int index;
    for (index = 0; index < rows * cols; index++) {
        mygame->cells[index] = -1;
    }
    
    // Initializing other elements of struct
    mygame->score = 0;
    mygame->rows = rows;
    mygame->cols = cols;

    return mygame;
}


void remake_game(game ** _cur_game_ptr,int new_rows,int new_cols)
/*! Given a game structure that is passed by reference, change the
	game structure to have the given number of rows and columns. Initialize
	the score and all elements in the cells to -1. Make sure that any 
	memory previously allocated is not lost in this function.	
*/
{
	/*Frees dynamically allocated memory used by cells in previous game,
	 then dynamically allocates memory for cells in new game.  DO NOT MODIFY.*/
	free((*_cur_game_ptr)->cells);
	(*_cur_game_ptr)->cells = malloc(new_rows*new_cols*sizeof(cell));

        // Initializing all elements of struct except for cells array
        (*_cur_game_ptr)->score = 0;
        (*_cur_game_ptr)->rows = new_rows;
        (*_cur_game_ptr)->cols = new_cols;

        // Initializing all cells in cells array to -1
        int index;
        for (index = 0; index < new_rows * new_cols; index++) {
            (*_cur_game_ptr)->cells[index] = -1;
        }

	return;	
}


void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains. Do not modify this function.*/
{
    free(cur_game->cells);
    free(cur_game);
    cur_game = NULL;
    return;
}


cell * get_cell(game * cur_game, int row, int col)
/*! Given a game, a row, and a column, return a pointer to the corresponding
    cell on the game. (See game.h for game data structure specification)
    This function should be handy for accessing game cells. Return NULL
	if the row and col coordinates do not exist.
*/
{
    //YOUR CODE STARTS HERE

    int max = cur_game->cols * cur_game->rows;  // Index of last element of cells array in game struct
    int displace = cur_game->cols * row + col;  // Index of specified cell in cells array
    if ( displace < max ) {  // If specified cell index is less than maximum index, return pointer to cell
        return cur_game->cells + displace;
    } 

    return NULL;  // Otherwise, return null
}


int move_w(game * cur_game){
/*!Slides all of the tiles in cur_game upwards. If a tile matches with the 
   one above it, the tiles are merged by adding their values together. When
   tiles merge, increase the score by the value of the new tile. A tile can 
   not merge twice in one turn. If sliding the tiles up does not cause any 
   cell to change value, w is an invalid move and return 0. Otherwise, return 1. 
*/

    // Misc variables used
    cell cur_cell_value1;
    cell cur_cell_value2;
    int last_combined_row;
    int target_row;
    int flag = 0;

    // Variables used in loops
    int i;
    int j;
    int k;

    for (j = 0; j < cur_game->cols; j++) {  // Iterate through every column of array
        last_combined_row = -2;
        for (i = 1; i < cur_game->rows; i++) {  // Iterate through every row of array except first one
            cur_cell_value1 = cur_game->cells[ (i * cur_game->cols) + j ];
            if ( !(cur_cell_value1 == -1) ) {  // If current cell is not empty, then...
                
                target_row = i;  // Reset target row
                for (k = 0; k < i; k++) {  // Iterate through every row between start of column and i
                    cur_cell_value2 = cur_game->cells[ (k * cur_game->cols) + j ]; 
                    if (cur_cell_value2 == -1) {  // If cell at row k is empty, then set target row to k
                        target_row = k;
                        break;
                    }
                }
                if ( target_row != i) {  // If their are any empty cells above current cell, move current cell to empty spot
                    cur_game->cells[ (target_row * cur_game->cols) + j] = cur_cell_value1;
                    cur_game->cells[ (i * cur_game->cols) + j] = -1;
                    flag = 1;  // Signal a change in game
                }
                // If row above target row hasn't been combined already, and if they are both equal to each other, then combine them
                if ( ( target_row - 1 != last_combined_row ) && 
                     ( cur_game->cells[ (target_row - 1) * cur_game->cols + j ] == cur_game->cells[ target_row * cur_game->cols + j ] ) ) {
                    cur_game->cells[ (target_row - 1) * cur_game->cols + j ] *= 2;
                    cur_game->cells[ target_row * cur_game->cols + j] = -1;
                    last_combined_row = target_row - 1;
                    flag = 1;  // Signal a change in game
                    cur_game->score += cur_game->cells[ (target_row - 1) * cur_game->cols + j ];
                }
            }
        }
    }

    return flag;
};

int move_s(game * cur_game){ //slide down

    // Misc variables used
    cell cur_cell_value1;
    cell cur_cell_value2;
    int last_combined_row;
    int target_row;
    int flag = 0;

    // Variables used in loops
    int i;
    int j;
    int k;

    for (j = cur_game->cols - 1; j >= 0; j--) {  // Iterate through every column of array is descending order
        last_combined_row = -2;
        for (i = cur_game->rows - 2; i >= 0; i--) {  // Iterate through every row of array except last one in desceding order
            cur_cell_value1 = cur_game->cells[ (i * cur_game->cols) + j ];
            if ( !(cur_cell_value1 == -1) ) {  // If current cell is not empty,	then...
                
                target_row = i;  // Reset target row
                for (k = cur_game->rows - 1; k > i; k--) {  // Iterate through every row between end of column and i
                    cur_cell_value2 = cur_game->cells[ (k * cur_game->cols) + j ]; 
                    if (cur_cell_value2 == -1) {  // If	cell at row k is empty,	then set target	row to k
                        target_row = k;
                        break;
                    }
                }
                if ( target_row != i) {  // If their are any empty cells below current cell, move current cell to empty spot
                    cur_game->cells[ (target_row * cur_game->cols) + j] = cur_cell_value1;
                    cur_game->cells[ (i * cur_game->cols) + j] = -1;
                    flag = 1;  // Signal a change in game
                }
                // If row below	target row hasn't been combined	already, and if	they are both equal to each other, then	combine	them
                if ( ( target_row + 1 != last_combined_row ) && 
                     ( cur_game->cells[ (target_row + 1) * cur_game->cols + j ] == cur_game->cells[ target_row * cur_game->cols + j ] ) ) {
                    cur_game->cells[ (target_row + 1) * cur_game->cols + j ] *= 2;
                    cur_game->cells[ target_row * cur_game->cols + j] = -1;
                    last_combined_row = target_row + 1;
                    flag = 1;  // Signal a change in game
                    cur_game->score += cur_game->cells[ (target_row + 1) * cur_game->cols + j ];
                }
            }
        }
    }

    return flag;
};

int move_a(game * cur_game){ //slide left

    // Misc variables used
    cell cur_cell_value1;
    cell cur_cell_value2;
    int last_combined_col;
    int target_col;
    int flag = 0;

    // Variables used for loops 
    int i;
    int j;
    int k;

    for (i = 0; i < cur_game->rows; i++) {  // Iterate through every row of array in ascending order
        last_combined_col = -2;
        for (j = 1; j < cur_game->cols; j++) {  // Iterate through every column of array except first one in ascending order
            cur_cell_value1 = cur_game->cells[ (i * cur_game->cols) + j ];
            if ( !(cur_cell_value1 == -1) ) {  // If current cell is not empty,	then...

                target_col = j;  // Reset target column
                for (k = 0; k < j; k++) {  // Iterate through every column between start of row and j
                    cur_cell_value2 = cur_game->cells[ (i * cur_game->cols) + k ];
                    if (cur_cell_value2 == -1) {  // If	cell at col k is empty,	then set target	col to k
                       	target_col = k;
                       	break;
                    }
               	}
               	if ( target_col != j) {  // If their are any empty cells to left of current cell, move current cell to empty spot
                    cur_game->cells[ (i * cur_game->cols) + target_col] = cur_cell_value1;
                    cur_game->cells[ (i * cur_game->cols) + j] = -1;
                    flag = 1;  // Signal a change in game
                }
                // If row above	to left of target row hasn't been combined already, and if they are both equal to each other, then combine them
                if ( ( target_col - 1 != last_combined_col ) &&
                     ( cur_game->cells[ i * cur_game->cols + (target_col - 1) ] == cur_game->cells[ i * cur_game->cols + target_col ] ) ) {
                    cur_game->cells[ i * cur_game->cols + (target_col - 1) ] *= 2;
                    cur_game->cells[ i * cur_game->cols + target_col ] = -1;
                    last_combined_col = target_col - 1;
                    flag = 1;  // Signal a change in game
                    cur_game->score += cur_game->cells[ i * cur_game->cols + (target_col - 1) ];
                }
            }
	}
    }

    return flag;
};

int move_d(game * cur_game){ //slide to the right

    // Misc variables used 
    cell cur_cell_value1;
    cell cur_cell_value2;
    int last_combined_col;
    int target_col;
    int flag = 0;

    // Variables used for loops 
    int i;
    int j;
    int k;

    for (i = cur_game->rows - 1; i >= 0; i--) {  // Iterate through every row of array in descending order
        last_combined_col = -2;
        for (j = cur_game->cols - 2; j >= 0; j--) {  // Iterate through every column of array except last one in descending order
            cur_cell_value1 = cur_game->cells[ (i * cur_game->cols) + j ];
            if ( !(cur_cell_value1 == -1) ) {  // If current cell is not empty,	then...

                target_col = j;  // Reset target column
                for (k = cur_game->cols - 1; k > j; k--) {  Iterate through every column between end of row and j
                    cur_cell_value2 = cur_game->cells[ (i * cur_game->cols) + k ];
                    if (cur_cell_value2 == -1) {  // If	cell at col k is empty,	then set target	col to k
                       	target_col = k;
                       	break;
                    }
               	}
               	if ( target_col != j) {  // If their are any empty cells to right of current cell, move current cell to empty spot
                    cur_game->cells[ (i * cur_game->cols) + target_col] = cur_cell_value1;
                    cur_game->cells[ (i * cur_game->cols) + j] = -1;
                    flag = 1;  // Signal a change in game
                }
                // If row above to right of target row hasn't been combined already, and if they are both equal to each other, then combine them
                if ( ( target_col + 1 != last_combined_col ) &&
                     ( cur_game->cells[ i * cur_game->cols + (target_col + 1) ] == cur_game->cells[ i * cur_game->cols + target_col ] ) ) {
                    cur_game->cells[ i * cur_game->cols + (target_col + 1) ] *= 2;
                    cur_game->cells[ i * cur_game->cols + target_col ] = -1;
                    last_combined_col = target_col + 1;
                    flag = 1;  // Signal a change in game
                    cur_game->score += cur_game->cells[ i * cur_game->cols + (target_col + 1) ];
                }
            }
	}
    }

    return flag;
};

int legal_move_check(game * cur_game){
/*! Given the current game check if there are any legal moves on the board. There are
    no legal moves if sliding in any direction will not cause the game to change.
	Return 1 if there are possible legal moves, 0 if there are none.
 */

    int index;
    for (index = 0; index < cur_game->rows * cur_game->cols; index++) {  // Iterate through every index of array
        if ( cur_game->cells[index] == -1) {  // If cell is empty return 1
            return 1;
        }
        if ( !(index < cur_game->cols) ) {  // If cell has same top neighbor, return 1
            if ( cur_game->cells[index] == cur_game->cells[index - cur_game->cols] ) return 1;
        }
        if ( !(index >= cur_game->cols * (cur_game->rows - 1) ) ) {  // If cell has same bottom neighbor, return 1
            if ( cur_game->cells[index] == cur_game->cells[index + cur_game->cols] ) return 1;
        }
        if ( !(index % cur_game->cols == 0 )  ) {  // If cell has same left neighbor, return 1
            if ( cur_game->cells[index] == cur_game->cells[index - 1] ) return 1;
        }
        if ( !(index % cur_game->cols == cur_game->cols - 1) ) {  // If cell has same right neighbor, return 1
            if ( cur_game->cells[index] == cur_game->cells[index + 1] ) return 1;
        }
    }

    return 0;
}


/*! code below is provided and should not be changed */

void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
*/
{
	
	cell * cell_ptr;
    cell_ptr = 	cur_game->cells;
	
    if (cell_ptr == NULL){ 	
        printf("Bad Cell Pointer.\n");
        exit(0);
    }
	
	
	//check for an empty cell
	int emptycheck = 0;
	int i;
	
	for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
		if ((*cell_ptr) == -1){
				emptycheck = 1;
				break;
		}		
        cell_ptr += 1;
	}
	if (emptycheck == 0){
		printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
		exit(0);
	}
	
    int ind,row,col;
	int num;
    do{
		ind = rand()%((cur_game->rows)*(cur_game->cols));
		col = ind%(cur_game->cols);
		row = ind/cur_game->cols;
    } while ( *get_cell(cur_game, row, col) != -1);
        //*get_cell(cur_game, row, col) = 2;
	num = rand()%20;
	if(num <= 1){
		*get_cell(cur_game, row, col) = 4; // 1/10th chance
	}
	else{
		*get_cell(cur_game, row, col) = 2;// 9/10th chance
	}
}

int print_game(game * cur_game) 
{
    cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int i,j;
	
	printf("\n\n\nscore:%d\n",cur_game->score); 
	
	
	printf("\u2554"); // topleft box char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // top box char
	printf("\u2557\n"); //top right char 
	
	
    for(i = 0; i < rows; i++){
		printf("\u2551"); // side box char
        for(j = 0; j < cols; j++){
            if ((*cell_ptr) == -1 ) { //print asterisks
                printf(" **  "); 
            }
            else {
                switch( *cell_ptr ){ //print colored text
                    case 2:
                        printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4:
                        printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8:
                        printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 16:
                        printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 32:
                        printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 64:
                        printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 128:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 256:
                        printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 512:
                        printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 1024:
                        printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 2048:
                        printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4096:
                        printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8192:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
					default:
						printf("  X  ");

                }

            }
            cell_ptr++;
        }
	printf("\u2551\n"); //print right wall and newline
    }
	
	printf("\u255A"); // print bottom left char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // bottom char
	printf("\u255D\n"); //bottom right char
	
    return 0;
}

int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{ 
	int rows,cols;
	char buf[200];
	char garbage[2];
    int move_success = 0;
	
    switch ( input_char ) {
    case 'w':
        move_success = move_w(cur_game);
        break;
    case 'a':
        move_success = move_a(cur_game);
        break;
    case 's':
        move_success = move_s(cur_game);
        break;
    case 'd':
        move_success = move_d(cur_game);
        break;
    case 'q':
        destroy_game(cur_game);
        printf("\nQuitting..\n");
        return 0;
        break;
	case 'n':
		//get row and col input for new game
		dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
		while (NULL == fgets(buf,200,stdin)) {
			printf("\nProgram Terminated.\n");
			return 0;
		}
		
		if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
		rows < 0 || cols < 0){
			printf("Invalid dimensions.\n");
			goto dim_prompt;
		} 
		
		remake_game(&cur_game,rows,cols);
		
		move_success = 1;
		
    default: //any other input
        printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
    }

	
	
	
    if(move_success == 1){ //if movement happened, insert new tile and print the game.
         rand_new_tile(cur_game); 
		 print_game(cur_game);
    } 

    if( legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
        printf("Game Over!\n");
        return 0;
    }
    return 1;
}
