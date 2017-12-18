TakeGameInput MACRO FrogPos1, BoundsFlag1
    ;Inputs to this macro are the frog position (word) and a collision flag (byte)
    LOCAL KeyPressed
    LOCAL Up
    LOCAL Down
    LOCAL Right
    LOCAL Left
    LOCAL TouchedUp
    LOCAL TouchedDown
    LOCAL TouchedLeft
    LOCAL TouchedRight
    LOCAL Finished
    LOCAL AgainU
    LOCAL char 
    pusha 

    ;Get key pressed
    mov ah,1
    int 16h
    jnz KeyPressed ;If a key was pressed, let's process it
    jmp Finished   ;If not, return

    KeyPressed:
      mov ah,00   ;consume buffer
      int 16h     ;Ah holds the key status
      cmp ah,48h  ;(first player up)
      je Up 
      cmp ah,50h  ;(first player down)
      je Down  
      cmp ah,4bh  ;(first player left)
      je Left
      cmp ah,4dh  ;(first player right)
      je Right
      cmp al,0
      jne char 
      jmp Finished ;otherkey 

    Up:  
      mov BoundsFlag1,1  ;Set flag top   
      sub FrogPos1,32     ;y--
      cmp FrogPos1,64     ;if(y>=64 && y<=95) then it's in the top row (pavement)
      jb TouchedUp
      jae AgainU
      jmp Finished
      AgainU:
      cmp FrogPos1, 95
      jbe TouchedUp
      jmp Finished
      TouchedUp:
      jmp Finished
    
    Down:
      mov BoundsFlag1,2  ;Set flag buttom
      add FrogPos1, 32  ;y++
      cmp FrogPos1, 608  ;if(y>=608 && y<=639) then it's in the buttom row (pavement)
      jae TouchedDown
      jmp Finished
      TouchedDown:
      jmp Finished

    Right:
      mov BoundsFlag1,3 ;set flag right
      inc FrogPos1      ;x++
      mov ax, FrogPos1  ;if((x+1)%32==0) then it's on the right col
      inc ax
      mov bl,32
      div bl
      cmp ah,0
      je TouchedRight
      jmp Finished
      TouchedRight:
      jmp Finished

    Left:
      mov BoundsFlag1,4  ;set left
      dec FrogPos1
      mov ax, FrogPos1 ;if(y%32==0) then it's on the left col
      mov bl,32
      div bl
      cmp ah,0
      je TouchedLeft
      jmp Finished
      TouchedLeft:
      jmp Finished

    char:
      mov BoundsFlag1, al

    Finished:
        popa
ENDM TakeGameInput