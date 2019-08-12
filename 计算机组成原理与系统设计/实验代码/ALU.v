 
module ALU(
     input [3:0] ALUop,           
    input [31:0] busA,            
    input [31:0] B,  //select depend on busB or immediate's expand            
    output reg zero,            
    output reg [31:0] result   
    );

   
    always@(busA or ALUop or B)
     begin
       
        case (ALUop)
            4'b0000 : result = busA + B;   
            4'b0001 : result = busA - B;   
            4'b0010 : result = B - busA;   
            4'b0011 : result = busA | B;  
            4'b0100 : result = busA & B;   
	    4'b0101:result = (busA < B);
            4'b0110 : result =~( busA |B);  
	    4'b0111:result = busA << B;
	    4'b1000:result = busA >> B;
            default : result = 0;
        endcase
        // assign zero
        if (result)  zero = 0;
        else  zero = 1;
     end

endmodule
