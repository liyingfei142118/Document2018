                                        
/*module ControlUnit(func,op,Branch,Jump,RegDst,ALUsrc,funcop,aluop,MemtoReg,RegWr,MemWr,ExtOp,pcW,Rtype);
  input [5:0] func;
  input [5:0] op;
  output reg Branch;
  output reg Jump;
  output reg RegDst;
  output reg ALUsrc;
  output reg [2:0] funcop;
  output reg [2:0] aluop;
  output reg MemtoReg;
  output reg RegWr;
  output reg MemWr;
  output reg ExtOp;
  output reg pcW;
output reg Rtype;

//wire [2:0] ALUop2;
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
//assign ALUop=Rtype?ALUop1:ALUop2;
always @(func)begin
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
                                      
module ControlUnit(func,op,rt,Branch_bn,Branch_be,Jump,RegDst,ALUsrc,funcop,aluop,
MemtoReg,RegWr,MemWr,ExtOp,pcW,Rtype,Jr,Bgez, Bgtz, Blez, Bltz,_B,Jal,Jalr);
  input [5:0] func;
  input [5:0] op;
  input [4:0] rt;
  output reg  Branch_bn;
  output reg  Branch_be;
  output reg Jump;
  output reg RegDst;
  output reg ALUsrc;
  output reg [3:0] funcop;
  output reg [3:0] aluop;
  output reg MemtoReg;
  output reg RegWr;
  output reg MemWr;
  output reg ExtOp;
  output reg pcW;
  output reg Rtype;
  output reg Jr;
  output reg Bgez ;
  output reg Bgtz ;
  output reg Blez ;
  output reg Bltz ;
  output reg _B ;
  output reg Jal;
  output reg Jalr;


  initial begin
        Branch_bn=0;
        Branch_be=0;
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
	Jr=0;
        Bgez = 0;
        Bgtz = 0;
        Blez = 0;
        Bltz = 0;
	_B=0;
        Jal =0;
        Jalr=0;
  end


	
/*always @(func)begin
   funcop[3]=(func==6'b000010);
   funcop[2]=(func==6'b100100)//and
	||(func==6'b101010)//slt
	||(func==6'b101011)//sltu
	||(func==6'b100111);//nor
   funcop[1]=(func==6'b100101)//or
	||(func==6'b100110)//xor
	||(func==6'b100111);//nor
   funcop[0]=(func==6'b100101)//or
	||(func==6'b100010)//sub
	||(func==6'b101010)//slt
	||(func==6'b100011)//subu
	||(func==6'b101011);//sltu
end*/
always@(op or func ) begin 
   Rtype=(op==6'b000000);
   pcW=1;
   Branch_bn=(op==6'b000101);//bne
   Branch_be=(op==6'b000100);//beq
   Jump=(op==6'b000010);//jump
   RegDst=(op==6'b000000);
   ExtOp=(op==6'b100011)//lw
	||(op==6'b101011)//sw
	||(op==6'b001000)//addi
	||(op==6'b000001) //bgez & bltz
	||(op==6'b000111) //bgtz
	||(op==6'b000110) //blez
	||(op==6'b100000) //lb
	||(op==6'b100100) //lbu
	||(op==6'b101000) //sb
	||(op==6'b001010) //slti
	||(op==6'b001011) //sltiu
	||(op==6'b001001);//addiu

   ALUsrc=(op==6'b100011)//lw
	||(op==6'b101011)//sw
	||(op==6'b001000)//addi
	||(op==6'b001001)//addiu
	||(op==6'b100000) //lb
	||(op==6'b100100) //lbu
	||(op==6'b101000) //sb
	||(op==6'b001010) //slti
	||(op==6'b001011) //sltiu
	||(op==6'b001101);//ori

   MemtoReg=(op==6'b100000) //lb
	||(op==6'b100100) //lbu
	||(op==6'b100011);//lw
   RegWr=(op==6'b000000)//R
	||(op==6'b001000)//addi
	||(op==6'b100011)//lw
	||(op==6'b001001)//addiu
	||(op==6'b001100)//andi
	||(op==6'b001101)//ori
	||(op==6'b001110)//xori
	||(op==6'b100000) //lb
	||(op==6'b100100) //lbu
	||(op==6'b001010) //slti
	||(op==6'b001011) //sltiu
	||(op==6'b001111);//lui
   MemWr=(op==6'b101000)//sb
	||(op==6'b101011);//sw
   Rtype=op?0:1;
   Jr=(func==6'b001000&&op==6'b000000);
   Bgez = (op==6'b000001 && rt==5'b00001);
   Bgtz = (op==6'b000111 && rt==5'b00000);
   Blez = (op==6'b000110 && rt==5'b00000);
   Bltz = (op==6'b000001 && rt==5'b00000);
   _B = (op==6'b100000) || (op==6'b100100) || (op==6'b101000);         //sb && lb && lbu
   Jal = (op==6'b000011);
   Jalr=(func==6'b001001&&op==6'b000000);
   aluop[3]=(op==6'b001010) //slti
	||(op==6'b001111);//lui
   aluop[2]=(op==6'b001011) //sltiu
	||(op==6'b001010) //slti
	||(op==6'b001100 );//andi
   aluop[1]=(op==6'b001110)//xori
	||(op==6'b001101);//ori
   aluop[0]=(op==6'b000100)//beq
	||(op==6'b001101)//ori
	||(op==6'b000101)//bne
	||(op==6'b001010) //slti
	||(op==6'b001011) //sltiu
	||(op==6'b001111);//lui
 // 000110
   funcop[3]=(func==6'b000010)//srl
	||(func==6'b000011)//sra
	||(func==6'b000111)//srav
	||(func==6'b000110)//srlv
        ||(func==6'b000100);//sllv;
   funcop[2]=(func==6'b100100)//and
	||(func==6'b101010)//slt
	||(func==6'b101011)//sltu
	||(func==6'b000000)//sll
	||(func==6'b000111)//srav
	||(func==6'b000110)//srlv
	||(func==6'b100111);//nor
   funcop[1]=(func==6'b100101)//or
	||(func==6'b100110)//xor
	||(func==6'b100111)//nor
	||(func==6'b000000)//sll
	||(func==6'b000011)//sra
	||(func==6'b000110)//srlv
        ||(func==6'b000100);//sllv
   funcop[0]=(func==6'b100101)//or
	||(func==6'b100010)//sub
	||(func==6'b101010)//slt
	||(func==6'b100011)//subu
	||(func==6'b000000)//sll
	||(func==6'b000011)//sra
	||(func==6'b000110)//srlv
	||(func==6'b101011);//sltu

 end
endmodule
