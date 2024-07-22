`timescale 1ns / 1ps

module EX_WB_REG(
    input       clk, rst,
    
    input [31:0]        alu_result_from,
    input               write_to_regfile_from,
    input               mem_write_from, mem_read_from,
    input               mem_to_reg_from,
    input [31:0]        mem_write_data_from,
    input [4:0]         writeback_reg_id_from,

    output reg [31:0]   alu_result_to,
    output reg          write_to_regfile_to,
    output reg          mem_write_to, mem_read_to,
    output reg          mem_to_reg_to,
    output reg [31:0]   mem_write_data_to,
    output reg [4:0]    writeback_reg_id_to
);

always @(posedge clk or posedge rst)
begin
    if (rst) begin
        alu_result_to           <= 0;
        write_to_regfile_to     <= 0;
        mem_write_to            <= 0;
        mem_read_to             <= 0;
        mem_to_reg_to           <= 0;
        mem_write_data_to       <= 0;
        writeback_reg_id_to     <= 0;
    end
    else begin
        alu_result_to           <= alu_result_from      ;
        write_to_regfile_to     <= write_to_regfile_from;
        mem_write_to            <= mem_write_from       ;
        mem_read_to             <= mem_read_from        ;
        mem_to_reg_to           <= mem_to_reg_from      ;
        mem_write_data_to       <= mem_write_data_from  ;
        writeback_reg_id_to     <= writeback_reg_id_from;
    end
end

endmodule