; 16 bit x86 assembly program that performs certain manipulations on matrices   

; At first it finds the transpose of a given matrix
; It prints both matrices with background/foreground color effects
; It finds the (integer) average of both matrices (result should be the same)
; It finds the coordinates of the max element of both matrices 
; Notes\assumptions:
; It is assumed that all division results fit in one 16 bit register
; It is assumed tat all matrix elements are 32 bit unsigned numbers
; It is assumed that the screen is the default 80x25 screen
; The color effects work only for 3x3 matrices
; The max function finds the first max occurance in the matrix, 
; so if there are duplicates, the max function will find the first one

; Ioannis Manthopoulos
; 3579
; 7/12/22

data segment
    matrix_A DD 1, 123, 45367
             DD 0, 1, 0
             DD 123, 0, 1
             
    matrix_B DD 0, 0, 0
             DD 0, 0, 0
             DD 0, 0, 0
             
    msg1     DB 'm', 'a', 't', 'r', 'i', 'x', ' ', 'A', '=', 0
    msg2     DB 'm', 'a', 't', 'r', 'i', 'x', ' ', 'B', '=', 0  
    
    msg3     DB 'a', 'v', 'g', ' ', 'o', 'f', ' ', 'A', ' ', '=', ' ', 0  
    msg4     DB 'a', 'v', 'g', ' ', 'o', 'f', ' ', 'B', ' ', '=', ' ', 0 
    
    msg5     DB 'm', 'a', 'x', ' ', 'p', 'o', 's', 'i', 't', 'i', 'o', 'n', ' ', 'o', 'f', ' ', 'A', ' ', '=', ' ', 0 
    msg6     DB 'm', 'a', 'x', ' ', 'p', 'o', 's', 'i', 't', 'i', 'o', 'n', ' ', 'o', 'f', ' ', 'B', ' ', '=', ' ', 0
    
    cols     DB 00001111b, 00011110b, 00101100b, 00111100b, 01001011b, 01011010b, 01100111b, 10001010b, 11011110b
             
    N           EQU 3
    M           EQU 3
    screen      EQU 0B800h
    screen_step EQU 160                 ; number of empty characters to reach the new screen line (only for default 80x25 screen)

ends

stack segment
    dw   128  dup(0)
ends

code segment
    jmp START
    
    
; args: string pointer, printing coordinate
    
PRINT_MESSAGE proc
    push bp 
    mov bp, sp
    
    push ax
    push bx
    push cx
    push dx
    push es
    push di
    
    mov ax, screen
    mov es, ax
    
    mov bx, [bp + 4]                        ; message pointer
    mov di, [bp + 6]                        ; print coordinate
    
LOOP5_START:
    cmp BYTE PTR [bx], 0                    ; if character is \0 then jump out of the loop
    je LOOP5_END
    
    mov ch, 11011111b                       ; set ch to the default print color
    mov cl, [bx]                            ; set cl to the character to be printed
    
    mov es:[di], cx                         ; print it
    
    inc bx                                  ; increase message pointer
    add di, 2                               ; increase print coordinate by one character
    
    jmp LOOP5_START
LOOP5_END:   
                                            ; restore original registers
    pop di
    pop es
    pop dx
    pop cx
    pop bx
    pop ax
    
    pop bp
    ret
PRINT_MESSAGE endp

; args: matrix pointer, print coordinate, color effects control flag, counter of the colors array (optional)
PRINT_NUMBER proc
    push bp
    mov bp, sp
    
    push bx
    push cx
    push dx
    push es
    push di
    
    mov ax, screen                  ; move screen pointer to es register
    mov es, ax
    
    mov ax, [bp + 4]                ; matrix pointer
    mov di, [bp + 6]                ; start of print
                                    ; [bp + 8] is control flag argument
                                    ; [bp + 10] is the counter of the colors array

; if control = 0
    cmp WORD PTR [bp + 8], 0        
    jne else1b
then1b:                 
    mov ch, 11011111b               ; move the default color value to ch
    jmp endif1b 
; else if control != 0
else1b:
    mov bx, [bp + 10]               ; else get a color value from the colors array to ch
    mov ch, [cols + bx]      
endif1b:

; if number = 0
    cmp ax, 0                       
    jne else1a
then1a:
    mov cl, 48                      ; set cl = '0' ascii
    mov es:[di], cx                 ; print it
    
    mov ax, 1                       ; return value is the length of the number
    
    jmp endif1a
else1a:
    mov bx, 10                      ; else set bx to 10 (to use it in division)
    mov dx, 0                       ; dx is the digit count
LOOP3_START:
    cmp ax, 0                       ; if number is 0 jump out of the loop
    je LOOP3_END
    ; else
    push dx                         ; save dx
    xor dx, dx                      ; set dx to 0
    div bx                          ; divide the number (ax) by bx (10)
                                    ; the remainder of division by 10 is the current last digit
    
    add dx, 48                      ; convert result to ascii
    mov cl, dl                      ; move the result to cl
    pop dx                          ; restore dx
    
    inc dx                          ; add one to the digits count
    
    push cx                         ; save digits in reverse order
    
    jmp LOOP3_START
LOOP3_END:
    mov ax, dx                      ; return value is the length of the number
                              
                                    ; now we have to print the digits in the correct order
    mov bx, 0                       ; bx is the print coordinate
LOOP3A_START:
    cmp dx, 0                       ; if digit count has reached zero, jump out of the loop
    je LOOP3A_END
    
    pop cx                          ; get the saved digit
    mov es:[di + bx], cx            ; print it
    
    dec dx                          ; remove one from the digit count
    add bx, 2                       ; increase the print coordinate
    jmp LOOP3A_START
LOOP3A_END:
endif1a:
    
    pop di                          ; restore registers
    pop es
    pop dx
    pop cx
    pop bx
    
    pop bp
    ret
PRINT_NUMBER endp
 
; args: matrix pointer, print coordinate
PRINT_AVG proc
    push bp
    mov bp, sp
    
    push ax
    push bx
    push cx
    push dx
    push si
    
    mov si, [bp + 4]            ; matrix pointer
    mov cx, [bp + 6]            ; coordinate
    
    mov ax, 0                   ; ax is low 16 bits of sum
    mov dx, 0                   ; dx is high 16 bits of sum
    
    mov bx, 0                   ; bx is counter
    
LOOP6_START:
    cmp bx, 4*(N*M)
    je LOOP6_END
    
    add ax, [si + bx]           ; perform 32 bit addition with add & ad-carry pair
    adc dx, [si + bx + 2]
    
    add bx, 4            
    jmp LOOP6_START            
LOOP6_END:
    ; note: we assume the division result fits in one 16 bit register
    push cx                     ; save cx before modifying it
    mov cx, N*M                 ; put the count to cx
    div cx                      ; divide dx|ax by cx, avg = sum / count
    pop cx
    
    mov dx, 0                   
    push dx                     ; pass the '0' color flag
    
    push cx                     ; pass the coordinate argument
    
    push ax                     ; pass the average value 

    call PRINT_NUMBER
    
    add sp, 3*2
    
    pop si
    pop dx
    pop cx
    pop bx
    pop ax
    
    pop bp
    ret
PRINT_AVG endp

; args: matrix pointer, print coordinate
PRINT_MAX proc
    push bp
    mov bp, sp
    
    push ax
    push bx
    push cx
    push dx
    push si
    
    mov si, [bp + 4]                ; matrix pointer
                                    ; [bp + 6] is the coordinate to print argument, it is used after the loop
    
    sub sp, 2*6                     ; allocate two 16 bit words for the max element, two 16 bit words for the max coordinates 
                                    ; and two for the temporary cx and bx values
    
    mov WORD PTR [bp - 2], 0        ; init the current_max element with 0, low 16 bits
    mov WORD PTR [bp - 4], 0        ; high 16 bits 
    
    mov WORD PTR [bp - 6], 0        ; max coordinate cols
    mov WORD PTR [bp - 8], 0        ; max coordinate rows
    
    mov WORD PTR [bp - 10], 0       ; temp cx value
    mov WORD PTR [bp - 12], 0       ; temp bx value
    
    ; the way we compare 32 bit numbers is by comparing high and low parts
    ; the simplified decision tree is as follows:
    ; if (y_h != x_h) then result is same as (y_h <=> x_h)
    ; else if (y_h == x_h) then result is same as (x_l <=> y_l)
    ; where a_l are the low 16 bits of a and a_h are the 16 high bits of a
    
    mov bx, 0                       ; bx is the row counter (i)
LOOP7A_START:
    cmp bx, N
    je LOOP7A_END
    
    mov cx, 0                       ; cx is the columns counter (j)
LOOP7B_START:
    cmp cx, M
    je LOOP7B_END
    
    mov [bp - 10], cx               ; we save cx and bx before modifying them, because we may need the original values in "then3" label
    mov [bp - 12], bx               ; and we can't pop them to find the original values because the "then3" label is conditional
    
    push ax                         ; save register values before main loop
    push bx
    push cx
    push dx
                                    
    shl cx, 2                       ; multiply cols by 4 to address 32 bit data (4 bytes = 32 bits)
    mov di, cx                      ; move cols to di, to use it in addresing                      
    
    xor dx, dx                      ; reset dx because it might mess the multiplication
    mov ax, bx                      ; move rows to ax
    mov bx, 12                      
    mul bx                          ; multiply ax (rows) by 12, since each row is 12 bytes
    mov bx, ax                      ; here bx = 12 * old_bx
    add bx, si                      ; add si (the matrix pointer) to the address
    
    mov ax, [bx][di]                ; ax is the low 16 bits of the matrix value
    mov dx, [bx][di + 2]            ; dx is the high 16 bits
    
    ; if (xh == yh)
    cmp dx, [bp - 4]                ; compare high bits of current value and current max
    je else3:
then3:                              ; if they are not the same, we are interested in the case when dx > current_max
    ; (xh != yh)
    ; if dx <= current_max we do not care
    jna endif3                                                      
    
    ; otherwise:
    ; if we are here then current number is bigger than current max
    ; so replace current max with current number
    mov [bp - 4], dx                ; save low and high bits to current_max                
    mov [bp - 2], ax 
    
    ; save original cx and bx values to the max coordinates
    mov cx, [bp - 10]               ; move original cx to cx               
    mov bx, [bp - 12]               ; move original bx to bx
    mov [bp - 6], cx                ; move original cx to the max coordinate variable
    mov [bp - 8], bx                ; same for bx

    jmp endif3
else3:
    ; if we are here then the high 16 bits of both numbers are the same
    ; so we compare the low 16 bits
    ; if ax <= current_max we do not care
    cmp ax, [bp - 2]
    jna endif3                     

    ; if we are here then the current number is bigger than current max
    ; same as before
    mov [bp - 4], dx
    mov [bp - 2], ax
    
    mov cx, [bp - 10]
    mov bx, [bp - 12]
    
    mov [bp - 6], cx
    mov [bp - 8], bx

    jmp endif3
endif3:
    
    pop dx                          ; reset register values
    pop cx
    pop bx
    pop ax
    
    inc cx
    jmp LOOP7B_START
LOOP7B_END:
    
    inc bx
    jmp LOOP7A_START
LOOP7A_END:
    ; loop is done, [bp - 6] and [bp - 8] hold the max coordinates
    
    mov di, [bp + 6]                ; di = coordinate argument passed
    
    mov ax, 0
    push ax                         ; push '0' color flag 
    
    push di                         ; pass coordinate 
    
    mov ax, [bp - 8]                ; load ax with rows coordinate
    push ax                         ; pass number 

    call PRINT_NUMBER
    add sp, 3*2
    
    mov ax, 0                       ; same as before, pass '0' color flag
    push ax
    
    add di, 4                       ; add 2 spaces to the print coordinate
    push di                         ; pass coordinate
     
    mov ax, [bp - 6]                ; load ax with columns coordinate
    push ax                         ; pass number
                                    
    call PRINT_NUMBER
    add sp, 3*2
    
    pop si
    pop dx                          ; restore original registers
    pop cx
    pop bx
    pop ax
    
    add sp, 2*6
    
    pop bp
    ret
PRINT_MAX endp

; args: matrix pointer, print coordinate
PRINT_MATRIX proc
    push bp
    mov bp, sp
    
    push ax
    push bx
    push cx
    push dx
    push si
    
    mov si, [bp + 4]                    ; matrix pointer
    mov cx, [bp + 6]                    ; start of print
    
    sub sp, 2*2                         ; allocate variable for the position of the matrix to be printed
                                        ; also allocate the number of rows printed
                                        
    mov [bp - 2], cx                    ; init print coordinate to cx 
    mov [bp - 4], cx                    ; init printed rows to cx         
    
    mov cx, 0                           ; cx counts the elements printed, used to control line breaks
    mov bx, 0                           ; bx is the matrix element pointer
    mov dx, 0                           ; dx is the color counter
LOOP4_START:
    cmp bx, 4*(N*M)
    je LOOP4_END
  
    push dx                             ; pass color counter argument, used to get the background foreground color combination
    mov ax, 1                           ; pass '1' argument, the flag to control background and foreground colors 
    push ax
    
    mov ax, [bp - 2]                    ; pass the current coordinate argument
    push ax                               
    
    mov ax, [si+bx]                     ; get matrix element   
    push ax                             ; pass the matrix element 
                                                                           
    call PRINT_NUMBER                   ; return value (ax) is the number of digits printed
    add sp, 4*2 
    
    inc cx                              ; add one to the printed elements

    cmp cx, M                           
    jne else2 
; if printed elements == M              ; in this case add a line break
then2:
    mov cx, 0                           ; reset the element counter 
    
    add WORD PTR [bp - 4], screen_step  ; add a row step to printed rows
    mov ax, [bp - 4]                    ; move printed rows to ax 
    
    mov [bp - 2], ax                    ; move ax (printed rows) to next print coordinates
    
    jmp endif2 
; if printed elements != M
else2:                                  ; here ax is the return value of print_number, the number of chars printed
    inc ax                              ; advance printed chars with one space char
    shl ax, 1                           ; multiply by 2 since video memory is addressed per 16 bits
                              
    add [bp - 2], ax                    ; add printed characters to the coordinates  
endif2: 

    add bx, 4                           ; advance matrix pointer
    inc dx                              ; advance color counter
                
    jmp LOOP4_START            
LOOP4_END:
    
    pop si
    pop dx
    pop cx
    pop bx
    pop ax
    
    add sp, 2*2
        
    pop bp
    ret
PRINT_MATRIX endp

; no args
TRANSPOSE proc
    push bp
    mov bp, sp
    
    sub sp, 2*2                     ; reserve 2 words in stack
    
    mov cx, 0                       ; cx = rows counter
; outer loop start
LOOP1_START:
    cmp cx, N
    je LOOP1_END
; inner loop start
    mov bx, 0                       ; bx = cols counter
LOOP2_START:
    cmp bx, M
    je LOOP2_END
    
    push ax                         ; inner loop body, save all registers
    push bx
    push cx
    push dx
    push di
    
    shl bx, 2                       ; multiply cols by 4 since each column element is 32 bits (4 bytes)
              
    xor dx, dx                      ; reset dx for multiplication
    mov ax, cx                  
    mov cx, 12                      ; multiply rows by 12 since each row is 12 bytes
    mul cx
    mov cx, ax
    mov di, cx                      ; set rows to di, to use it in addressing
    
    mov ax, matrix_A[di][bx]        ; get low 16 bits of matrix value
    mov [bp - 2], ax                ; save to temp variable
    mov ax, matrix_A[di][bx + 2]    ; same for 16 high bits
    mov [bp - 4], ax
    
    pop di                          ; restore and re-save registers before the second part of the loop
    pop dx                          
    pop cx
    pop bx
    pop ax
    
    push ax
    push bx
    push cx
    push dx
    push di
                                    ; same procedure but with swapped rows and cols
                                    ; since transposing is matrix_B[j][i] = matrix_A[i][j] for all i & j
                                    ; now cx is cols and bx is rows
    shl cx, 2                       ; multiply cols by 4                       
    mov di, cx
    
    xor dx, dx
    mov ax, bx                      ; multiply rows by 12
    mov bx, 12
    mul bx
    mov bx, ax
    
    mov ax, [bp - 2]                ; load low 16 bits of matrix_A value
    mov matrix_B[di][bx], ax        ; store it in transpose position of matrix B
    
    mov ax, [bp - 4]                ; same for 16 high bits
    mov matrix_B[di][bx + 2], ax
    
    pop di
    pop dx
    pop cx
    pop bx
    pop ax
    
    inc bx    

    jmp LOOP2_START
LOOP2_END:
    inc cx
    jmp LOOP1_START
LOOP1_END:

    add sp, 2*2
    
    pop bp
    ret
TRANSPOSE endp

START:
; set segment registers:
    mov ax, data
    mov ds, ax
    mov es, ax

    call TRANSPOSE
    
    mov ax, 0                           ; argument passed is flag to control colors
    push ax  
    
    lea ax, [msg1]                      ; argument for the string pointer
    push ax      
    
    call PRINT_MESSAGE
    add sp, 2*2
    
    mov ax, screen_step                 ; argument for the starting coordinate for the printing
    push ax   

    lea ax, [matrix_A]                  ; pass the pointer to the matrix to be printed
    push ax                                 
                  
    call PRINT_MATRIX          
    add sp, 2*2
    
    mov ax, 5*screen_step               ; same
    push ax  
    
    lea ax, [msg2]
    push ax   
    
    call PRINT_MESSAGE
    add sp, 2*2 
                          
    mov ax, 6*screen_step
    push ax                             ; pass as argument the start of the print  
    
    lea ax, [matrix_B]
    push ax                             ; pass the pointer to the matrix to be printed 
                     
    call PRINT_MATRIX          
    add sp, 2*2
    
    mov ax, 10*screen_step
    push ax   
    
    lea ax, [msg3]
    push ax   
    
    call PRINT_MESSAGE
    add sp, 2*2
    
    mov ax, 11*screen_step
    push ax   
    
    lea ax, [matrix_A]
    push ax  
    
    call PRINT_AVG
    add sp, 2*2
    
    mov ax, 13*screen_step
    push ax  
    
    lea ax, [msg4]
    push ax  
    
    call PRINT_MESSAGE
    add sp, 2*2
    
    mov ax, 14*screen_step
    push ax   
    
    lea ax, [matrix_B]
    push ax   
    
    call PRINT_AVG
    add sp, 2*2
    
    mov ax, 16*screen_step
    push ax   
    
    lea ax, [msg5]
    push ax   
    
    call PRINT_MESSAGE
    add sp, 2*2
    
    mov ax, 17*screen_step
    push ax    
    
    lea ax, [matrix_A]
    push ax  
    
    call PRINT_MAX
    add sp, 2*2
    
    mov ax, 19*screen_step
    push ax  
    
    lea ax, [msg6]
    push ax   
    
    call PRINT_MESSAGE
    add sp, 2*2
    
    mov ax, 20*screen_step
    push ax   
    
    lea ax, [matrix_B]
    push ax  
    
    call PRINT_MAX
    add sp, 2*2
   
ends

end start ; set entry point and stop the assembler.
