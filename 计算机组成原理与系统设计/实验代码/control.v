                                      
module ControlUnit(func,op,Branch,Jump,RegDst,ALUsrc,funcop,aluop,MemtoReg,RegWr,MemWr,ExtOp,pcW,Rtype);
  input [5:0] func;
  input [5:0] op;
  output reg Branch;
  output reg Jump;
  output reg RegDst;
  output reg ALUsrc;
  output reg [3:0] funcop;
  output reg [3:0] aluop;
  output reg MemtoReg;
  output reg RegWr;
  output reg MemWr;
  output reg ExtOp;
  output reg pcW;//it contral instrction's always have sign
  output reg Rtype;//it uses to chose ALUop from aluop and funcop

  initial begin
        Branch=0;
        Jump=0;
	RegDst=0;
	ALUsrc=0;
	funcop=3'b000;
        aluop=3'b000;
	MemtoReg=0;
	RegWr=0;
	MemWr=0;
	ExtOp=1;
	pcW=1;
        Rtype=0;
  end


//according  to op and func to make sure 
always @(func)begin
   funcop[3]=(func==6'b000010);
   funcop[2]=(func==6'b100100)||(func==6'b101010)||(func==6'b100111);
   funcop[1]=(func==6'b100101)||(func==6'b100111);
   funcop[0]=(func==6'b100101)||(func==6'b100010)||(func==6'b101010)||(func==6'b100011)||(func==6'b101010);
end
//I have more detail information at 36 singlecpu,then here have no more
always@(op ) begin 
   Rtype=(op==6'b000000);
   pcW=1;
   Branch=(op==6'b000100);
   Jump=(op==6'b000010);
	RegDst=(op==6'b000000);
   ExtOp=(op==6'b100011)||(op==6'b101011)||(op==6'b001000)||(op==6'b001001);

   ALUsrc=(op==6'b100011)||(op==6'b101011)||(op==6'b001000)||(op==6'b001001)||(op==6'b001101);

   MemtoReg=(op==6'b100011);
   RegWr=(op==6'b000000)||(op==6'b001000)||(op==6'b100011)||(op==6'b001001)||(op==6'b001101);
   MemWr=(op==6'b101011);
   Rtype=op?0:1;

   aluop[3]=0;
   aluop[2]=1'b0;
   aluop[1]=(op==6'b001101);
   aluop[0]=(op==6'b000100)||(op==6'b001101);
//assign ALUop=Rtype?ALUop1:ALUop2;
/*always @(func)begin
   funcop[2]=func[5]& !func[4]& !func[3]& func[2]& !func[1]& !func[0];
   funcop[1]=func[5]& !func[4]& !func[3]& func[2]& !func[1]& func[0];
   funcop[0]=(func[5]& !func[4]& !func[3]& func[2]& !func[1]& func[0])|(func[5]& !func[4]& !func[3]& !func[2]& func[1]& !func[0])|(func[5]& !func[4]& func[3]& !func[2]& !func[1]& func[0]);
end
always@(op ) begin 
   pcW=1;
   Branch=!op[5]& !op[4]& !op[3]& op[2]& !op[1]& !op[0];
   Jump=!op[5]& !op[4]& !op[3]& !op[2]& op[1]& !op[0];
	RegDst=!op[5]& !op[4]& !op[3]& !op[2]& !op[1]& !op[0];
   ExtOp=(op[5]& !op[4]& !op[3]& !op[2]& op[1]& op[0])|(op[5]& !op[4]& op[3]& !op[2]& op[1]& op[0])|(
            !op[5]& !op[4]& op[3]& !op[2]& !op[1]& !op[0]);

   ALUsrc=(op[5]& !op[4]& !op[3]& !op[2]& op[1]& op[0])|(op[5]& !op[4]& op[3]& !op[2]& op[1]& op[0])|(
            !op[5]& !op[4]& op[3]& !op[2]& !op[1]& !op[0]);*/

 end
endmodule
