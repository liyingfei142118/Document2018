
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt


DATA  SEGMENT 
A	DW      1234H,  5678H   	 	;被加数 
B	DW      0FEDCH, 123AH  	 	;加数 
C	DW      2  DUP (?) 	 	 	 	;预留和 

AD  	 DW      0FEDCH, 0BA98H 	 	;被减数 
BD  	 DW      1234H,  789AH  	 	;减数 
CD  	 DW      2  DUP (?) 	 	 	 	;预留差
 
A1  	 DW      0D678H  	 	 	 	;被乘数 
B1  	 DW      0012H 	 	 	 	 	;乘数 
C1  	 DW      2  DUP (?) 	 	 	 	;预留积 

A2  	 DW      5678H,  0234H  	 	;被除数 
B2  	 DW      0F234H  	 	 	 	;除数 
C2  	 DW      2  DUP (?) 	 	 	 	;预留商,余数 
DATA  ENDS 
 
STACK1 	 SEGMENT  STACK  
         DB      100  DUP(0) 
STACK1 	 ENDS 
 
CODE   SEGMENT 
        ASSUME  CS:CODE,DS:DATA,SS:STACK1 
 
START  PROC  FAR       
    PUSH  DS 
	MOV 	AX,0          ;标准序 
	PUSH  	AX         
    MOV 	AX, DATA 
    MOV 	DS, AX 
	
	MOV 	AX, A 
	ADD 	AX,B 
	MOV 	C,AX 
	MOV 	AX,A+2            ;32位加32位 
    ADC     AX,B+2
    MOV     C+2,AX 

	MOV 	AX, AD 
	SUB 	AX,BD 
	MOV 	CD,AX 
	MOV 	AX,AD+2            ;32位减32位 
    SBB     AX,BD+2
    MOV     CD+2,AX
     
    XOR DX,DX
	MOV 	AX, A1 
	MUL 	B1 
	MOV 	C1,AX            ;16位乘16位 
    MOV     C1+2,DX 
    
    
    MOV 	AX, A2 
    MOV     DX,A2+2
	DIV 	B2 
	MOV 	C2,AX            ;32位除16位 
    MOV     C2+2,DX  
    POP    AX
    POP    DS
RET 
START ENDP 
 
CODE  ENDS 
        END       START 




