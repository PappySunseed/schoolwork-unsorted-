      ******************************************************************
      * Author:
      * Date:
      * Purpose:
      * Tectonics: cobc
      ******************************************************************

      *[][][][][][][][][][][][][][][][][][][][][][][][][][][][]
       IDENTIFICATION DIVISION.
         PROGRAM-ID. PROG3-PAYROLL.
      *[][][][][][][][][][][][][][][][][][][][][][][][][][][][]
       ENVIRONMENT DIVISION.
           INPUT-OUTPUT SECTION.
           FILE-CONTROL.
               SELECT INPUT-FILE     ASSIGN TO 'input.txt'
                   ORGANIZATION IS LINE SEQUENTIAL.
               SELECT OUTPUT-FILE       ASSIGN TO 'output.txt'
                   ORGANIZATION IS LINE SEQUENTIAL.
      *[][][][][][][][][][][][][][][][][][][][][][][][][][][][]
       DATA DIVISION.
         FILE SECTION.
               FD INPUT-FILE
               RECORD CONTAINS 33 CHARACTERS
               DATA RECORD IS IN-RECORD.
           01  EMPLOYEE-DATA.
                   08  FIRST-NAME  PIC X(10).
                   08  LAST-NAME   PIC X(15).
                   08  HOURS       PIC 99V99.
                   08  RATE        PIC 99V99.

               FD  OUTPUT-FILE
               RECORD CONTAINS 80 CHARACTERS
               DATA RECORD IS OUT-RECORD.
       01      OUT-RECORD     PIC X(33).
      *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
         WORKING-STORAGE SECTION.
       01  EOF-SWITCH      PIC XXX  VALUE SPACES.
       01  BONUS-SWITCH    PIC X(5) VALUE "TRUE".

       01  LOOP-COUNTER    PIC 99 VALUE 1.

       01  OUT-HEADING     PIC X(40) VALUE
      -    'FirstName LastName       GrossPay'.

       01  EMPLOYEE-OUT OCCURS 25 TIMES.
               08 FIRST-NAME-OUT   PIC X(10).
               08 LAST-NAME-OUT    PIC X(15).
               08 GROSS-PAY-DISPLAY PIC ZZZ9.99.
       01 GROSS-PAY        PIC 9(4)V99.

       01  TABLE-DATA.
           05 EMP-INDEX    PIC 99  VALUE 1.
           05 EMP-COUNT    PIC 99  VALUE ZERO.
      *[][][][][][][][][][][][][][][][][][][][][][][][][][][][]
       PROCEDURE DIVISION.
      *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
       MAIN-PROCEDURE.
           PERFORM OPEN-FILES.

           PERFORM UNTIL EOF-SWITCH = 'YES'
               PERFORM PROCESS-INPUT
           END-PERFORM.

           PERFORM CALCULATE-BONUS.

           PERFORM DISPLAY-PAYROLL.

           PERFORM CLOSE-FILES.

           STOP RUN.




      *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
       OPEN-FILES.
           OPEN INPUT INPUT-FILE
                OUTPUT OUTPUT-FILE.
      *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
       CLOSE-FILES.
           CLOSE   INPUT-FILE
                   OUTPUT-FILE.
      *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
      *reads data, places in table
       PROCESS-INPUT.
           READ INPUT-FILE
                 AT END MOVE 'YES' TO EOF-SWITCH
           END-READ.

           IF EOF-SWITCH NOT EQUAL 'YES'
               PERFORM FILL-TABLE
           END-IF.
      *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
       FILL-TABLE.
           MOVE FIRST-NAME TO FIRST-NAME-OUT(EMP-INDEX).
           MOVE LAST-NAME TO LAST-NAME-OUT(EMP-INDEX).

      *compute the pay, including overtime
           IF HOURS <= 40
               COMPUTE GROSS-PAY ROUNDED = HOURS * RATE
           ELSE
               COMPUTE GROSS-PAY ROUNDED =
               (RATE * 1.5 * (HOURS - 40)) + (RATE * 40)
           END-IF.

           MOVE GROSS-PAY TO GROSS-PAY-DISPLAY(EMP-INDEX).


           IF HOURS < 35
               MOVE 'FALSE' TO BONUS-SWITCH
           END-IF

           ADD 1 TO EMP-INDEX.
           ADD 1 TO EMP-COUNT.
      *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
       CALCULATE-BONUS.
           IF BONUS-SWITCH EQUAL TO 'TRUE'
               PERFORM VARYING LOOP-COUNTER FROM 1 BY 1 UNTIL
               LOOP-COUNTER > EMP-COUNT
                   MOVE GROSS-PAY-DISPLAY(LOOP-COUNTER) TO GROSS-PAY
                   ADD 50 TO GROSS-PAY
                   MOVE GROSS-PAY TO GROSS-PAY-DISPLAY(LOOP-COUNTER)
               END-PERFORM
           END-IF.
      *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
       DISPLAY-PAYROLL.
           MOVE OUT-HEADING TO OUT-RECORD.
           WRITE OUT-RECORD.

           MOVE 1 TO LOOP-COUNTER.

           PERFORM VARYING LOOP-COUNTER FROM 1 BY 1 UNTIL
           LOOP-COUNTER > EMP-COUNT
               MOVE EMPLOYEE-OUT(LOOP-COUNTER) TO OUT-RECORD
               WRITE OUT-RECORD
           END-PERFORM.
