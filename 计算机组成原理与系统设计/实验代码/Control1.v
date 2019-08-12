 module Control1(
input Rtype,
input [3:0] funcop,
input [3:0] aluop,
output [3:0] ALUop);
//to chose ALUop ,so I have  not ALUctr signal
assign ALUop=Rtype?funcop:aluop;

endmodule
