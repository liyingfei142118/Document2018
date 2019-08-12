 module Multiplexer5(
     input control,
    input [4:0] in1,
    input [4:0] in0,
    output [4:0] out
    );

    // 5??????
    assign out = control ? in1 : in0;

endmodule