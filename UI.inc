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

MACRO CleanCell startX, startY, color 
      pusha
      LOCAL Clean 
      mov bx,10
      Clean:
            DrawVerticalLine startX,startY,10,color 
            dec bx
            jnz Clean 
      popa
ENDM CleanCell

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

MACRO DrawSidesCar startX,startY
	pusha
	
	mov cx, startX
      mov dx, startY
	
	;first wheel
	add cx,2
	DrawHorizontalLine cx, dx, 6, 14D
	
	inc dx
	DrawHorizontalLine cx, dx, 6, 14D
	
	;car body between the two wheels
	mov cx,startX
	inc dx
	DrawHorizontalLine cx, dx, 10, 001b
	
	inc dx
	DrawHorizontalLine cx, dx, 10, 001b
	
	inc dx
	DrawHorizontalLine cx, dx, 10, 001b
	
	inc dx
	DrawHorizontalLine cx, dx, 10, 001b
	
	inc dx
	DrawHorizontalLine cx, dx, 10, 001b
	
	inc dx
	DrawHorizontalLine cx, dx, 10, 001b
	
	;second wheel
	inc dx
	add cx,2
	DrawHorizontalLine cx, dx, 6, 14D
	
	inc dx
	DrawHorizontalLine cx, dx, 6, 14D

	popa
ENDM DrawSidesCar

MACRO DrawMiddleCar startX,startY
	pusha
	
	mov cx, startX
      mov dx, startY
	
	add dx,2
	DrawHorizontalLine cx, dx, 10, 001b
	
	inc dx
	DrawHorizontalLine cx, dx, 10, 001b
	
	inc dx
	DrawHorizontalLine cx, dx, 10, 001b
	
	inc dx
	DrawHorizontalLine cx, dx, 10, 001b
	
	inc dx
	DrawHorizontalLine cx, dx, 10, 001b
	
	inc dx
	DrawHorizontalLine cx, dx, 10, 001b
	
	mov dx,startY
	
	inc cx
	add dx,3
	DrawHorizontalLine cx, dx, 8, 11D
	
	inc dx
	DrawHorizontalLine cx, dx, 8, 11D
	
	inc dx
	DrawHorizontalLine cx, dx, 8, 11D
	
	inc dx
	DrawHorizontalLine cx, dx, 8, 11D

	popa
ENDM DrawMiddleCar

MACRO DrawBackLog startX,startY
	pusha
	
	mov cx, startX
      mov dx, startY
	
	add cx,4
	add dx,2
	DrawHorizontalLine cx, dx, 6, 06h
	
	inc dx
	dec cx
	DrawHorizontalLine cx, dx, 7, 06h
	
	inc dx
	dec cx
	DrawHorizontalLine cx, dx, 8, 06h
	
	inc dx
	dec cx
	DrawHorizontalLine cx, dx, 9, 06h
	
	inc dx
	inc cx
	DrawHorizontalLine cx, dx, 8, 06h
	
	inc dx
	inc cx
	DrawHorizontalLine cx, dx, 7, 06h
	
	inc dx
	inc cx
	DrawHorizontalLine cx, dx, 6, 06h
	
	popa
ENDM DrawBackLog

MACRO DrawMiddleLog startX,startY
	pusha
	
	mov cx, startX
      mov dx, startY
	
	add dx,2
	DrawHorizontalLine cx,dx,10,06h
	
	inc dx
	DrawHorizontalLine cx,dx,10,06h
	
	inc dx
	DrawHorizontalLine cx,dx,10,06h
	
	inc dx
	DrawHorizontalLine cx,dx,10,06h
	
	inc dx
	DrawHorizontalLine cx,dx,10,06h
	
	inc dx
	DrawHorizontalLine cx,dx,10,06h
	
	inc dx
	DrawHorizontalLine cx,dx,10,06h
	
	popa
ENDM DrawMiddleLog

MACRO DrawFrontLog startX,startY
	pusha
	
	mov cx, startX
      mov dx, startY
	
	add dx,2
	DrawHorizontalLine cx, dx, 6, 06h
	
	inc dx
	DrawHorizontalLine cx, dx, 7, 06h
	
	inc dx
	DrawHorizontalLine cx, dx, 8, 06h
	
	inc dx
	DrawHorizontalLine cx, dx, 9, 06h
	
	inc dx
	DrawHorizontalLine cx, dx, 8, 06h
	
	inc dx
	DrawHorizontalLine cx, dx, 7, 06h
	
	inc dx
	DrawHorizontalLine cx, dx, 6, 06h
	
	popa
ENDM DrawFrontLog

PrintMessage MACRO MyMessage
      pusha 
      mov ah,9h
      mov dx,offset MyMessage
      int 21h
      popa 
ENDM PrintMessage      

ScoreBar MACRO PlayerName1, PlayerScore1, PlayerName2, PlayerScore2, sep 
      pusha
        PrintMessage PlayerName1
        mov ah,2
        mov dx,0006
        int 10h
        PrintMessage PlayerScore1
        mov ah,2
        mov dx,0015
        int 10h
        PrintMessage sep
        mov ah,2
        mov dx,0032
        int 10h   
        PrintMessage PlayerScore2
        mov ah,2
        mov dx,0034
        int 10h
        PrintMessage PlayerName2
      popa 
ENDM ScoreBar