      **************************************************************** 
      * PROGRAM:      SAMPLE1.CBL
      * DESCRIPTION:  A WELCOME MESSAGE IS DISPLAYED
      * WRITTEN BY:   PAUL SIBLE
      **************************************************************** 
       IDENTIFICATION DIVISION.
       PROGRAM-ID. SAMPLE1.
       AUTHOR. PAUL SIBLE.
      
       ENVIRONMENT DIVISION.
       CONFIGURATION SECTION.
       SOURCE-COMPUTER. PC.
       OBJECT-COMPUTER. PC.
      
       DATA DIVISION.
       WORKING-STORAGE SECTION.
       01	NAME.
	      05	FIRST-NAME	PIC X(4)	VALUE 'PAUL'.
	      05	FILLER		PIC X		VALUE SPACES.
	      05	LAST-NAME	PIC X(5)	VALUE 'SIBLE'.      
      
       PROCEDURE DIVISION.
       10-BEGIN.
	      DISPLAY ' '.
	      DISPLAY 'WELCOME TO COBOL'.
	      DISPLAY ' '.
	      DISPLAY 'SINCERELY'.
	      DISPLAY NAME.
	      STOP RUN.
