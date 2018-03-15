#include "sudoku.h"

/*----------------------------------------------------------------------------------------------------------------------------
Sudoku Solver

Written by Marc Harvey
UIUC ECE 220 MP7
031518

The functions in this file are used in main.c to solve incomplete sudoku boards. They are is_val_in_row, is_val_in_col,
is_val_in_3x3_zone, is_val_valid, and solve_sudoku.

The is_val_in_row function checks if a given value is in the specified row of a 9x9 matix. It does this by iterating
through each column of the specified row in the matrix, and comparing the current matrix value to the specified value.

The is_val_in_col function checks if a given value is in the specified column of a 9x9 matix. It does this by iterating   
through	each row of the specified column in the	matrix,	and comparing the current matrix value to the specified	value.

is_val_in_3x3_zone checks if a specified value is in the same 3x3 area as the position specifie by row and column. (i and 
j) It does this by iterating through each position of the 3x3 square using a nested for-loop method. It determines the
starting position of the 3x3 area by dividing both the row and column by 3, and then multiplying both by 3. 

The is_val_valid function merely checks if all of the three above function are false for a given position on a given
9x9 matrix, and returns true (1) if they are indeed all false, and false (0) otherwise.

The solve_sudoku function uses a recursive backtracking method to fill a matrix with values. If the matrix is full of 
non-zero-but-less-than-ten numbers, the matrix is full and the function stops. 


----------------------------------------------------------------------------------------------------------------------------*/


// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

  int j;
  for (j = 0; j < 9; j++) {  // Iterate through every column (value) of specified row
    if ( sudoku[i][j] == val) {  // If specified value is equal to matrix value, return true
      return 1;
    }
  }

  return 0;
}


// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);

  int i;
  for (i = 0; i < 9; i++) {  // Iterate through every row (value) of specified column
    if ( sudoku[i][j] == val) {  // If specified value is equal	to matrix value, return	true
      return 1;
    }
  }

  return 0;
}


// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   
  assert(i>=0 && i<9);
  
  int startx = (j / 3) * 3;  // Get starting position of 3x3 zone
  int starty = (i / 3) * 3; 

  int row, col;
  for (row = starty; row < starty + 3; row++) {  // Iterate from starting row to starting row + 3 
    for (col = startx; col < startx + 3; col++) {  // Iterate from starting cloumn to starting column +	3
      if (sudoku[row][col] == val) {  // If specified value is equal to matrix value, return true
        return 1;
      } 
    }
  }

  return 0;
}


// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);

  // If value is in row, column, or 3x3 zone, return false
  if (is_val_in_row(val, i, sudoku) || is_val_in_col(val, j, sudoku) || is_val_in_3x3_zone(val, i, j, sudoku)) {
    return 0;
  }

  return 1;
}


// Function: no_zeros
// Return true if there are no zeros in 9x9 matrix
int no_zeros(int sudoku[9][9]) {

  int i, j;
  for (i = 0; i < 9; i++) {  // Iterate through all rows
    for (j = 0; j < 9; j++) {  // Iterate through all columns
      if (sudoku[i][j] == 0) {  // If matrix value is zero, return false
        return 0;
      }
    }
  } 
  
  return 1;
}


// Function: find_cell_i
// Return row of cell holding value 0 in 9x9 matrix
int find_cell_i(int sudoku[9][9]) {

  int i, j;
  for (i = 0; i < 9; i++) {  // Iterate through all rows
    for (j = 0; j < 9; j++) {  // Iterate through all clolumns 
      if (sudoku[i][j] == 0) {  // If value is equal to zero, return row
        return i;
      }
    }
  }
  return 0;
}


// Function: find_cell_j
// Return column of cell holding value 0 in 9x9 matrix
int find_cell_j(int sudoku[9][9]) {

  int i, j;
  for (i = 0; i < 9; i++) {  // Iterate through all rows
    for (j = 0; j < 9; j++) {  // Iterate through all columns
      if (sudoku[i][j] == 0) {  // If value is equal to zero, return column
        return j;
      }
    }
  }
  return 0;
}


// Function: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

  int i, j;
  if (no_zeros(sudoku)) {  // If there are no zeros in matrix, return 1
    return 1;
  }
  else {
    i = find_cell_i(sudoku);  // Find empty cell row 
    j = find_cell_j(sudoku);  // Find empty cell column
  }
  
  int num; 
  for (num = 1; num <= 9; num++) {  // Iterate through numbers 1 through 9
    if ( is_val_valid(num, i, j, sudoku) ) {  // If num can be placed in position, then place it
      sudoku[i][j] = num; 
      if (solve_sudoku(sudoku)) {  // Recursive part: checks if sudoku board has been solved while also solving it
        return 1;
      }
      sudoku[i][j] = 0; 
    }
  }
  return 0;
}


// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}


// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}





