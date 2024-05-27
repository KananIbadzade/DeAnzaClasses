;exercise 2
; student name: Kanan Ibadzade

INCLUDE Irvine32.inc

.data
buffer BYTE 21 DUP(0)   ;buffer to hold a 20-character string plus a null termination

.code
main PROC
    call Randomize       ;start the random number generator.

    mov ecx, 20          ;to create and show 20 strings, loop 20 times.
generateStrings:
    push ecx             ;keep the loop counter safe.
    lea edx, buffer      ;load the buffer's address.
    mov ecx, 10          ;string length is 10 
    call GenerateRandomString
    call WriteString     ;outputing the string
    call Crlf            ;newline
    pop ecx              ;restoring
    loop generateStrings ;continue looping

    exit
main ENDP

; GenerateRandomString - generates a random string of uppercase alphabets
; Receives: ECX - the length of the string, EDX - pointer to the buffer
; Returns: nothing
GenerateRandomString PROC
    pushad               ;saving all general-purpose registers
    mov ebx, edx         ;EBX will point to the current position in buffer

generate:
    mov eax, 'Z' - 'A' + 1 ;range (A-Z)
    call RandomRange     ;generate a random number between 0 and range
    add al, 'A'          ;convert to an uppercase letter
    mov [ebx], al        ;store the letter in the buffer
    inc ebx              ;move to the next position in buffer
    loop generate        ;repeat for the length of the string

    mov byte ptr [ebx], 0 ;null-terminate the string
    popad                ;restore all general-purpose registers
    ret
GenerateRandomString ENDP

END main