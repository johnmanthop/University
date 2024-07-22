`timescale 1ns / 1ps

/*
 * @author              Ioannis Manthopoulos
 * @input a, b          32bit values to be used in operation
 * @input alu_sel       Specifies the operation to be performed
 * @ouput result        ALU output
 */

module ALU(
    input       [3:0] alu_sel,
    input       [31:0] a, b,
    output reg  zero,
    output reg  [31:0] result
);
always @(*) begin
    if (alu_sel == 'b0000) begin // add
        result = a + b;
        zero = 0;
    end 
    else if (alu_sel == 'b0001) begin // sub
        result = a - b;
        zero = (result == 0);
    end
    else if (alu_sel == 'b0010) begin // mul
        result = a * b;
        zero = 0;
    end
    else if (alu_sel == 'b0011) begin // div
        result = a / b;
        zero = 0;
    end
    else if (alu_sel == 'b0100) begin // and
        result = a & b;
        zero = 0;
    end
    else if (alu_sel == 'b0101) begin // or
        result = a | b;
        zero = 0;
    end
    else if (alu_sel == 'b0110) begin // nor
        result = ~(a | b);
        zero = 0;
    end
    else if (alu_sel == 'b0111) begin // shift left
        result = a << b;
        zero = 0;
    end
    else if (alu_sel == 'b1000) begin // shift right
        result = a >> b;
        zero = 0;
    end
    else begin 
        result = 0;
        zero = 0;
    end
end
endmodule


