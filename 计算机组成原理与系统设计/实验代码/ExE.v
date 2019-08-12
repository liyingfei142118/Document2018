
module SignZeroExtend(immediate, ExtOp, Eimm);  
    input [15:0] immediate;  
     input ExtOp;  
     output [31:0] Eimm;  
       
     assign Eimm[15:0] = immediate;  
     assign Eimm[31:16] = ExtOp? (immediate[15]? 16'hffff : 16'h0000) : 16'h0000;  
  
endmodule  