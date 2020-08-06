LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.numeric_std.all;

--  Entity Declaration

ENTITY RESET_GEN IS
	GENERIC
	(
		RESET_TIME	: POSITIVE := 1000;	-- RESET HOLD TIME
		SIZE		: POSITIVE := 11	-- RESET HOLD TIME
	);
	PORT
	(
		CLK,nHW_RST  	: IN STD_LOGIC;
		nHWRESET	: OUT STD_LOGIC
	);
END RESET_GEN;

--  Architecture Body

ARCHITECTURE BEHAVIOR OF RESET_GEN IS

	SIGNAL CNT_SW	: UNSIGNED(SIZE-1 DOWNTO 0) := (OTHERS=>'0');
	SIGNAL CNT_HW	: UNSIGNED(SIZE-1 DOWNTO 0) := (OTHERS=>'0');
	
BEGIN
	TIMER: PROCESS(CLK)
	BEGIN
		IF(CLK'EVENT AND CLK='1')THEN
			IF(nHW_RST='0')THEN
				CNT_HW	<= (OTHERS=>'0');
			ELSIF(CNT_HW /= to_unsigned(RESET_TIME,SIZE))THEN
				CNT_HW	<= CNT_HW + 1;
			ELSE
				CNT_HW	<= CNT_HW;
			END IF;
			IF(CNT_HW = to_unsigned(RESET_TIME,SIZE))THEN
				nHWRESET <= '1';
			ELSE
				nHWRESET <= '0';
			END IF;
			
		END IF;
	END PROCESS;
		
END BEHAVIOR;
