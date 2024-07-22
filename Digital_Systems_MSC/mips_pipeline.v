`timescale 1ns / 1ps

module MIPS(
    input       clk,
    input       rst,

    input       int_occured,
    input [9:0] int_pc,
    output      available_for_int
);

// NOTE: wire *9 is left for compatibility reasons for now

// wires from stage fetch_dec to fetch_ex_reg
wire      [15:0]  a1;
wire      [5:0]   a2;
wire      [15:0]  a3;
wire      [31:0]  a4, a5;
wire      [1:0]   a6;
wire              a7; 
wire              a8;
wire              a9;
wire              a10;
wire              a11, a12;
wire              a13;
wire              a14, a15;
wire      [4:0]   a16;
wire              a17;

// wires from fetch_ex_reg to stage ex
wire      [15:0]  b1;
wire      [5:0]   b2;
wire      [15:0]  b3;
wire      [31:0]  b4, b5;
wire      [1:0]   b6;
wire              b7; 
wire              b8;
wire              b9;
wire              b10;
wire              b11, b12;
wire              b13;
wire              b14, b15;
wire      [4:0]   b16;
wire              b17;

// wires from stage ex to ex_wb_register
wire [31:0] c1;
wire        c3;
wire        c4;
wire        c5, c6;
wire        c7;
wire [31:0] c8;
wire [4:0]  c9;

// wires from ex_wb_register to wb stage
wire [31:0] d1;
wire        d3;
wire        d4;
wire        d5, d6;
wire        d7;
wire [31:0] d8;
wire [4:0]  d9;

// wires from wb to fetch stage (no between register)
wire        e1;
wire [31:0] e2;
wire [4:0]  e3;

// PC wire from ex to fetch (no between register)
wire [9:0] PC_from_ex_to_fetch;

FETCH_DEC fetch_decode_stage(
    .clk                    (clk),
    .rst                    (rst),
    .int_occured            (int_occured),
    .int_pc                 (int_pc),
    .available_for_int      (available_for_int),

    // input signals
    .write_to_regfile_from_wb(e1),
    .write_data_from_wb      (e2),
    .writeback_reg_id_from_wb(e3),
    .PC_from_ex              (PC_from_ex_to_fetch),
    
    // output signals
    .imm_or_shamt_data      (a1),
    .func_field             (a2),
    .jump_offset            (a3),
    .reg1_data              (a4), 
    .reg2_data              (a5),
    .alu_op_type_to_ex      (a6),
    .is_shift_to_ex         (a7), 
    .write_to_regfile_to_ex (a8),
    .alu_src_imm_to_ex      (a10),
    .mem_write_to_ex        (a11), 
    .mem_read_to_ex         (a12),
    .mem_to_reg_to_ex       (a13),
    .beq_to_ex              (a14), 
    .bneq_to_ex             (a15),
    .writeback_reg_id_to_ex (a16),
    .uc_b_to_ex             (a17)
);

FETCH_DEC_EX_REG fetch_dec_to_ex_register(
    .clk(clk),
    .rst(rst),

    // input signals
    .imm_or_shamt_data_from     (a1),
    .func_field_from            (a2),
    .jump_offset_from           (a3),
    .reg1_data_from             (a4),
    .reg2_data_from             (a5),
    .alu_op_type_from           (a6),
    .is_shift_from              (a7), 
    .write_to_regfile_from      (a8),
    .alu_src_imm_from           (a10),
    .mem_write_from             (a11), 
    .mem_read_from              (a12),
    .mem_to_reg_from            (a13),
    .beq_from                   (a14), 
    .bneq_from                  (a15),
    .writeback_reg_id_from      (a16),
    .uc_b_from                  (a17),

    // output signals
    .imm_or_shamt_data_to       (b1),
    .func_field_to              (b2),
    .jump_offset_to             (b3),
    .reg1_data_to               (b4),
    .reg2_data_to               (b5),
    .alu_op_type_to             (b6),
    .is_shift_to                (b7), 
    .write_to_regfile_to        (b8),
    .alu_src_imm_to             (b10),
    .mem_write_to               (b11), 
    .mem_read_to                (b12),
    .mem_to_reg_to              (b13),
    .beq_to                     (b14), 
    .bneq_to                    (b15),
    .writeback_reg_id_to        (b16),
    .uc_b_to                    (b17)
);

EX execute_stage(
    .clk(clk),
    .rst(rst),
    
    // input signals
    .imm_or_shamt_data          (b1),
    .func_field                 (b2),
    .jump_offset                (b3),
    .reg1_data                  (b4), 
    .reg2_data                  (b5),
    .alu_op_type_from_fetch     (b6),
    .is_shift_from_fetch        (b7), 
    .write_to_regfile_from_fetch(b8),
    .alu_src_imm_from_fetch     (b10),
    .mem_write_from_fetch       (b11),
    .mem_read_from_fetch        (b12),
    .mem_to_reg_from_fetch      (b13),
    .beq_from_fetch             (b14), 
    .bneq_from_fetch            (b15),
    .writeback_reg_id_from_fetch(b16),
    .uc_b_from_fetch            (b17),

    // output signals
    .alu_result                 (c1),
    .PC                         (PC_from_ex_to_fetch),
    .write_to_regfile_to_wb     (c3),
    .mem_write_to_wb            (c5), 
    .mem_read_to_wb             (c6),
    .mem_to_reg_to_wb           (c7),
    .mem_write_data             (c8),
    .writeback_reg_id_to_wb     (c9)
);

EX_WB_REG execute_writeback_register(
    .clk(clk),
    .rst(rst),

    //input signals
    .alu_result_from            (c1),
    .write_to_regfile_from      (c3),
    .mem_write_from             (c5), 
    .mem_read_from              (c6),
    .mem_to_reg_from            (c7),
    .mem_write_data_from        (c8),
    .writeback_reg_id_from      (c9),

    // output signals
    .alu_result_to              (d1),
    .write_to_regfile_to        (d3),
    .mem_write_to               (d5), 
    .mem_read_to                (d6),
    .mem_to_reg_to              (d7),
    .mem_write_data_to          (d8),
    .writeback_reg_id_to        (d9)
);

WB writeback_stage(
    .clk(clk),
    .rst(rst),

    // input signals
    .alu_result                 (d1),
    .write_to_regfile_from_ex   (d3),
    .mem_write_from_ex          (d5), 
    .mem_read_from_ex           (d6),
    .mem_to_reg_from_ex         (d7),
    .mem_write_data_from_ex     (d8),
    .writeback_reg_id_from_ex   (d9),

    // output signals
    .write_to_regfile_to_fetch  (e1),
    .write_data_to_fetch        (e2),
    .writeback_reg_id_to_fetch  (e3)
);

endmodule