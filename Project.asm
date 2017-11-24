include Drawing.inc
include InputMotion.inc
include Shift.inc

.model small

.stack 64

.data

tiles db 640 dup(3)    ;Code byte for the content of each tile 0:Status | 1:Frog | 2:Log main | 3:Water | 4:Pavement | 5:Road | 6: log beg. | 7: log end | 8: Car rear | 9: Car front | 10: endPoint

frogPos dw 610
BoundsFlag db ?

oldCode db 4
oldPos dw 2

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
    
    
GameLoop:
    mov cx,0
    mov xpos,0
    mov ypos,0
	
	cmp delayLoops,0
	jnz DelayedLoop
	;Shifting the rows
	mov bh,0
	mov bl,tiles
	
	;Shift bx 16 1 frogPos	
	;Shift bx 32 0 frogPos	
	;Shift bx 48 1 frogPos
	;Shift bx 64 0 frogPos
	
	;Shift bx 96 1 frogPos	
	;Shift bx 112 0 frogPos	
	;Shift bx 128 1 frogPos
	
	
	mov delayLoops,4
	DelayedLoop:
	dec delayLoops
	
	mov ax,frogPos
	mov oldPos,ax
	
	TakeInputGame frogPos, BoundsFlag
	
	lea bx,tiles
    add bx,oldPos
    mov al,oldCode
    mov [bx],al
	
	lea bx,tiles
	add bx,frogPos
	mov al,[bx]
	mov oldCode,al 
	
    lea bx,tiles
    add bx,frogPos
    mov [bx],01h
	
		
    drawCubes:       
    mov bx, offset tiles
    add bx,cx
    
    mov dl,[bx]
    
    cmp [bx],6
    jnz logBeg:
    
    ;Draw log beg
    
    jmp DoneDrawing
    logBeg:
    
    cmp [bx],7
    jnz logEnd:
    
    ;Draw log End
    
    jmp DoneDrawing
    logEnd:
    
    
    
    cmp [bx],1
    jnz Frog:
    
    ;Draw Frog
    
    jmp DoneDrawing
    Frog:
    
    cmp [bx],8
    jnz carBeg:
    
    ;Draw car Beg
    
    jmp DoneDrawing
    carBeg:
    
    cmp [bx],9
    jnz carEnd:
    
    ;Draw car end
    
    jmp DoneDrawing
    carEnd:    
        
    cmp [bx],2
    jnz logMain:
    
    ;Draw logMain
    
    jmp DoneDrawing
    logMain:
    
    
    DrawTileCode xpos ypos [bx]
    
    DoneDrawing:
    
    
    add xpos, 10
    cmp xpos, 320
    jnz rowCompleted
    mov xpos,0
    add ypos,10
    rowCompleted:    
    
    inc cx
    cmp cx,640
    jnz drawCubes 
jmp GameLoop 
 

hlt               