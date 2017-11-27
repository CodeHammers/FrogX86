
;base_addr => offset address of an array
;sflag => 0 => shift left , 1=> shift right


Shift MACRO base_addr,start,sflag,froggy,froggy2
    
    LOCAL ShiftRight
    LOCAL ShiftLeft
    LOCAL shift_loopL
    LOCAL shift_loopR
    LOCAL Done
    LOCAL Frog_outL
    LOCAL Frog_outR
    LOCAL Frog_outL2
    LOCAL Frog_outR2
    pusha   
     mov ax,0
     mov bx,0
     mov cx,0
     mov dx,0

     mov cx,31
     add cx,base_addr
     add cx,start

     mov al,sflag
     cmp al,1
     jnz ShiftRight
     
     
     
     ShiftLeft:
     push cx
     cmp cx,froggy
     jb Frog_outL
     sub cx,31
     cmp cx,froggy
     ja Frog_outL
     dec froggy
     cmp cx,froggy
     jbe Frog_outL
     add cx,31
     mov froggy ,cx

    Frog_outL:
     pop cx
     cmp cx,froggy2
     jb Frog_outL2
     sub cx,31
     cmp cx,froggy2
     ja Frog_outL2
     dec froggy2
     cmp cx,froggy2
     jbe Frog_outL2
     add cx,31
     mov froggy2 ,cx




     Frog_outL2:
	   mov bx,base_addr 
		add bx, start 
       mov cx,31

       mov dh,[bx]
       shift_loopL:
         mov dl,[bx+1]
         mov [bx],dl
         inc bx
         ;cmp bx,31
         ;jne Shift_loopL 
		 loop shift_LoopL

       mov [bx],dh;put the first element in the last element
     
     jmp Done
     
     ShiftRight:
     push cx
     cmp cx,froggy
     jb Frog_outR
     sub cx,31
     cmp cx,froggy
     ja Frog_outR
     inc froggy
     add cx,31
     cmp cx,froggy
     jae Frog_outR
     sub cx,31
     mov froggy,cx

     Frog_outR:
     pop cx
     cmp cx,froggy2
     jb Frog_outR2
     sub cx,31
     cmp cx,froggy2
     ja Frog_outR2
     inc froggy2
     add cx,31
     cmp cx,froggy2
     jae Frog_outR2
     sub cx,31
     mov froggy2,cx

     Frog_outR2:
       mov bx,base_addr 
		add bx,start
       add bx,31
       mov dh,[bx]
	   mov cx,31
       shift_loopR:
         mov dl,[bx-1]
         mov [bx],dl
         dec bx
         ;cmp bx,base_addr
         ;jne Shift_loopR
		 loop shift_loopR 
       mov [bx],dh;put the last element in the first element
         
         
     
     Done:
    popa

ENDM Shift