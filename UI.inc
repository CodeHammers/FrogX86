MACRO DrawVerticalLine startX, startY, length, color  
      ;StartX, StartY and length are words, color is a byte 
      LOCAL Draw
      pusha 
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
      LOCAL Draw
      pusha 
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

MACRO DrawFrog startX, startY
      pusha 
      ;Draw the frog's 4 legs
      mov cx, startX
      mov dx, startY
      inc cx 
      DrawVerticalLine cx,dx,4,010b
      add dx,5
      DrawVerticalLine cx,dx,4,010b
      mov cx, startX
      mov dx, startY
      add cx,8
      DrawVerticalLine cx,dx,4,010b
      add dx,5
      DrawVerticalLine cx,dx,4,010b

      ;Draw 4 feet
      mov cx, startX
      mov dx, startY
      inc dx
      DrawPixel cx,dx,010b
      add cx,9 
      DrawPixel cx,dx,010b 
      mov cx, startX
      mov dx, startY
      add dx,7
      DrawPixel cx,dx,010b
      add cx,9
      DrawPixel cx,dx,010b 

      ;Draw the connections between legs and body
      mov cx, startX
      mov dx, startY
      add cx,2
      add dx,3
      DrawPixel cx,dx,010b 
      add cx,5
      DrawPixel cx,dx,010b
      mov cx, startX
      mov dx, startY
      add dx,5
      add cx,2
      DrawPixel cx,dx,010b 
      add cx,5
      DrawPixel cx,dx,010b 
      
      ;Draw the frog body
      mov cx, startX
      mov dx, startY
      add cx,3
      add dx,2
      DrawVerticalLine cx,dx,6,110b
      add cx,3
      DrawVerticalLine cx,dx,6,110b
      mov cx, startX
      mov dx, startY
      add cx,4
      DrawVerticalLine cx,dx,9,110b
      inc cx
      DrawVerticalLine cx,dx,9,110b

      ;Draw the frog's eyes
      mov cx, startX
      mov dx, startY
      add cx,3
      inc dx
      DrawPixel cx,dx,100b
      add cx,3
      DrawPixel cx,dx,100b
      popa
ENDM DrawFrog


MACRO DrawCar startX, startY
      pusha 
	  ;car head
      mov cx,startX
      mov dx,startY
      add dx,2 ;car head starting y
      add cx,3 ;car head starting x
      mov ax,3 ;head is three pixels long
      mov bl,110b ;head color
      DrawHorizontalLine cx,dx,ax,bl

      ;car body
      mov cx,startX
      mov dx,startY
      add dx,3
      add cx,1
      mov ax,7

      mov bl,0

      Y_loop:

		DrawHorizontalLine cx,dx,ax,001b		
		inc dx
		inc bl
		cmp bl,4

      jne Y_loop

	  ;car tail
      mov cx,startX
      mov dx,startY
      add dx,8 ;car tail starting y
      add cx,3 ;car tail starting x
      mov ax,3 ;tail is three pixels long
      mov bl,110b ;tail color
      DrawHorizontalLine cx,dx,ax,bl
      

      popa
ENDM DrawCar

MACRO DrawLog startX,startY
	pusha
	mov cx, startX
    mov dx, startY
	
	add cx,2
	add dx,2
	DrawHorizontalLine cx,dx,5,06h
	
	inc dx
	dec cx
	DrawHorizontalLine cx,dx,7,06h
	
	inc dx
	dec cx
	DrawHorizontalLine cx,dx,9,06h
	
	inc dx
	inc cx
	DrawHorizontalLine cx,dx,7,06h
	
	inc dx
	inc cx
	DrawHorizontalLine cx,dx,5,06h
	
	popa
ENDM DrawLog