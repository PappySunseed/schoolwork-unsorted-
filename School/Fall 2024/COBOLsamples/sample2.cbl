       IDENTIFICATION DIVISION.
       PROGRAM-ID.       SENIOR.
       AUTHOR.           ROBERT GRAUER.

       ENVIRONMENT DIVISION.
       INPUT-OUTPUT SECTION.
       FILE-CONTROL.
           SELECT STUDENT-FILE     ASSIGN TO 'input2.txt'
               ORGANIZATION IS LINE SEQUENTIAL.
           SELECT PRINT-FILE       ASSIGN TO 'output2.txt'
               ORGANIZATION IS LINE SEQUENTIAL.

       DATA DIVISION.
       FILE SECTION.
       FD  STUDENT-FILE
           RECORD CONTAINS 43 CHARACTERS
           DATA RECORD IS STUDENT-IN.
       01  STUDENT-IN.
           05  STU-NAME            PIC X(25).
           05  STU-CREDITS         PIC 9(3).
           05  STU-MAJOR           PIC X(15).

       FD  PRINT-FILE
           RECORD CONTAINS 80 CHARACTERS
           DATA RECORD IS PRINT-LINE.
       01  PRINT-LINE              PIC X(80).

       WORKING-STORAGE SECTION.
       01  DATA-REMAINS-SWITCH     PIC X(2)      VALUE SPACES.

       01  HEADING-LINE.
           05  FILLER              PIC X(10)     VALUE SPACES.
           05  FILLER              PIC X(12)     VALUE 'STUDENT NAME'.
           05  FILLER              PIC X(58)    VALUE SPACES.

       01  DETAIL-LINE.
           05  FILLER              PIC X(8)      VALUE SPACES.
           05  PRINT-NAME          PIC X(25).
           05  FILLER              PIC X(47)     VALUE SPACES.

       PROCEDURE DIVISION.
       PREPARE-SENIOR-REPORT.
           OPEN INPUT  STUDENT-FILE
                OUTPUT PRINT-FILE.
           READ STUDENT-FILE
                AT END MOVE 'NO' TO DATA-REMAINS-SWITCH
           END-READ.
           PERFORM WRITE-HEADING-LINE.
           PERFORM PROCESS-RECORDS
                UNTIL DATA-REMAINS-SWITCH = 'NO'.
           CLOSE STUDENT-FILE
                 PRINT-FILE.
           STOP RUN.

       WRITE-HEADING-LINE.
           MOVE HEADING-LINE TO PRINT-LINE.
           WRITE PRINT-LINE.

       PROCESS-RECORDS.
           IF STU-CREDITS > 110 AND STU-MAJOR = 'ENGINEERING'
               MOVE STU-NAME TO PRINT-NAME
               MOVE DETAIL-LINE TO PRINT-LINE
               WRITE PRINT-LINE
           END-IF.
           READ STUDENT-FILE
               AT END MOVE 'NO' TO DATA-REMAINS-SWITCH
           END-READ.