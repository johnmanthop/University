`timescale 1ns / 1ps

/*
 * Per the Patterson-Hennessy version of mips, an extra alu_ctrl module is needed
 */
module ALU_CTRL(
    input       [1:0] op_type,
    input       [5:0] func_field,
    output reg  [3:0] alu_op_sel
);
always @(*) begin
    if (op_type == 'b10) begin // r type
                // func field
        if      (func_field == 'b100000) alu_op_sel = 'b0000; // func = add
        else if (func_field == 'b100010) alu_op_sel = 'b0001; // sub
        else if (func_field == 'b100100) alu_op_sel = 'b0100; // and
        else if (func_field == 'b100101) alu_op_sel = 'b0101; // or
        else if (func_field == 'b011000) alu_op_sel = 'b0010; // mul
        else if (func_field == 'b100111) alu_op_sel = 'b0110; // nor
        else if (func_field == 'b000000) alu_op_sel = 'b0111; // shift left
        else if (func_field == 'b000010) alu_op_sel = 'b1000; // shift right
        else alu_op_sel = 'b0000;
    end
    else if (op_type == 'b00) alu_op_sel = 'b0000; // imm add type
    else if (op_type == 'b01) alu_op_sel = 'b0001; // imm sub type
    else alu_op_sel = 'b0000;
end
endmodule