 
module ALU(
    input [3:0] ALUop,           // ALU????
    input [31:0] busA,              // ??1
    input [31:0] B,
    input [4:0] shf,
    input [15:0] immediate,              // ??2
    output reg zero,             // ????result????result?0??1?????0
    output reg [31:0] result     // ALU????
    );

    // ??ALU??
    always@(busA or ALUop or B)
     begin
        // ????
        case (ALUop)
            4'b0000 : result = busA + B;  // ??
            4'b0001 : result = busA - B;  // ??
            4'b0010 : result = busA ^ B;  // ??
            4'b0011 : result = busA | B;  // ?
            4'b0100 : result = busA & B;  // ??
	    4'b0101:result = (busA < B);
            4'b0110 : result =~( busA |B);  // ??
	    4'b0111:result = B << shf;
	    4'b1000:result = B >> shf;
	    4'b1001:result= {immediate,16'b0};
            4'b1010:result= B<<busA ;
	    4'b1011:result= ($signed(B))>>>shf ;
	    4'b1100:result= ($signed(B))>>>busA ;
            4'b1101:
		begin
		   if(busA[31]==0&&B[31]==1)
			result<=0;
		   else if(busA[31]==0&&B[31]==0)
			result<=(busA[30:0]<B[30:0]);
		   else if(busA[31]==1&&B[31]==1)
			result<=(busA[30:0]>B[30:0]);
		   else
			result<=1;
		end
	    4'b1111:result=B >> busA;
            default : result = 0;
        endcase
        // ??zero
        if (result)  zero = 0;
        else  zero = 1;
     end

endmodule
