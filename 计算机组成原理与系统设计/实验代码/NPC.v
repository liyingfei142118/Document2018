module NPC(targe,immediate,Branch,Jump, Zero,pc,npc);
	input [25:0] targe;
	input [15:0]immediate;
	input Branch,Jump, Zero;
	input [31:0] pc; 
	output [31:0] npc;

	wire [31:0] pc_plus_4, pc_br;		
	
assign    pc_plus_4 = pc + 4;//normal pc
//according branch to chose beq address or J adress
assign	  pc_br = Branch?pc_plus_4 + {{14{immediate[15]}}, immediate, 2'b00}:{pc[31:28],targe[25:0],2'b00};
//to chose npc
assign    npc=(Branch || Jump)?pc_br:pc_plus_4;

endmodule 
