;Programming Exercise 2

INCLUDE Irvine32.inc

.data
    guardHead BYTE 4 DUP('$'), 0Dh, 0Ah  ; Add newline characters after guard characters
    source    BYTE "This is the source string",0
    guardMid  BYTE 4 DUP('%'), 0Dh, 0Ah  ; Add newline characters after guard characters
    target    BYTE SIZEOF source DUP('#')
    guardTail BYTE 4 DUP('^'), 0Dh, 0Ah  ; Add newline characters after guard characters
    dot       BYTE '.',0Dh,0Ah,0          ; Dot character followed by newline and null terminator

.code
main PROC
    ; Prepare registers for the loop
    mov ecx, SIZEOF source - 1
    lea esi, [source + SIZEOF source - 2]  ; Point ESI to the last character of source before null
    lea edi, target

    ; Copying loop
CopyLoop:
    mov al, [esi]       ; Load character from source
    mov [edi], al       ; Store character in target
    dec esi             ; Move to previous character in source
    inc edi             ; Move to next character in target
    loop CopyLoop       ; Repeat until ECX reaches 0

    ; Replace the last '#' in target with a null terminator
    mov byte ptr [edi], 0

    ; Display the data block with newline separations
    ; Show source string and guards
    mov edx, OFFSET guardHead
    call WriteString
    mov edx, OFFSET source
    call WriteString
    mov edx, OFFSET dot
    call WriteString     ; Display the dot and newline after source string
    
    ; Show target string and guards
    mov edx, OFFSET guardMid
    call WriteString
    mov edx, OFFSET target
    call WriteString
    mov edx, OFFSET dot
    call WriteString     ; Display the dot and newline after target string

    ; Show the tail guard characters
    mov edx, OFFSET guardTail
    call WriteString

    exit
main ENDP

END main

