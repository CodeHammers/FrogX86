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
;delay for number of secs
delay macro sec
	pusha
    LOCAL Again
	mov ah,2ch 
	int 21h
	mov bl,dh
	add bl,sec
	cmp bl,60
    jl Again    
    sub bl,60
	Again:
	  int 21h
	  cmp dh,bl
	  jne Again
	  popa
ENDM delay

MainMenu MACRO mes1,mes2,mes3,mes4,chatFlag
	pusha
	LOCAL check
	LOCAL input
	LOCAL check2
	LOCAL EnterPressed
	
	mov ah,2
	mov bh,0
    mov dh,10
	mov dl,10
    int 10h
	
	PrintMessage mes1

	mov ah,2
	mov bh,0
    mov dh,12
	mov dl,10
    int 10h
	
	PrintMessage mes2
	
	mov ah,2
	mov bh,0
    mov dh,14
	mov dl,10
    int 10h
	
	PrintMessage mes3
	
	mov ah,2
	mov bh,0
    mov dh,16
	mov dl,10
    int 10h
	
	PrintMessage mes4
	
	mov ah,01h
	mov cx,2607h
	int 10h
	
	input:
	mov ah,0
    int 16h     ;AL:ASCII
	
	cmp al, 27
	jne check
	
	;ESC Pressed
	;clear screen
	mov ax, 0600h 
	mov bh, 00h
	mov cx, 0
	mov dl, 80
	mov dh, 25
	int 10h

	mov bx, 0

	;Set cursor to 0,0
	mov ah, 2
	mov dx, 0;X=0, Y=0
	int 10h
	
	mov ah, 4ch
	int 21h
	hlt
	
	check:
	cmp al,0dh ;Enter pressed
    je EnterPressed
	
	check2:
	cmp al,20h
	jne input
	
	mov chatFlag,1
	
	EnterPressed:
	
	popa
ENDM MainMenu

LevelMenu MACRO mes1,mes2,levelflag
	pusha
	LOCAL input
	LOCAL check2
	LOCAL finish
	
	mov ah,2
	mov bh,0
    mov dh,10
	mov dl,10
    int 10h
	
	PrintMessage mes1

	mov ah,2
	mov bh,0
    mov dh,12
	mov dl,10
    int 10h
	
	PrintMessage mes2
	
	mov ah,01h
	mov cx,2607h
	int 10h
	
	input:
	mov ah,0
    int 16h     ;AL:ASCII
	
	cmp al,31h
	jne check2
	mov levelflag,1
	jmp finish
	
	check2:
	cmp al,32h
	jne input
	
	mov levelflag,2
	
	finish:
	popa
ENDM LevelMenu

IntroScreen MACRO Mes1,Mes2,Mes3,MyBuffer,Username,ActualSize
	pusha
	LOCAL First
	LOCAL Checking
	LOCAL Invalid
	LOCAL ClearString
	LOCAL ClearScreen
	LOCAL DONE
	LOCAL WaitForENTER
	
	First:  
	mov ah,2
	mov bh,0
    mov dh,10
	mov dl,10
    int 10h
    
	PrintMessage Mes1
    	
    mov ah,2
	mov bh,0
    mov dh,11
	mov dl,10
    int 10h
    	
    	MOV AH,0AH        
        MOV DX,OFFSET MyBuffer                  
        INT 21h  
        
        MOV SI,OFFSET Username
        MOV CL,ActualSize
        MOV CH,0       
               
Checking: 
        CMP [SI],'z'
        JG Invalid
        
        CMP [SI],'a'
        JGE DONE
        
	    CMP [SI],'Z' 
        JG Invalid 
		
        CMP [SI],'A'
        JGE DONE
     
Invalid:
	mov ah,2
	mov bh,0
    mov dh,12
	mov dl,10
    int 10h
    
	PrintMessage Mes3
    delay 2
	
    	LEA DI,Username
        MOV CL,ActualSize
        MOV CH,0       
ClearString:
        MOV [DI],'$'
        INC DI
        LOOP ClearString 
        
ClearScreen:        
        MOV AX,0600H    ;06 TO SCROLL & 00 FOR FULLJ SCREEN
        MOV BH,00H      
        MOV CX,0000H    ;STARTING COORDINATES
        MOV DX,184FH    ;ENDING COORDINATES
        INT 10H
                 
        JMP First    	        
               
DONE:   INC SI
        LOOP Checking    
        
    mov ah,2
	mov bh,0
    mov dh,12
	mov dl,10
    int 10h
    
	PrintMessage Mes2
    	
    mov ah,01h
	mov cx,2607h
	int 10h
    	  
WaitForENTER:
        MOV AH,0
        INT 16H     ;AL:ASCII
        
        CMP AL,0DH
        JNE WaitForENTER
	
	popa
ENDM IntroScreen

ScoreBar MACRO PlayerName1, PlayerScore1, PlayerName2, PlayerScore2, sep 
      pusha
        mov ah,2
		mov bh,0
        mov dx,0000
        int 10h
		PrintMessage PlayerName1
        mov ah,2
		mov bh,0
        mov dx,0006
        int 10h
        PrintMessage PlayerScore1
        mov ah,2
        mov bh,0
		mov dx,0011
        int 10h
        PrintMessage sep
        mov ah,2
        mov bh,0
		mov dx,0032
        int 10h   
        PrintMessage PlayerScore2
        mov ah,2
        mov bh,0
		mov dx,0034
        int 10h
        PrintMessage PlayerName2
      popa 
ENDM ScoreBar

scrollVideo MACRO row 
	LOCAL label 
      pusha
	  mov al,8
	  mov dx,row 
	  mov cx,0
	  label:
	  	DrawHorizontalLine cx,dx,320,000b 
		inc dx 
		dec al 
		jnz label  
	  popa   
ENDM scrollVideo 