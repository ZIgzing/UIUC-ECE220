.ORIG x3000
; R4 is going to be the number, R0 will be ascii value for printing, R5 is pointer, R6 is pointer
; R7 to be used as a method to see if the value is over 10
; R1 is used as the amount to jump when seeking the ascii value

; init R6 as 4 to be counted down
        AND     R6,R6,#0         ;
        ADD     R6,R6,#4         ;

; init R5 as 4 to be counted down
OUTERL  AND     R5,R5,#0         ;
        ADD     R5,R5,#4         ;
	AND     R0,R0,#0         ;

INNERL	ADD     R0,R0,R0         ;
	ADD     R3,R3,#0         ;  purely for the setcc :)
        BRzp    #1               ;
        ADD     R0,R0,#1         ;
	ADD     R3,R3,R3         ;

; decremement inner point (R5) by one
        ADD     R5,R5,#-1        ;
        BRp     INNERL           ;

; printing needs to go here

        ADD     R7,R0,#-9        ;    Copy 4 digits -9 to R7, so we can see if it is greater than 10
        BRzp    SKIP1            ;        If R0 is greater than 9, then jump ahead

        LD      R1,NUMS          ;
        ADD     R0,R0,R1         ;
        TRAP    x21              ;          
        BRnzp   SKIP2            ;

SKIP1   LD      R1,LETS          ;
        ADD     R0,R0,R1         ;
        TRAP    x21              ;

; Outer loop
SKIP2   ADD     R6,R6,#-1        ;
        BRp     OUTERL           ; 

HALT                             ;

NUMS   .FILL  x0030 
LETS   .FILL  x0037
.END
