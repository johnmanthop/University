; Ioannis Manthopoulos
; 3579
; Implementation of 6 string io standard C functions
; It is assumed strings end with $ (instead of \0)
; If the user wants to print a new line they must first print 10 (newline) and then 13 (cursor return)
; As a convention and to avoid confusion all pushes in stack are 16 bit, even if only 8 bits are needed
; Function references from en.cppreference.com

data segment        
    scanf_buffer    DB 20 dup(32)
    
    scanf_arg1      DB 0
    scanf_arg2      DB 0
    scanf_arg3      DB 0
    
    scanf_fstr1     DB "$"
    scanf_fstr2     DB "%c$"
    scanf_fstr3     DB " %c$"
    scanf_fstr4     DB " %c $"
    scanf_fstr5     DB "  %c  $"               
    scanf_fstr6     DB "abc  %c  def %c$"
    scanf_fstr7     DB "    qwe%c%c  asd%casd$"
    scanf_fstr8     DB "%c%c%c$"  
    
    test_buffer          DB "                  "
    
    printf_msg1     DB 'a', 'b', 'c', 10, 13, 'd', 'e', 'f', '$'
    printf_msg2     DB "First char is %c, second char is%c , third char is%cnon valid char is %s and non valid char is %$" 
ends

stack segment
    dw   128  dup(0)
ends

code segment
    jmp START

; parameter is ascii character
; 8 bit parameter is always valid ascii
; print and return the character
PUTCHAR proc
    push bp
    mov bp, sp
    push dx

; body starts here
    mov dl, [bp + 4]                    ; set dl to parameter  
    mov dh, 0                           ; null the 8 higher bits
    
    mov ah, 2                           ; set interrupt    
                                        ; call interrupt
    int 21h                             ; interrupt sets the al return value automatically
    mov ah, 0                           ; set ah to zero so ax = al    
    
; body ends here
    
    pop dx
    pop bp
    ret     
PUTCHAR endp

; return value is character read
GETCHAR proc
    push bp
    mov bp, sp
    
    mov ah, 1                           ; set interupt to 1 (read char with echo)
    int 21h
    mov ah, 0                           ; set ah to 0 so ax = char read
    
    pop bp
    ret
GETCHAR endp

; input is string pointer
; return value is 0 on success   
; prints the message and one \n at the end
PUTS proc
    push bp
    mov bp, sp
    
    push bx
    
    mov dx, [bp + 4]                    ; msg pointer 
    mov ah, 9                            
    int 21h                             ; print msg with interupt
    
    mov ax, 10
    push ax                             ; write one \n at the end as per the C standard
    call PUTCHAR
    add sp, 2
    
    mov ax, 13
    push ax                             ; write one cursor return after \n
    call PUTCHAR
    add sp, 2                           
    
    mov ax, 0                           ; return non-negative 0
    
    pop bx
    pop bp
    ret
PUTS endp

; input is buffer pointer              
; return is buffer pointer
; note, as in C, this function does not perform any bounds checking other than that of the DOS interrupts
; it fills the buffer pointer with the input string (buffer size and no of characters are discarded)
GETS proc
    push bp
    mov bp, sp 
    
    push bx
    push cx
    push dx
    
    mov dx, [bp + 4]                    ; buffer pointer
    mov ah, 0ah
    int 21h                             
    ; 1st byte is buffer size
    ; 2nd byte is no of characters read
    ; we must add the $ character manually and discard the first 2 bytes
        
    mov bx, dx                          ; now bx is the buffer pointer 
    
    mov cl, [bx + 1]                    ; set cx to number of characters read
    mov ch, 0        
    add bx, cx
    mov BYTE PTR [bx + 2], '$'
    
    mov bx, dx                          ; reset bx to the original buffer pointer
    add bx, 2                           ; make bx point to the start of the string                                                                       
                                                                                         
    ; if string is empty, this still works because the first 2 bytes are always available   
    ; loop to move all characters 2 characters left
LOOP1_START:
    mov al, [bx]                        ; store character in ax
    mov [bx - 2], al                    ; store ax in buffer but shifted 2 bytes left
                                                                                              
    inc bx                              ; inc changes the flags so do it before cmp
    
    cmp BYTE PTR [bx - 1], '$'           ; the condition needs to be checked at the end
    jne LOOP1_START
LOOP1_END:
                              
    mov ax, [bp + 4]                    ; return value is buffer pointer
    
    pop dx
    pop cx
    pop bx
    
    pop bp
    ret
GETS endp

; input is at least one string and a variable number of arguments
; it prints only "char" (%c) types
; % character is not printable
; returns the number of characters written
PRINTF proc
    push bp
    mov bp, sp
    
    push bx
    push cx
    push dx
    push si
    
    mov bx, [bp + 4]                    ; format string pointer
    
    ; all in one pass, print characters until you find a %c pair      
    
    mov si, 6                           ; si is the variable argument counter 
    mov dx, 0                           ; dx is the printed chars counter (aka return value)
LOOP2_START:
    cmp [bx], '$'
    je LOOP2_END
    
; if current char == '%'
    cmp [bx], '%'
    jne ELSE1
THEN1:
    cmp [bx + 1], 'c'                   ; see if % is %c (for now only this is supported)
    jne ENDIF2
THEN2:
    inc bx                              ; skip the c char in %c
    inc dx                              ; add one to printed chars counter
    
    mov ax, [bp + si]                   ; get char argument
    mov ah, 0                           ; null high 8 bits
    push ax
    call PUTCHAR                        ; print it
    add sp, 2
    
    add si, 2
ENDIF2:

jmp ENDIF1
ELSE1:
    inc dx                              ; add one to printed chars counter

    mov al, [bx]                        ; get current char
    mov ah, 0                           ; null high 8 bits
    push ax
    call PUTCHAR                        ; print it
    add sp, 2
ENDIF1:      

    inc bx
    jmp LOOP2_START
LOOP2_END:

    mov ax, dx                          ; dx is return value
    
    pop si
    pop dx
    pop cx
    pop bx
              
    pop bp
    ret
PRINTF endp

; arguments are one format string and a variable number of char pointers
; this version of scanf reads the format string and tries to match coresponding inputs
; 1> function stops when format string ends
; 2> it is assumed user input is no bigger than 20 characters
; 3> consecutive spaces in format string are treated as one
; 4> any space in format string consumes all following consecutive input spaces
; 5> any non space and non %c character in fstring consumes one user input
; 6> if fstring and input don't match error is returned
; 7> any input after the format string ends is ingored
; return value is number of input pointer successfully written to or -1 in case of error
SCANF proc
    push bp
    mov bp, sp
    
    push bx
    push cx
    push dx
    push si
    push di          
              
    lea ax, [scanf_buffer]                  ; read user input string to scanf_buffer
    push ax
    call GETS                               ; using gets function
    add sp, 2                                
    
    mov si, 6                               ; argument position pointer  
    lea di, [scanf_buffer]                  ; user input pointer
    mov bx, [bp + 4]                        ; format string pointer  
    
    ; allocate one local WORD var for the return value 
    sub sp, 2                               
    
    mov WORD PTR [bp - 2], 0                ; set counter to 0
                                                                                           
; main loop body starts here     
LOOPSCANF_START:
    cmp BYTE PTR [bx], '$'                  ; until fstring ends
    je LOOPSCANF_END
    
; if ([bx] == '%')
    cmp BYTE PTR [bx], '%' 
    jne ELSEIFA
THENA: ; here [bx] == '%'
; if ([bx + 1] == 'c')
    cmp BYTE PTR [bx + 1], 'c'
    jne ERROR                               ; if string is not "%c" go to error

; here the string is "%c" 
    mov al, [di]                            ; load next user's character to al
    
    push bx                                  
    mov bx, [bp + si]                       ; set al to next argument counter
    mov [bx], al
    pop bx
    
    inc di                                  ; advance user input pointer                                                 
    add si, 2                               ; advance next_arg counter
    add bx, 2                               ; advance fstring counter by 2 (one for "%" and one for "c")
    
    jmp ENDIFA
ELSEIFA:
; here ([bx] != '%')
    cmp BYTE PTR [bx], ' '                  ; if ([bx] != ' ')
    jne ELSEA                               ; go to else

; here ([bx] == ' ')
LOOPSCANFB_START:                           ; this loop consumes all consecutive fstring spaces
    cmp BYTE PTR [bx], ' '
    jne LOOPSCANFB_END                      
    
    inc bx
    jmp LOOPSCANFB_START
LOOPSCANFB_END:

LOOPSCANFC_START:                           ; this loop consumes all consecutive following input spaces
    cmp BYTE PTR [di], ' '
    jne LOOPSCANFC_END                      ; if al != ' ' exit the loop
    
    inc di
    jmp LOOPSCANFC_START
LOOPSCANFC_END:                                          

    jmp ENDIFA
ELSEA:        
    ; here fstring is neither space not "%c" so consume next user's input
    mov al, [di]
    cmp al, [bx]                            ; compare fstring and user input
    jne ERROR                               ; if they don't match go to error
    
    inc bx                                  ; advance fstring input
    inc di                                  ; advance user input

ENDIFA:
    jmp LOOPSCANF_START
LOOPSCANF_END:
    jmp NOERROR 
; main loop body ends here    
ERROR:                                      ; if error has occured, set ax to -1, goto end of routine 
    mov ax, -1
    jmp END_OF_ROUTINE                      
NOERROR:                                    ; otherwise set ax to local counter
    mov ax, [bp - 2]  
    
END_OF_ROUTINE:    
    add sp, 2                               ; release allocated memory
    
    pop di    
    pop si                                  ; pop all regs
    pop dx
    pop cx
    pop bx
    
    pop bp
    ret
SCANF endp

START:
; set segment registers:
    mov ax, data
    mov ds, ax
    mov es, ax
; test main function
;;;;;;;;;;;;;;;;;;;;;;;;;
; the following tests getchar and puts
    lea bx, [test_buffer]
    
    call GETCHAR                                ; read three characters from user
    mov [bx], al
    
    call GETCHAR                                ; store them in test_buffer
    mov [bx + 1], al
    
    call GETCHAR
    mov [bx + 2], al
    
    mov BYTE PTR [bx + 3], '$'                  ; set '$' in end of string
    
    mov ax, 10
    push ax
                                                ; print \n
    call PUTCHAR
    add sp, 2
    
    mov ax, 13
    push ax
    
    call PUTCHAR
    add sp, 2
    
    push bx                                     ; print test_buffer with puts
    call PUTS 
    add sp, 2

;;;;;;;;;;;;;;;;;;;;;;;;;
; the following tests printf, scanf, gets (internal in scanf) and putchar
    lea ax, [scanf_arg3]                        ; use scanf to set scanf_arg1, 2 & 3 arguments
    push ax                                     ; according to given format string 
                                                
    lea ax, [scanf_arg2]
    push ax
    
    lea ax, [scanf_arg1]
    push ax 

    lea ax, [scanf_fstr8]
    push ax
    
    call SCANF
    add sp, 2*4
    
    mov ax, 10
    push ax
    
    call PUTCHAR                                ; print \n
    add sp, 2
    
    mov ax, 13
    push ax
    
    call PUTCHAR
    add sp, 2
                                                ; use printf to print the printf_msg2 with the 3 arguments read
    mov al, scanf_arg3
    mov ah, 0
    push ax
    
    mov al, scanf_arg2
    mov ah, 0
    push ax
    
    mov al, scanf_arg1
    mov ah, 0
    push ax 

    lea ax, [printf_msg2]
    push ax
    
    call PRINTF
    add sp, 2*4
ends

end START ; set entry point and stop the assembler.
