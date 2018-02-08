; Witten by Marc Harvey 
; Univerisity of Illinois 
; ECE 220 MP2 
; 02/08/18

; This program takes input from a user in the form of a postfix expression and 
; prints the answer using a stack calculator type method

; First, the main function has the user input a character. It then checks whether that character is an
; operator, operand, space, or equal sign. If it isn't any, the program prints and error message. If the character 
; an operand, the main program pushes it to the top of a stack. If it is an operator, then the main 
; function jumps to the characters correlating subroutine (eg. '+' jumps to PLUS.) If the character is a
; space, the main function does nothing. Then, the main function loops back to the beginning and gets 
; another character and repeats itself. However, if the character was an equal sign, the function will
; print the top value in the stack if there is only one value. If there are multiple values in the stack,
; it will return an error message.

; The 5 operand subroutines work in the same exact way. They all pop 2 values out of the stack, and perform
; whatever operation on the two, and then push that single answer back to the stack.



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Main Function
.ORIG x3000
	
;your code goes here
	
BEGIN	GETC			; Get User Input
	
	LD R1,SPACEB		; Load R1 with ascii for space bar
	NOT R1,R1		;
	ADD R1,R1,#1		; R1 = R1 * -1
	ADD R2,R0,R1		; R2 = R0 + R1
	BRnp #2			; If R2 is not zero, skip 2 lines
	TRAP x21		; Print R0, which is space
	BRnzp SKIPOP		; Go to SKIPOP

	LD R1,ASIGN		; Load R1 with ascii for '+'
	NOT R1,R1		;
	ADD R1,R1,#1		; R1 = R1 * -1
	ADD R2,R0,R1		; R2 = R0 + R1
	BRnp #4			; If R2 is not zero, skip 4 lines
	LD R0,ASIGN		; Load R0 with ascii for '+', for printing
	TRAP x21		; Print '+'
	JSR PLUS		; Jump to addition subroutine
	BRnzp SKIPOP		; Go to SKIPOP

	LD R1,SSIGN		; Load R1 with ascii for '-'
	NOT R1,R1		;
	ADD R1,R1,#1		; R1 = R1 * -1
	ADD R2,R0,R1		; R2 = R0 + R1
	BRnp #4			; If R2 is not zero, skip 4 lines
        LD R0,SSIGN		; Load R0 with ascii for '-', for printing
        TRAP x21        	; Print '-'
	JSR MIN			; Jump to subtraction subroutine
	BRnzp SKIPOP		; Go to SKIPOP
 
	LD R1,MSIGN     	; Load R1 with ascii for '*'
        NOT R1,R1       	;
        ADD R1,R1,#1		; R1 = R1 * -1
        ADD R2,R0,R1    	; R2 = R0 + R1
        BRnp #4			; If R2 is not zero, skip 4 lines
	LD R0,MSIGN     	; Load R0 with ascii for '*', for printing
        TRAP x21        	; Print '*'
        JSR MUL	        	; Jump to multiplication subroutine
	BRnzp SKIPOP		; Go to SKIPOP

	LD R1,DSIGN     	; Load R1 with ascii for '/'
        NOT R1,R1       	;
        ADD R1,R1,#1		; R1 = R1 * -1
        ADD R2,R0,R1    	; R2 = R0 + R1
        BRnp #4			; If R2 is not zero, skip 4 lines
        LD R0,DSIGN     	; Load R0 with ascii for '/', for printing
        TRAP x21        	; Print '/'
	JSR DIV	        	; Jump to division subroutine
	BRnzp SKIPOP		; Go to SKIPOP

	LD R1,EXSIGN    	; Load R1 with ascii for '^'
        NOT R1,R1       	;
        ADD R1,R1,#1		; R1 = R1 * -1
        ADD R2,R0,R1    	; R2 = R0 + R1
        BRnp #4			; If R2 is not zero, skip 4 lines
	LD R0,EXSIGN    	; Load R0 with ascii for '^', for printing
        TRAP x21        	; Print '^'
        JSR EXP	        	; Jump to exponent subroutine
	BRnzp SKIPOP		; Go to SKIPOP

	LD R1,ESIGN     	; Load R1 with ascii for '='
        NOT R1,R1       	; 
        ADD R1,R1,#1		; R1 = R1 * -1
        ADD R2,R0,R1    	; R2 = R0 + R1
        BRnp #4			; If R2 is not zero, skip 4 lines
	LD R0,ESIGN		; Load R0 with ascii for '=', for printing
	TRAP x21		; Print '='
        JSR EVALUATE		; Jump to evaluate subroutine
	BRnzp FINISH		; Go to FINISH

	TRAP x21		; Print whatever ascii value is in R1
	LD R3,NEG48		; R1 <- -48
	ADD R1,R0,R3		; R1 = R0 + R3
	ADD R0,R0,R3		; R0 = R0 + R3
	BRn ERROR1		; If R0 is negative, display error
	LD R3,NEG10		; R3 <- -10
	ADD R1,R1,R3		; R1 = R1 + R3
	BRzp ERROR1		; If R1 is zero or positive, display error
	JSR PUSH		; Jump to PUSH

SKIPOP	BRnzp BEGIN		; Loop back to BEGIN

FINISH	
	HALT			;
ERROR1	
	JSR ERROR		;
	HALT			;

ASIGN	.FILL x2B		;
SSIGN	.FILL x2D		;
MSIGN	.FILL x2A		;
DSIGN	.FILL x2F		;
ESIGN	.FILL x3D		;
EXSIGN	.FILL x5E		;
SPACEB	.FILL x20		;
NEG48	.FILL #-48		;
NEG10	.FILL #-10		;


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
ERROR
	ST R0,ERR_SaveR0	; Store registers so they can be restored
	ST R7,ERR_SaveR7	;	

	LEA R0,ERRORM		; Load starting address of error message in R0
	PUTS			; Print error message

	LD R0,ERR_SaveR0	; Restore registers
	LD R7,ERR_SaveR7	;
	RET			; Return 

ERR_SaveR0	.BLKW #1	;
ERR_SaveR7	.BLKW #1	;
ERRORM	.STRINGZ "Invalid Expression"	;



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R3- value to print in hexadecimal
PRINT_HEX

	ST R5,HEX_SaveR5	; Store registers so they can be restored
	ST R0,HEX_SaveR0	;
	ST R3,HEX_SaveR3	;
	ST R2,HEX_SaveR2	;
	ST R7,HEX_SaveR7	;

	AND R2,R2,#0		; 
	ADD R2,R2,#4		; Init R2 as 4, a counter for each char during the printing

OUTERL	AND R5,R5,#0		; 
	ADD R5,R5,#4		; Init R5 as 4, a counter for each char, meaning 4 chars per line
	AND R0,R0,#0		; Init R0 as 0

INNERL	ADD R0,R0,R0		; Double the value of R0
	ADD R3,R3,#0		; Purely for the setcc, so we can tell if it is negative :)
	BRzp #1			; If R3 is not negative, skip 1 line
	ADD R0,R0,#1		; Add 1 to R0
	ADD R3,R3,R3		; Double the value of R3

	ADD R5,R5,#-1		; Decrement inner counter R5 by 1
	BRp INNERL		; If R5 is postive, go back to INNERL (inner loop)

; This is where the hex printing happens

	ADD R1,R0,#-9		; Copy 4 digits in R0 + -9 to R1, so we can see if it is greater than 10
	BRp SKIP1		; If R0 is greater than 9, then jump ahead to SKIP1

	LD R1,NUMS		; Load NUMS (#48) in R1 for help getting the ascii number values
	ADD R0,R0,R1		; Add R0 and R1 into R0, getting the correct ascii value in R0
	TRAP x21		; Print the ascii value in R0
	BRnzp SKIP2		; Unconditional jump to SKIP2

SKIP1	LD R1,LETS		; Load LETS (#55) in R1 for help getting the ascii letter values
	ADD R0,R0,R1		; Add R0 and R1 into R0, getting the correct ascii value in R0
	TRAP x21		; Print the ascii value in R0

; This is where the program decides whether to stop or keep going

SKIP2	ADD R2,R2,#-1		; Decrement R2 by 1
	BRp OUTERL		; If R2 is positive, then go back to OUTERL, effectively printing another char

	LD R5,HEX_SaveR5        ; Restore registers
	LD R0,HEX_SaveR0        ;
	LD R3,HEX_SaveR3        ;
	LD R2,HEX_SaveR2        ;
	LD R7,HEX_SaveR7	;
	RET			; Return

HEX_SaveR5	.BLKW #1	; Memory for storing register values 
HEX_SaveR0	.BLKW #1	;
HEX_SaveR3	.BLKW #1	;
HEX_SaveR2	.BLKW #1	;
HEX_SaveR7	.BLKW #1	;
NUMS		.FILL x0030	; #48, for getting ascii value of numbers
LETS		.FILL x0037	; #55, for getting ascii value of letters


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard
;R6 - current numerical output
;
;
EVALUATE
;your code goes here
	
	ST R7,EVAL_SaveR7	; Store registers so they can be restored later
	ST R3,EVAL_SaveR3	;

	JSR POP			; Pop top value in stack to R0
	ADD R3,R0,#0		; Set R3 = R0
	JSR POP			; Pop top value in stack to R0
	ADD R5,R5,#0		; Purely for the setcc :)
	BRz ERROR2		; If R5	is positive, print error message

	JSR PRINT_HEX		; Print the hex value stored in R3
	ADD R5,R3,#0		; R5 = R3

	LD R7,EVAL_SaveR7	; Restore registers
	LD R3,EVAL_SaveR3	;
	RET			; Return

ERROR2	JSR ERROR		; Print error message
	HALT			; Halt

EVAL_SaveR7	.BLKW #1	; Memory for storing register values
EVAL_SaveR3	.BLKW #1	;



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
PLUS	
;your code goes here

	ST R1,PLUS_SaveR1	; Store registers so they can be restored later
	ST R7,PLUS_SaveR7	;

	JSR POP			; Pop top value in stack to R0
	ADD R1,R0,#0		; Set R1 = R0
	JSR POP			; Pop top value	in stack to R0

	ADD R5,R5,#0		; Purely for the setcc :)
	BRp ERROR3		; If R5	is positive, print error message

	ADD R0,R1,R0		; Set R0 = R1 + R0
	JSR PUSH		; Push value in R0 to top of stack
	
	LD R1,PLUS_SaveR1	; Restore registers
	LD R7,PLUS_SaveR7	;
	RET			; Return
	

PLUS_SaveR1     .BLKW #1        ; Memory for saving register values
PLUS_SaveR7	.BLKW #1	;

ERROR3	JSR ERROR		; Print error message
	HALT			; Halt



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MIN	
;your code goes here

        ST R1,MIN_SaveR1 	; Store registers so they can be restored later
	ST R7,MIN_SaveR7	;

        JSR POP          	; Pop top value	in stack to R0
        ADD R1,R0,#0     	; Set R1 = R0
	NOT R1,R1		;
	ADD R1,R1,#1		; Set R1 = R1 * -1
        JSR POP          	; Pop top value	in stack to R0

	ADD R5,R5,#0            ; Purely for the setcc :)
        BRp ERROR4              ; If R5	is positive, print error message

        ADD R0,R1,R0     	; Set R0 = R1 + R0
        JSR PUSH         	; Push value in	R0 to top of stack

        LD R1,MIN_SaveR1	; Restore registers
	LD R7,MIN_SaveR7	;
        RET                     ; Return

MIN_SaveR1      .BLKW #1        ; Memory for saving register values
MIN_SaveR7	.BLKW #1	;

ERROR4  JSR ERROR               ; Print error message
        HALT                    ; Halt



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MUL	
;your code goes here
	
	ST R1,MUL_SaveR1	; Store registers so they can be restored later
	ST R2,MUL_SaveR2	;
	ST R7,MUL_SaveR7	;

	JSR POP			; Pop top value	in stack to R0
	ADD R1,R0,#0		; Set R1 = R0
	JSR POP			; Pop top value	in stack to R0

	ADD R5,R5,#0            ; Purely for the setcc :)
        BRp ERROR5              ; If R5	is positive, print error message

	AND R2,R2,#0		; 
CONT1	ADD R2,R2,R0		; Init R2 as value in R0
	ADD R1,R1,#-1		; Decrement R1 by 1
	BRp CONT1		; If R1 is positive, loop back to CONT1
	ADD R0,R2,#0		; Set R0 = R2
	JSR PUSH		; Push value in	R0 to top of stack
	
	LD R1,MUL_SaveR1	; Restore registers
	LD R2,MUL_SaveR2	;
	LD R7,MUL_SaveR7	;
	RET			; Return
	
MUL_SaveR1	.BLKW #1	; Memory for storing regisiters
MUL_SaveR2	.BLKW #1	;
MUL_SaveR7	.BLKW #1	;

ERROR5  JSR ERROR               ; Print error message
        HALT                    ; Halt



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
DIV	
;your code goes here
	
	ST R1,DIV_SaveR1	; Store registers so they can be restored later
        ST R2,DIV_SaveR2        ;
        ST R7,DIV_SaveR7        ;

	JSR POP			; Pop top value	in stack to R0
	ADD R1,R0,#0		; Set R1 = R0
	NOT R1,R1		;
	ADD R1,R1,#1		; Set R1 = R1 * -1
	JSR POP			; Pop top value	in stack to R0

	ADD R5,R5,#0            ; Purely for the setcc :)
        BRp ERROR6              ; If R5	is positive, print error message

	AND R2,R2,#0		; Set R2 = 0

CONT2	ADD R2,R2,#1		; Increment R2 by 1
	ADD R0,R0,R1		; Set R0 = R0 + R1
	BRp CONT2		; If R0 is positive, loop back to CONT2
	BRz #1			; If R0 is zero, skip 1 line
	ADD R2,R2,#-1		; Decrement R2 by 1
	ADD R0,R2,#0		; Push value in	R0 to top of stack
	JSR PUSH		; Push value in R0 to top of stack

        LD R1,DIV_SaveR1        ; Restore registers
        LD R2,DIV_SaveR2        ;
        LD R7,DIV_SaveR7        ;
        RET                     ; Return

DIV_SaveR1	.BLKW #1        ; Memory for storing registers
DIV_SaveR2	.BLKW #1        ;
DIV_SaveR7	.BLKW #1        ;

ERROR6  JSR ERROR               ; Print error message
        HALT                    ; Halt



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
EXP
;your code goes here

	ST R1,EXP_SaveR1	; Store registers so they can be restored later
	ST R2,EXP_SaveR2	;
	ST R3,EXP_SaveR3	;
	ST R7,EXP_SaveR7	;

	JSR POP			; Pop top value	in stack to R0
	ADD R1,R0,#-1		;
	JSR POP			; Pop top value	in stack to R0

	ADD R5,R5,#0            ; Purely for the setcc :)
        BRp ERROR7              ; If R5 is positive, print error message

	ADD R2,R0,#0		; Set R2 = R0
	ADD R3,R0,#0		; Set R3 = R0

EXP1	JSR PUSH		; Push the value in R0 to top of stack
	ADD R0,R2,#0		; Set R0 = R2
	JSR PUSH		; Push the value in R0 to top of stack
	JSR MUL			; Multiply the 2 values at top of stack and push answer to top 
	JSR POP			; Pop top value in stack to R0
	ADD R2,R0,#0		; Set R2 = R0

	ADD R0,R3,#0		; Set R0 = R3
	
	ADD R1,R1,#-1		; Decrement R1 by 1
	BRp EXP1		; If R1 is positive, loop back to EXP1
	
	ADD R0,R2,#0		; Set R0 = R2
	JSR PUSH		; Push value in	R0 to top of stack

        LD R1,EXP_SaveR1        ; Restore registers
        LD R2,EXP_SaveR2        ;
        LD R3,EXP_SaveR3        ;
        LD R7,EXP_SaveR7        ;
        RET			; Return

EXP_SaveR1	.BLKW #1	; Memory for storing register values
EXP_SaveR2	.BLKW #1	;
EXP_SaveR3	.BLKW #1	;
EXP_SaveR7	.BLKW #1	;

ERROR7  JSR ERROR               ; Print error message
        HALT                    ; Halt


	
;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH	
	ST R3, PUSH_SaveR3	;save R3
	ST R4, PUSH_SaveR4	;save R4
	AND R5, R5, #0		;
	LD R3, STACK_END	;
	LD R4, STACk_TOP	;
	ADD R3, R3, #-1		;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz OVERFLOW		;stack is full
	STR R0, R4, #0		;no overflow, store value in the stack
	ADD R4, R4, #-1		;move top of the stack
	ST R4, STACK_TOP	;store top of stack pointer
	BRnzp DONE_PUSH		;
OVERFLOW
	ADD R5, R5, #1		;
DONE_PUSH
	LD R3, PUSH_SaveR3	;
	LD R4, PUSH_SaveR4	;
	RET


PUSH_SaveR3	.BLKW #1	;
PUSH_SaveR4	.BLKW #1	;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP	
	ST R3, POP_SaveR3	;save R3
	ST R4, POP_SaveR4	;save R3
	AND R5, R5, #0		;clear R5
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz UNDERFLOW		;
	ADD R4, R4, #1		;
	LDR R0, R4, #0		;
	ST R4, STACK_TOP	;
	BRnzp DONE_POP		;
UNDERFLOW
	ADD R5, R5, #1		;
DONE_POP
	LD R3, POP_SaveR3	;
	LD R4, POP_SaveR4	;
	RET


POP_SaveR3	.BLKW #1	;
POP_SaveR4	.BLKW #1	;
STACK_END	.FILL x3FF0	;
STACK_START	.FILL x4000	;
STACK_TOP	.FILL x4000	;


.END
