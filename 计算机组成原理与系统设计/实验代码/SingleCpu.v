
module SingleCPU(
    input CLK,
    input Reset,
    output [5:0] op,
    output [4:0] rs,
    output [4:0] rt,
    output [4:0] rd,
    output [5:0] func,
    output [25:0] targe,
    output [15:0] immediate,
    output [31:0] busA,
    output [31:0] busB,
    output [31:0] WriteData,
    output [31:0] DataOut,
    output [31:0] currentAddress,
    output [31:0] result,



   output [3:0] ALUop,
   output [3:0] funcop,
   output [3:0] aluop,
   output [31:0] B, 
   output [31:0]newAddress,
   output[31:0] Eimm,  
   output [4:0] WriteReg,  
   output Branch,
   output Jump,
   output RegDst,
   output ALUsrc,
   output MemtoReg,
   output RegWr,
   output MemWr,
   output ExtOp,
   output pcW,
   output Rtype);

//get pc
    PC pc(CLK, Reset,pcW, newAddress, currentAddress);

//according to func or op or rt to make sure others signal
    ControlUnit control(func,op,Branch,Jump,RegDst,ALUsrc,funcop,aluop,MemtoReg,RegWr,MemWr,ExtOp,pcW,Rtype);

//according to currentAdress to get op ,rs,rt,rd,shf,immediate,targe
//in order to next as compare
    InstructionMemory im(currentAddress, op, rs, rt, rd,func, immediate,targe);

        
 //it can get busA and busB to deliver to ALU
//and according to Jal and Jalr to save pc        
     RegisterFile rf(CLK, RegWr, rs, rt, WriteReg, WriteData, busA, busB);

//acorrding to Rtype to chose ALUop from aluop and funcop
    Control1 con(Rtype,funcop,aluop,ALUop);

//32 wei two Multiplexer
//according to ALUsrc to chose ALU'B from Eimm or busB
    Multiplexer32 m321(ALUsrc, Eimm, busB, B);


//ALU count
    ALU alu(ALUop,busA,B,  Zero, result);

// Sign or Zero Extend
    SignZeroExtend Extend(immediate, ExtOp, Eimm);  

//save data and read data
    DataMemory dm(CLK,MemWr,result,busB, DataOut); 

 
//5 wei two Multiplexer
//according RegDest to chose WriteReg from rd or st      
    Multiplexer5 m5(RegDst, rd, rt, WriteReg);

    
//according to MemtoReg to chose writeData from Dataout or result
    Multiplexer32 m322(MemtoReg,DataOut , result, WriteData);

//to acount npc
   NPC pc1(targe,immediate,Branch,Jump, Zero,currentAddress,newAddress);
   
   
endmodule