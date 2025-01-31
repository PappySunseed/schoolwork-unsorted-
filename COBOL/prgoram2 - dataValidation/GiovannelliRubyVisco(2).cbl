      ******************************************************************
      * Author: Caleb Ruby
      * Date: 10/23/2024
      * Purpose:
      * Tectonics: cobc
      ******************************************************************
       IDENTIFICATION DIVISION.
           PROGRAM-ID. COMMISSION-VALIDATION.

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
               FD INPUT-FILE
               RECORD CONTAINS 67 CHARACTERS
               DATA RECORD IS IN-RECORD.
       01      IN-RECORD.
                   05 LOCATION         PIC X(11).
                   05 BRANCH           PIC 9(4).
                   05 SALES-PERSON     PIC X(10).
                   05 CUSTOMER-NAME    PIC X(10).
                   05 SALE-DATE        PIC 9(6).
                   05 SALE-AMMOUNT     PIC 9(6).
                   05 COMMISSION-RATE  PIC 999.
                   05 CAR-MODEL        PIC X(13).
                   05 CAR-YEAR         PIC 9(4).

               FD  BAD-REPORT
               RECORD CONTAINS 80 CHARACTERS
               DATA RECORD IS BAD-OUT.
       01      BAD-OUT     PIC X(120).

               FD  GOOD-REPORT
               RECORD CONTAINS 80 CHARACTERS
               DATA RECORD IS GOOD-OUT.
       01      GOOD-OUT     PIC X(80).


           WORKING-STORAGE SECTION.
       01      EOF-SWITCH      PIC XXX  VALUE SPACES.
       01      BAD-SWITCH      PIC XXX VALUE SPACES.


       01 TEMP-DAY PIC     99.
           88 VALID-28 VALUES 1 THROUGH 29.
           88 VALID-30 VALUES 1 THROUGH 30.
           88 VALID-31 VALUES 1 THROUGH 31.
       01 TEMP-MONTH PIC   99.
           88 VALID-MONTH VALUES 1 THROUGH 12.
           88 MONTH-28-DAYS VALUE 2.
           88 MONTH-30-DAYS VALUES 4,6,9,11.
           88 MONTH-31-DAYS VALUES 1,3,5,7,8,10,12.
       01 TEMP-YEAR PIC    99.


       01 TEMP-COMMISSION-RATE PIC 999.
           88 VALID-RATE VALUES 0 THROUGH 100.

       01 TEMP-CAR-YEAR PIC 9999.
           88 VALID-CAR-YEAR VALUES 1930 THROUGH 2024.

       01 ERROR-MESSAGE PIC X(38).

       PROCEDURE DIVISION.
       MAIN-PROCEDURE.
           PERFORM OPEN-FILES.

           PERFORM UNTIL EOF-SWITCH = 'YES'
               PERFORM PROCESS-INPUT
           END-PERFORM.

           PERFORM CLOSE-FILES.

           STOP RUN.

      *procedure to open necessary files
       OPEN-FILES.
           OPEN INPUT INPUT-FILE
                OUTPUT GOOD-REPORT
                OUTPUT BAD-REPORT.
       CLOSE-FILES.
           CLOSE   GOOD-REPORT
                   INPUT-FILE
                   BAD-REPORT.
      *reads data, calls validation function
       PROCESS-INPUT.
           READ INPUT-FILE
                 AT END MOVE 'YES' TO EOF-SWITCH
           END-READ.

           IF EOF-SWITCH NOT EQUAL 'YES'
               PERFORM VALIDATION
           END-IF.

       VALIDATION.
      *checking for missing fields
             IF LOCATION = SPACES OR
                 BRANCH = SPACES OR
                 SALES-PERSON = SPACES OR
                 CUSTOMER-NAME = SPACES OR
                 SALE-AMMOUNT = SPACES OR
                 COMMISSION-RATE = SPACES OR
                 CAR-MODEL = SPACES OR
                 CAR-YEAR = SPACES
               THEN
               MOVE 'INCOMING RECORD MISSING DATA:' TO ERROR-MESSAGE
               STRING ERROR-MESSAGE DELIMITED BY SIZE
               IN-RECORD DELIMITED BY SIZE
               INTO BAD-OUT

               WRITE BAD-OUT

               MOVE SPACES TO BAD-OUT

               MOVE 'BAD' TO BAD-SWITCH
               END-IF.

      *checking for numeric data in numeric fields
              IF BRANCH NOT NUMERIC OR
                 SALE-DATE NOT NUMERIC OR
                 SALE-AMMOUNT NOT NUMERIC OR
                 COMMISSION-RATE NOT NUMERIC OR
                 CAR-YEAR NOT NUMERIC
               THEN
              MOVE 'NON-NUMERIC DATA IN NUMERIC FIELD:' TO ERROR-MESSAGE
               STRING ERROR-MESSAGE
               DELIMITED BY SIZE
               IN-RECORD DELIMITED BY SIZE
               INTO BAD-OUT

               WRITE BAD-OUT

               MOVE SPACES TO BAD-OUT
               MOVE 'BAD' TO BAD-SWITCH
               END-IF.

      *checking for valid dates
         IF SALE-DATE NUMERIC
           MOVE SALE-DATE(1:2) TO TEMP-DAY
           MOVE SALE-DATE(3:2) TO TEMP-MONTH
           MOVE SALE-DATE(5:2) TO TEMP-YEAR

           IF NOT VALID-MONTH
               MOVE 'INVALID MONTH:' TO ERROR-MESSAGE
               STRING ERROR-MESSAGE
               DELIMITED BY SIZE
               IN-RECORD DELIMITED BY SIZE
               INTO BAD-OUT

               WRITE BAD-OUT
               MOVE SPACES TO BAD-OUT
               MOVE 'BAD' TO BAD-SWITCH
               END-IF

           IF VALID-31
               IF MONTH-28-DAYS AND NOT VALID-28
                   MOVE 'INVALID DAY:' TO ERROR-MESSAGE
                   STRING ERROR-MESSAGE
                   DELIMITED BY SIZE
                   IN-RECORD DELIMITED BY SIZE
                   INTO BAD-OUT

                       WRITE BAD-OUT
                   MOVE SPACES TO BAD-OUT
                   MOVE 'BAD' TO BAD-SWITCH
               END-IF

               IF MONTH-30-DAYS AND NOT VALID-30
                   MOVE 'INVALID DAY:' TO ERROR-MESSAGE
                   STRING ERROR-MESSAGE
                   DELIMITED BY SIZE
                   IN-RECORD DELIMITED BY SIZE
                   INTO BAD-OUT

                       WRITE BAD-OUT
                   MOVE SPACES TO BAD-OUT
                   MOVE 'BAD' TO BAD-SWITCH
               END-IF
           ELSE
               MOVE 'INVALID DAY:' TO ERROR-MESSAGE
               STRING ERROR-MESSAGE
               DELIMITED BY SIZE
               IN-RECORD DELIMITED BY SIZE
               INTO BAD-OUT

               WRITE BAD-OUT
               MOVE SPACES TO BAD-OUT
               MOVE 'BAD' TO BAD-SWITCH
           END-IF

           MOVE ZEROES TO TEMP-MONTH
           TEMP-DAY
           TEMP-YEAR
         END-IF.
      *checking commission rate
         IF COMMISSION-RATE NUMERIC
           MOVE COMMISSION-RATE TO TEMP-COMMISSION-RATE

           IF NOT VALID-RATE
               MOVE 'INVALID COMMISSION-RATE:' TO ERROR-MESSAGE
               STRING ERROR-MESSAGE
               DELIMITED BY SIZE
               IN-RECORD DELIMITED BY SIZE
               INTO BAD-OUT

               WRITE BAD-OUT
               MOVE SPACES TO BAD-OUT
               MOVE 'BAD' TO BAD-SWITCH
           END-IF

           MOVE ZEROES TO TEMP-COMMISSION-RATE
         END-IF.
      *checking for reasonable car year
         IF CAR-YEAR NUMERIC
           MOVE CAR-YEAR TO TEMP-CAR-YEAR

           IF NOT VALID-CAR-YEAR
               MOVE 'INVALID CAR-YEAR:' TO ERROR-MESSAGE
               STRING ERROR-MESSAGE
               DELIMITED BY SIZE
               IN-RECORD DELIMITED BY SIZE
               INTO BAD-OUT

               WRITE BAD-OUT
               MOVE SPACES TO BAD-OUT
               MOVE 'BAD' TO BAD-SWITCH
           END-IF

           MOVE ZEROES TO TEMP-CAR-YEAR
         END-IF.


           IF BAD-SWITCH = SPACES
               PERFORM WRITE-GOOD
           END-IF.

           MOVE SPACES TO BAD-SWITCH.
       WRITE-GOOD.
           STRING LOCATION DELIMITED BY SIZE
               BRANCH DELIMITED BY SIZE
               SALES-PERSON DELIMITED BY SIZE
               CUSTOMER-NAME DELIMITED BY SIZE
               SALE-DATE DELIMITED BY SIZE
               SALE-AMMOUNT DELIMITED BY SIZE
               COMMISSION-RATE DELIMITED BY SIZE
               CAR-MODEL DELIMITED BY SIZE
               CAR-YEAR DELIMITED BY SIZE
               INTO GOOD-OUT
           END-STRING.


           WRITE GOOD-OUT.

           MOVE SPACES TO GOOD-OUT.
