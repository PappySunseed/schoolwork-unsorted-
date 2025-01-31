Include Irvine32.inc

title G1P4 Network Simulator

;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
;(CMSC-3100-001 Spring 2024) WRITTEN BY
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
; Allan Cunningham  | cun82935@pennwest.edu
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

;~~~~~~~~
;MESSAGES
;~~~~~~~~
current_node BYTE "Node:  ", 0
is_connected_to BYTE "Connected to  ", 0

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

transmitBeginning PROC
   ;preserve registers 
   push edx
   

   ;beginnong of the current node's queue
   mov edx, NodePointer ;points to currennt node 
   mov ebx, QueueAddress[edx]   ;start of queue
        ;as designed, queueAddress and NodePointer will be set to the current node before calling this procedure 

   pop edx

   ;ebx contains the return value, the start of the current node's transmit queue 

transmitBeginning ENDP

transmitEnd PROC
    push edx 
    
    mov edx, NodePointer    ;points to current node 
    mov ebx, QueueAddress[edx]  ;moves start of queue to ebx 
    add ebx, QueueSize          ;adds the size of the queue to ebx
        ;as designed, queueAddress, queueSize, and NodePointer will be set to the current node before calling this procedure

   ;ebx contains the return value (end of the current node's transmit queue)

   pop edx

transmitEnd ENDP

queueEmpty PROC 
   push edx
   push eax

    ;as designed IN/OUT pointer, and NodePointer will be set to the current node before calling this procedure



   mov edx, NodePointer         ;pointer to current node 
   mov eax, inPtrOffset[edx]    ;current node's "inPointer"
   mov ebx, OutPtrOffset[edx]   ;current node's "outPointer"
   cmp eax, ebx                 ;compare in and Out pointer 



   je get2      ;queue empty if in and out pointer are equal 
        mov ebx, 1  ;use ebx to send flag 1 for queue not empty 
   JMP end

    get2: ;queue was empty 
        mov ebx, 0      ;using ebx to send flag 0 for queue empty 

    end:
        pop edx
        pop eax 

    ;ebx contains the return value
        ;1 signals queue is not empty, 0 signals it is empty 
queueEmpty endp




main PROC

    ; Initialize ESI with the address of the first node
    mov edi, OFFSET Network

    ;~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    ;MAIN LOOP PRINTING EACH NODE
    ;~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    mainloop:
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
    jl mainloop ; process next node
    endmain:
    
    exit
main ENDP

end main