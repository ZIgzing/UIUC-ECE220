/*---------------------------------------------------------------------------------
Semiprime Number Printer

Written by Marc Harvey
UIUC ECE 220 MP4
021918

This program works by looping through a range of numbers (provided by user), and
printing whichever numbers it deems to be semiprimes.

The method of checking whether or not a number is semiprime is through the use of
a semiprime verifying algorithm (privided by professors). The algorithm loops through
the bounds between 0 and the current number (exclusive), and returns True if the
current number between the 2 bounds is a prime factor of the number in question, and
if the number in question over the current bounded number is a prime number. Because
this algorithm checks for prime numbers so often, it was essential to implement a 
prime number checking function. The prime number function works by looping between
the bounds of 2 and the middle of a number in question (inclusive), and if the number
in question modulo the looped number is 0 (during any of the loops), then it decides
the number in question is not a prime.
----------------------------------------------------------------------------------*/


#include <stdlib.h>
#include <stdio.h>


int is_prime(int number);
int print_semiprimes(int a, int b);


int main(){   
   int a, b;
   printf("Input two numbers: ");
   scanf("%d %d", &a, &b);
   if( a <= 0 || b <= 0 ){
     printf("Inputs should be positive integers\n");
     return 1;
   }

   if( a > b ){
     printf("The first number should be smaller than or equal to the second number\n");
     return 1;
   }

   print_semiprimes(a, b);
}


/*
 * Checks if a number is a prime
 * Input    : a number
 * Return   : 0 if the number is not prime, else 1
 */
int is_prime(int number)
{
  if (number == 4)
  {
    return 0;
  }

  /*
  This loop increments from 2 to half of the number, and decides the number is not prime
  if the number in question is divisible by any of the looped numbers.
  */

  for(int i = 2; i < number / 2; i++)
  {
    if ((number % i) == 0)
    {
      return 0;
    }
  }
  return 1;
}


/*
 * Prints all semiprimes within a given range of numbers
 * Input   : a, b (a should be smaller than or equal to b)
 * Return  : 0 if there is no semiprime in [a,b], else 1
 */
int print_semiprimes(int a, int b)
{
  int answer = 0;
  
  /*
  This loop increments by 1, starts at the first number, and ends at the last one.
  */

  for(int i = a; i <= b; i++)
  {

    /*
    This loop increments by 1, starting at 2 and ending at the current number(i) minus 1.
    For each number between those 2 bounds (inclusive) it checks if the if the number is a 
    semiprime using the current looped number.
    */

    for(int j = 2; j <= i - 1; j++)
    {
      if ( ((is_prime(j) == 1) && (i % j == 0) ) && (is_prime(i / j) == 1) )
      {
        printf("%d ", i);
        answer = 1;
        break;
      }
    }
  }
  return answer;
}



