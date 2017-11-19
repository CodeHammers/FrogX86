;-----------------MACROS------
ShowMessage MACRO MyMessage
            mov ah,9h
            mov dx,offset MyMessage
            int 21h
ENDM ShowMessage              

;--------------------------------
ShowThreeTimes MACRO MyMessage
               LOCAL AGAIN
                mov cx,3
                mov ah,9h
                mov dx,offset MyMessage
          AGAIN:int 21h 
                LOOP AGAIN
ENDM ShowThreeTimes
;-------------------------------------------------

DrawTile MACRO posX  posY Color1 Color2

LOCAL row
LOCAL column
LOCAL ColorChange
     
mov cx,posX      ;Column 
mov dx,posY       ;Row
mov al,Color1    ;Pixel color 
mov ah,0ch       ;Draw Pixel Command 

mov bl,0

row:
	mov cx,posX

	mov bh,0
	column:
		int 10h
		inc cx
		inc bh
		cmp bh,20
	jnz column

	inc dx
	inc bl 
	cmp bl,20  
jnz row      

ENDM DrawTile
;---------------------------------
DrawTileCode MACRO posX posY Code
LOCAL log
LOCAL water
LOCAL pavement

LOCAL row
LOCAL column
LOCAL ColorChange

mov al,0h
cmp Code,02h
jnz  log
mov al,06h
log:

cmp Code,03h
jnz  water
mov al,01h
water:

cmp Code,04h
jnz  pavement
mov al,07h
pavement:

mov cx,posX      ;Column 
mov dx,posY       ;Row
mov ah,0ch       ;Draw Pixel Command 

mov bl,0

row:
	mov cx,posX

	mov bh,0
	column:
		int 10h
		inc cx
		inc bh
		cmp bh,20
	jnz column

	inc dx
	inc bl 
	cmp bl,20  
jnz row 

ENDM DrawTileCode
;-----------------------------
InitializeArena MACRO

LOCAL PavementSet
LOCAL Water1Set
LOCAL RestSet
LOCAL Water2Set
LOCAL StartSet

mov cx,16
PavementSet:
mov bx,offset tiles
add bx,cx
dec bx
mov [bx],4
loop PavementSet

mov cx,16
Water1Set:
inc cx
mov bx,offset tiles
add bx,cx
dec bx
mov [bx],3
cmp cx,80
jnz Water1Set

mov cx,80
RestSet:
inc cx
mov bx,offset tiles
add bx,cx
dec bx
mov [bx],4
cmp cx,96
jnz RestSet

mov cx,96
Water2Set:
inc cx
mov bx,offset tiles
add bx,cx
dec bx
mov [bx],3
cmp cx,144
jnz Water2Set

mov cx,144
StartSet:
inc cx
mov bx,offset tiles
add bx,cx
dec bx
mov [bx],4
cmp cx,160
jnz StartSet

ENDM InitializeArena
;-----------------------------