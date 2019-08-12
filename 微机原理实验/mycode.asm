
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
       START  PROC      FAR
              PUSH      DS
              MOV       AX, 0       ;±ê×¼Ðò
              PUSH      AX
              MOV       AX, DATA
              MOV       DS, AX
              MOV       SI,OFFSET NUM
              MOV       CX,N
              CLD
              MOV       BX,0
        @M0:
              LODSB
              CBW
              ADD       BX,AX
              CMP       AL,0
              JG        @M1
              JL        @M2
              INC       ZERO
              JMP       @MM
        @M1:
              INC       POSITIVE
              JMP       @MM
        @M2:
              INC       NEGATIVE
        @MM:
              LOOP      @M0
               
              MOV       SUM,BX
              MOV       AX,BX
              CALL      DSPAXS
              MOV       AL,POSITIVE
              MOV       AH,0
              CALL      DSPAXS
              MOV       AL,NEGATIVE
              MOV       AH,0
              CALL      DSPAXS
              MOV       AL,ZERO
              MOV       AH,0
              CALL      DSPAXS
              RET
       START  ENDP
 
;============================
      DSPAXS  PROC      NEAR
              PUSH      AX
              TEST      AX,8000H
              JNS       @DSPAXS1
              PUSH      AX
              PUSH      DX
              MOV       AH,2
              MOV       DL,'-'
              INT       21H
              POP       DX
              POP       AX
              NEG       AX
   @DSPAXS1:
              CALL      DSPAX
              POP       AX
              RET
      DSPAXS  ENDP
;============================
       DSPAX  PROC      NEAR
              PUSH      AX
              PUSH      BX
              PUSH      CX
              PUSH      DX
              PUSHF
              XOR       CX,CX
              MOV       BX,10
    @DSPAX1:
              XOR       DX,DX
              DIV       BX
              INC       CX
              OR        DX,30H
              PUSH      DX
              CMP       AX,0
              JNE       @DSPAX1
              MOV       AH,2
   @DISPAX2:
              POP       DX
              INT       21H
              LOOP      @DISPAX2
              MOV       DL,32
              INT       21H
              POPF
              POP       DX
              POP       CX
              POP       BX
              POP       AX
              RET
       DSPAX  ENDP
;============================       
        CODE  ENDS
              END       START


