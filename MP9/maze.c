/*----------------------------------------------------------------------------------------------------------------------------
Maze Solver 3000

Written by Marc Harvey
UIUC ECE 220 MP9
040718

The functions in this file are used in main.c to solve mazes of a specific format. The ones I wrote are createMaze,
destroyMaze, printMaze, and solveMazeManhattanDFS.

The createMaze function creates and returns a maze_t struct which has been declared in the maze.h header file. It does this
by first allocating enough memory for the struct (which depends on size of maze), and then filling the maze struct's cells
array with values (walls, start points, end points, etc.) from a specified text file.

The destroyMaze function frees the allocated memory given from the createMaze function. It does this basically by using
the free function a lot.

The printMaze function prints the 2d cells array inside a specified maze_t struct. It just does this by looping through the
array once.

The solveMazeManhattanDFS function uses a recursive backtracking depth first algorithm. It is really exhaustive, and checks
many places before it find the end of the maze, but it is far more effective than any iterative solution if that is even 
possible. Overall, it doesn't check surrounding cells, but only checks the cell specified. It calls itself to check 
surrounding cells by running it's function on them until it find the end.

----------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include "maze.h"


/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
    // Your code here. Make sure to replace following line with your own code.

    int width, height;
    char cur_cell;

    FILE * file = fopen(fileName, "r");  // Open the file for reading

    fscanf(file, "%d", &width);  // Get the width and height of the maze while scrapping the extra '\n'
    fscanf(file, "%d", &height);
    fgetc(file);

    maze_t * maze = malloc(sizeof(maze_t));  // Dynamically allocate memory of size of the maze_t struct

    maze->width = width;  // Set easy struct values to what they should be according to file
    maze->height = height;
    maze->cells = (char**)malloc( height * sizeof(char*) );  // Allocate memory for cells array
    int k;
    for (k = 0; k < height; k++) {  // Loop through rows of array, allocating memory for each one
        maze->cells[k] = (char*)malloc( width * sizeof(char) );
    }

    int i, j;
    for (i = 0; i < height; i++) {  // Loop through rows of cells array
        for (j = 0; j < width + 1; j++) {  // Loop through cols of cells array
            cur_cell = fgetc(file);  // Get character from stream
            if (cur_cell == '\n') continue;  // If it is newline, ignore
            if (cur_cell == 'S') {  // If it is S, set starting pos
                maze->startColumn = j;
                maze->startRow = i;
            }
            if (cur_cell == 'E') {  // If it is E, set end pos
                maze->endColumn = j;
                maze->endRow = i;
            }
            maze->cells[i][j] = cur_cell;  // Copy file char to cells array
        }
    }

    fclose(file);  // Close file and return maze
    return maze;
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    // Your code here.

    int i;
    for (i = 0; i < maze->height; i++) {  // Loop through all rows of array, freeing each one
        free(maze->cells[i]);
    }
    free(maze->cells);  // Free array of rows
    free(maze);  // Free whole rest of struct
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    int i, j;
    for (i = 0; i < maze->height; i++) {  // Loop through cells array rows
        for (j = 0; j < maze->width; j++) {  // Loop through cells array cols
            printf("%c", maze->cells[i][j]);  // Print char in current pos
        }
        printf("\n");
    }
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */
int solveMazeManhattanDFS(maze_t * maze, int col, int row)
{
    // Your code here. Make sure to replace following line with your own code.
    char cur_cell = maze->cells[row][col];

    // BASE CASES
    if (col == maze->endColumn && row == maze->endRow) return 1;  // If current pos is end, return true
    if (col < 0 || col >= maze->width || row < 0 || row >= maze->height) return 0;  // If current pos is on edge, return false
    if (cur_cell == '%' || cur_cell == '*' || cur_cell == '~') return 0;  // If current cell is wall, or past path, return false
    if (cur_cell != 'S') maze->cells[row][col] = '*';  // Mark cell as been there done that

    // RECURSE CASES
    if ( solveMazeManhattanDFS(maze, col + 1, row) ) return 1;  // Recurse through right cell
    if ( solveMazeManhattanDFS(maze, col, row - 1) ) return 1;  // Recurse through bottom cell
    if ( solveMazeManhattanDFS(maze, col, row + 1) ) return 1;  // Recurse through top cell
    if ( solveMazeManhattanDFS(maze, col - 1, row) ) return 1;  // Recurse through left cell
    if (cur_cell != 'S') maze->cells[row][col] = '~';
    return 0;
}
