`timescale 1ns / 1ps


/*
 * @brief   Dummy RAM module, no delays, no outstanding requests
 *          Word adressable, in reality memory is byte addresable
 *          A complete RAM module is out of the scope of this assignment
 * @author  Ioannis Manthopoulos
 * @input   write_enable    Weather to write or only read data
 * @input   addr            Address of said data
 * @input   write_data      Data to conditionally write
 * @output  read_data       Data to retrieve if write_enable is false
 */
module RAM(
    input       clk, rst, 
    input       write_enable, read_enable,
    input       [9:0] addr,
    input       [31:0] write_data,
    output reg  [31:0] read_data
);

reg [31:0] memory_table[0:1023];
reg [31:0] i;

always @(posedge clk) begin 
    if (write_enable && !rst) begin
        memory_table[addr] <= write_data;
    end
end
always @(*) begin
    if (read_enable) begin 
        read_data = memory_table[addr];
    end
    else begin
        read_data = 0;
    end
end

always @(rst) begin 
    for (i = 40; i < 1022; i = i+1) begin
        memory_table[i] = 0;
    end

    // mem & branch test
    /*
    memory_table[0]  = 'b00100000000000010000000001100100; // addi t1, t0, 100
    memory_table[1]  = 'b00100000000000100000000000110010; // addi t2, t0, 50

    memory_table[2]  = 'b11111111111111111111111111111111; // nop
    memory_table[3]  = 'b11111111111111111111111111111111; // nop

    memory_table[4]  = 'b10101100010000010000000000000001; // sw t1, 0(t2)
    memory_table[5]  = 'b10001100010000110000000000000001; // lw t3, 0(t2)

    memory_table[6]  = 'b11111111111111111111111111111111; // nop
    memory_table[7]  = 'b11111111111111111111111111111111; // nop

    memory_table[8]  = 'b00010100001000110000000000001011; // beq t1, t3, 9

    memory_table[9]  = 'b11111111111111111111111111111111; // nop

    memory_table[10]  = 'b00100000000001000000000000111100; // addi t4, t0, 60

    memory_table[11]  = 'b11111111111111111111111111111110; // halt
    */


    // dummy interrupt code
    memory_table[38] = 'b00100000000001000000000000100011; // addi t4, t0, 35 (0x23)
    memory_table[39] = 'b11111111111111111111111111111111; // nop
    memory_table[40] = 'b11111111111111111111111111111111; // nop
    memory_table[41] = 'b11111111111111111111111111111101; // reti

    // ops test
    memory_table[0] = 'b00100000000000010000000000100011;  // addi t1, t0, 35 (t1 = 35)
    memory_table[1] = 'b00100000000000100000000000001000;  // addi t2, t0, 8  (t2 = 8)
    
    memory_table[2] = 'b11111111111111111111111111111111;  // nop
    memory_table[3] = 'b11111111111111111111111111111111;  // nop

    memory_table[4] = 'b00100100010000100000000000000010;  // subi t2, t2, 2 (t2 = 6)
    
    memory_table[5] = 'b11111111111111111111111111111111;  // nop
    memory_table[6] = 'b11111111111111111111111111111111;  // nop

    memory_table[7] = 'b00000000010000010001100000011000;  // mult t3, t2, t1 (t3 = 35 * 6)

    memory_table[8] = 'b11111111111111111111111111111111;  // nop
    memory_table[9] = 'b11111111111111111111111111111111;  // nop
 
    memory_table[10] = 'b00000000011000000001100001000010; // sr t3, t3, 1 

    memory_table[11] = 'b11111111111111111111111111111111;  // nop
    memory_table[12] = 'b11111111111111111111111111111111;  // nop

    memory_table[13] = 'b00000000011000000001100010000000; // sl t3, t3, 2
    memory_table[14] = 'b00100000000000100000110010001100; // addi t2, t0, 3212 

    memory_table[15] = 'b11111111111111111111111111111111; // nop
    memory_table[16] = 'b11111111111111111111111111111111; // nop

    memory_table[17] = 'b00000000011000100000100000100000; // add t1, t2, t3 (t1 = t3 + t2 = 3632)

    memory_table[18] = 'b11111111111111111111111111111111; // nop
    memory_table[19] = 'b11111111111111111111111111111111; // nop

    memory_table[20] = 'b00000000001000010001000000100010; // sub t1, t1, t2
    
    memory_table[21] = 'b11111111111111111111111111111110; // halt
    
end

endmodule
