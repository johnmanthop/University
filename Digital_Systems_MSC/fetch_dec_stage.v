`timescale 1ns / 1ps
/*
 * interrupt protocol:
 * check if available_for_int == 1, otherwise the interrupt will be ignored
 * write to the int_pc register the PC of the interrupt code to be executed
 * set int_occured = 1 for one cycle then set to 0
 * interrupt code needs to include a reti instruction
 *
 * on int_occured:
    save PC to a register
    create and issue a jump instruction to the int_pc
 * 
 * special opcodes: b11111111111111111111111111111111 == nop
 *                  b11111111111111111111111111111110 == halt
 *                  b11111111111111111111111111111101 == reti
 */

module FETCH_DEC(
    input               clk, rst,

    input               int_occured,
    input       [9:0]   int_pc,
    output reg          available_for_int,

    input               write_to_regfile_from_wb,
    input       [31:0]  write_data_from_wb,
    input       [4:0]   writeback_reg_id_from_wb,
    input       [9:0]   PC_from_ex,
    
    output reg  [15:0]  imm_or_shamt_data,
    output reg  [5:0]   func_field,
    output reg  [15:0]  jump_offset,
    output      [31:0]  reg1_data, reg2_data,

    output      [1:0]   alu_op_type_to_ex,
    output              is_shift_to_ex, 
    output              write_to_regfile_to_ex,
    output              alu_src_imm_to_ex,
    output              mem_write_to_ex, mem_read_to_ex,
    output              mem_to_reg_to_ex,
    output              beq_to_ex, bneq_to_ex,
    output reg  [4:0]   writeback_reg_id_to_ex,
    output              uc_b_to_ex
);

parameter CPU_NORM_EX = 0;
parameter CPU_INT_EX  = 1;
parameter CPU_HALT    = 2;
parameter NOP_OPCODE  = 'b11111111111111111111111111111111;
parameter HALT_OPCODE = 'b11111111111111111111111111111110;
parameter RETI_OPCODE = 'b11111111111111111111111111111101;

// internal control stuff
wire reg_destination;
reg  [9:0]  SPC;            // saved pc from interrupt
reg  [31:0] current_inst;   // instruction to be execued, can change based on halt and interrupt
// 0 = normal execution (can accept interrupt), 1 = executing and interrupt, 2 = halted execution
reg [1:0] cpu_state, next_cpu_state;

// iram wires
wire [31:0] inst_from_iram;
wire [31:0] dummy;

// reg file wires
wire [4:0] reg1_id = current_inst[25:21];
wire [4:0] reg2_id = current_inst[20:16];
wire [4:0] reg3_id = writeback_reg_id_from_wb; 


assign is_shift_to_ex  = (alu_op_type_to_ex == 'b10 && (current_inst[5:0] == 'b000000 || current_inst[5:0] == 'b000010));

always @(posedge clk or posedge rst) begin
    if (rst) begin
        cpu_state       <= CPU_NORM_EX;
        next_cpu_state  <= CPU_NORM_EX;
    end
    else begin
        cpu_state <= next_cpu_state;
    end
end

// stage logic
always @(*) begin
    // if current and next state is normal execution then the cpu is available for int
    available_for_int = (cpu_state == CPU_NORM_EX && next_cpu_state == CPU_NORM_EX);

    if (cpu_state == CPU_NORM_EX) begin // normal execution
        
        if (inst_from_iram == HALT_OPCODE) begin // is halt

            next_cpu_state = CPU_HALT;

        end
        else if (int_occured) begin

            next_cpu_state  = CPU_INT_EX;
            SPC             = PC_from_ex;
            current_inst    = { 'b0001100000000000000000, int_pc[9:0] }; // unconditional branch to int_pc

        end
        else begin // keep executing normally

            next_cpu_state  = CPU_NORM_EX;
            current_inst    = inst_from_iram;

        end
    end
    else if (cpu_state == CPU_INT_EX) begin // interrupt execution
        if (inst_from_iram == HALT_OPCODE) begin // is halt

            next_cpu_state = CPU_HALT; 

        end
        else if (inst_from_iram == RETI_OPCODE) begin  // is reti

            next_cpu_state = CPU_NORM_EX;
            current_inst = { 'b0001100000000000000000, SPC[9:0] };

        end
        else begin // keep executing the interrupt

            next_cpu_state = CPU_INT_EX;
            current_inst = inst_from_iram;

        end
    end
    else begin // halt

        current_inst    = NOP_OPCODE;
        next_cpu_state  = CPU_HALT;
    end


    // ctrl signal values
    writeback_reg_id_to_ex      = reg_destination ? current_inst[15:11] : current_inst [20:16];
    func_field                  = current_inst[5:0];
    jump_offset                 = current_inst[15:0];

    if (alu_src_imm_to_ex)      imm_or_shamt_data = current_inst[15:0];
    else if (is_shift_to_ex)    imm_or_shamt_data = current_inst[10:6];
    else                        imm_or_shamt_data = 0; 
end

RAM iram(
    .clk(clk),
    .rst(rst),
    
    .write_enable   ('b0),
    .read_enable    ('b1),
    .addr           (PC_from_ex),
    .write_data     (dummy),
    .read_data      (inst_from_iram)
);

CTRL_UNIT control_unit(
    .nop                (current_inst == NOP_OPCODE), // is nop
    .opcode             (current_inst[31:26]),
    .write_to_regfile   (write_to_regfile_to_ex),
    .reg_destination    (reg_destination),
    .alu_source_imm     (alu_src_imm_to_ex),
    .alu_op             (alu_op_type_to_ex),
    .mem_write          (mem_write_to_ex),
    .mem_read           (mem_read_to_ex),
    .mem_to_reg         (mem_to_reg_to_ex),
    .beq                (beq_to_ex),
    .bneq               (bneq_to_ex),
    .uc_b               (uc_b_to_ex) //unconditional branch
);

REG_FILE register_file(
    .clk                (clk),
    .rst                (rst), 
    .read_reg_id1       (reg1_id), 
    .read_reg_id2       (reg2_id), 
    .write_reg_id       (reg3_id),
    .write_reg_enable   (write_to_regfile_from_wb),
    .write_reg_data     (write_data_from_wb),
    .reg1_data          (reg1_data), 
    .reg2_data          (reg2_data)
);

endmodule