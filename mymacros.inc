;-----------------MACROS------
ShowMessage MACRO MyMessage
pusha 
            mov ah,9h
            mov dx,offset MyMessage
            int 21h
popa
ENDM ShowMessage              

ShowThreeTimes MACRO MyMessage
               LOCAL AGAIN
                mov cx,3
                mov ah,9h
                mov dx,offset MyMessage
          AGAIN:int 21h 
                LOOP AGAIN
ENDM ShowThreeTimes 

TakeInput    Macro InputBuffer  ; take the value that shall be changed when taking an input 
		mov ah,0ah
		mov dx,offset InputBuffer; ah and dx are altered
		int 21h
ENDM TakeInput


DisplayChar  Macro char 
		mov ah,2 ;output whatever in dl as 1 char 
		mov dl,char
		int 21h
ENDM DisplayChar


NewLine     Macro
	DisplayChar 10
	DisplayChar 13
ENDM NewLine

ReadChar     Macro  Num
	mov ah,07
      int 21h
      mov dl, al
      mov ah, 0
      sub al,'0'
      mov Num,ax
      mov ah,2
      int 21h
ENDM ReadChar

ShowMessageAtPos MACRO Pos
            mov ah,9h
            mov dx,pos
            int 21h
ENDM ShowMessageAtPos	

PrintRegister MACRO Result
            LOCAL Loop1
            LOCAL loop2
            pusha
            mov cx,0
            mov bx,10
            mov si, offset Result
            Loop1:
                  mov dx,0
                  div bx
                  add dx,'0'
                  push dx
                  inc cx
                  cmp ax,9
                  jg Loop1

                  add ax,'0'
                  mov [si],ax

            Loop2:
                  pop ax
                  inc si
                  mov [si],ax
                  loop Loop2

            ShowMessage Result
            popa
ENDM PrintRegister

FromRegToString MACRO Result, Color  
            LOCAL Loop1
            LOCAL loop2
            LOCAL Fill
            LOCAL No
            pusha
            mov cx,0
            mov bx,10
            mov si, offset Result
            Loop1:
                  mov dx,0
                  div bx
                  add dx,'0'
                  push dx
                  inc cx
                  cmp ax,9
                  jg Loop1

                  mov bx,2
                  sub bx,cx

                  Fill:
                    jz No 
                    mov [si],'0' 
                    inc si
                    dec bx
                    jnz Fill

                  No:
                  add ax,'0'
                  mov [si],ax

            Loop2:
                  pop ax
                  inc si
                  mov [si],ax
                  loop Loop2

            ;Uncomment the following if you want a normal printable string (no color)
            ;inc si 
            ;mov [si], ' '
            ;inc si
            ;mov [si], '$'

            ;ShowMessage Result  (No color)
            popa

ENDM FromRegToString

PrintStringWithColor MACRO Message   
      LOCAL Loop1 
      pusha
      mov si, offset Message 
      mov di, 3  ;size of the message
      ; the color is stored in bl
      Loop1:
            mov al,[si]
            inc si 
            mov cx,1
            mov ah,9 
            int 10h

            mov ah,3h
            mov bh,0h
            int 10h 

            inc dl

            mov ah,2
            int 10h

            dec di
            jnz Loop1

            DisplayChar ' ' 
      popa
ENDM PrintStringWithColor

ReadDecimalNumber Macro input, output  
      LOCAL pow
      LOCAL NoPow
      LOCAL Convert
      LOCAL Sum

      TakeInput input 
      mov cl, input[1]
      dec cl
      mov bl,10
      mov al,1
      pow:
            cmp cl,0
            je Nopow
            mul bl
            dec cl
            jnz pow
             
      NoPow: 

      mov si, offset input+2
      mov bh, input[1]
      Convert:
            mov dl,[si]
            sub dl,'0'
            mov cl,al
            mov al,dl
            mul cl
            push ax
            mov ch,0
            mov ax,cx
            div bl
            inc si
            dec bh
            jnz Convert 
            
      mov cl, input[1] 
      mov bx, 0
      Sum:
            pop ax
            add bx,ax
            dec cl
            jnz Sum
       
       mov output,bl  ;up to 2-digits
       ;mov output,bx  ;up to 3-digits
ENDM ReadDecimalNumber

MACRO DrawVerticalLine startX, startY, length, color  
      ;StartX, StartY and length are words, color is a byte 
      pusha
      LOCAL Draw
      mov cx,startX
      mov dx,startY
      mov al,color 
      mov ah,0ch
      mov bx,startY
      add bx,length 

      Draw:
            int 10h
            inc dx
            cmp dx,bx
            jnz Draw 

      popa 
ENDM DrawVerticalLine

MACRO DrawHorizontalLine startX, startY, length, color  
      ;StartX, StartY and length are words, color is a byte
      pusha 
      LOCAL Draw 
      mov cx,startX
      mov dx,startY
      mov al,color 
      mov ah,0ch
      mov bx,startx
      add bx,length 

      Draw:
            int 10h
            inc cx
            cmp cx,bx
            jnz Draw 

      popa 
ENDM DrawHorizontalLine

MACRO DrawPixel x,y,color 
      pusha 
      mov cx,x
      mov dx,y
      mov al,color 
      mov ah,0ch
      int 10h
      popa
ENDM DrawPixel

CLEAR_SCREEN_UP MACRO 
      mov ax,0600h      ;Scroll Screen AH=06 (Scroll),AL=0 Entire Page
      mov bh,07         ;Normal attributes
      mov cx,0          ;from 0,0
      mov dx,184FH      ;To 18h,4fh
      int 10h   
ENDM CLEAR_SCREEN_UP

MOVECURSOR MACRO ROW,COL
      mov bh,00 
      MOV DH,ROW
      MOV DL,COL
      MOV AH,2
      INT 10H
ENDM MOVECURSOR

scroll MACRO from, to  
      mov ah,06h      ;Scroll Screen AH=06 (Scroll)
      mov al,01h
      mov bh,07         ;Normal attributes
      mov cx, from          ;from 0,0
      mov dx, to      ;To 18h,4fh
      int 10h     
ENDM scroll 

;-----------------------------		

;TEST
portinitialization MACRO  
	pusha
	
;Set Divisor Latch Access Bit
	mov dx,3fbh 			; Line Control Register
	mov al,10000000b		;Set Divisor Latch Access Bit
	out dx,al				;Out it

;Set LSB byte of the Baud Rate Divisor Latch register.
	mov dx,3f8h			
	mov al,0ch			
	out dx,al

;Set MSB byte of the Baud Rate Divisor Latch register.
	mov dx,3f9h
	mov al,00h
	out dx,al

;Set port configuration
	mov dx,3fbh
	mov al,00011011b
		;0:Access to Receiver buffer, Transmitter buffer
		;0:Set Break disabled
		;011:Even Parity
		;0:One Stop Bit
		;11:8bits
	out dx,al
	
	popa
ENDM portinitialization

;send a value
send MACRO value
	LOCAL AGAIN
	pusha
	
;Check that Transmitter Holding Register is Empty
	mov dx,3FDH		; Line Status Register
AGAIN:
	In al,dx 			;Read Line Status
  	AND al,00100000b
  	JZ AGAIN

;If empty put the VALUE in Transmit data register
  	mov dx,3F8H		; Transmit data register
  	mov al,value
  	out dx,al 

	popa
ENDM send

;recieve a value
receive MACRO value
	LOCAL read 
  LOCAL finish
	pusha
	
  ;Check that Data Ready
  mov dx,3FDH		; Line Status Register
  in al,dx 
  AND al,1
  jnz read 
  jmp finish

  read:
  ;If Ready read the VALUE in Receive data register
	mov dx,03F8H
	in al,dx 
	mov value,al

  finish:
  	popa
ENDM receive