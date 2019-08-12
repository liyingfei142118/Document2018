
module DataMemory(
    input CLK,
    input MemWr,            // write signal
    input [31:0] Adr,         // write address
    input [31:0] DataIn,        // write data
    output [31:0] DataOut   // out data
    );

    //  data register
    reg [31:0] memory[1023:0];

    
    integer i;
    initial
     begin
        for (i = 0; i < 1023; i = i + 1)  memory[i] <= 0;
     end

assign DataOut=memory[Adr[11:2]];
    
always@( posedge CLK)
     begin

        if (MemWr)
         begin
	memory[Adr[11:2]]=DataIn;
         end


     end

endmodule