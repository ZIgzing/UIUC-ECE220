/*---------------------------------------------------------------------------------------------------------------
Number Guessing Game

Written by Marc Harvey
UIUC ECE 220 MP5
030118

This file holds the functions used in the actual game (written by Lumetta), which is located in main.c. The
functions are set_seed, start_game, and make_guess.

The set_seed function takes in a string from a user with a single integer, and plugs the number into C's 
built-in srand function. This helps the computer generate the same numbers for each seed.

The start_game function is very simple in that it only gives values to global variables depending on whatever
numbers (1 through 8) it generates using C's rand() function. This is essential to having the user be able to 
guess what numbers were generated, while keeping the solutions constant.

The make_guess function is the meat of this file, and has the logic behind giving the user feedback on their 
guess. It takes in a string which is the user's guess, and then first tells if there are any direct matches
between it and the solution set. These are refered to as 'perfect matches'. If any of the solutions hasn't been 
matched perfectly, they are then attemped to match with the other three guess numbers. The first one it finds a
match with counts toward the 'mismatched answer' category. Note that each of the user's guess numbers can match
with only one solution and vice versa. The function returns 1 if all four guesses are perfect, and returns a 0
if the matches are incorrect.
----------------------------------------------------------------------------------------------------------------*/


#include <stdio.h>
#include <stdlib.h>

#include "prog5.h"

static int guess_number;
static int solution1;
static int solution2;
static int solution3;
static int solution4;


/* --------------------------------------------------------------------------------------------------------------
 * set_seed -- This function sets the seed value for pseudorandom
 * number generation based on the number the user types.
 * The input entered by the user is already stored in the string seed_str by the code in main.c.
 * This function should use the function sscanf to find the integer seed value from the 
 * string seed_str, then initialize the random number generator by calling srand with the integer
 * seed value. To be valid, exactly one integer must be entered by the user, anything else is invalid. 
 * INPUTS: seed_str -- a string (array of characters) entered by the user, containing the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (string contains anything
 *               other than a single integer), or 1 if string is valid (contains one integer)
 * SIDE EFFECTS: initializes pseudo-random number generation using the function srand. Prints "set_seed: invalid seed\n"
 *               if string is invalid. Prints nothing if it is valid.
 * --------------------------------------------------------------------------------------------------------------
 */

int set_seed (const char seed_str[])
{
    int seed;  // This will be an int passed into srand
    char checker;  // This is used to check if there is any extra stuff in the user input

    // This formats the user input into an int and a char
    int num_scanned = sscanf(seed_str, "%d %c", &seed, &checker); 
    
    // This only applies the srand if the user input seed_str is valid (only has an int)
    if (num_scanned == 1){
       	srand(seed);
        return 1;       	 
    }

    printf("set_seed: invalid seed\n");
    return 0;
}


/* --------------------------------------------------------------------------------------------------------------
 * start_game -- This function is called by main.c after set_seed but before the user makes guesses.
 *               This function creates the four solution numbers using the approach
 *               described in the wiki specification (using rand())
 *               The four solution numbers should be stored in the static variables defined above. 
 *               The values at the pointers should also be set to the solution numbers.
 *               The guess_number should be initialized to 1 (to indicate the first guess)
 * INPUTS: none
 * OUTPUTS: *one -- the first solution value (between 1 and 8)
 *          *two -- the second solution value (between 1 and 8)
 *          *three -- the third solution value (between 1 and 8)
 *          *four -- the fourth solution value (between 1 and 8)
 * RETURN VALUE: none
 * SIDE EFFECTS: records the solution in the static solution variables for use by make_guess, set guess_number
 * --------------------------------------------------------------------------------------------------------------
 */

void start_game (int* one, int* two, int* three, int* four)
{
    // Since these are pointers, we need to refer to the value they are pointing at using the * operator
    *one = ( rand() % 8 ) + 1;  
    *two = ( rand() % 8 ) + 1;
    *three = ( rand() % 8 ) + 1;
    *four = ( rand() % 8 ) + 1;
    
    guess_number = 1;
    
    // This seems kindof redundant, but they did provide those weird pointer type parameters
    solution1 = *one;
    solution2 = *two;
    solution3 = *three;
    solution4 = *four;
}


/* --------------------------------------------------------------------------------------------------------------
 * make_guess -- This function is called by main.c after the user types in a guess.
 *               The guess is stored in the string guess_str. 
 *               The function must calculate the number of perfect and misplaced matches
 *               for a guess, given the solution recorded earlier by start_game
 *               The guess must be valid (contain only 4 integers, within the range 1-8). If it is valid
 *               the number of correct and incorrect matches should be printed, using the following format
 *               "With guess %d, you got %d perfect matches and %d misplaced matches.\n"
 *               If valid, the guess_number should be incremented.
 *               If invalid, the error message "make_guess: invalid guess\n" should be printed and 0 returned.
 *               For an invalid guess, the guess_number is not incremented.
 * INPUTS: guess_str -- a string consisting of the guess typed by the user
 * OUTPUTS: the following are only valid if the function returns 1 (A valid guess)
 *          *one -- the first guess value (between 1 and 8)
 *          *two -- the second guess value (between 1 and 8)
 *          *three -- the third guess value (between 1 and 8)
 *          *four -- the fourth color value (between 1 and 8)
 * RETURN VALUE: 1 if the guess string is valid (the guess contains exactly four
 *               numbers between 1 and 8), or 0 if it is invalid
 * SIDE EFFECTS: prints (using printf) the number of matches found and increments guess_number(valid guess) 
 *               or an error message (invalid guess)
 *               (NOTE: the output format MUST MATCH EXACTLY, check the wiki writeup)
 * --------------------------------------------------------------------------------------------------------------
 */

int make_guess (const char guess_str[], int* one, int* two, int* three, int* four)
{
//  One thing you will need to read four integers from the string guess_str, using a process
//  similar to set_seed
//  The statement, given char post[2]; and four integers w,x,y,z,
//  sscanf (guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post)
//  will read four integers from guess_str into the integers and read anything else present into post
//  The return value of sscanf indicates the number of items sucessfully read from the string.
//  You should check that exactly four integers were sucessfully read.
//  You should then check if the 4 integers are between 1-8. If so, it is a valid guess
//  Otherwise, it is invalid.  
//  Feel free to use this sscanf statement, delete these comments, and modify the return statement as needed

    int num_perfect = 0;  // count of how many perfect matches there are
    int num_mismatch = 0;  // count of how many mismatched matches there are
    int top1 = 0, top2 = 0, top3 = 0, top4 = 0;  // flags that say if solutions have been matched
    int gus1 = 0, gus2 = 0, gus3 = 0, gus4 = 0;  // flags that say if guesses have been matched
    char checker;  // Helps check if there is extra stuff in the user guess

    // This will format the string into 4 digits and one checking character
    int num_scanned = sscanf(guess_str, "%d %d %d %d %c", one, two, three, four, &checker);

// *** Checking if guess is formatted properly *** //
    // This uses the fact that sscanf returns the number of values obtained, and checks if is 4. If it isn't,
    // then it is an incorrectly formatted guess
    if (num_scanned != 4)
    {
        printf("make_guess: invalid guess\n");
        return 0;
    }
    if (*one < 1 || *one > 8 || *two < 1 || *two > 8 ||*three < 1 || *three > 8 ||*four < 1 || *four > 8)
    {
        printf("make_guess: invalid guess\n");
        return 0;
    }

// *** Checking if there are any perfect matches *** //
    if (*one == solution1)
    {
        num_perfect++;
        top1 = 1;
        gus1 = 1;
    }
    if (*two == solution2)
    {
       	num_perfect++;
        top2 = 1;
        gus2 = 1;
    }
    if (*three == solution3)
    {
       	num_perfect++;
        top3 = 1;
        gus3 = 1;
    }
    if (*four == solution4)
    {
       	num_perfect++;
        top4 = 1;
        gus4 = 1;
    }

// *** Checking if there are any mismatched... matches? *** //
// btw I know this is kindof atrocious, but I was pressed for time. In hindsight there are
// many better solutions that involve loops that would have reduced the line count
// significantly
    if (top1 == 0)
    {        
        if (*two == solution1 && top1 == 0 && gus2 == 0) 
        {
            num_mismatch++;
            top1 = 1;
            gus2 = 1;
        }
        if (*three == solution1 && top1 == 0 && gus3 == 0)
        {
            num_mismatch++;
            top1 = 1;
            gus3 = 1;
        }
        if (*four == solution1 && top1 == 0 && gus4 == 0)
        {
            num_mismatch++;
            top1 = 1;
            gus4 = 1;
        }        
    }
    if (top2 == 0)
    {
       	if (*one == solution2 && top2 == 0 && gus1 == 0) 
        {
       	    num_mismatch++;
       	    top2 = 1;
            gus1 = 1;
       	}
       	if (*three == solution2 && top2 == 0 && gus3 == 0)
       	{
       	    num_mismatch++;
       	    top2 = 1;
            gus3 = 1;
       	} 
       	if (*four == solution2 && top2 == 0 && gus4 == 0)
       	{
       	    num_mismatch++;
       	    top2 = 1;
            gus4 = 1;
       	}
    }
    if (top3 == 0)
    {
       	if (*one == solution3 && top3 == 0 && gus1 == 0) 
        {
       	    num_mismatch++;
       	    top3 = 1;
            gus1 = 1;
       	}
       	if (*two == solution3 && top3 == 0 && gus2 == 0)
       	{
       	    num_mismatch++;
       	    top3 = 1;
            gus2 = 1;
       	} 
       	if (*four == solution3 && top3 == 0 && gus4 == 0)
       	{
       	    num_mismatch++;
       	    top3 = 1;
            gus4 = 1;
       	}
    }
    if (top4 == 0)
    {
       	if (*one == solution4 && top4 == 0 && gus1 == 0) 
        {
       	    num_mismatch++;
       	    top4 = 1;
            gus1 = 1;
       	}
       	if (*two == solution4 && top4 == 0 && gus2 == 0)
       	{
       	    num_mismatch++;
       	    top4 = 1;
            gus2 = 1;
       	} 
       	if (*three == solution4 && top4 == 0 && gus3 == 0)
       	{
       	    num_mismatch++;
       	    top4 = 1;
            gus3 = 1;
       	}
    }


    printf("With guess %d, you got %d perfect matches and %d misplaced matches.\n", guess_number, num_perfect, num_mismatch);
    guess_number++;
    return 1;

}


