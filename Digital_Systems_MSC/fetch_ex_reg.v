`timescale 1ns / 1ps

module FETCH_DEC_EX_REG(
    input clk, rst,
    input      [15:0]       imm_or_shamt_data_from,
    input      [5:0]        func_field_from,
    input      [15:0]       jump_offset_from,
    input      [31:0]       reg1_data_from, reg2_data_from,

    input      [1:0]        alu_op_type_from,
    input                   is_shift_from, 
    input                   write_to_regfile_from,
    input                   alu_src_imm_from,
    input                   mem_write_from, mem_read_from,
    input                   mem_to_reg_from,
    input                   beq_from, bneq_from,
    input      [4:0]        writeback_reg_id_from,
    input                   uc_b_from,

    output reg      [15:0]  imm_or_shamt_data_to,
    output reg      [5:0]   func_field_to,
    output reg      [15:0]  jump_offset_to,
    output reg      [31:0]  reg1_data_to, reg2_data_to,

    output reg      [1:0]   alu_op_type_to,
    output reg              is_shift_to, 
    output reg              write_to_regfile_to,
    output reg              alu_src_imm_to,
    output reg              mem_write_to, mem_read_to,
    output reg              mem_to_reg_to,
    output reg              beq_to, bneq_to,
    output reg      [4:0]   writeback_reg_id_to,
    output reg              uc_b_to
);

always @(posedge clk or posedge rst)
begin
    if(rst) begin
        imm_or_shamt_data_to    <= 0;
        func_field_to           <= 0;
        jump_offset_to          <= 0;
        reg1_data_to            <= 0;
        reg2_data_to            <= 0;
        alu_op_type_to          <= 0;
        is_shift_to             <= 0;
        write_to_regfile_to     <= 0;
        alu_src_imm_to          <= 0;
        mem_write_to            <= 0;
        mem_read_to             <= 0;
        mem_to_reg_to           <= 0;
        beq_to                  <= 0;
        bneq_to                 <= 0;
        writeback_reg_id_to     <= 0;
        uc_b_to                 <= 0;
    end
    else begin
        imm_or_shamt_data_to    <= imm_or_shamt_data_from;
        func_field_to           <= func_field_from       ;
        jump_offset_to          <= jump_offset_from      ;
        reg1_data_to            <= reg1_data_from        ;
        reg2_data_to            <= reg2_data_from        ;
        alu_op_type_to          <= alu_op_type_from      ;
        is_shift_to             <= is_shift_from         ;
        write_to_regfile_to     <= write_to_regfile_from ;
        alu_src_imm_to          <= alu_src_imm_from      ;
        mem_write_to            <= mem_write_from        ;
        mem_read_to             <= mem_read_from         ;
        mem_to_reg_to           <= mem_to_reg_from       ;
        beq_to                  <= beq_from              ;
        bneq_to                 <= bneq_from             ;
        writeback_reg_id_to     <= writeback_reg_id_from ;
        uc_b_to                 <= uc_b_from             ;
    end
end

endmodule