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
		cmp bh,10
	jnz column

	inc dx
	inc bl 
	cmp bl,10  
jnz row      

ENDM DrawTile
;---------------------------------
DrawTileCode MACRO posX posY Code
pushA
LOCAL log
LOCAL logFront
LOCAL logRear
LOCAL water
LOCAL pavement
LOCAL frog
LOCAL road
LOCAL CarFront
LOCAL CarRear
LOCAL endPoint

LOCAL row
LOCAL column
LOCAL ColorChange

mov al,0h

cmp Code,02h
jnz  log
mov al,06h
log:
cmp Code,06h
jnz  logFront
mov al,06h
logFront:
cmp Code,07h
jnz  logRear
mov al,06h
logRear:

cmp Code,03h
jnz  water
mov al,01h
water:

cmp Code,04h
jnz  pavement
mov al,07h
pavement:

cmp Code,05h
jnz  road
mov al,08h
road:

cmp Code,01h
jnz  frog
mov al,010b
frog:

cmp Code,10
jnz  endPoint
mov al,14
endPoint:

cmp Code,8
jnz  CarFront
mov al,15
CarFront:
cmp Code,9
jnz  CarRear
mov al,15
CarRear:

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
		cmp bh,10
	jnz column

	inc dx
	inc bl 
	cmp bl,10  
jnz row 

popA
ENDM DrawTileCode
;-----------------------------
;-----------------------------
InitializeArena MACRO

LOCAL PavementSet
LOCAL Water1Set
LOCAL RestSet
LOCAL RoadSet
LOCAL StartSet
LOCAL STATUS

pushA

;Setting status codes in the tiles
mov cx,0
mov bx,offset tiles
Status:
inc cx
mov [bx],0
inc bx
cmp cx,64
jnz Status

;Setting status codes in the tiles
Water1Set:
inc cx
mov [bx],3
inc bx
cmp cx,320
jnz Water1Set

;Setting rest codes in the tiles
RestSet:
inc cx
mov [bx],4
inc bx
cmp cx,352
jnz RestSet

;Setting road codes in the tiles
RoadSet:
inc cx
mov [bx],5
inc bx
cmp cx,608
jnz RoadSet

;Setting pavement codes in the tiles
StartSet:
inc cx
mov [bx],4
inc bx
cmp cx,640
jnz StartSet

pushA

ENDM InitializeArena
;-----------------------------

InitializeBlocks MACRO

;Manualy creating endpoints
mov tiles + 68,10
mov tiles + 72,10
mov tiles + 79,10
mov tiles + 87,10
mov tiles + 91,10

;Manualy creating Logs
mov tiles + 140,7
mov tiles + 141,2
mov tiles + 142,2
mov tiles + 143,2
mov tiles + 144,2
mov tiles + 145,2
mov tiles + 146,2
mov tiles + 147,6

;Manualy creating Cars
mov tiles + 394,8
mov tiles + 395,9

ENDM InitializeBlocks