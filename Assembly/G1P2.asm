title G1P2.ASM
; (CMSC-3100-001)
; Allan Cunningham, Evan Thompson, Caleb Ruby
; cun82935@pennwest.edu, tho86271@pennwest.edu, rub4133@pennwest.edu
INCLUDE Irvine32.inc

.data
    prompt BYTE "Enter a number or operation (+, -, *, /, X, N, U, D, V, C, Q): ", 0
    youEntered BYTE "You entered ", 0
    isValidInput BYTE 0 ; flag to indicate whether the input is valid
    isNegative BYTE 0 ; flag to indicate if there is a negative value or subtraction operation

    errormsg BYTE "ERROR", 0

    value SDWORD 0

    buffersize equ 41
    buffer byte buffersize dup(0) ; for the input string
    result byte buffersize dup(0) ; New string to store characters without spaces or tabs
    bytecount DWORD ?

    stackSize equ 8 ;constant for stack size (ik not case sensitive, just readability for me)
    stackIndex SDWORD -4    ;stack index - starts at -4 so when first item PUSHED, 1st item will be at position "0"
    numstack SDWORD stacksize dup(0)    ;stack declaration

    null equ 0
    tab equ 9

.code

pushit PROC
    push esi        ;stores original value of esi on system stack
    cmp stackindex, stacksize * 4 - 4  ;checks if stack full, -4 I think because we start at -4 as the beginning of the stack?
    jge nopush      ;if(stack == full) -> jump to "nopush"
    add stackindex, 4           ;increment index of stack 4 bytes 
    mov esi, stackindex         ;move the current index (stack position) into esi,setting top of stack
    mov numStack[esi], eax      ;mov value stored in eax to the top position of stack (using eax to pass)
    clc                         ;clear carry flag to indicate success (use JC and JNC to respond to carry flag)
    jmp endpush                 ;jump to end of procedure 
nopush: ;case where stack was full
    stc ;indicates stack was full (use JC and JNC to check)
endpush:        ;end of program
    pop esi ;restore ESI
    ret     ;return to calling procedure 
pushit ENDP 

popit PROC
    push esi ;save og value of esi
    cmp stackindex, -4   ;test if stack empty 
    jl nopop            ;jump if stack was empty 
    mov esi, stackindex ;get stackindex in esi
    mov eax, numstack[esi]      ;get top value from stack 
    sub stackindex, 4           ;lower stack index(top of stack) by 4 bytes 
    clc     ;clear carry flag to indicate sucessful pop
    jmp endpop      ;move to end of procedure 
nopop:  ;case where stack was empty 
    stc ;set carry flag to show stack was empty 
endpop:
    pop esi     ;restore esi 
    ret         ;return to calling procedure 
popit endp

addthem PROC
    push esi ; save original value of esi
    call popit ; pop the first value
    jc emptyStack ; jump if stack was empty
    mov ebx, eax ; store the value in ebx
    call popit ; pop the second value
    jc emptyStack ; jump if stack was empty
    add eax, ebx ; add the two values
    call WriteInt
    call Crlf
    call pushit ; push the result onto the stack
    jmp endAdd ; jump to the end of the procedure
emptyStack:
    mov edx, OFFSET errormsg ; point to the error message
    call WriteString ; print the error message
endAdd:
    pop esi ; restore esi
    ret ; return
addthem ENDP

subtract PROC
    push esi ; save original value of esi
    call popit ; pop the first value
    jc emptyStack ; jump if stack was empty
    mov ebx, eax ; store the first value in ebx
    call popit ; pop the second value
    jc emptyStack ; jump if stack was empty
    sub eax, ebx ; subtract the second value from the first
    call WriteInt
    call Crlf
    call pushit ; push the result onto the stack
    jmp endSubtract ; jump to the end of the procedure
emptyStack:
    mov edx, OFFSET errormsg ; point to the error message
    call WriteString ; print the error message
endSubtract:
    pop esi ; restore esi
    ret ; return
subtract ENDP

multiply PROC
    push esi ; save original value of esi
    call popit ; pop the first value
    jc emptyStack ; jump if stack was empty 
    mov ebx, eax ; store the value in ebx
    call popit ; pop the second value
    jc emptyStack ; jump if stack was empty
    imul eax, ebx ; multiply the two values
    call WriteInt
    call Crlf
    call pushit ; push the result onto the stack
    jmp endMultiply ; jump to the end of the procedure
emptyStack:
    mov edx, OFFSET errormsg ; point to the error message
    call WriteString ; print the error message
endMultiply:
    pop esi ; restore esi
    ret ; return
multiply ENDP

divide PROC
    push esi ; save original value of esi
    call popit ; pop the first value
    jc emptyStack ; jump if stack was empty
    mov ebx, eax ; store the divisor in ebx
    cmp ebx, 0 ; check if divisor is zero
    je zeroDivisor ; if divisor is zero, jump to error message
    call popit ; pop the second value
    jc emptyStack ; jump if stack was empty
    mov edx, 0 ; clear the edx register
    idiv ebx; divide eax by the value at ebx
    call WriteInt
    call Crlf
    call pushit ; push the result onto the stack
    jmp endDivide ; jump to the end of the procedure
emptyStack:
    mov edx, OFFSET errormsg ; point to the error message
    call WriteString ; print the error message
    jmp endDivide ; jump to the end of the procedure
zeroDivisor:
    mov edx, OFFSET errormsg ; point to the error message for division by zero
    call WriteString ; print the error message
endDivide:
    pop esi ; restore esi
    ret ; return
divide ENDP

exchange PROC
    push esi          ; Save original value of esi
    call popit       ; Pop the first value
    jc emptyStack       ; Jump if stack was empty
    mov ebx, eax       ; Store the first value in ebx
    call popit          ; Pop the second value
    jc emptyStack       ; Jump if stack was empty
    mov ecx, ebx        ; Store the first value in ecx
    mov ebx, eax        ; Move the second value into ebx
    mov eax, ecx        ; Move the first value into eax
    call pushit      ; Push the second value onto the stack
    mov eax, ebx        ; Put the second value into eax
    call WriteInt
    call Crlf
    call pushit         ; Push the first value onto the stack
    jmp endExchange    ; Jump to the end of the procedure
emptyStack:
    mov edx, OFFSET errormsg ; Point to the error message
    call WriteString    ; Print the error message
endExchange:
    pop esi             ; Restore esi
    ret                 ; Return
exchange ENDP

negate PROC
    push esi ; save original value of esi
    call popit ; pop the top value
    jc emptyStack ; jump if stack was empty
    neg eax ; negate the value
    call WriteInt
    call Crlf
    call pushit ; push the result onto the stack
    jmp endNegate ; jump to the end of the procedure
emptyStack:
    mov edx, OFFSET errormsg ; point to the error message
    call WriteString ; print the error message
endNegate:
    pop esi ; restore esi
    ret ; return
negate ENDP

rollup PROC
    push esi            ; Save original value of esi
    mov esi, stackIndex ; Initialize index to the top element
    mov eax, numStack[esi - 4] ; Load the 2nd stack element
    call WriteInt   ; Print the top element
    call Crlf       ; Move to the next line
    mov eax, numStack[esi] ; load the top element
    rollup_loop:
        cmp esi, 0      ; Compare index with zero
        jle end_rollup  ; If index <= 0, end loop
        mov ebx, numStack[esi - 4] ; Load the previous stack element
        mov numStack[esi], ebx ; Move the previous element up
        sub esi, 4      ; Decrement the index
        jmp rollup_loop ; Loop
    end_rollup:
        mov numStack[esi], eax ; Put the top element at the bottom of the stack
    pop esi             ; Restore esi
    ret                 ; Return
rollup ENDP


rolldown PROC
    push esi            ; Save original value of esi
    mov esi, 0          ; Initialize index to the bottom element
    mov eax, numStack[0] ; Load the bottom stack element
    call WriteInt
    call Crlf
    rolldown_loop:
        cmp esi, stackIndex ; Compare index with stack index
        jge end_rolldown   ; If index >= stack index, end loop
        mov ebx, numStack[esi + 4] ; Load the next stack element
        mov numStack[esi], ebx ; Move the next element down
        add esi, 4        ; Increment the index
        jmp rolldown_loop ; Loop
    end_rolldown:
        mov numStack[esi], eax ; Put the bottom element at the top of the stack
    pop esi             ; Restore esi
    ret                 ; Return
rolldown ENDP

clearstack PROC
    mov esi, 0 ; initialize index
clear_loop:
    cmp esi, stackSize * 4 ; compare index with stack size
    jge end_clear ; if index >= stack size, end loop
    mov numStack[esi], 0 ; set stack element to zero
    add esi, 4 ; increment the index
    jmp clear_loop ; loop
end_clear:
    mov stackIndex, -4 ; reset the stack index
    ret ; return
clearstack ENDP

viewthem PROC
    push esi ; save original value of esi
    mov esi, stackIndex ; initialize index to the last element
print_loop:
    cmp esi, 0 ; compare index with zero
    jl end_print ; if index < 0, end loop
    mov eax, numStack[esi] ; load stack element
    call WriteInt ; print the value
    call Crlf ; move to next line
    sub esi, 4 ; decrement the index
    jmp print_loop ; loop
end_print:
    pop esi ; restore esi
    ret ; return to calling procedure
viewthem ENDP


main PROC
inputloop:
    mov value, 0
    mov edi, OFFSET buffer ; Point to the beginning of the buffer
    mov ecx, SIZEOF buffer ; Specify the size of the buffer
    mov eax, 0
    mov isValidInput, 0 ; initialize the flag as false
    mov isNegative, 0 ; set the flag to false

clear_buffer_loop:
    cmp ecx, 0            ; Check if we've cleared the entire buffer
    je read_input         ; If so, proceed with input
    mov [edi], al         ; Fill the current byte with null
    inc edi               ; Move to the next byte
    dec ecx               ; Decrement the loop counter
    jmp clear_buffer_loop ; Repeat until the entire buffer is cleared

read_input:
    mov edx, OFFSET prompt
    call WriteString ; print the prompt

    mov edx, OFFSET buffer ; point to the buffer
    mov ecx, SIZEOF buffer ; specify max characters
    call ReadString ; read the input

    mov bytecount, eax ; number of characters
    mov ecx, eax       ; counter for loop

    mov edi, 0         ; initialize index
    mov esi, 0         ; initialize index for result string

Skip:
    CMP edi, ecx      ; compare index with count
    jge endloop        ; if index >= count, end loop

    mov al, buffer[edi] ; load character
    cmp al, null        ; check for null
    je endloop          ; if null, end loop

    cmp al, ' '        ; check for space
    je skipchar        ; if space, skip adding to result string

    cmp al, tab        ; check for tab
    je skipchar        ; if tab, skip adding to result string

    mov result[esi], al ; store character in string
    inc esi            ; move to next character in result string

skipchar:
    inc edi            ; move to next character in input string
    jmp Skip           ; loop

endloop:
    mov edx, OFFSET youEntered
    call WriteString
    mov result[esi], null ; add null character to the end of the result string
    mov edx, OFFSET result ; move the result string into edx
    call WriteString      ; print the result string
    call Crlf             ; move to next line

    mov ecx, SIZEOF result ; specify max characters
    mov edi, 0             ; initialize index
    jmp checkcharacters   ; call the checkcharacters procedure

    jmp inputloop ; repeat the 

    mov ecx, SIZEOF result ; specify max characters
    mov edi, 0             ; initialize index

checkcharacters:
    cmp edi, ecx           ; compare index with count
    jge end_check        ; if index >= count, end loop
    mov al, result[edi]    ; load character
    cmp al, '+'            ; check if its a +
    je is_add
    cmp al, '-'
    je checkfornegative
    cmp al, '*'            ; check if its a *
    je is_multiply
    cmp al, '/'             ; check for division
    je is_div
    cmp al, 'V'             ; check if its a V
    je is_View
    cmp al, 'X'             ; check if its an X
    je is_exchange
    cmp al, 'N'             ; check if its an N
    je is_negate
    cmp al, 'U'             ; check if its a U
    je is_rollup
    cmp al, 'D'             ; check if its a D
    je is_rolldown
    cmp al, 'C'             ; check if its a C
    je is_clearstack
    cmp al, 'Q'             ; check if its a Q
    je endprog
    cmp al, 'v'             ; check if its a v
    je is_View
    cmp al, 'x'             ; check if its an x
    je is_exchange
    cmp al, 'n'             ; check if its an n
    je is_negate
    cmp al, 'u'             ; check if its a u
    je is_rollup
    cmp al, 'd'             ; check if its a d
    je is_rolldown
    cmp al, 'c'             ; check if its a c
    je is_clearstack
    cmp al, 'q'             ; check if its a q
    je endprog
    cmp al, '0'            ; compare with digits 0-9
    je is_Digit
    cmp al, '1'
    je is_Digit
    cmp al, '2'
    je is_Digit
    cmp al, '3'
    je is_Digit
    cmp al, '4'
    je is_Digit
    cmp al, '5'
    je is_Digit
    cmp al, '6'
    je is_Digit
    cmp al, '7'
    je is_Digit
    cmp al, '8'
    je is_Digit
    cmp al, '9'
    je is_Digit
    jmp noDigit

is_Digit:
    mov isValidInput, 1 ; set the flag as true
    sub al, '0'            ; convert from ASCII to digit
    imul ebx, value, 10    ; value = value * 10
    add ebx, eax           ; ebx = ebx + digit
    mov value, ebx         ; value = ebx
    inc edi
    jmp checkcharacters

is_add:
    mov isValidInput, 1 ; set the flag as true
    call addthem ; call the addthem procedure   
    jmp inputloop

checkfornegative:
    inc edi
    mov al, result[edi]
    cmp al, '0'
    jl is_subtract
    cmp al, '9'
    jg is_subtract
    mov isNegative, 1
    jmp checkcharacters

is_subtract:
    mov isValidInput, 1
    call subtract
    jmp inputloop

is_multiply:
    mov isValidInput, 1 ; set the flag as true
    call multiply ; call the multiply procedure
    jmp inputloop

is_div:
    mov isValidInput, 1 ; set the flag as true
    call divide ; call division procedure
    jmp inputloop

is_View:
    mov isValidInput, 1 ; set the flag as true
    call viewthem
    jmp inputloop

noDigit:
    jmp end_check

is_exchange:
    mov isValidInput, 1 ; set flag to true
    call exchange
    jmp inputloop

is_negate:
    mov isValidInput, 1 ; set flag to true
    call negate
    jmp inputloop

is_rollup:
    mov isValidInput, 1 ; set flag as true
    call rollup
    jmp inputloop

is_rolldown:
    mov isValidInput, 1 ; set the flag to true
    call rolldown
    jmp inputloop

is_clearstack:
    mov isValidInput, 1 ; set flag to true
    call clearstack
    jmp inputloop

setnegative:
    mov isValidInput, 1
    neg value
    mov isNegative, 0
    jmp end_check

end_check:
    cmp isValidInput, 0 ; check if the input is valid
    je inputloop ; if not valid, jump to inputloop without pushing anything to the stack
    cmp isNegative, 1 ; check if the negative flag is set
    je setnegative
    mov eax, value
    call pushit
    call WriteInt
    call Crlf
    jmp inputloop ; repeat the input

endprog:

main ENDP
END main
