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
    
GameLoop:
    mov cx,0
    mov xpos,0
    mov ypos,0
    
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
	
	;lea bx,tiles
	;add bx,frogPos
	;mov al,[bx]
	;mov newCode,al
	
    ;lea bx,tiles
	;add bx,frogPos
	;mov al,[bx]
	;mov oldCode,al
	
    ;lea bx,tiles
    ;add bx,oldPos
    ;mov al,oldCode
    ;mov [bx],al
    
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