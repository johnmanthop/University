`timescale 1ns / 1ps
module mips_tb ();

reg clk;
reg rst;
reg interrupt;
reg [9:0] int_pc;
wire available_for_int;
reg [31:0] t;

MIPS mips(
    .clk                (clk),
    .rst                (rst),
    .int_occured        (interrupt),
    .int_pc             (int_pc),
    .available_for_int  (available_for_int)
);

initial begin
    t           = 0;    
    interrupt   = 0;
    int_pc      = 38;
    rst         = 1;
    #10 rst     = 0;
    #10 clk     = 0;
    forever begin
        #15 clk = ~clk;
        t = t + 1;

        if (t == 10 || t == 11) interrupt = 1;
        else interrupt = 0;
    end
end

endmodule