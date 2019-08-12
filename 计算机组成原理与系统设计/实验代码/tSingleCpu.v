




module tSingleCPU();

    reg CLK;
    reg Reset;

    wire [5:0] op;
    wire [4:0] rs;
    wire [4:0] rt;
   wire [4:0] rd;
   wire [5:0] func;
    wire [25:0] targe;
   wire [15:0] immediate;
    wire [31:0] busA;
   wire [31:0] busB;
    wire [31:0] WriteData;
    wire [31:0] DataOut;
    wire [31:0] currentAddress;
    wire [31:0] result;

   wire [3:0] ALUop;
   wire [3:0] funcop;
   wire[3:0] aluop;
   wire [31:0] B;
   wire [31:0]newAddress;
   wire[31:0] Eimm; 
   wire [4:0] WriteReg;  
   wire Branch;
   wire Jump;
   wire RegDst;
   wire ALUsrc;
   wire MemtoReg;
   wire RegWr;
   wire MemWr;
   wire ExtOp;
   wire pcW;
wire Rtype;

SingleCPU cpu(.CLK(CLK),.Reset(Reset),.op(op),.rs(rs),.rt(rt),.rd(rd),.func(func),.targe(targe),.immediate(immediate),.busA(busA),.busB(busB),
.WriteData(WriteData),.DataOut(DataOut),.currentAddress(currentAddress),.result(result),.ALUop(ALUop),.funcop(funcop),.aluop(aluop),.B(B),.newAddress(newAddress),
.Eimm(Eimm),.WriteReg(WriteReg),.Branch(Branch),.Jump(Jump),.RegDst(RegDst),.ALUsrc(ALUsrc),.MemtoReg(MemtoReg),.RegWr(RegWr),.MemWr(MemWr),.ExtOp(ExtOp),.pcW(pcW),.Rtype(Rtype));

initial
begin
CLK= 0; 
Reset=1;
#20 Reset=0;
end

always #10 CLK= ~CLK;
endmodule
