`timescale 1ns / 1ps
module CTRL_UNIT (
    input      nop,
    input  [5:0] opcode,
    output reg write_to_regfile,
    output reg reg_destination,
    output reg alu_source_imm,
    output reg [1:0] alu_op,
    output reg mem_write,
    output reg mem_read,
    output reg mem_to_reg,
    output reg beq, bneq,
    output reg uc_b
);

always @(*) begin
    if (nop) begin // set all signals, especially the write signals, to 0
        write_to_regfile    = 0;
        reg_destination     = 0;
        alu_source_imm      = 0;
        alu_op              = 'b00;
        mem_write           = 0;
        mem_read            = 0;
        mem_to_reg          = 0;
        beq                 = 0;
        bneq                = 0;
        uc_b                = 0;
    end
    else if (opcode == 'b000000) begin // generic r type
        write_to_regfile    = 1;
        reg_destination     = 1;
        alu_source_imm      = 0;
        alu_op              = 'b10;
        mem_write           = 0;
        mem_read            = 0;
        mem_to_reg          = 0;
        beq                 = 0;
        bneq                = 0;
        uc_b                = 0;
    end
    else if (opcode == 'b001000) begin // addi
        write_to_regfile    = 1;
        reg_destination     = 0;
        alu_source_imm      = 1;
        alu_op              = 'b00;
        mem_write           = 0;
        mem_read            = 0;
        mem_to_reg          = 0;
        beq                 = 0;
        bneq                = 0;
        uc_b                = 0;
    end
    else if (opcode == 'b001001) begin // subi
        write_to_regfile    = 1;
        reg_destination     = 0;
        alu_source_imm      = 1;
        alu_op              = 'b01;
        mem_write           = 0;
        mem_read            = 0;
        mem_to_reg          = 0;
        beq                 = 0;
        bneq                = 0;
        uc_b                = 0;
    end
    else if (opcode == 'b000100) begin // beq
        write_to_regfile    = 0;
        reg_destination     = 0;
        alu_source_imm      = 0;
        alu_op              = 'b01;
        mem_write           = 0;
        mem_read            = 0;
        mem_to_reg          = 0;
        beq                 = 1;
        bneq                = 0;
        uc_b                = 0;
    end
    else if (opcode == 'b000101) begin // bneq
        write_to_regfile    = 0;
        reg_destination     = 0;
        alu_source_imm      = 0;
        alu_op              = 'b01;
        mem_write           = 0;
        mem_read            = 0;
        mem_to_reg          = 0;
        beq                 = 0;
        bneq                = 1;
        uc_b                = 0;
    end
    else if (opcode == 'b000110) begin // unconditional branch
        write_to_regfile    = 0;
        reg_destination     = 0;
        alu_source_imm      = 0;
        alu_op              = 'b00;
        mem_write           = 0;
        mem_read            = 0;
        mem_to_reg          = 0;
        beq                 = 0;
        bneq                = 0;
        uc_b                = 1;
    end
    else if (opcode == 'b100011) begin // lw
        write_to_regfile    = 1;
        reg_destination     = 0;
        alu_source_imm      = 1;
        alu_op              = 00;
        mem_write           = 0;
        mem_read            = 1;
        mem_to_reg          = 1;
        beq                 = 0;
        bneq                = 0;
        uc_b                = 0;
    end
    else if (opcode == 'b101011) begin // sw
        write_to_regfile    = 0;
        reg_destination     = 0;
        alu_source_imm      = 1;
        alu_op              = 00;
        mem_write           = 1;
        mem_read            = 0;
        mem_to_reg          = 0;
        beq                 = 0;
        bneq                = 0;
        uc_b                = 0;
    end
    else begin // nop
        write_to_regfile    = 0;
        reg_destination     = 0;
        alu_source_imm      = 0;
        alu_op              = 'b00;
        mem_write           = 0;
        mem_read            = 0;
        mem_to_reg          = 0;
        beq                 = 0;
        bneq                = 0;
        uc_b                = 0;
    end
end

endmodule