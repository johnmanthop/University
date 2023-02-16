library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity counter4 is
    port( clk:      in STD_LOGIC;
          reset:    in STD_LOGIC;
          outp:     out STD_LOGIC_VECTOR (3 downto 0) );
end counter4;

architecture impl of counter4 is
    -- internal register storing the current number
    signal register4: STD_LOGIC_VECTOR(3 downto 0);             
begin
    -- use a process that trigers when a clk or reset change is made
    process (clk, reset)
    begin
        -- if reset is 1 set register to zero asynchronously
        if (reset = '1') then
            register4 <= (register4'range => '0');
        -- else if a rising edge of clock happens add one to the counter
        elsif (rising_edge(clk)) then             
            register4 <= register4 + 1;   
        end if;
    end process;

    outp <= register4;
end impl;