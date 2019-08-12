
module DataMemory(
    input [5:0] op,
    input CLK,
    input MemWr,
    input _B, 
    input [31:0] busA,       
    input [31:0] Adr,        
    input [31:0] DataIn,       
    output [31:0] DataOut
    );
    wire [7:0]  pB;
    wire [31:0] data;
    reg [31:0] memory[1023:0];

    // ????
   integer i;
    initial
     begin
        for (i = 0; i < 1023; i = i + 1)  memory[i] <= 0;
     end


assign pB=(op==6'b100000)?{24*memory[Adr][7],memory[Adr][7:0]}:{24'b0,memory[Adr][7:0]};
assign data=(op==6'b101000)?{memory[Adr][31:8],busA[7:0]}:DataIn;
//B = (op==6'b100000) || (op==6'b100100) || (op==6'b101000);         //sb && lb && lbu

assign DataOut=(_B ? pB : memory[Adr[11:2]]);
//assign pB=memory[Adr][7:0];
    
always@(/*Adr or DataIn*/ posedge CLK)
     begin
        // ???
        if (MemWr)
         begin
           /* memory[Adr] <= DataIn[31:24];
            memory[Adr + 1] <= DataIn[23:16];
            memory[Adr + 2] <= DataIn[15:8];
            memory[Adr + 3] <= DataIn[7:0];*/
	memory[Adr[11:2]]=data;
         end
        // ???
        /*else
         begin
            DataOut[31:24] <= memory[Adr];
            DataOut[23:16] <= memory[Adr + 1];
            DataOut[15:8] <= memory[Adr + 2];
            DataOut[7:0] <= memory[Adr + 3];
	DataOut=memory[Adr[11:2]];
         end*/
     end

endmodule