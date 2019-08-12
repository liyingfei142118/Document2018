module NPC(busA,targe,Eimm,immediate,Branch,Jump,Jr,Bgez, Bgtz, Blez, Bltz,Jal,Jalr, Zero,pc,npc);
	input [31:0] busA;
	input [25:0] targe;
        input [31:0] Eimm;
	input [15:0]immediate;
	input Branch,Jump, Zero;
	input [31:0] pc;
	input Bgez;
	input Bgtz;
	input Blez;
	input Bltz;
        input Jal;
        input Jalr;
        input Jr;
	output reg[31:0] npc;

	//wire [31:0] pc_plus_4, pc_br;		
	//wire [31:0] npc;
/*assign    pc_plus_4 = pc + 4;
assign	  pc_br = Branch?pc_plus_4 + {{14{immediate[15]}}, immediate, 2'b00}:{pc[31:28],targe[25:0],2'b00};
assign    npc=(Branch || Jump)?pc_br:pc_plus_4;*/
//assign    npc=
always @(*)
begin
	if(Branch)
		npc<=(pc+4)+{{14{immediate[15]}}, immediate, 2'b00};
	else if(Jump)
 		npc<={pc[31:28],targe[25:0],2'b00};
	else if( Bgez &&((busA[31]==0)||(busA==0)) )
		npc<=pc+{{14{immediate[15]}}, immediate, 2'b00};
		//npc<=(pc+4)+Eimm<<2;
 	else if( Bgtz && (busA!=0)&&(busA[31]==0) )
		npc<=pc+{{14{immediate[15]}}, immediate, 2'b00};
	else if( Blez && ((busA==0)||(busA[31]==1)) )
		npc<=pc+{{14{immediate[15]}}, immediate, 2'b00};
	else if( Bltz && (busA[31]==1) )
		npc<=pc+{{14{immediate[15]}}, immediate, 2'b00};
        else if(Jal)
                npc<={pc[31:28],targe<<2};
        else if(Jalr || Jr)
		npc<=busA+32'h3000;
	else
		npc<=pc + 4;
end
endmodule 
