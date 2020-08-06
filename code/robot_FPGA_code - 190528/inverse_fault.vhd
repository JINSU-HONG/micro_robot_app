LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.numeric_std.all;

--  Entity Declaration

ENTITY inverse_fault IS
	GENERIC
	(
	--	Cnt_max	: POSITIVE := 7500;	-- Cnt
		SIZE		: POSITIVE := 16	-- SIZE
	);
	PORT
	(	
		CLK, nRST	: IN STD_LOGIC;
		
		
	
		
		HWFAULT		: IN STD_LOGIC_VECTOR(SIZE-1 DOWNTO 0);
		nFault_init_on : IN STD_LOGIC; 
		nFault_init_off : IN STD_LOGIC; 		
		--nINT_PWM : OUT STD_LOGIC;
		

		FAULT	: out STD_LOGIC_VECTOR(SIZE-1 DOWNTO 0)
		

	);
END inverse_fault;

--  Architecture Body


ARCHITECTURE BEHAVIOR_TEST OF inverse_fault IS 



--buff enable
	
	SIGNAL Fault_temp : std_logic_vector(SIZE-1 downto 0):= (OTHERS=>'0');
	SIGNAL Fault_init : std_logic_vector(SIZE-1 downto 0):= (OTHERS=>'0');

BEGIN
------------------------------------------------------------------------

-----------------------------------------------------------------------



-----------------------------------------------------
--buf_enable
------------------------------------------------

	
buf_enable:	process(nRST, CLK, HWFAULT,nFault_init_on,nFault_init_off)--, FAULT2) --BUF, FAULT)
	--variable fault_init : integer :=0;
	begin
	

			
			--if(nFault_init_on='0') then
			
				--Fault_init <= "1111111111111111";
				--	fault_init:=1;
			--else
					--fault_init:=0;
			--end if;
		--fault_init:=0;
		
	
		if(nRST='0')then
			Fault_temp <= "0000000000000000";
		elsif(CLK'EVENT AND CLK='1')then
			--if(fault_init=1) then
			--	case(nFault_init_on) is
			--		when '0' => Fault_init <= "1111111111111111";
			--		when '1' => Fault_init <= Fault_init;
			--		WHEN OTHERS	=> Fault_init <= Fault_init;
			--	end case;
				
				if(nFault_init_on='0') then
			
					Fault_init <= "1111111111111111";
				
				elsif(nFault_init_off ='0') then
					
					Fault_init <= "0000000000000000";
				
				end if;
			 	
				
				
				
				Fault_temp <= (not HWFAULT) and Fault_init;
				
				
			--else
			--	Fault_temp <= "0000000000000000";
			--end if;
			
			--case(fault_init) is
			--		when 0 => Fault_temp <= "0000000000000000";
			--		when 1 => Fault_temp <= (not HWFAULT);
			--		WHEN OTHERS	=> Fault_temp <= "0000000000000000";
			--end case;
			
			
				
			
		end if;
		
		
		
	end process;
--	FAULT <= Fault_temp;
	FAULT <= Fault_init;

-- 12 gating signal required (NPC)

		
		

	

END BEHAVIOR_TEST;

