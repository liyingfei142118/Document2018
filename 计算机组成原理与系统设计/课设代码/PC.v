module PC(CLK,Reset,pcW,newAddress,currentAddress);
    input CLK;                       
    input Reset;                          
    input [31:0] newAddress; 
    input pcW;          
    output reg[31:0] currentAddress; 
    initial begin
        currentAddress =32'h00003000; 
    end

    always@(posedge CLK or posedge Reset)
     begin
        if (Reset == 1)  currentAddress <=32'h00003000; //32'b0000 0000 0000 0000 0011 0000 0000 0000
        else 
         begin
            if (pcW)  currentAddress <= newAddress;
            else  currentAddress <= currentAddress;
         end
     end

endmodule