
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt


DATA  SEGMENT
         NUM  DB        12H,88H,82H,89H,33H,90H,0H,10H,0BDH,01H
           N  EQU       $-NUM
    POSITIVE  DB        0
    NEGATIVE  DB        0
        ZERO  DB        0
         SUM  DW        0 
DATA  ENDS
         
STACK1  SEGMENT   STACK
              DB        100 DUP(0)
STACK1  ENDS
       
CODE  SEGMENT
              ASSUME    CS:CODE,DS:DATA,SS:STACK1
 START  PROC      
    
   
              PUSH      DS
              MOV       AX, 0       ;标准序
              PUSH      AX
              MOV       AX, DATA
              MOV       DS, AX
              MOV       SI,OFFSET NUM
              MOV       CX,N ;总数
              CLD           ;清除方向标志
              MOV       BX,0
        NEXT0:
              LODSB ;扫描字节 将si指向的一个字节放入al中
              CBW     ;  字节转换为字
              
              ADD       BX,AX
              CMP       AL,0
              
              JG        NEXT1
              JL        NEXT2
              INC       ZERO
              
              JMP       NEXT4
        NEXT1:
              INC       POSITIVE
              JMP       NEXT4
       NEXT2:
              INC       NEGATIVE
       NEXT4:
              LOOP      NEXT0
              MOV SUM,BX
       START  ENDP
    
           CODE  ENDS
              END       START






