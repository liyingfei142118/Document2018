
module RegisterFile(
     input CLK,               
     input RegWr,             
    input [4:0] rs,           
    input [4:0] rt,            
    input [4:0] WriteReg,     
    input [31:0] WriteData,  
     output [31:0] busA,  
    output [31:0] busB    
    );


    reg [31:0] register[0:31];  
    
    integer i;
    initial 
     begin
        for(i = 0; i < 32; i = i + 1)  register[i] <= 0;
     end

    // 
     assign busA = register[rs];  
     assign busB = register[rt];

    // wirte data
    always@(negedge CLK)
     begin
        if (RegWr && WriteReg != 0)  register[WriteReg] <= WriteData;
     end 

endmodule