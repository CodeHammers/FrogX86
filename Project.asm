include Drawing.inc
include UI.inc 
include InputMotion.inc
include Shift.inc

.model small

.stack 64

.data

tiles db 640 dup(3)    ;Code byte for the content of each tile 0:Status | 1:Frog | 2:Log main | 3:Water | 4:Pavement | 5:Road | 6: log beg. | 7: log end | 8: Car rear | 9: Car front | 10: endPoint

frogPos dw 610
fakePos dw 610
BoundsFlag db ?

PlayerName1 db 'Sayed$'
PlayerName2 db 'Kareem$'
PlayerScore1 db '0$'
PlayerScore2 db '0$'
sep db '*******$'

;oldCode db 4
;oldPos dw 2

xpos dw 0
ypos dw 0

color db 0

delayLoops db 4

.code

mov ax,@data
mov ds,ax

mov ah,0
mov al,13h
int 10h

    
    InitializeArena    
    
    ;Drawing Background Once
    mov cx,0
    mov xpos,0
    mov ypos,0
    drawBackGround:       
        mov bx, offset tiles
        add bx,cx
        DrawTileCode xpos ypos [bx]    
        
        add xpos, 10
        cmp xpos, 320
        jnz BGrowCompleted
        mov xpos,0
        add ypos,10
        BGrowCompleted:    
    
    inc cx
    cmp cx,640
    jnz drawBackGround
    
    InitializeBlocks  

    ;Status bar
    ;ScoreBar PlayerName1,PlayerScore1,PlayerName2,PlayerScore2,sep   
    
GameLoop:

    ScoreBar PlayerName1,PlayerScore1,PlayerName2,PlayerScore2,sep

    mov cx,0
    mov xpos,0
    mov ypos,0
    ScoreBar PlayerName1,PlayerScore1,PlayerName2,PlayerScore2,sep  
	cmp delayLoops,0
	jnz DelayedLoop
	;Shifting the rows
	mov bh,0
	mov bl,tiles
	
	;Shift bx 16 1 frogPos	
	;Shift bx 32 0 frogPos	
	;Shift bx 48 1 frogPos
	;Shift bx 64 0 frogPos
	Shift bx 96 0 frogPos
    Shift bx 128 1 frogPos
	Shift bx 160 0 frogPos
	Shift bx 192 1 frogPos
    Shift bx 224 0 frogPos
	Shift bx 256 1 frogPos
	Shift bx 288 0 frogPos
    Shift bx 352 1 fakePos
    Shift bx 384 0 fakePos
    Shift bx 416 1 fakePos
	;Shift bx 96 1 frogPos	
	;Shift bx 112 0 frogPos	
	;Shift bx 128 1 frogPos
	
	mov delayLoops,4
	DelayedLoop:
	dec delayLoops
	
	;Testing the score
	push dx
	mov dl,delayLoops
	mov playerScore1,dl
	add playerScore1,'0'
	pop dx
	
	;mov ax,frogPos
	;mov oldPos,ax
	
	TakeInputGame frogPos, BoundsFlag
	
    lea bx,tiles
	add bx , frogPos
	mov al,tiles[bx]
    cmp al,3  ;water     
    je Dead 
    cmp al,8  ;Car front 
    je Dead 
    cmp al,9  ;Car end
    je Dead 
    jmp Alive 

    Dead:
        mov frogPos,610
    
    Alive:

	;lea bx,tiles
    ;add bx,oldPos
    ;mov al,oldCode
    ;mov [bx],al
	
	;lea bx,tiles
	;add bx,frogPos
	;mov al,[bx]
	;mov oldCode,al 
	
    ;lea bx,tiles
    ;add bx,frogPos
    ;mov [bx],01h
	
		
    drawCubes:       
    mov bx, offset tiles
    add bx,cx
    
    mov dl,[bx]
    
    cmp [bx],6
    jnz logBeg:
    
    ;Draw log beg------------------------
    push cx 
    push dx 
    mov cx, xpos
    mov dx, ypos
	
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
	
	;water filling
	mov dx,ypos
	DrawHorizontalLine cx, dx, 10, 001b
	inc dx
	DrawHorizontalLine cx, dx, 10, 001b
	inc dx
	add cx,6
	DrawHorizontalLine cx, dx, 4, 001b
	inc dx
	inc cx
	DrawHorizontalLine cx, dx, 3, 001b
	inc dx
	inc cx
	DrawHorizontalLine cx, dx, 2, 001b
	inc dx
	inc cx
	DrawHorizontalLine cx, dx, 1, 001b
	inc dx
	dec cx
	DrawHorizontalLine cx, dx, 2, 001b
	inc dx
	dec cx
	DrawHorizontalLine cx, dx, 3, 001b
	inc dx
	dec cx
	DrawHorizontalLine cx, dx, 4, 001b

    pop dx 
    pop cx 
    ;------------------------------------
    jmp DoneDrawing
    logBeg:
    
    cmp [bx],7
    jnz logEnd:
    
    ;Draw log End------------------------
    push cx
    push dx
    mov cx, xpos
    mov dx, ypos 
	
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
	;water filling
	mov cx,xpos
	mov dx,ypos
	DrawHorizontalLine cx, dx, 10, 001b
	inc dx
	DrawHorizontalLine cx, dx, 10, 001b
	inc dx
	DrawHorizontalLine cx, dx, 4, 001b
	inc dx
	DrawHorizontalLine cx, dx, 3, 001b
	inc dx
	DrawHorizontalLine cx, dx, 2, 001b
	inc dx
	DrawHorizontalLine cx, dx, 1, 001b
	inc dx
	DrawHorizontalLine cx, dx, 2, 001b
	inc dx
	DrawHorizontalLine cx, dx, 3, 001b
	inc dx
	DrawHorizontalLine cx, dx, 4, 001b
	
    pop dx
    pop cx 
    ;------------------------------------
    
    jmp DoneDrawing
    logEnd:
    
    
    cmp [bx],8
    jnz carBeg:
    
    ;Draw car Beg-----------------------
    push cx 
    push dx 
 	mov cx, xpos
    mov dx, ypos
	
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
	
	mov dx,ypos
	
	inc cx
	add dx,3
	DrawHorizontalLine cx, dx, 8, 11D
	
	inc dx
	DrawHorizontalLine cx, dx, 8, 11D
	
	inc dx
	DrawHorizontalLine cx, dx, 8, 11D
	
	inc dx
	DrawHorizontalLine cx, dx, 8, 11D
   pop dx 
    pop cx 
    ;--------------------------------------
    
    jmp DoneDrawing
    carBeg:
    
    cmp [bx],9
    jnz carEnd:
    
    ;Draw car end--------------------------
    push cx 
    push dx 
    mov cx, xpos
    mov dx, ypos
	
	;first wheel
	add cx,2
	DrawHorizontalLine cx, dx, 6, 14D
	
	inc dx
	DrawHorizontalLine cx, dx, 6, 14D
	
	;car body between the two wheels
	mov cx,xpos 
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
    pop dx 
    pop cx 
    ;--------------------------------------
    
    jmp DoneDrawing
    carEnd:    
        
    cmp [bx],2
    jnz logMain:
    
    ;Draw logMain--------------------------
    push cx 
    push dx 
    mov cx, xpos
    mov dx, ypos
	
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
	;water filling
	mov dx,ypos
	DrawHorizontalLine cx,dx,10,001b
	inc dx
	DrawHorizontalLine cx,dx,10,001b
	
    pop dx 
    pop cx 
    ;--------------------------------------
    
    jmp DoneDrawing
    logMain:
    
    
    DrawTileCode xpos ypos [bx]
    
    DoneDrawing:
    
    cmp cx,frogPos
    jnz Frog:
    
    ;Draw Frog----------------------------
    ;Draw the frog's 4 legs
      push cx 
      push dx 
      mov cx, xpos 
      mov dx, ypos 
      inc cx 
      DrawVerticalLine cx,dx,4,010b
      add dx,5
      DrawVerticalLine cx,dx,4,010b
      mov cx, xpos 
      mov dx, ypos
      add cx,8
      DrawVerticalLine cx,dx,4,010b
      add dx,5
      DrawVerticalLine cx,dx,4,010b

      ;Draw 4 feet
      mov cx, xpos 
      mov dx, ypos
      inc dx
      DrawPixel cx,dx,010b
      add cx,9 
      DrawPixel cx,dx,010b 
      mov cx, xpos 
      mov dx, ypos
      add dx,7
      DrawPixel cx,dx,010b
      add cx,9
      DrawPixel cx,dx,010b 

      ;Draw the connections between legs and body
      mov cx, xpos 
      mov dx, ypos
      add cx,2
      add dx,3
      DrawPixel cx,dx,010b 
      add cx,5
      DrawPixel cx,dx,010b
      mov cx, xpos 
      mov dx, ypos
      add dx,5
      add cx,2
      DrawPixel cx,dx,010b 
      add cx,5
      DrawPixel cx,dx,010b 
      
      ;Draw the frog body
      mov cx, xpos 
      mov dx, ypos
      add cx,3
      add dx,2
      DrawVerticalLine cx,dx,6,110b
      add cx,3
      DrawVerticalLine cx,dx,6,110b
      mov cx, xpos 
      mov dx, ypos
      add cx,4
      DrawVerticalLine cx,dx,9,110b
      inc cx
      DrawVerticalLine cx,dx,9,110b

      ;Draw the frog's eyes
      mov cx, xpos 
      mov dx, ypos
      add cx,3
      inc dx
      DrawPixel cx,dx,100b
      add cx,3
      DrawPixel cx,dx,100b
      pop dx 
      pop cx 
      ;--------------------------------
    
    ;jmp DoneDrawing
    Frog:
    
    add xpos, 10
    cmp xpos, 320
    jnz rowCompleted
    mov xpos,0
    add ypos,10
    rowCompleted:    
    
    inc cx
    cmp cx,640
    jnz drawCubes
    
    ScoreBar PlayerName1,PlayerScore1,PlayerName2,PlayerScore2,sep
     
jmp GameLoop 
 

hlt               