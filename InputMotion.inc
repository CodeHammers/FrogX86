TakeGameInput MACRO FrogPos1, FrogPos2, BoundsFlag1, BoundsFlag2
    ;Inputs to this macro are the frog position (word) and a collision flag (byte)
    LOCAL KeyPressed
    LOCAL Up
    LOCAL Down
    LOCAL Right
    LOCAL Left
    LOCAL UpSecond
    LOCAL DownSecond
    LOCAL RightSecond
    LOCAL LeftSecond 
    LOCAL Finished
    LOCAL TouchedUp
    LOCAL TouchedDown
    LOCAL TouchedLeft
    LOCAL TouchedRight
    LOCAL Finished
    LOCAL TouchedUpSecond
    LOCAL TouchedDownSecond
    LOCAL TouchedLeftSecond
    LOCAL TouchedRightSecond
    LOCAL AgainU
    LOCAL AgainUSecond
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
      cmp ah,11h  ;w (second player up)
      je UpSecond
      cmp ah,1fh  ;s (second player down)
      je DownSecond
      cmp ah,20h  ;d (second player right)
      je RightSecond
      cmp ah,1Eh  ;a (second player left)
      je LeftSecond
      jmp Finished ;otherkey 

    Up:     
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
      mov BoundsFlag1,1  ;Set flag top
      jmp Finished
    
    UpSecond:
      sub FrogPos2,32     ;y--
      cmp FrogPos2,64     ;if(y>=64 && y<=95) then it's in the top row (pavement)
      jb TouchedUpSecond
      jae AgainUSecond
      jmp Finished
      AgainUSecond:
      cmp FrogPos2, 95
      jbe TouchedUpSecond
      jmp Finished
      TouchedUpSecond:
      mov BoundsFlag2,1  ;Set flag top
      jmp Finished

    Down:
      add FrogPos1, 32  ;y++
      cmp FrogPos1, 608  ;if(y>=608 && y<=639) then it's in the buttom row (pavement)
      jae TouchedDown
      jmp Finished
      TouchedDown:
      mov BoundsFlag1,2  ;Set flag buttom
      jmp Finished

    DownSecond:
      add FrogPos2, 32  ;y++
      cmp FrogPos2, 608  ;if(y>=608 && y<=639) then it's in the buttom row (pavement)
      jae TouchedDownSecond
      jmp Finished
      TouchedDownSecond:
      mov BoundsFlag2,2  ;Set flag buttom
      jmp Finished

    Right:
      inc FrogPos1      ;x++
      mov ax, FrogPos1  ;if((x+1)%32==0) then it's on the right col
      inc ax
      mov bl,32
      div bl
      cmp ah,0
      je TouchedRight
      jmp Finished
      TouchedRight:
      mov BoundsFlag1,3 ;set flag right
      jmp Finished

    RightSecond:
      inc FrogPos2      ;x++
      mov ax, FrogPos2  ;if((x+1)%32==0) then it's on the right col
      inc ax
      mov bl,32
      div bl
      cmp ah,0
      je TouchedRightSecond
      jmp Finished
      TouchedRightSecond:
      mov BoundsFlag2,3 ;set flag right
      jmp Finished

    Left:
      dec FrogPos1
      mov ax, FrogPos1 ;if(y%32==0) then it's on the left col
      mov bl,32
      div bl
      cmp ah,0
      je TouchedLeft
      jmp Finished
      TouchedLeft:
      mov BoundsFlag1,4  ;set left
      jmp Finished

    LeftSecond:
      dec FrogPos2
      mov ax, FrogPos2 ;if(y%32==0) then it's on the left col
      mov bl,32
      div bl
      cmp ah,0
      je TouchedLeftSecond
      jmp Finished
      TouchedLeftSecond:
      mov BoundsFlag2,4  ;set left
      jmp Finished

    Finished:
        popa
ENDM TakeGameInput