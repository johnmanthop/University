`timescale 1ns / 1ps
/*
 * @brief           Floating point registers are ignored for now
 * @author          Ioannis Manthopoulos
 * @input clk                           The writing is clk triggered
 * @input read_reg_id1, read_reg_id2    The registers to read values from
 * @input write_reg_id                  The register to possibly write to
 * @input write_reg_flag                Weather to write to a register or not
 * @input write_reg_data                The data to possible write
 * @input reg1_data, reg2_data          The output data of 2 read registers
 */

module REG_FILE(
    input               clk,
    input               rst,
    input       [4:0]   read_reg_id1, read_reg_id2, write_reg_id,
    input               write_reg_enable,
    input       [31:0]  write_reg_data,
    output reg  [31:0]  reg1_data, reg2_data
);

reg [31:0] registers [0:31];         // 32 registers of 32 bits
reg [5:0]  i;

always @(*) begin
    reg1_data = registers[read_reg_id1];
    reg2_data = registers[read_reg_id2];
end

always @(posedge clk or posedge rst) begin
    if (rst) begin
        for (i = 0; i <= 31; i = i+1) begin
            registers[i] = 'b0;
        end
    end
    else if (write_reg_enable) begin 
        registers[write_reg_id] <= write_reg_data;
    end
end

endmodule
