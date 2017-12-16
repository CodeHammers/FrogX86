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
LOCAL NoDraw

LOCAL row
LOCAL column
LOCAL ColorChange

mov al,0h

cmp code,0h
jz NoDraw

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

NoDraw:

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
cmp cx,96
jnz Status

;Setting Water codes in the tiles
Water1Set:
inc cx
mov [bx],3
inc bx
cmp cx,288
jnz Water1Set

;Setting rest codes in the tiles
RestSet:
inc cx
mov [bx],4
inc bx
cmp cx,320
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

popA

ENDM InitializeArena
;-----------------------------

InitializeBlocks MACRO

;Manualy creating endpoints
mov tiles + 100,10
mov tiles + 104,10
mov tiles + 111,10
mov tiles + 119,10
mov tiles + 123,10

;Manualy creating Logs

mov tiles + 140,7
mov tiles + 141,2
mov tiles + 142,2
mov tiles + 143,2
mov tiles + 144,2
mov tiles + 145,2
mov tiles + 146,2
mov tiles + 147,6

mov tiles + 160,7
mov tiles + 161,2
mov tiles + 162,2
mov tiles + 163,2
mov tiles + 164,2
mov tiles + 165,2
mov tiles + 166,2
mov tiles + 167,6
mov tiles + 177,7
mov tiles + 178,2
mov tiles + 179,2
mov tiles + 180,2
mov tiles + 181,2
mov tiles + 182,2
mov tiles + 183,2
mov tiles + 184,6

mov tiles + 200,7
mov tiles + 201,2
mov tiles + 202,2
mov tiles + 203,2
mov tiles + 204,2
mov tiles + 205,2
mov tiles + 206,2
mov tiles + 207,6

mov tiles + 225,7
mov tiles + 226,2
mov tiles + 227,2
mov tiles + 228,2
mov tiles + 229,2
mov tiles + 230,2
mov tiles + 231,2
mov tiles + 232,6

mov tiles + 280,7
mov tiles + 281,2
mov tiles + 282,2
mov tiles + 283,2
mov tiles + 284,2
mov tiles + 285,2
mov tiles + 286,2
mov tiles + 287,6

;Manualy creating Cars
mov tiles + 324,9
mov tiles + 325,8
mov tiles + 326,9

mov tiles + 359,9
mov tiles + 360,8
mov tiles + 361,9

mov tiles + 394,9
mov tiles + 395,8
mov tiles + 396,9

mov tiles + 422,9
mov tiles + 423,8
mov tiles + 424,9


mov tiles + 458,9
mov tiles + 459,8
mov tiles + 460,9


mov tiles + 496,9
mov tiles + 497,8
mov tiles + 498,9

mov tiles + 535,9
mov tiles + 536,8
mov tiles + 537,9


mov tiles + 571,9
mov tiles + 572,8
mov tiles + 573,9

mov tiles + 605,9
mov tiles + 606,8
mov tiles + 607,9

ENDM InitializeBlocks

CLEAR_SCREEN_UP MACRO 
      mov ax,0600h      ;Scroll Screen AH=06 (Scroll),AL=0 Entire Page
      mov bh,07         ;Normal attributes
      mov cx,0          ;from 0,0
      mov dx,184FH      ;To 18h,4fh
      int 10h   
ENDM CLEAR_SCREEN_UP

MOVECURSOR MACRO ROW,COL
      mov bh,00 
      MOV DH,ROW
      MOV DL,COL
      MOV AH,2
      INT 10H
ENDM MOVECURSOR

scroll MACRO from, to  
      mov ah,06h      ;Scroll Screen AH=06 (Scroll)
      mov al,01h
      mov bh,07         ;Normal attributes
      mov cx, from          ;from 0,0
      mov dx, to      ;To 18h,4fh
      int 10h     
ENDM scroll 