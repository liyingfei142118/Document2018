module InstructionMemory(IAddr,op,rs,rt,rd,func,immediate,targe);         
     input [31:0] IAddr;      
  
    output [5:0] op;
    output [4:0] rs;
    output [4:0] rt;
    output [4:0] rd;
    output [5:0] func;
    output [15:0] immediate;
    output [25:0] targe;  


    reg[31:0] mem[1023:0]; 

    initial 
     begin
        $readmemh("code.txt", mem);  
     end
//assign these signal to make sure we read right.
    assign op[5:0] = mem[IAddr[11:2]][31:26];
    assign rs[4:0] = mem[IAddr[11:2]][25:21];
    assign rt = mem[IAddr[11:2]][20:16];
    assign rd[4:0] = mem[IAddr[11:2]][15:11];    
    assign func[5:0]=mem[IAddr[11:2]][5:0];   
    assign immediate[15:0] = mem[IAddr[11:2]][15:0];   
    assign targe[25:0]=mem[IAddr[11:2]][25:0];

// the beginning read data way from net.
   /* assign op = mem[IAddr][7:2];
    assign rs[4:3] = mem[IAddr][1:0];
    assign rs[2:0] = mem[IAddr + 1][7:5];
    assign rt = mem[IAddr + 1][4:0];
    assign rd = mem[IAddr + 2][7:3];
    
assign func[5:0]=mem[IAddr + 3][5:0];
    
    assign immediate[15:8] = mem[IAddr + 2];
    assign immediate[7:0] = mem[IAddr + 3];
    
assign targe[25:24]=mem[IAddr][1:0];
    assign targe[23:16]=mem[IAddr + 1];
    assign targe[15:8]=mem[IAddr + 2];
    assign targe[7:0]=mem[IAddr + 3];*/
endmodule