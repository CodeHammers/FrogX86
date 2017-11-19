;Authors:
;Kareem Emad
;Kareem Emad
;Kareem Emad
;Kareem Emad
;---------------------------
        .MODEL SMALL
        .STACK 64
        .DATA

grid db 9 dup( 10 dup(?) ) ; 1 pavement + 3  + 1 pavement + 3 + 1 pavement = 9
        
        .code
MAIN    PROC FAR               
        MOV AX,@DATA
        MOV DS,AX 

        mov dx,9
        Draw_Loop:
            
            mov cx,10
            For_Each_Array:
                ;call draw with dx,cx,grid as Sx,Sy,gridoffset
                ;call shift with dx,cx,10,0 as Sx,Sy,gridsize,sflag
                dec cx
            loop For_Each_Array

            ;call check input
            dec dx
            cmp dx,0
        jae Draw_Loop


        
MAIN    ENDP
        END MAIN