
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt


DATA  SEGMENT
         NUM  DB        12H,88H,82H,89H,33H,90H,0H,10H,0BDH,01H
           N  EQU       $-NUM
    POSITIVE  DB        0
    NEGATIVE  DB        0
        ZERO  DB        0
         SUM  DW        0 
         NOTE DB        "POSITIVE:",0DH,0AH,'$' 
         NOTE1 DB        "NEGATIVE:",0DH,0AH,'$'
         NOTE2 DB        "ZERO:",0DH,0AH,'$'
         NOTE3 DB        "SUM:",0DH,0AH,'$'
DATA  ENDS
         
STACK1  SEGMENT   STACK
              DB        100 DUP(0)
STACK1  ENDS
       
CODE  SEGMENT
              ASSUME    CS:CODE,DS:DATA,SS:STACK1
 START  PROC      
    
   
              PUSH      DS
              MOV       AX, 0       ;��׼��
              PUSH      AX
              MOV       AX, DATA
              MOV       DS, AX
              MOV       SI,OFFSET NUM
              MOV       CX,N ;����
              CLD           ;��������־
              MOV       BX,0
        NEXT0:
              LODSB ;ɨ���ֽ� ��siָ���һ���ֽڷ���al��
              CBW     ;  �ֽ�ת��Ϊ��
              
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
              
              MOV DX,OFFSET NOTE3
              MOV AH,9  ;����ַ���
              INT 21H 
              MOV       SUM,BX
              MOV       AX,BX
              CALL      DSPAXS

              MOV DX,OFFSET NOTE
              MOV AH,9
              INT 21H             
              MOV       AL,POSITIVE
              MOV       AH,0
              CALL      DSPAXS

              MOV DX,OFFSET NOTE1
              MOV AH,9
              INT 21H             
              MOV       AL,NEGATIVE
              MOV       AH,0
              CALL      DSPAXS

              MOV DX,OFFSET NOTE2
              MOV AH,9
              INT 21H             
              MOV       AL,ZERO
              MOV       AH,0
              CALL      DSPAXS
              
              POP AX
              POP DS
            ; RET
       START  ENDP

;============================
      DSPAXS  PROC      NEAR
              PUSH      AX
              TEST      AX,8000H ;Ӱ��SF��־
              JNS       @DSPAXS1;Ϊ��ת��SF
              
              PUSH      AX
              PUSH      DX
              
              MOV       AH,2  ;�������
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
              DIV       BX ;����AX ������DX
              
              INC       CX
              
              OR        DX,30H;ת��Ϊ�ַ����൱�ڼӡ�0��                                 
              
              PUSH      DX  ;������ջ
              CMP       AX,0
              JNE       @DSPAX1
             
              MOV       AH,2  ;���ϳ�ջ Ȼ�����
   @DISPAX2:
              POP       DX
              INT       21H
              LOOP      @DISPAX2
 
              MOV       DX,0DH;
              INT       21H            
              MOV       DX,0AH;
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


