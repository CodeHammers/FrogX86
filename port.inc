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
receive MACRO value, flag 
	LOCAL read 
    LOCAL finish
	pusha
	
  ;Check that Data Ready
  mov dx,3FDH		; Line Status Register
  in al,dx 
  AND al,1
  jnz read 
  mov flag,0
  jmp finish

  read:
  ;If Ready read the VALUE in Receive data register
    mov flag,1
	mov dx,03F8H
	in al,dx 
	mov value,al

  finish:
  	popa
ENDM receive

receive3ady MACRO value
	LOCAL CHK
	pusha
	
	mov dx , 3FDH		; Line Status Register
	
	CHK:
	in al , dx 
  	AND al , 1
  	JZ CHK

 ;If Ready read the VALUE in Receive data register
  	mov dx , 03F8H
  	in al , dx 
  	mov VALUE , al
	
	popa
ENDM receive3ady