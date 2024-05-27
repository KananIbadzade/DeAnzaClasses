;Programming Exercise 1

INCLUDE Irvine32.inc

.data
bigEndian BYTE 12h, 34h, 56h, 78h  ; Big endian array
littleEndian DWORD ?               ; Little endian DWORD

.code
main PROC
    ; clearing the EAX register to prepare for byte manipulation
    xor eax, eax

    ; loading bytes from bigEndian into EAX in reverse order to achieve little endian
    mov al, bigEndian[3]  ; moving the last byte into AL
    mov ah, bigEndian[2]  ; moving the third byte into AH
    shl eax, 16           ; shifting left to make room for the next two bytes
    mov al, bigEndian[1]  ; moving the second byte into AL
    mov ah, bigEndian[0]  ; moving the first byte into AH

    ; store the little endian value in the littleEndian variable
    mov littleEndian, eax

    ; Output the original big endian value
    mov esi, OFFSET bigEndian      ; point ESI to the start of bigEndian
    mov ecx, 4                     ; set ECX to the length of bigEndian
    call DumpMem                   ; dump memory to show big endian format

    ; output the converted little endian value
    mov esi, OFFSET littleEndian   ; point ESI to the start of littleEndian
    mov ecx, SIZEOF littleEndian   ; set ECX to the size of littleEndian
    call DumpMem                   ; dump memory to show little endian format

    exit
main ENDP

END main
