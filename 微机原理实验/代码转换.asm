
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

CRLF   MACRO 	 	 	 	 	      
	    MOV 	 	DL,   0DH 
        MOV 	 	AH,   02H  	  	 
	    INT  	 	21H 
	    
        MOV 	 	DL,   0AH  	 ;宏定义回车,换行 
        MOV 	 	AH,   02H 
        INT  	 	21H 
       ENDM 
 
DATA  SEGMENT 
    MES1    DB    'PLEASE INPUT THE SMALL LETTER,ENDED WITH ".":$' 
    MES2    DB    'THE CAPTAL LETTER IS:$' 
    SMALL   DB    50   	 	 	 	; 预留键盘输入缓冲区长度为50个 
        DB    0  	 	 	 	; 预留实际键盘输入字符数的个数 
        DB    50  DUP(0) 
    CAPITAL  DB   50  DUP(0)       ; 预留大写字母缓冲区长度为50个 
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
        LEA 	DX,   MES1        ;输岀提示信息MES1 
	    INT  	 	21H 
	    CRLF 	 	 	 	 	 	    ;宏调用 
 
        MOV 	 	AH,   0AH 
        MOV 	 	DX,OFFSET  SMALL      ; 接收小写字符串 
        INT  	 	21H 
        CRLF                            ;宏调用 
         
         MOV BX,OFFSET SMALL
         MOV DI,OFFSET CAPITAL
        
         MOV CX,20
      NEXT:
           MOV AL,[BX+2]
           MOV AH,AL;取字符
           CMP AL,2EH;判断是不是结束符'.'，这里可以改变使用我们想要的结束符
           JE KE
           CMP AL,'A'
           JL KE
           CMP AL,'Z'
           JB KE
           SUB AL,20H ;获得小写字母
           MOV [DI],AL
           INC BX
           INC DI
           LOOP NEXT

 
        KE:      	
	        MOV         AL,   '$'     ;大写字符串后加"$" 
	        MOV 	 	[DI],  AL 
 
	        MOV 	 	DX,   OFFSET  MES2     ; 输岀提示信息MES2 
	        MOV 	 	AH,   9 
	        INT  	 	21H 
            CRLF                               ;宏调用 
 
             MOV 	 	DX,   OFFSET  CAPITAL  
            MOV 	 	AH,   9                    ; 输岀大写字符串 
            INT  	 	21H 
            RET 
START  ENDP 
CODE   ENDS 	
        END 	 	START 




