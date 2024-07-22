`timescale 1ns / 1ps

module EX(
    input clk, rst,
    input   [15:0]  imm_or_shamt_data,
    input   [5:0]   func_field,
    input   [15:0]  jump_offset,
    input   [31:0]  reg1_data, reg2_data,

    input   [1:0]   alu_op_type_from_fetch,
    input           is_shift_from_fetch, 
    input           write_to_regfile_from_fetch,
    input           alu_src_imm_from_fetch,
    input           mem_write_from_fetch, mem_read_from_fetch,
    input           mem_to_reg_from_fetch,
    input           beq_from_fetch, bneq_from_fetch,
    input   [4:0]   writeback_reg_id_from_fetch,
    input           uc_b_from_fetch,
     
    output  [31:0]  alu_result,
    output  reg [9:0] PC,
    output          write_to_regfile_to_wb,
    output          mem_write_to_wb, mem_read_to_wb,
    output          mem_to_reg_to_wb,
    output  [31:0]  mem_write_data,
    output  [4:0]   writeback_reg_id_to_wb
);

wire [3:0] alu_op_sel;
wire [31:0] alu_in1 = reg1_data;
wire [31:0] alu_in2 = (alu_src_imm_from_fetch || is_shift_from_fetch) ? 
                        imm_or_shamt_data : reg2_data; 
wire zero;

assign mem_write_data = reg2_data;

ALU_CTRL alu_control_unit(
    .op_type(alu_op_type_from_fetch),
    .func_field(func_field),
    .alu_op_sel(alu_op_sel)
);

ALU alu(
    .alu_sel    (alu_op_sel),
    .a          (alu_in1), 
    .b          (alu_in2), 
    .zero       (zero), 
    .result     (alu_result)
);

assign write_to_regfile_to_wb  = write_to_regfile_from_fetch;
assign mem_write_to_wb         = mem_write_from_fetch;
assign mem_read_to_wb          = mem_read_from_fetch;
assign mem_to_reg_to_wb        = mem_to_reg_from_fetch;
assign writeback_reg_id_to_wb  = writeback_reg_id_from_fetch;

always @(posedge clk or posedge rst) begin
    if (rst) begin
        PC <= 0;
    end
    else begin
        if ((beq_from_fetch && zero) || (bneq_from_fetch && ~zero) || uc_b_from_fetch) begin 
            PC <= jump_offset;
        end 
        else begin 
            PC <= PC + 1;
        end
    end
end

endmodule