;exercise 3
; student name: Kanan Ibadzade

INCLUDE Irvine32.inc

.data
charToDisplay BYTE 'X' ;

.code
main PROC
    mov ecx, 0 ;counter for background colors

    ; Iterate over each background color (0-15)
    while1: cmp ecx, 16
    jae end_while1

        push ecx ;preserve the stack's backdrop color index.
        mov ebx, 0 ;foreground color counter
        
        ; Iterate over each foreground color (0-15)
        while2: cmp ebx, 16
        jae end_while2

            ; Calculate the color attribute (background * 16 + foreground)
            mov eax, ecx ;change the backdrop color index to AL
            shl eax, 4   ;move 4 bits to the left to create room for the foreground color.
            add al, bl   ;in AL, provide the foreground color index.

            ; Set the color and print the character
            call SetTextColor
            mov al, charToDisplay
            call WriteChar

            inc ebx ; Increment foreground color index
        jmp while2
        end_while2:

        ; Output a newline after each line of characters
        call Crlf
        pop ecx ;restore the background color index from the stack
        inc ecx ;increment background color index
    jmp while1
    end_while1:

    ; Restore default color
    mov eax, 7h ;light gray on black text
    call SetTextColor

    exit
main ENDP

END main