library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.STD_LOGIC_UNSIGNED.all;
use IEEE.numeric_std.all;
library WORK;

entity testb is 
end testb;

architecture impl of testb is
    signal clk:     STD_LOGIC;
    signal reset:   STD_LOGIC;
    signal led_dec: STD_LOGIC_VECTOR(6 downto 0);
begin
    TL: entity WORK.top_level_module port map( clk, reset, led_dec );

    process begin 
        -- reset the counter to zero 
        reset <= '1';
        wait for 1 ms;
        reset <= '0';
        wait for 1 ms;
        -- set reset to false to start the test
        for i in 0 to 15 loop 
            clk <= '0'; wait for 1 ms;
            clk <= '1'; wait for 1 ms;
            --report "clk=" & std_logic'image(clk);
        end loop;
        wait;
    end process;
end impl;