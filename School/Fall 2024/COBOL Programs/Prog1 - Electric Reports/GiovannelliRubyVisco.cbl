      ******************************************************************
      * Author: Caleb Ruby
      * Date:   9/18/24
      * Purpose: sort input file to two output files based on if there is non-numeric data
      ******************************************************************
       IDENTIFICATION DIVISION.
       PROGRAM-ID. ELECTRIC-REPORTS.
       AUTHOR.     CALEB R. & GROUP.

       ENVIRONMENT DIVISION.

       INPUT-OUTPUT SECTION.

       FILE-CONTROL.
           SELECT INPUT-FILE     ASSIGN TO 'input.txt'
               ORGANIZATION IS LINE SEQUENTIAL.
           SELECT GOOD-REPORT       ASSIGN TO 'good.txt'
               ORGANIZATION IS LINE SEQUENTIAL.
           SELECT BAD-REPORT       ASSIGN TO 'bad.txt'
               ORGANIZATION IS LINE SEQUENTIAL.

       DATA DIVISION.
       FILE SECTION.
       FD  INPUT-FILE
           RECORD CONTAINS 43 CHARACTERS
           DATA RECORD IS IN-RECORD.
       01  IN-RECORD.
           05  FIRST-NAME            PIC X(12).
           05  LAST-NAME            PIC X(12).
           05  STREET-ADDRESS            PIC X(15).
           05  CITY            PIC X(13).
           05  STATE            PIC X(2).
           05  ACC-NUMBER            PIC X(6).
           05  PREV-READING            PIC X(5).
           05  CURRENT-READING            PIC X(5).

       FD  BAD-REPORT
           RECORD CONTAINS 80 CHARACTERS
           DATA RECORD IS BAD-OUT.
       01  BAD-OUT     PIC X(80).

       FD  GOOD-REPORT
           RECORD CONTAINS 80 CHARACTERS
           DATA RECORD IS GOOD-OUT.
       01  GOOD-OUT     PIC X(80).

       WORKING-STORAGE SECTION.
       01  EOF-SWITCH      PIC XXX  VALUE SPACES.



       01  BAD-HEADING.
           05 FILLER   PIC X(14)   VALUE 'ACCOUNT-NUMBER'.
           05 FILLER   PIC XXX     VALUE ALL '_'.
           05 FILLER   PIC X(16)   VALUE 'PREVIOUS-READING'.
           05 FILLER   PIC XXX     VALUE ALL '_'.
           05 FILLER   PIC X(15)     VALUE 'CURRENT-READING'.

        01 BAD-LINE.
           05 PRINT-ACC2               PIC X(17).
           05 PRINT-PREV-READING2      PIC X(19).
           05 PRINT-CURR-READING2      PIC X(10).

       01  GOOD-HEADING.
           05 FILLER   PIC X(9)   VALUE 'LAST-NAME'.
           05 FILLER   PIC XXXXX     VALUE ALL '_'.
           05 FILLER   PIC X(10)   VALUE 'FIRST-NAME'.
           05 FILLER   PIC XXXX     VALUE ALL '_'.
           05 FILLER   PIC X(14)   VALUE 'ACCOUNT-NUMBER'.
           05 FILLER   PIC XXX     VALUE ALL '_'.
           05 FILLER   PIC X(7)   VALUE 'ADDRESS'.
           05 FILLER   PIC X(9)     VALUE ALL '_'.
           05 FILLER   PIC X(10)   VALUE 'UNITS-USED'.

        01 GOOD-LINE.
           05 PRINT-LAST       PIC X(14).
           05 PRINT-FIRST      PIC X(14).
           05 PRINT-ACC        PIC X(17).
           05 PRINT-ADDRESS    PIC X(16).
           05 PRINT-UNITS      PIC 9(10).

       01  STRING-TO-NUM.
           05 CURRENT-TEMP      PIC X(10) VALUE ALL '0'.
           05 CURRENT-TO-NUM   REDEFINES CURRENT-TEMP PIC 9(10).
           05 PREV-TEMP         PIC X(10)    VALUE ALL '0'.
           05 PREV-TO-NUM      REDEFINES PREV-TEMP PIC 9(10).

       PROCEDURE DIVISION.
       MAIN-PROCEDURE.
           DISPLAY "Program starting...".

      *write headings & open files
           OPEN INPUT INPUT-FILE
                OUTPUT GOOD-REPORT
                OUTPUT BAD-REPORT.

           DISPLAY "EOF-SWITCH before READ: " EOF-SWITCH.
           READ INPUT-FILE
                 AT END MOVE 'YES' TO EOF-SWITCH
           END-READ.
           DISPLAY "EOF-SWITCH after READ: " EOF-SWITCH.



           MOVE GOOD-HEADING TO GOOD-OUT.
           WRITE GOOD-OUT.


           MOVE BAD-HEADING TO BAD-OUT.
           WRITE BAD-OUT.

           DISPLAY "Headings created".

      *process the input file
           DISPLAY "Processing data...".

           PERFORM PROCESS-INPUT
               UNTIL EOF-SWITCH = 'YES'.

           DISPLAY "Data sorted".
      *wrapping up, closing files
           CLOSE   GOOD-REPORT
                   INPUT-FILE
                   BAD-REPORT.
           DISPLAY "program complete.".
           STOP RUN.




      *reads input file and places data in good or bad REPORT
       PROCESS-INPUT.
           PERFORM DATA-CHECK.

           DISPLAY "EOF-SWITCH before READ: " EOF-SWITCH.
           READ INPUT-FILE
                 AT END MOVE 'YES' TO EOF-SWITCH
           END-READ.
           DISPLAY "EOF-SWITCH after READ: " EOF-SWITCH.
      *checks for bad data
       DATA-CHECK.
           DISPLAY 'checking input: ' ACC-NUMBER.
           IF ACC-NUMBER IS NUMERIC
               DISPLAY ACC-NUMBER 'Is numeric'

               DISPLAY 'checking input: ' PREV-READING
               IF PREV-READING IS NUMERIC
                   DISPLAY PREV-READING 'Is numeric'

                   DISPLAY 'checking input: ' CURRENT-READING
                   IF CURRENT-READING IS NUMERIC
                       DISPLAY CURRENT-READING 'Is numeric'
                       PERFORM WRITE-GOOD
                   ELSE
                       PERFORM WRITE-BAD
                   END-IF
               ELSE
                   PERFORM WRITE-BAD
               END-IF
           ELSE
               PERFORM WRITE-BAD
           END-IF.



      *grabs all needed data and writes to appropriate report file
       WRITE-GOOD.
           MOVE LAST-NAME TO PRINT-LAST.
           MOVE FIRST-NAME TO PRINT-FIRST.
           MOVE ACC-NUMBER TO PRINT-ACC.
           MOVE STREET-ADDRESS TO PRINT-ADDRESS.

           PERFORM TOTAL-USED.

      *     MOVE CURRENT-UNITS TO PRINT-UNITS.


           MOVE GOOD-LINE TO GOOD-OUT.
           WRITE GOOD-OUT.
      *grabs all needed data and writes to appropriate report file
       WRITE-BAD.
           MOVE ACC-NUMBER TO PRINT-ACC2.
           MOVE PREV-READING TO PRINT-PREV-READING2.
           MOVE CURRENT-READING TO PRINT-CURR-READING2.

           MOVE BAD-LINE TO BAD-OUT.
           WRITE BAD-OUT.
      *calculates total used electricity (accounting for wraparound
       TOTAL-USED.
      *       check if current reading < last reading to check for wraparound
      *            if wraparound, add the two readings for total
           MOVE CURRENT-READING TO CURRENT-TEMP.
           MOVE PREV-READING TO PREV-TEMP.

           MOVE FUNCTION NUMVAL(CURRENT-TEMP) TO CURRENT-TO-NUM.
           MOVE FUNCTION NUMVAL(PREV-TEMP) TO PREV-TO-NUM.

           IF CURRENT-TO-NUM IS LESS THAN PREV-TO-NUM
              ADD CURRENT-TO-NUM TO PREV-TO-NUM GIVING PRINT-UNITS
           ELSE
               MOVE CURRENT-TO-NUM TO PRINT-UNITS
           END-IF.




       END PROGRAM ELECTRIC-REPORTS.
