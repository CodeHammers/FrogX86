TakeInputGame MACRO FrogPos, BoundsFlag
    ;Inputs to this macro are the frog position (word) and a collision flag (byte)
    LOCAL KeyPressed
    LOCAL Up
    LOCAL Down
    LOCAL Right
    LOCAL Left
    LOCAL Finished
    LOCAL TouchedUp
    LOCAL TouchedDown
    LOCAL TouchedLeft
    LOCAL TouchedRight
    LOCAL AgainD

    pusha 

    ;Get key pressed
    mov ah,1
    int 16h
    jnz KeyPressed ;If a key was pressed, let's process it
    jmp Finished   ;If not, return

    KeyPressed:
        mov ah,00   ;consume buffer
        int 16h     ;Ah holds the key status
        cmp ah,48h  ;up
        je Up 
        cmp ah,50h  ;down
        je Down  
        cmp ah,4bh  ;left
        je Left
        cmp ah,4dh  ;right
        je Right 
    
    Up:     
        sub FrogPos, 16    ;y--
        cmp FrogPos,15     ;if(y>=0 && y<=15) then it's in the top row (pavement)
        jbe TouchedUp
        jmp Finished
        TouchedUp:
            mov BoundsFlag,1  ;Set flag top
            jmp Finished
    
    Down:
        add FrogPos, 16  ;y++
        cmp FrogPos, 144  ;if(y>=144 && y<=159) then it's in the buttom row (pavement)
        jae AgainD
        jmp Finished
        AgainD:
            cmp FrogPos, 159
            jbe TouchedDown
            jmp Finished
        TouchedDown:
            mov BoundsFlag,2  ;Set flag buttom
            jmp Finished

    Right:
        inc FrogPos      ;x++
        mov ax, FrogPos  ;if((x+1)%16==0) then it's on the right col
        inc ax
        mov bl,16
        div bl
        cmp ah,0
        je TouchedRight
        jmp Finished
        TouchedRight:
            mov BoundsFlag,3 ;set flag right
            jmp Finished

    Left:
        dec FrogPos
        mov ax, FrogPos ;if(y%16==0) then it's on the left col
        mov bl,16
        div bl
        cmp ah,0
        je TouchedLeft
        jmp Finished
        TouchedLeft:
            mov BoundsFlag,4  ;set left
            jmp Finished

    Finished:
        popa

ENDM TakeInputGame