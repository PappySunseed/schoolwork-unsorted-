title G1P2.ASM
; (CMSC-3100-001)
; Allan Cunningham, Evan Thompson, Caleb Ruby
; cun82935@pennwest.edu, tho86271@pennwest.edu, rub4133@pennwest.edu
INCLUDE Irvine32.inc

.data
    prompt BYTE "Enter Something:", 0

    buffersize equ 41
    buffer byte buffersize dup(0) ; for the input string
    result byte buffersize dup(0) ; New string to store characters without spaces or tabs
    bytecount DWORD ?
    null equ 0
    tab equ 9

.code

main PROC

inputloop:
    mov edi, OFFSET buffer ; Point to the beginning of the buffer
    mov ecx, SIZEOF buffer ; Specify the size of the buffer
    mov eax, 0

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
    mov result[esi], null ; add null character to the end of the result strint
                          ; it wouldnt work properly unless I did this
    mov edx, OFFSET result ; move the result string into edx
    call WriteString      ; print the result string
    call Crlf             ; move to next line

    jmp inputloop ; repeat the input loop

endprog:

main ENDP
END main
