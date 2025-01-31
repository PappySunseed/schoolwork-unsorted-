Include Irvine32.inc

title G1P4 Network Simulator

;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
; Program 4 : Network Simulator
;(CMSC-3100-001 Spring 2024) WRITTEN BY
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
; Caleb Ruby        |  rub4133@pennwest.edu
; Evan Thompson     | tho86271@pennwest.edu 
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.data
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~
;DEFINING PACKET DATA OFFSETS
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Destination equ 0   ;target offset 
Sender equ 1        ;last sender offset 
Origin equ 2        ;source offset 
TTL equ 3           ;time to live offset 
Received equ 4      ;receive time offset 
PacketSize equ 6    ;definition of packet size (bytes)

Connection equ 0 ; offset to pointer to the connected node
XMT equ 4 ; offset to the transmit buffer pointer
RCV equ 8 ; offset to receive buffer pointer

QueueSize equ 10

echof BYTE false ; echo / no echo flag
time WORD 0 ; system time
newpackets word 0 ; number of new packets generated
generatedpackets word 0 ; number of generated packets
totalpackets word 0 ; number of total generated packets
activepackets word 1 ; number of active packets
receivedpackets word 0 ; number of packets received by destination
totalhops word 0 ; total hops of packets to reach destination
totaltime word 0 ; total time of packets to reach the destination
avghops dword 0 ; average hops of packets to reach destination
MaxHops byte 6 ; maximum number of hops
defaultHops byte 6 ; default number of hops

tempPacket byte PacketSize dup(0) ; temp packet buffer
initPacket byte PacketSize dup(0) ; initial packet

MessagePointer dword ?
NodePointer dword ?
sendPOInter dword ?
QueueAddress dword ?
inPtrOffset equ 6
outPtrOffset equ 10
queueAddressOffset equ 2

queueEmpty_flag byte ?
messageAccepted_flag byte 0
validNodeInput_flag byte 0

;~~~~~~~~~~~
;echo data 
 echoPrompt db "Do you want local echo to be turned on? (y/n): ", 0
 echoInvalid db "Invalid input. Please enter y or n.", 0
 yes db "y", 0
 no db "n", 0
 localEcho byte ?


;~~~~~~~~
;MESSAGES
;~~~~~~~~
PromptOutputFile BYTE "Enter output file name:  ", 0
filebuffersize equ 81
fileName BYTE filebuffersize dup(0)
fileBuffer byte filebuffersize dup(0) ; file buffer
outFileHandle DWORD ?
FileErrorMessage BYTE "ERROR: INVALID FILE", 0
bytesread DWORD 0
fileWriteMsg byte "Issue writing to file", 0
newlineChar BYTE 0Ah  ; Define the newline characternewlineChar BYTE 0Ah  ; Define the newline character

current_node BYTE "Node:  ", 0
is_connected_to BYTE "Connected to  ", 0
prompt_destination BYTE "Enter destination node:    ", 0
prompt_origin BYTE "Enter origin node:  ", 0
prompt_TTL BYTE "Enter time to live:    ", 0

sendernode byte "Sender Node:   ", 0
sentto byte "       Message sent to Node:  ", 0
msgAcceptedBy byte "Message accepted by Node:   ", 0

currentTimeis byte "Time is  ", 0
num_generatedpackets byte "New packets generated this step:  ", 0

buffersize equ 2
buffer BYTE buffersize dup(0) ; input buffer

;~~~~~~~~~~~~~~~
;output messages 
msgStarts byte "Message started from node: ", 0
msgRcvd byte "  Message received by node: ", 0
msgDied BYTE ":(      Message has died from node: ", 0
totalMsgsOutp BYTE "Total Messages: ",0
totalMsgs BYTE 0
;avgHops BYTE "Average number of hops: ", 0

;~~~~~~~~~~~~~~~~~~~~~~~~
;DEFINING TRANSMIT QUEUES
;~~~~~~~~~~~~~~~~~~~~~~~~
; Transmit Queues
QueueA BYTE QueueSize*PacketSize dup(0) ; space for Queue A
QueueB BYTE QueueSize*PacketSize dup(0) ; space for Queue B
QueueC BYTE QueueSize*PacketSize dup(0) ; space for Queue C
QueueD BYTE QueueSize*PacketSize dup(0) ; space for Queue D
QueueE BYTE QueueSize*PacketSize dup(0) ; space for Queue E
QueueF BYTE QueueSize*PacketSize dup(0) ; space for Queue F

;~~~~~~~~~~~~~~~~~~~~~~~~~~~~
;DEFINING BUFFERS FOR PACKETS
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~
; Buffers for node A
AXMTB label BYTE ; A transmit buffer to B label to a byte space
BRCVA BYTE PacketSize dup(0) ; B receive buffer from A PacketSize bytes
AXMTE label BYTE ; A transmit buffer to E label to a byte space
ERCVA BYTE PacketSize dup(0) ; E receive buffer from A PacketSize bytes

; Buffers for node B
BXMTA label BYTE ; B transmit buffer to A label to a byte space
ARCVB BYTE PacketSize dup(0) ; A receive buffer from B PacketSize bytes
BXMTC label BYTE ; B transmit buffer to C label to a byte space
CRCVB BYTE PacketSize dup(0) ; C receive buffer from B PacketSize bytes
BXMTF label BYTE ; B transmit buffer to F label to a byte space
FRCVB BYTE PacketSize dup(0) ; F receive buffer from B PacketSize bytes

; Buffers for node C
CXMTB label BYTE ; C transmit buffer to B label to a byte space
BRCVC BYTE PacketSize dup(0) ; B receive buffer from C PacketSize bytes
CXMTD label BYTE ; C transmit buffer to D label to a byte space
DRCVC BYTE PacketSize dup(0) ; D receive buffer from C PacketSize bytes
CXMTE label BYTE ; C transmit buffer to E label to a byte space
ERCVC BYTE PacketSize dup(0) ; E receive buffer from C PacketSize bytes

; Buffers for node D
DXMTC label BYTE ; D transmit buffer to C label to a byte space
CRCVD BYTE PacketSize dup(0) ; C receive buffer from D PacketSize bytes
DXMTF label BYTE ; D transmit buffer to F label to a byte space
FRCVD BYTE PacketSize dup(0) ; F receive buffer from D PacketSize bytes

; Buffers for node E
EXMTA label BYTE ; E transmit buffer to A label to a byte space
ARCVE BYTE PacketSize dup(0) ; A receive buffer from E PacketSize bytes
EXMTC label BYTE ; E transmit buffer to C label to a byte space
CRCVE BYTE PacketSize dup(0) ; C receive buffer from E PacketSize bytes
EXMTF label BYTE ; E transmit buffer to F label to a byte space
FRCVE BYTE PacketSize dup(0) ; F receive buffer from E PacketSize bytes

; Buffers for node F
FXMTB label BYTE ; F transmit buffer to B label to a byte space
BRCVF BYTE PacketSize dup(0) ; B receive buffer from F PacketSize bytes
FXMTE label BYTE ; F transmit buffer to E label to a byte space
ERCVF BYTE PacketSize dup(0) ; E receive buffer from F PacketSize bytes
FXMTD label BYTE ; F transmit buffer to D label to a byte space
DRCVF BYTE PacketSize dup(0) ; D receive buffer from F PacketSize bytes

;~~~~~~~~~~~~~~~~~~~~~
;OFFSETS FOR NODE DATA
;~~~~~~~~~~~~~~~~~~~~~
NumConnectionsOffset equ 1 ; Offset for number of connections in a node
NameOffset equ 0
NodePositionOffset equ sizeof current_node - 2
ConnectionPositionOffset equ sizeof is_connected_to - 2

;~~~~~~~~~~~~~~~~~~~~~~~~~
;FIXED SIZES FOR NODE DATA
;~~~~~~~~~~~~~~~~~~~~~~~~~
ConnectionSize equ 12
NodeMinimunSize equ 14

;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
;DEFINING NETWORK NODE STRUCTURES
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Network label byte ;entry to start of network
; Node structure for node A
NodeA BYTE 'A'
    BYTE 2 ; Number of connections
    DWORD QueueA ; Address of Queue A
    DWORD QueueA ; In Pointer initialized to Queue A
    DWORD QueueA ; Out pointer initialized to Queue A
    ; Connection information
    ; Connection 1: A to B
    DWORD NodeB ; Pointer to connected node (B)
    DWORD AXMTB ; Pointer to transmit buffer from A to B
    DWORD BRCVA ; Pointer to receive buffer from B to A
    ; Connection 2: A to E
    DWORD NodeE ; Pointer to connected node (E)
    DWORD AXMTE ; Pointer to transmit buffer from A to E
    DWORD ERCVA ; Pointer to receive buffer from E to A

; Node structure for node B
NodeB BYTE 'B'
    BYTE 3 ; Number of connections
    DWORD QueueB ; Address of Queue B
    DWORD QueueB ; In Pointer initialized to Queue B
    DWORD QueueB ; Out pointer initialized to Queue B
    ; Connection information
    ; Connection 1: B to A
    DWORD NodeA ; Pointer to connected node (A)
    DWORD BXMTA ; Pointer to transmit buffer from B to A
    DWORD ARCVB ; Pointer to receive buffer from A to B
    ; Connection 2: B to C
    DWORD NodeC ; Pointer to connected node (C)
    DWORD BXMTC ; Pointer to transmit buffer from B to C
    DWORD CRCVB ; Pointer to receive buffer from C to B
    ; Connection 3: B to F
    DWORD NodeF ; Pointer to connected node (F)
    DWORD BXMTF ; Pointer to transmit buffer from B to F
    DWORD FRCVB ; Pointer to receive buffer from F to B

; Node structure for node C
NodeC BYTE 'C'
    BYTE 3 ; Number of connections
    DWORD QueueC ; Address of Queue C
    DWORD QueueC ; In Pointer initialized to Queue C
    DWORD QueueC ; Out pointer initialized to Queue C
    ; Connection information
    ; Connection 1: C to B
    DWORD NodeB ; Pointer to connected node (B)
    DWORD CXMTB ; Pointer to transmit buffer from C to B
    DWORD BRCVC ; Pointer to receive buffer from B to C
    ; Connection 2: C to D
    DWORD NodeD ; Pointer to connected node (D)
    DWORD CXMTD ; Pointer to transmit buffer from C to D
    DWORD DRCVC ; Pointer to receive buffer from D to C
    ; Connection 3: C to E
    DWORD NodeE ; Pointer to connected node (E)
    DWORD CXMTE ; Pointer to transmit buffer from C to E
    DWORD ERCVC ; Pointer to receive buffer from E to C

; Node structure for node D
NodeD BYTE 'D'
    BYTE 2 ; Number of connections
    DWORD QueueD ; Address of Queue D
    DWORD QueueD ; In Pointer initialized to Queue D
    DWORD QueueD ; Out pointer initialized to Queue D
    ; Connection information
    ; Connection 1: D to C
    DWORD NodeC ; Pointer to connected node (C)
    DWORD DXMTC ; Pointer to transmit buffer from D to C
    DWORD CRCVD ; Pointer to receive buffer from C to D
    ; Connection 2: D to F
    DWORD NodeF ; Pointer to connected node (F)
    DWORD DXMTF ; Pointer to transmit buffer from D to F
    DWORD FRCVD ; Pointer to receive buffer from F to D

; Node structure for node E
NodeE BYTE 'E'
    BYTE 3 ; Number of connections
    DWORD QueueE ; Address of Queue E
    DWORD QueueE ; In Pointer initialized to Queue E
    DWORD QueueE ; Out pointer initialized to Queue E
    ; Connection information
    ; Connection 1: E to A
    DWORD NodeA ; Pointer to connected node (A)
    DWORD EXMTA ; Pointer to transmit buffer from E to A
    DWORD ARCVE ; Pointer to receive buffer from A to E
    ; Connection 2: E to C
    DWORD NodeC ; Pointer to connected node (C)
    DWORD EXMTC ; Pointer to transmit buffer from E to C
    DWORD CRCVE ; Pointer to receive buffer from C to E
    ; Connection 3: E to F
    DWORD NodeF ; Pointer to connected node (F)
    DWORD EXMTF ; Pointer to transmit buffer from E to F
    DWORD FRCVE ; Pointer to receive buffer from F to E

; Node structure for node F
NodeF BYTE 'F'
    BYTE 3 ; Number of connections
    DWORD QueueF ; Address of Queue F
    DWORD QueueF ; In Pointer initialized to Queue F
    DWORD QueueF ; Out pointer initialized to Queue F
    ; Connection information
    ; Connection 1: F to B
    DWORD NodeB ; Pointer to connected node (B)
    DWORD FXMTB ; Pointer to transmit buffer from F to B
    DWORD BRCVF ; Pointer to receive buffer from B to F
    ; Connection 2: F to D
    DWORD NodeD ; Pointer to connected node (D)
    DWORD FXMTD ; Pointer to transmit buffer from F to D
    DWORD DRCVF ; Pointer to receive buffer from D to F
    ; Connection 3: F to E
    DWORD NodeE ; Pointer to connected node (E)
    DWORD FXMTE ; Pointer to transmit buffer from F to E
    DWORD ERCVF ; Pointer to receive buffer from E to F
    endofnodes DWORD endofnodes

.code

MainLoop PROC
    pushad

    mov NodePointer, offset NodeA
    mov QueueAddress, offset NodeA

    mov edi, offset initPacket
    mov NodePointer, offset NodeA ; point to node A
    mov bl, Sender[edi] ; get source node
    mov edi, NodePointer ; get current node pointer

    findSource: ; locate source Node
	    cmp byte ptr NameOffset[edi], bl ; check if this is the source node
	    je finishfind ; found the source node
	    mov ecx, 0 ; clear ecx
	    mov cl, NumConnectionsOffset[edi] ; get number of connections
	    add edi, NodeMinimunSize ; move to connection space of structure
	    mov eax, ConnectionSize ; get size of each connection
	    mul ecx ; determine size of all bl connections
	    add edi, eax
	    mov NodePointer, edi ; update nodepointer with new node
	    cmp edi, endofnodes ; test for end of nodes
	    jl findSource ; check next node
	    mov NodePointer, offset NodeA ; requested node not found, use Node A
	    finishfind:
	    	mov MessagePointer, offset initPacket ; put init packet address in message address
            mov sendPOinter, edi

            ;print starting node
            mov edi, NodePointer
            mov edx, offset msgStarts ; get source node: message address
	        mov eax, sizeof msgStarts ; get size of the source node message
	        add edx, eax ; add together to point to the end
	        sub edx, 2 ; adjust to node name position in string
	        mov al, NameOffset[edi] ; get node name
            mov [edx], al ; put node name into message

                ; print message
                mov edx, offset msgStarts
                mov ecx, sizeof msgStarts
                call PrintMessage


            call putit ; copy message into node transmit queue



    main_loop:
    call PrintTime
    call TransmitLoop
    call printnewpackets
    inc time
    call ReceiveLoop ; check each node to see if the message received is at the destination
    cmp messageAccepted_flag, 1
    je done
    jmp main_loop
    done:
    popad
    ret
MainLoop ENDP

TransmitLoop PROC
    pushad
    call CheckTransmitQueues ; check each node's transmit queues, send messages out to their connections
    popad
    ret
TransmitLoop ENDP

CheckTransmitQueues PROC
    pushad

    mov NodePointer, offset NodeA ; Start from the first node
    mov edi, NodePointer

CheckNextNode:
    ; Check if the current node's transmit queue is empty
    mov NodePointer, edi
    mov bl, NameOffset[edi]
    call queueEmpty
    cmp queueEmpty_flag, 0 ; if flag is 0, there is nothing in the transmit queue
    je NextNode ; If the queue is empty, move to the next node

    ; If the queue is not empty, send the message from the transmit queue
    mov edi, NodePointer
    mov edx, offset sendernode ; get source node: message address
	mov eax, sizeof sendernode ; get size of the source node message
	add edx, eax ; add together to point to the end
	sub edx, 2 ; adjust to node name position in string
	mov al, byte ptr NameOffset[edi] ; get node name
    mov [edx], al ; put node name into message

    ; print message
    mov edx, offset sendernode
    mov ecx, sizeof sendernode
    
    call PrintMessage

    call SendToConnections

NextNode:
    ; Move to the next node
    mov cl, NumConnectionsOffset[edi] ; put number of connections into cl
	add edi, NodeMinimunSize ; move to connection space of structure
	mov eax, ConnectionSize ; get size of each connection
	mul ecx ; determine size of all bl connections
	add edi, eax ; move to the next node
	mov NodePointer, edi ; update nodepointer with new node
	cmp edi, endofnodes ; test for end of nodes
    jl CheckNextNode ; If not end of nodes, check the next node

    popad
    ret
CheckTransmitQueues ENDP

SendToConnections PROC
    pushad
    mov generatedpackets, 0
    mov ecx, NodePointer ; original node stored for later
    mov edi, NodePointer ; move the current node into edx
    mov ebx, offset initPacket
    mov dl, NameOffset[edi]
    mov byte ptr Sender[ebx], dl
    dec byte ptr TTL[ebx]
    cmp byte ptr TTL[ebx], 0
    jg continue
    jmp done
    continue:
    mov al, NumConnectionsOffset[edi] ; number of connections into al
    add edi, NodeMinimunSize ; move edx to the first connected node
    mov bl, 0 ; number of connections processed
    checkdone:
        cmp bl, al ; while number of connections processed less that total number of connections
        jl NextConnection
        jmp done
    NextConnection:
        mov edx, [edi]       ; Load the value of the connected node into eax
        mov NodePointer, edx ; put connected node into NodePointer

        cmp localEcho, 0
        jne send

        cmp sendPointer, edx
        je noSend

        send:
        call putit ; put the message into the connected node
        inc generatedpackets
        inc bl
        add edi, ConnectionSize ; move to the next connection
        call PrintSentTo
        call receivedPrint
        jmp checkdone

        noSend:
         call putit ; put the message into the connected node
            inc generatedpackets
            inc bl
            add edi, ConnectionSize ; move to the next connection
            jmp checkdone
    done:
    mov NodePointer, ecx
    mov sendPOinter, ecx
    call printDead
    call removeit ; remove the message from the current nodes queue

    popad
    ret
SendToConnections ENDP

printDead proc
pushad
mov edi, NodePointer
            mov edx, offset msgDied ; get source node: message address
	        mov eax, sizeof msgDied ; get size of the source node message
	        add edx, eax ; add together to point to the end
	        sub edx, 2 ; adjust to node name position in string
	        mov al, NameOffset[edi] ; get node name
            mov [edx], al ; put node name into message

                ; print message
                mov edx, offset msgDied
                mov ecx, sizeof msgDied
                call PrintMessage
popad
ret
printDead endp

printnewpackets PROC
     pushad

    ; Convert time to string
    mov eax, dword ptr [generatedpackets]  ; Load the integer value of generatedpackets into EAX
    mov ebx, 10                 ; Divisor for decimal conversion
    mov ecx, offset num_generatedpackets + sizeof num_generatedpackets - 1 ; Point ECX to the end of the string
    add ecx, 1                  ; Move ECX to the last character position
    mov byte ptr [ecx], 0      ; Null-terminate the string
    dec ecx                     ; Move ECX to the position before the null terminator

; we need to convert time from an integer to a string to add it to the end of the string
convert_loop:
    mov edx, 0                  ; Clear EDX for division
    div ebx                     ; Divide EAX by 10, quotient in EAX, remainder in EDX
    add dl, '0'                 ; Convert remainder to ASCII character
    dec ecx                     ; Move buffer pointer back
    mov [ecx], dl               ; Store ASCII character in buffer
    cmp eax, 0               ; Check if quotient is zero
    jne convert_loop            ; If not zero, continue looping

    ; Print message
    mov edx, offset num_generatedpackets
    mov ecx, sizeof num_generatedpackets
    call PrintMessage
    popad
    ret
printnewpackets ENDP

removeit PROC
    pushad
    mov edx, NodePointer
    mov eax, OutPtrOffset[edx]  ; Get current out pointer
    add eax, PacketSize         ; Move out pointer forward by message size
    mov ebx, queueAddressOffset[edx] ; Start of queue
    add ebx, QueueSize * PacketSize ; End of queue
    cmp eax, ebx                ; Is out pointer past the end of the queue?
    jl updateOutPtr            ; Not past the end
    mov eax, queueAddressOffset[edx] ; Get start of queue
updateOutPtr:
    mov OutPtrOffset[edx], eax ; Update out pointer
    popad
    ret
removeit ENDP

PrintSentTo PROC
    pushad
    mov edi, NodePointer
    mov edx, offset sentto ; get source node: message address
	mov eax, sizeof sentto ; get size of the source node message
	add edx, eax ; add together to point to the end
	sub edx, 2 ; adjust to node name position in string
	mov al, NameOffset[edi] ; get node name
    mov [edx], al ; put node name into message

    ; print message
    mov edx, offset sentto
    mov ecx, sizeof sentto
    call PrintMessage
    popad
    ret
PrintSentTO ENDP 

PrintTime PROC
    pushad

    ; Convert time to string
    mov eax, dword ptr [time]  ; Load the integer value of time into EAX
    mov ebx, 10                 ; Divisor for decimal conversion
    mov ecx, offset currentTimeis + sizeof currentTimeis - 1 ; Point ECX to the end of the currentTimeis string
    add ecx, 1                  ; Move ECX to the last character position
    mov byte ptr [ecx], 0      ; Null-terminate the string
    dec ecx                     ; Move ECX to the position before the null terminator

; we need to convert time from an integer to a string to add it to the end of the currentTimeis string
convert_loop:
    mov edx, 0                  ; Clear EDX for division
    div ebx                     ; Divide EAX by 10, quotient in EAX, remainder in EDX
    add dl, '0'                 ; Convert remainder to ASCII character
    dec ecx                     ; Move buffer pointer back
    mov [ecx], dl               ; Store ASCII character in buffer
    cmp eax, 0               ; Check if quotient is zero
    jne convert_loop            ; If not zero, continue looping

    ; Print message
    mov edx, offset currentTimeis
    mov ecx, sizeof currentTimeis
    call PrintMessage

    popad
    ret
PrintTime ENDP

CheckAcceptedMessage PROC
    pushad
    call queueEmpty
    cmp queueEmpty_flag, 1
    je HasMessages
    jmp NoMessageAccepted

HasMessages:
    ; Get the current node's pointer
    mov edi, NodePointer
    mov al, NameOffset[edi]

    mov edx, queueAddressOffset[edi]
    mov ecx, QueueSize * PacketSize
    add ecx, edx

CheckNextMessage:
    ; Compare the 'Destination' field of the message with the name of the current node
    mov bl, Destination[edx]
    cmp bl, al
    je MessageAccepted ; If the destination matches the current node, message accepted

    ; Move to the next message in the transmit queue
    add edx, PacketSize
    cmp edx, ecx
    jge NoMessageAccepted ; If reached end of transmit queue, no message accepted
    jmp CheckNextMessage ; Continue checking next message

MessageAccepted:
    mov messageAccepted_flag, 1

    mov edx, offset msgAcceptedBy ; get source node: message address
	mov eax, sizeof msgAcceptedBy ; get size of the source node message
	add edx, eax ; add together to point to the end
	sub edx, 2 ; adjust to node name position in string
	mov al, NameOffset[edi] ; get node name
    mov [edx], al ; put node name into message

    ; print message
    mov edx, offset msgAcceptedBy
    mov ecx, sizeof msgAcceptedBy

    call PrintMessage

NoMessageAccepted:
    popad
    ret
CheckAcceptedMessage ENDP

ReceiveLoop PROC
    pushad
    mov NodePointer, offset NodeA
    mov edi, NodePointer
    CheckEndOfNodes:
        cmp edi, endofnodes
        jl MoreNodes
        jmp ReceiveDone
    MoreNodes:
        call CheckAcceptedMessage
        cmp messageAccepted_flag, 1
        je ReceiveDone
        mov cl, NumConnectionsOffset[edi]
        mov eax, ConnectionSize
        mul cl
        add edi, NodeMinimunSize
        add edi, eax
        mov NodePointer, edi
        jmp CheckEndOfNodes
    ReceiveDone:
   
        popad
        ret
ReceiveLoop ENDP

queueEmpty PROC 
    pushad ; push all registers

   ;as designed IN/OUT pointer, and NodePointer will be set to the current node before calling this procedure

   mov edx, NodePointer         ;pointer to current node 
   mov eax, inPtrOffset[edx]    ;current node's "inPointer"
   mov ebx, outPtrOffset[edx]   ;current node's "outPointer"
   cmp eax, ebx                 ;compare in and Out pointer 

   je queueEmpty_empty      ;queue empty if in and out pointer are equal 
   mov queueEmpty_flag, 1               ; flag 1 for queue not empty 
   jmp queueEmpty_end

   queueEmpty_empty: ;queue was empty
        mov queueEmpty_flag, 0        ; flag 0 for queue empty 

   queueEmpty_end:
        popad ; pop all registers
    ret
    ; flag contains the return value
        ;1 signals queue is not empty, 0 signals it is empty 
queueEmpty endp

putit PROC
    pushad
	cld
    mov edx, NodePointer
	mov esi, MessagePointer ; message address in esi
	mov edi, InPtrOffset[edx] ; in pointer in edi
	mov ecx, Packetsize ; get bytes to move
	rep movsb ; move the bytes
	mov eax, InPtrOffset[edx] ; get in poiner
	add eax, Packetsize ; update in pointer
	mov ebx, queueAddressOffset[edx] ; start of queue
	add ebx, QueueSize ; end of queue
	cmp eax, ebx ; in pointer past end of queue?
	jl put1 ; not past end of queue
	mov eax, queueAddressOffset[edx] ; get start of queue
	put1:
	mov InPtrOffset[edx], eax ; update in pointer
    popad
    ret
putit ENDP

PrintNodes PROC
    pushad
    ; Initialize ESI with the address of the first node
    mov edi, OFFSET Network

    ;~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    ;MAIN LOOP PRINTING EACH NODE
    ;~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    main_loop:
    mov edx, OFFSET current_node ; Node: message
    mov ecx, sizeof current_node ; get size of message
    mov al, NameOffset[edi] ; get node name
    mov NodePositionOffset[edx], al ; put node name into end of message
    call WriteString ; print message
    call Crlf

    mov ebx, 0 ; initialize connection counter

    ;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    ;CONNECTION LOOP PRINTING EACH NODE'S CONNECTIONS
    ;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    connectionloop:
    mov eax, ConnectionSize ; get connection size
    mul bl ; multiply by connection index
    mov esi, NodeMinimunSize[edi + eax] ; get connection address
    mov edx, OFFSET is_connected_to
    mov ecx, sizeof is_connected_to
    mov al, NameOffset[esi] ; get connection node name
    mov ConnectionPositionOffset[edx], al ; put node name into end of message
    call WriteString ; print message
    call Crlf
    inc ebx
    cmp bl, NumConnectionsOffset[edi]
    jl connectionloop

    mov eax, 0 ; clear eax
    mov al, NumConnectionsOffset[edi] ; get number of connections
    mov cl, ConnectionSize ; get size of each connection
    mul cl ; determine size of all connections
    add edi, NodeMinimunSize ; move to connection space of structure
    add edi, eax ; offset esi over all connections to next node
    cmp edi, endofnodes ; test for end of nodes
    jl main_loop ; process next node
    endmain:
    popad
    ret
PrintNodes ENDP

PrintMessage PROC
    push edx
    push ecx
    call WriteString
    call Crlf
    
    pop ecx
    pop edx
    ; Need to write to file here
    call printFile
    ret
PrintMessage ENDP

ValidateNodeInput PROC
    mov validNodeInput_flag, 0
    movzx eax, buffer
    cmp al, 'A'
    je is_valid
    cmp al, 'B'
    je is_valid
    cmp al, 'C'
    je is_valid
    cmp al, 'D'
    je is_valid
    cmp al, 'E'
    je is_valid
    cmp al, 'F'
    je is_valid
    jmp endvalidate
    is_valid:
        mov validNodeInput_flag, 1
        jmp endvalidate
    endvalidate:
    ret
ValidateNodeInput ENDP

EnterMessage PROC
    pushad
    ; prompt for initial packet information
    mov edi, offset initPacket
    call PromptForLocalEcho
    promptorigin:
        mov edx, offset prompt_origin
        mov ecx, sizeof prompt_origin
        call WriteString
        mov edx, offset buffer
        mov ecx, sizeof buffer
        call readstring
        call ValidateNodeInput
        cmp validNodeInput_flag, 1
        jne promptorigin
        mov al, buffer
        mov byte ptr Sender[edi], al ; set sender to value entered by user
        mov byte ptr Origin[edi], al ; set origin to value entered by user
        call Crlf
    promptdestination:
        mov edx, offset prompt_destination
        mov ecx, sizeof prompt_origin
        call WriteString
        mov edx, offset buffer
        mov ecx, sizeof buffer
        call Readstring
        call ValidateNodeInput
        cmp validNodeInput_flag, 1
        jne promptdestination
        mov al, buffer
        mov byte ptr Destination[edi], al ; set destination node to value entered by user
        call Crlf
    ;mov edx, offset prompt_TTL
    ;mov ecx, offset prompt_TTL
    ;call WriteString
    ;call ReadInt
    ; need to validate data here as well
    mov byte ptr TTL[edi], 10 ; set destination node to value entered by user
    ;call Crlf
    popad
    ret
EnterMessage ENDP

GetOutputFile PROC
    pushad
    ; Prompting for output file
    mov edx, offset PromptOutputFile ; put reference to prompt in edx
	mov ecx, sizeof PromptOutputFile ; put size of bytes of prompt in ecx
	call WriteString ; print message
	mov edx, offset fileName ; put reference to filename in edx
	mov ecx, sizeof fileName ; put size of characters for filename in ecx
	call ReadString ; read the output file name
	; open output file
	mov edx, offset fileName ; put filename reference in edx
	call CreateOutputFile ; open the output file
	mov outFileHandle, eax ; keep output file handle
	cmp eax, INVALID_HANDLE_VALUE ; test if file error
	je outFileError ; terminate program if file error
    jmp success
    outFileError:
        STC
        jmp done
    success:
        CLC
        jmp done
    done:
        popad
        ret
GetOutputFile ENDP

printFile PROC
pushad


mov eax, outFileHandle      ;set file writing to 
;mov edx, offset fileBuffer  ;move the address of the writing buffer to edx 
call writeToFile            ;write to the file 

 mov edx, OFFSET newlineChar  ; Move the address of the newline character to edx
    mov eax, outFileHandle       ; Set file writing handle
    mov ecx, 1                   ; Number of bytes to write (1 for newline character)
    call writeToFile             ; Call a subroutine to write the newline character to the output

cmp eax, 0      ;eax will contain how many bytes were written 
je writeError   ;no bytes were written 

mov eax, outFileHandle      ;set file writing to 



jmp closefiles  

writeError:
    mov edx, offset fileWriteMsg
    mov ecx, sizeof fileWriteMsg
    call writestring
    call Crlf

closeFiles:


popad
ret

printFile endp

PromptForLocalEcho PROC
    prompt:
    pushad
    ; Write prompt to console
    mov edx, offset echoPrompt
    mov ecx, sizeof echoPrompt
    call WriteString

    ; Read user input
    mov edx, offset buffer
    mov ecx, sizeof buffer
    call readString

    ; Check if input is valid
    mov esi, offset buffer
  
    mov al, [esi]
    
    cmp al, "y"
    je SetLocalEchoOn
    jne setLocalEchoOff

SetLocalEchoOn:
    mov localEcho, 1
    jmp endechoprompt

SetLocalEchoOff:
    mov localEcho, 0

    endechoprompt:
    call Crlf
    popad   
    ret
    PromptForLocalEcho endp

receivedPrint proc
 pushad
            mov edi, NodePointer
            mov edx, offset msgRcvd ; get source node: message address
	        mov eax, sizeof msgRcvd ; get size of the source node message
	        add edx, eax ; add together to point to the end
	        sub edx, 2 ; adjust to node name position in string
	        mov al, NameOffset[edi] ; get node name
            mov [edx], al ; put node name into message

                ; print message
                mov edx, offset msgRcvd
                mov ecx, sizeof msgRcvd
                call PrintMessage
inc totalMsgs
popad
ret
receivedPrint endp



printTotal proc
pushad

            mov edx, offset totalMsgsOutp ; get source node: message address
	        mov eax, sizeof totalMsgsOutp ; get size of the source node message
	        add edx, eax ; add together to point to the end
	        sub edx, 2 ; adjust to node name position in string
	       
          

          

                ; print message
                mov edx, offset totalMsgsOutp
                mov ecx, sizeof totalMsgsOutp
                call PrintMessage
                mov al, totalMsgs
                call writeint
popad
ret
printtotal endp

main PROC
    ; initialize variables
    mov time, 1 ; system time
	mov totalpackets, 1 ; initialize number of total generated packets
	mov activepackets, 1 ; number of active packets
	mov receivedpackets, 0 ; number of packets received by destination
	mov totalhops, 0 ; total hops of packets to reach destination
    mov totaltime, 0 ; total time of packets to reach the destination

    call GetOutputFile
    jc outFileError
    call PrintNodes
    call EnterMessage
    call MainLoop

    outFileError:

    fullqueueabort:
    call printTotal
    ret
main ENDP

end main
