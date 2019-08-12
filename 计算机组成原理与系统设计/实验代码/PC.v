module PC(CLK,Reset,pcW,newAddress,currentAddress);
    input CLK,Reset;                       
   // input Reset;                          
    input [31:0] newAddress; // new address
    input pcW;          
    output reg[31:0] currentAddress; //now address
    initial begin
        currentAddress =32'h00003000; 
    end
//at the begginng urrentAddress <=32'h00003000
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