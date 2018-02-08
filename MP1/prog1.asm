;
; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming studio, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop


; ###  Written by Marc Harvey  ###

; Register usage:
; R0 - Holds ascii value of what needs to be printed to monitor (space, letter, etc.)
; R1 - Used to check if hex value is a number or letter, and then also adds either 48 or 55
;      depending on which one it is respectively. It does this by either loading NUMS (#48)
;      or LETS (#55)
; R2 - Used as a counter for the characters printed per line. Starts at 4 with every new line
;      and decrements by 1 with every char printed
; R3 - R3 is used when printing every character. It holds the value of the current memory
;      address and is multiplies with 2 to shift left, also determining whether it is 
;      negative or positive in the process. This is what is used to see which ascii char
;      print 
; R4 - Used a counter for the total amount of lines printed, In the case of printing the
;      histogram, that number is #27. It decrements by 1 with every line printed
; R5 - R5 is used for 2 purposes. One is to print the current letter in the histogram
;      and a space right after (so it can match the given output). The second is as a 
;      counter within the innermost loop, helping each character get printed, and counting
;      down from 4 for each character  
; R6 - R6 holds the current memory address to have its hex value printed. It starts at
;      x3F00 and increments by 1 for every line printed


PRINT_HIST
	LD      R6,START         ; Load the starting memory address to R6
	LD      R4,COUNT         ; Load the counter (r4) with the starting amount (26)

BEGIN   AND     R2,R2,#0         ;
        ADD     R2,R2,#4         ; Init R2 as 4
	LDR 	R3,R6,#0         ; Init R3 as the value of the memory address in R6
	
; This next chunk of code is for printing the letter plus a space eg. "A "

LTER    LD      R5,ASCII         ; Load R5 as the difference between original R6 and first ascii char that is needed, "@"
	ADD     R0,R6,R5         ; Add R6 and R5, getting the ascii value of whatever letter in histogram
	TRAP    x21              ; Print that character
	LD      R0,SPACE         ; Load ascii spaceabr value
	TRAP	x21 		 ; Print space

OUTERL  AND     R5,R5,#0         ; 
        ADD     R5,R5,#4         ; Init R5 as 4, a counter for each char, meaning 4 chars per line
        AND     R0,R0,#0         ; Init R0 as 0

INNERL  ADD     R0,R0,R0         ; Double the value of R0
        ADD     R3,R3,#0         ; Purely for the setcc, so we can tell if it is negative :)
        BRzp    #1               ; If R3 is not negative, skip 1 line
        ADD     R0,R0,#1         ; Add 1 to R0
        ADD     R3,R3,R3         ; Double the value of R3

        ADD     R5,R5,#-1        ; Decrement inner counter R5 by 1
        BRp     INNERL           ; If R5 is postive, go back to INNERL (inner loop)

; This is where the hex printing happens

        ADD     R1,R0,#-9        ; Copy 4 digits in R0 + -9 to R1, so we can see if it is greater than 10
        BRp     SKIP1            ; If R0 is greater than 9, then jump ahead to SKIP1

        LD      R1,NUMS          ; Load NUMS (#48) in R1 for help getting the ascii number values
        ADD     R0,R0,R1         ; Add R0 and R1 into R0, getting the correct ascii value in R0
        TRAP    x21              ; Print the ascii value in R0
        BRnzp   SKIP2            ; Unconditional jump to SKIP2

SKIP1   LD      R1,LETS          ; Load LETS (#55) in R1 for help getting the ascii letter values
        ADD     R0,R0,R1         ; Add R0 and R1 into R0, getting the correct ascii value in R0
        TRAP    x21              ; Print the ascii value in R0

; This is where the program decides whether to stop or keep going

SKIP2   ADD     R2,R2,#-1        ; Decrement R2 by 1
        BRp     OUTERL           ; If R2 is positive, then go back to OUTERL, effectively printing another char

; If a full line has been printed, we need a newline char
 
	LD	R0,NEWLN	 ; Load neline ascii into R0
	TRAP    x21              ; Print R0 to monitor

; Iterating R6 and R7

	ADD	R6,R6,#1         ; Increment R6 (holding current memory address) by 1
	ADD     R4,R4,#-1        ; Decrement R4 (line counter)  by 1
	BRzp    BEGIN            ; If R4 is zero or positive, restart the printing, effectively printing another line

DONE	HALT	 		 ; done


; the data needed by the program
NUM_BINS	.FILL #27	; 27 loop iterations
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00     ; histogram starting address
STR_START	.FILL x4000	; string starting address

; for testing, you can use the lines below to include the string in this
; program...
; STR_START	.FILL STRING	; string starting address
; STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."




; ###  These are my .FILLS that are essential for the program functionality ###

NUMS   		.FILL x0030	; #48, for getting ascii value of numbers
LETS   		.FILL x0037	; #55, for getting ascii value of letters
START  		.FILL x3F00	; Starting address for histogram data
COUNT  		.FILL x001A	; #26, or total number of lines to be printed - 1
NEWLN  		.FILL x000A	; Ascii newline char value
ASCII  		.FILL xC140	; A pointer to the ascii value given the current memory address being looked at
SPACE  		.FILL x0020	; Ascii space char value


	.END
