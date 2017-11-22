
;base_addr => offset address of an array
;sflag => 0 => shift left , 1=> shift right


Shift MACRO base_addr,start,sflag
    
    LOCAL ShiftRight
    LOCAL ShiftLeft
    
    pusha   
     mov ax,0
     mov bx,0
     mov cx,0
     mov dx,0
             
     mov al,sflag
     cmp al,1
     jnz ShiftRight
     
     
     
     ShiftLeft:
       mov bx,base_addr 
		add bx, start 
       
       mov dh,[bx]
       shift_loop:
         mov dl,[bx+1]
         mov [bx],dl
         inc bx
         cmp bx,15
         jne ShiftRight 
		 
       mov [bx],dh;put the first element in the last element
     
     jmp Done
     
     ShiftRight
       mov bx,base_addr 
		add bx,start
       add bx,15
       mov dh,[bx]
       shift_loop:
         mov dl,[bx-1]
         mov [bx],dl
         dec bx
         cmp bx,base_addr
         jne ShiftRight 
       mov [bx],dh;put the last element in the first element
         
         
     
     Done:
    popa

ENDM Shift