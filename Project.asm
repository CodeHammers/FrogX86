include Drawing.inc

.model small

.stack 64

.data

tiles db 160 dup(2)

xpos dw 0
ypos dw 0

color db 0

.code

mov ax,@data
mov ds,ax

mov ah,0
mov al,13h
int 10h

mov cx,16
PavementSet:
mov bx,offset tiles
add bx,cx
dec bx
mov [bx],4
loop PavementSet

mov cx,15
Water1Set:
inc cx
mov bx,offset tiles
add bx,cx
dec bx
mov [bx],3
cmp cx,64
jnz Water1Set

mov cx,0
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

 
 

hlt               