/*---------------------------------------------------------------------------------
Pascal's Triangle Row Printer

Written by Marc Harvey
UIUC ECE 220 MP3
021618

*** note: we are not allowed to use c99 ***

This program takes an integer input and prints the corresponding row 
of Pascal's Triangle. 

It works by using a formula to find each number based on the row and current index,
and then loops through however many indexes are in whatever row the user has
specified. 

The formula used is just a standard Pascal formula. However, when the row becomes 
over 19, the traditional formula experiences overflow at certain indexes. To fix 
this, the pascal_value function simply multiplies and then divides during each
loop, making the answer for each index not get incredibly large. It multiplies 
and then divides in that order because of the way division of integers works in
c, and in this case it would round down, and give bad values.
----------------------------------------------------------------------------------*/


#include <stdio.h>
#include <stdlib.h>


unsigned long int pascal_value(int row, int index);


int main() {
  int row;
  unsigned long int number;
  printf("Enter a row index: ");
  scanf("%d", &row);
  
  /*
  This loop increments the index of the answer, starting at 0 and ending at the amount
  of rows specified by the user
  */

  int index;
  for(index = 0; index <= row;index++)
  {
    number = pascal_value(row,index);
    printf("%lu", number);
    printf(" ");
  }
  return 0;
}


unsigned long int pascal_value(int row, int index) {

  unsigned long int answer = 1;
  unsigned long int num = 1;
  unsigned long int den = 1;

  /*
  This loop calculates a product of each part of the pascal triangle calculator, and then
  multiplies it with the current answer. To do this, it first multiplies the answer by a
  numerator and then divides immediately after by a denominator. This methodology helps 
  calculate accurate answers without causing any sort of overflow.
  */

  int i;
  for (i = 1; i <= index; i++)
  {
    num = row + 1 - i;
    den = i;
    answer *= num;
    answer /= den;
  }

  return answer;
}

