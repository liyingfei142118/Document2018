
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

CRLF   MACRO 	 	 	 	 	      
	    MOV 	 	DL,   0DH 
        MOV 	 	AH,   02H  	  	 
	    INT  	 	21H 
	    
        MOV 	 	DL,   0AH  	 ;�궨��س�,���� 
        MOV 	 	AH,   02H 
        INT  	 	21H 
       ENDM 
 
DATA  SEGMENT 
    MES1    DB    'PLEASE INPUT THE SMALL LETTER,ENDED WITH ".":$' 
    MES2    DB    'THE CAPTAL LETTER IS:$' 
    SMALL   DB    50   	 	 	 	; Ԥ���������뻺��������Ϊ50�� 
        DB    0  	 	 	 	; Ԥ��ʵ�ʼ��������ַ����ĸ��� 
        DB    50  DUP(0) 
    CAPITAL  DB   50  DUP(0)       ; Ԥ����д��ĸ����������Ϊ50�� 
DATA    ENDS 
 
STACK1  SEGMENT STACK 
        DB      100  DUP (0) 
STACK1  ENDS 
 
CODE  SEGMENT 
ASSUME CS:CODE,DS:DATA,SS:STACK1 

START PROC     FAR 
PUSH   	DS 
        MOV 	AX,   0 
        PUSH  	AX 
        MOV 	AX,   DATA 
        MOV 	DS,   AX 
        
        
        MOV 	AH,   9  	 	 	 
        LEA 	DX,   MES1        ;�����ʾ��ϢMES1 
	    INT  	 	21H 
	    CRLF 	 	 	 	 	 	    ;����� 
 
        MOV 	 	AH,   0AH 
        MOV 	 	DX,OFFSET  SMALL      ; ����Сд�ַ��� 
        INT  	 	21H 
        CRLF                            ;����� 
         
         MOV BX,OFFSET SMALL
         MOV DI,OFFSET CAPITAL
        
         MOV CX,20
      NEXT:
           MOV AL,[BX+2]
           MOV AH,AL;ȡ�ַ�
           CMP AL,2EH;�ж��ǲ��ǽ�����'.'��������Ըı�ʹ��������Ҫ�Ľ�����
           JE KE
           CMP AL,'A'
           JL KE
           CMP AL,'Z'
           JB KE
           SUB AL,20H ;���Сд��ĸ
           MOV [DI],AL
           INC BX
           INC DI
           LOOP NEXT

 
        KE:      	
	        MOV         AL,   '$'     ;��д�ַ������"$" 
	        MOV 	 	[DI],  AL 
 
	        MOV 	 	DX,   OFFSET  MES2     ; �����ʾ��ϢMES2 
	        MOV 	 	AH,   9 
	        INT  	 	21H 
            CRLF                               ;����� 
 
             MOV 	 	DX,   OFFSET  CAPITAL  
            MOV 	 	AH,   9                    ; ����д�ַ��� 
            INT  	 	21H 
            RET 
START  ENDP 
CODE   ENDS 	
        END 	 	START 




