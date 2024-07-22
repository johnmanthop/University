`timescale 1ns / 1ps

// START FOR NEXT TIME, finish wb stage
// wb needs to access dram "in the middle" of the stage
 
module WB(
    input clk, rst,

    input  [31:0]       alu_result,
    input               write_to_regfile_from_ex,
    input               mem_write_from_ex, mem_read_from_ex,
    input               mem_to_reg_from_ex,
    input  [31:0]       mem_write_data_from_ex,
    input  [4:0]        writeback_reg_id_from_ex,

    output              write_to_regfile_to_fetch,
    output reg [31:0]   write_data_to_fetch,
    output [4:0]        writeback_reg_id_to_fetch
);

wire [31:0] mem_read_data;

RAM dram(
    .clk(clk),
    .rst(rst),
    
    .write_enable   (mem_write_from_ex),
    .read_enable    (mem_read_from_ex),
    .addr           (alu_result),
    .write_data     (mem_write_data_from_ex),
    .read_data      (mem_read_data)
);

assign write_to_regfile_to_fetch   = write_to_regfile_from_ex;
assign writeback_reg_id_to_fetch   = writeback_reg_id_from_ex;

always @(*) begin
    if (mem_to_reg_from_ex) write_data_to_fetch = mem_read_data;
    else                    write_data_to_fetch = alu_result;
end

endmodule