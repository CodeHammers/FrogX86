;sflag => flag to indicate whether to shift right or left
;0=> right , 1=>left
;size => the number of bytes in the array to be shifted of the array to be shifted
;base_addr => offset address of an array
;y => start of the array (y*size)


Shift MACRO size,base_addr,y,sflag
    
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
       mov al,size
       mov ah,y
       mul ah
       ;ah => start of my array 
       add bx,ax
       add ax,size
       
       mov dh,[bx]
       shift_loop:
         mov dl,[bx+1]
         mov [bx],dl
         inc bx
         cmp bx,ax
         jne ShiftRight 
       mov [bx],dh;put the first element in the last element
     
     jmp Done
     
     ShiftRight
       mov bx,base_addr 
       mov al,size
       mov ah,y
       mul ah
       ;ah => start of my array 
       add bx,ax
       add bx,size
       
       mov dh,[bx]
       shift_loop:
         mov dl,[bx-1]
         mov [bx],dl
         dec bx
         cmp bx,ax
         jne ShiftRight 
       mov [bx],dh;put the last element in the firwst element
         
         
     
     Done:
    popa

ENDM TakeInput