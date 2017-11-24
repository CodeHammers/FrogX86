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
    LOCAL AgainU
    LOCAL HopForwards
    LOCAL HopBackwards 
    LOCAL AgainUHop
    LOCAL TouchedUpHop
    LOCAL TouchedDownHop
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
        cmp ah,11h  ;w (hop forward)
        je HopForwards
        cmp ah,1fh ;s (hop backwards)
        je HopBackwards
        jmp Finished ;otherkey 

    Up:     
        sub FrogPos,32     ;y--
        cmp FrogPos,64     ;if(y>=64 && y<=95) then it's in the top row (pavement)
        jb TouchedUp
        jae AgainU
        jmp Finished
        AgainU:
            cmp FrogPos, 95
            jbe TouchedUp
            jmp Finished
        TouchedUp:
            mov BoundsFlag,1  ;Set flag top
            jmp Finished
    
    Down:
        add FrogPos, 32  ;y++
        cmp FrogPos, 608  ;if(y>=608 && y<=639) then it's in the buttom row (pavement)
        jae TouchedDown
        jmp Finished
        TouchedDown:
            mov BoundsFlag,2  ;Set flag buttom
            jmp Finished

    Right:
        inc FrogPos      ;x++
        mov ax, FrogPos  ;if((x+1)%32==0) then it's on the right col
        inc ax
        mov bl,32
        div bl
        cmp ah,0
        je TouchedRight
        jmp Finished
        TouchedRight:
            mov BoundsFlag,3 ;set flag right
            jmp Finished

    Left:
        dec FrogPos
        mov ax, FrogPos ;if(y%32==0) then it's on the left col
        mov bl,32
        div bl
        cmp ah,0
        je TouchedLeft
        jmp Finished
        TouchedLeft:
            mov BoundsFlag,4  ;set left
            jmp Finished

    HopForwards:
        sub FrogPos,64     ; y-=2
        cmp FrogPos,64     ;if(y>=64 && y<=95) then it's in the top row (pavement)
        jb TouchedUpHop
        jae AgainUHop
        jmp Finished
        AgainUHop:
            cmp FrogPos,95
            jbe TouchedUpHop
            jmp Finished
        TouchedUpHop:
            mov BoundsFlag,1  ;Set flag top
            jmp Finished

    HopBackwards:
        add FrogPos,64    ;y+=2
        cmp FrogPos, 608  ;if(y>=608 && y<=639) then it's in the buttom row (pavement)
        jae TouchedDownHop
        jmp Finished
        TouchedDownHop:
            mov BoundsFlag,2  ;Set flag buttom
            jmp Finished
    
    Finished:
        popa

ENDM TakeInputGame