library IEEE;
use IEEE.std_logic_1164.all;
library WORK;

entity top_level_module is
    port( clk:              in STD_LOGIC;
          reset:            in STD_LOGIC;  
          led_decoder_outp: out STD_LOGIC_VECTOR (6 downto 0) );
end top_level_module;

architecture impl of top_level_module is
    signal count4: STD_LOGIC_VECTOR (3 downto 0);
begin
    C1: entity WORK.counter4 port map( clk, reset, count4 );
    L1: entity WORK.led_decoder4_7 port map( count4, led_decoder_outp );
end impl;
