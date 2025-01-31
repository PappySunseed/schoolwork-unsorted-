title G1P1.ASM
; (CMSC-3100-001)
; Allan Cunningham, Evan Thompson, Caleb Ruby
; cun82935@pennwest.edu, tho86271@pennwest.edu, rub4133@pennwest.edu
INCLUDE Irvine32.inc

.data
datamessage BYTE "Invalid entry detected, displaying calculated data:", 0
exitmessage BYTE "0 Valid entries detected, terminating program.", 0
newLine BYTE 10, 0 ; empty string to make a new line
buffer BYTE 21 DUP(0) ; input buffer
byteCount DWORD ? ; holds counter
entryCount DWORD 0 ; holds entry counter
sum DWORD 0 ; variable to store the sum
average DWORD 0 ; variable to store the average
remainder DWORD 0 ;stores remainder
prompt BYTE "Enter an integer value within the range 0-100: ", 0
; labels for displaying data
sumLabel BYTE "Sum: ", 0
countLabel BYTE "Total Count: ", 0
averageLabel BYTE "Average: ", 0
remainderLabel BYTE "Remainder: ", 0

.code
main PROC
    mov ebx, 0  ; reset sum to 0
    mov entryCount, 0 ; reset entry count to 0

prompt_loop:
    mov edx, OFFSET prompt
    call WriteString ; print the prompt

    mov edx, OFFSET buffer ; point to the buffer
    mov ecx, SIZEOF buffer ; specify max characters
    call ReadString ; read the input

    mov byteCount, eax ; number of characters
    mov edx, OFFSET buffer
    mov ecx, eax
    call ParseInteger32 ; convert string to 32-bit integer

    CMP eax, 0 ; compare the integer with 0
    JL Calculate_data ; leave input loop if less than 0
    CMP eax, 100 ; compare the integer with 100
    JG Calculate_data ; leave input loop if greater than 100
    ; else, continue

    ; Adding section
    add ebx, eax    ; adds most recently entered integer
    inc entryCount ; update entry counter

    ; Prints the integer
    mov edx, OFFSET buffer
    mov ecx, byteCount
    call WriteInt ; write the integer

    mov edx, OFFSET newLine
    call WriteString ; moves to a new line

    JMP prompt_loop ; jumps to the beginning of the input loop

Calculate_data:
    CMP entryCount, 0 ; check if 0 entries were made
    JE exit_process ; if there are 0, exit the program
    ; else, continue

    ; Calculate average
    mov eax, 0
    mov eax, ebx ; copy the sum to eax
    mov edx, 0 ; clear edx for the division
    div entryCount ; eax = sum / entryCount     edx = remainder
    mov remainder, edx ;stores remainder

    mov sum, ebx ; save the sum
    mov average, eax ; save the average

    ; Display results
    mov edx, OFFSET newLine
    call WriteString ; print a blank line

    mov edx, OFFSET datamessage
    call WriteString ; display a message
    call Crlf

    mov edx, OFFSET sumLabel
    call WriteString ; display the sum label
    mov eax, sum
    call WriteInt ; display the integer

    mov edx, OFFSET newLine
    call WriteString ; print a blank line

    mov edx, OFFSET countLabel
    call WriteString ; display the total count label
    mov eax, entryCount
    call WriteInt ; display the integer

    mov edx, OFFSET newLine
    call WriteString ; print a blank line

    mov edx, OFFSET averageLabel
    call WriteString ; display the average label
    mov eax, average
    call WriteInt ; display the integer

    mov edx, OFFSET newLine
    call WriteString ; print a blank line

    mov edx, OFFset remainderLabel
    call WriteString
    mov eax, remainder
    call WriteInt

    mov edx, OFFSET newLine
    call WriteString ; print a blank line
    mov edx, OFFSET newLine
    call WriteString ; print a blank line

    JMP main ; return to the beginning of the program

exit_process:
    mov edx, OFFSET newLine
    call WriteString ; print a blank line

    mov edx, OFFSET exitmessage
    call WriteString ; display an exit message

    mov edx, OFFSET newLine
    call WriteString ; print a blank line

    invoke ExitProcess, 0 ; exit with code 0

main ENDP
END main
