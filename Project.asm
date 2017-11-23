include Drawing.inc
include InputMotion.inc
include Shift.inc

.model small

.stack 64

.data

tiles db 160 dup(3)    ;Code byte for the content of each tile 1:Frog | 2:Log | 3:Water | 4:Pavement | 

frogPos dw 2
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

    pushA
    InitializeArena
    popA
    
    mov tiles+16,2
    mov tiles+17,2
    mov tiles+26,2
    mov tiles+27,2
    mov tiles+28,2
    
    mov tiles+38,2
    mov tiles+39,2
    mov tiles+40,2
    
    mov tiles+49,2
    mov tiles+50,2
    mov tiles+51,2
    mov tiles+59,2
    mov tiles+60,2
    mov tiles+61,2
    
    mov tiles+67,2
    mov tiles+68,2
    mov tiles+69,2
    mov tiles+70,2
    mov tiles+71,2
    mov tiles+72,2
    
    mov tiles+77,2
    mov tiles+78,2
    mov tiles+79,2 
    
    
    mov tiles+96,2
    mov tiles+97,2
    mov tiles+106,2
    mov tiles+107,2
    mov tiles+108,2
    
    mov tiles+118,2
    mov tiles+119,2
    mov tiles+120,2
    
    mov tiles+129,2
    mov tiles+130,2
    mov tiles+131,2
    mov tiles+139,2
    mov tiles+140,2
    mov tiles+141,2
    
GameLoop:
    mov cx,0
    mov xpos,0
    mov ypos,0
	
	cmp delayLoops,0
	jnz DelayedLoop
	;Shifting the rows
	mov bh,0
	mov bl,tiles
	
	Shift bx 16 1 frogPos	
	Shift bx 32 0 frogPos	
	Shift bx 48 1 frogPos
	Shift bx 64 0 frogPos
	
	Shift bx 96 1 frogPos	
	Shift bx 112 0 frogPos	
	Shift bx 128 1 frogPos
	
	
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
    
    pushA
    DrawTileCode xpos ypos [bx]
    popA
    
    add xpos, 20
    cmp xpos, 320
    jnz rowCompleted
    mov xpos,0
    add ypos,20
    rowCompleted:
    
    
    inc cx
    cmp cx,160
    jnz drawCubes 
jmp GameLoop 
 

hlt               