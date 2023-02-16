library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;

entity led_decoder4_7 is
port( inp:  in STD_LOGIC_VECTOR (3 downto 0);
      outp: out STD_LOGIC_VECTOR (6 downto 0) );
end led_decoder4_7;

architecture impl of led_decoder4_7 is
begin
    outp <= "1110111" when inp = "0000" else
            "0010010" when inp = "0001" else
            "1011101" when inp = "0010" else
            "1011011" when inp = "0011" else
            "0111010" when inp = "0100" else
            "1101011" when inp = "0101" else
            "1101111" when inp = "0110" else
            "1010010" when inp = "0111" else
            "1111111" when inp = "1000" else
            "1111011" when inp = "1001" else
            "1111110" when inp = "1010" else
            "0101111" when inp = "1011" else
            "1100101" when inp = "1100" else
            "0011111" when inp = "1101" else
            "1101101" when inp = "1110" else
            "1101100";
end impl;