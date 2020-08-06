
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;



ENTITY FAULT_GEN is
GENERIC(
	SIZE : POSITIVE :=16


	);
port(
		

		CLK 	: in std_logic;
		nRST	: in std_logic;
--		nCS		: in std_logic;
	
		--nWE		: in std_logic;
		--nXRD	: in std_logic;
--		XRnW : in std_logic;
--		A		: in std_logic_vector(3 downto 0);
--		D		: in std_logic_vector(SIZE-1 downto 0);
--		PROT_D	: out std_logic_vector(SIZE-1 downto 0);
		
	--	nPROT	: in std_logic_vector(13 downto 0);
		nCurrFLT : in std_logic_vector(11 downto 0);
		nVoltFLT : in std_logic_vector(5 downto 0);
		
		Curr_FAULT : out std_logic_vector(15 downto 0);  
		Volt_FAULT : out std_logic_vector(15 downto 0); 
		FAULT	: out std_logic_vector(15 downto 0);
		nFault_CLR : in std_logic;
		nGateFLT : in std_logic_vector(5 downto 0);
		Gate_FAULT : out std_logic_vector(15 downto 0) 
	--	nHW_FAULT_RD : in std_logic
	--	nINT	: out std_logic


	);
end FAULT_GEN;

architecture behav of FAULT_GEN is

	signal nPROT_temp : STD_LOGIC_VECTOR(15 downto 0):= (others=>'0');	
	signal HWFAULT		: std_logic_vector(SIZE-1 downto 0) := (others=>'0');	
	signal CurrFLT_temp	: std_logic_vector(15 downto 0) := (others=>'0');	
	signal VoltFLT_temp	: std_logic_vector(15 downto 0) := (others=>'0');
	signal GateFLT_temp	: std_logic_vector(15 downto 0) := (others=>'0');	
	signal Curr_HWFAULT : std_logic_vector(15 downto 0) := (others=>'0');	
	signal Volt_HWFAULT : std_logic_vector(15 downto 0) := (others=>'0');	
	signal Gate_HWFAULT	: std_logic_vector(15 downto 0) := (others=>'0');	
--	signal FAULT_sig	: std_logic := '0';
--	signal INT_buf		: std_logic_vector(1 downto 0) := "00";
--	signal CLR        : std_logic := '0';
	--SIGNAL MASK     : STD_LOGIC_VECTOR(SIZE-1 DOWNTO 0):= (others=>'0');
--	SIGNAL CLR     : STD_LOGIC_VECTOR(SIZE-1 DOWNTO 0) :=(others=>'0');
--	SIGNAL CLR_temp : std_logic :='0';


	begin

	

-------------------------------------------------------
--FPGA READ DATA OF DSP
------------------------------------------------------
	INT_gen : process (CLK, nRST,nCurrFLT,nVoltFLT,nGateFLT)
	BEGIN 
			CurrFLT_temp(0) <= nCurrFLT(0);
			CurrFLT_temp(1) <= nCurrFLT(1);
			CurrFLT_temp(2) <= nCurrFLT(2);
			CurrFLT_temp(3) <= nCurrFLT(3);
			CurrFLT_temp(4) <= nCurrFLT(4);
			CurrFLT_temp(5) <= nCurrFLT(5);
			CurrFLT_temp(6) <= nCurrFLT(6);
			CurrFLT_temp(7) <= nCurrFLT(7);
			CurrFLT_temp(8) <= nCurrFLT(8);
			CurrFLT_temp(9) <= nCurrFLT(9);
			CurrFLT_temp(10) <= nCurrFLT(10);
			CurrFLT_temp(11) <= nCurrFLT(11);
			CurrFLT_temp(12) <= '0';
			CurrFLT_temp(13) <= '0';
			CurrFLT_temp(14) <= '0';
			CurrFLT_temp(15) <= '0';
					
			VoltFLT_temp(0) <= nVoltFLT(0);
			VoltFLT_temp(1) <= nVoltFLT(1);
			VoltFLT_temp(2) <= nVoltFLT(2);
			VoltFLT_temp(3) <= nVoltFLT(3);
			VoltFLT_temp(4) <= nVoltFLT(4);
			VoltFLT_temp(5) <= nVoltFLT(5);
			VoltFLT_temp(6) <= '0';
			VoltFLT_temp(7) <= '0';
			VoltFLT_temp(8) <= '0';
			VoltFLT_temp(9) <= '0';
			VoltFLT_temp(10) <= '0';
			VoltFLT_temp(11) <= '0';
			VoltFLT_temp(12) <= '0';
			VoltFLT_temp(13) <= '0';
			VoltFLT_temp(14) <= '0';
			VoltFLT_temp(15) <= '0';
			
			GateFLT_temp(0) <= nGateFLT(0);
			GateFLT_temp(1) <= nGateFLT(1);
			GateFLT_temp(2) <= nGateFLT(2);
			GateFLT_temp(3) <= nGateFLT(3);
			GateFLT_temp(4) <= nGateFLT(4);
			GateFLT_temp(5) <= nGateFLT(5);
			GateFLT_temp(6) <= '0';
			GateFLT_temp(7) <= '0';
			GateFLT_temp(8) <= '0';
			GateFLT_temp(9) <= '0';
			GateFLT_temp(10) <= '0';
			GateFLT_temp(11) <= '0';
			GateFLT_temp(12) <= '0';
			GateFLT_temp(13) <= '0';
			GateFLT_temp(14) <= '0';
			GateFLT_temp(15) <= '0';
			
					
			nPROT_temp(0) <= nCurrFLT(0) and nCurrFLT(1) and nVoltFLT(0) and nGateFLT(0);
			nPROT_temp(1) <= nCurrFLT(2) and nCurrFLT(3) and nVoltFLT(1) and nGateFLT(1);
			nPROT_temp(2) <= nCurrFLT(4) and nCurrFLT(5) and nVoltFLT(2) and nGateFLT(2);
			nPROT_temp(3) <= nCurrFLT(6) and nCurrFLT(7) and nVoltFLT(3) and nGateFLT(3);
			nPROT_temp(4) <= nCurrFLT(8) and nCurrFLT(9) and nVoltFLT(4) and nGateFLT(4);
			nPROT_temp(5) <= nCurrFLT(10) and nCurrFLT(11) and nVoltFLT(5) and nGateFLT(5);	
			nPROT_temp(6) <= '0';
			nPROT_temp(7) <= '0';
			nPROT_temp(8) <= '0';
			nPROT_temp(9) <= '0';
			nPROT_temp(10) <= '0';
			nPROT_temp(11) <= '0';
			nPROT_temp(12) <= '0';
			nPROT_temp(13) <= '0';
			nPROT_temp(14) <= '0';
			nPROT_temp(15) <= '0';
		
	 -- IF(nRST='0') THEN 
		--	INT_buf <="00";
	--	if( CLR(0) = '1')then
	--		HWFAULT<=(others=>'0');	
		--ELSIF(RISING_EDGE(CLK)) THEN
	--	ELSIF(CLK'EVENT AND CLK='1') THEN	
		--	if( CLR(0) = '1')then
		--	HWFAULT<=(others=>'0');
			--else
	--			INT_buf(0) <= FAULT_sig;
	--			INT_buf(1) <= INT_buf(0);
			--nINT<= NOT(INT_buf(1) XOR FAULT_sig);;
			--FAULT<= HWFAULT(0) OR HWFAULT(1) OR HWFAULT(2) or HWFAULT(3) OR HWFAULT(4) OR HWFAULT(5) or HWFAULT(6) OR HWFAULT(7) OR HWFAULT(8) or HWFAULT(9) OR HWFAULT(10) OR HWFAULT(11) or HWFAULT(12) OR HWFAULT(13) OR HWFAULT(14) OR HWFAULT(15);
			--	HWFAULT <= (not nPROT_temp) or HWFAULT;
		--	end if;
		--END IF;
	END PROCESS;
	
	READ_DATA : PROCESS (CLK, nRST,nPROT_temp,CurrFLT_temp,VoltFLT_temp,GateFLT_temp)
	BEGIN
		--IF(nRST='0') THEN
			--MASK<=(OTHERS=>'0');
			--CLR <= '1';
			--FAULT <= (others => '0'); --CAN'T RESOLVE MULTIPLE CONSTANT DRIVERS FOR NET "HWFAUL
		--IF(CLK'EVENT AND CLK='1') THEN
			--IF (XRnW='0' AND nCS='0') THEN    -- Write = 0?;
			--	CASE(A(3 DOWNTO 0)) IS
					--WHEN "0010" => MASK <=D(MASK'LEFT DOWNTO 0);
					--WHEN "0100" => CLR <=D(CLR'LEFT DOWNTO 0);
			--		WHEN "0010" => MASK <=D;
			--		WHEN "0100" => CLR <=D;
			--		WHEN OTHERS	=> NULL;
			--	END CASE;
			
			
			
			--ELSE
			
			
			if( nFault_CLR = '0')then
				HWFAULT	<= (others=>'0');
				Curr_HWFAULT <= (others=>'0');
				Volt_HWFAULT <= (others=>'0');
				Gate_HWFAULT <= (others=>'0');
					--FAULT <= (others => '0');
			else 
			
			
			HWFAULT <= ((not nPROT_temp) or HWFAULT);
			
			Volt_HWFAULT <= ((not VoltFLT_temp) or Volt_HWFAULT);
			Curr_HWFAULT <= ((not CurrFLT_temp) or Curr_HWFAULT);
			Gate_HWFAULT <= ((not GateFLT_temp) or Gate_HWFAULT);
			
		
		--	HWFAULT <= nPROT_temp and HWFAULT;
				--	HWFAULT <= ((not MASK) NOR nPROT_temp) OR HWFAULT;	-- HWFAULT = 1: when fault (active high)
				--	HWFAULT <= nPROT_temp nor HWFAULT;	
					
					
					
			end if;										
		--END IF;
		
	END PROCESS;

-------------------------------------------------------
--FPGA WIRTE DATA IN DSP MEMORY
------------------------------------------------------	
--	WRITE_DATA : process(CLK,HWFAULT)--HWFAULT, CLK)
--	begin
		--IF(CLK'EVENT AND CLK='1') THEN
		
--			PROT_D <= HWFAULT;
		
		--	IF(nCS='0' AND XRnW='1') THEN 
			--	case(A(3 DOWNTO 0))is
				--	when "0000"	=> PROT_D <= HWFAULT;
				--	when "0010"	=> PROT_D <= MASK;
				--	when "0100" => PROT_D <= CLR;
				--	when others	=> PROT_D <= (others=>'0');
			--	end case;
		--	END IF;
	
--	end process;
	


	FAULT <= HWFAULT;
	Curr_FAULT <= Curr_HWFAULT;
	Volt_FAULT <= Volt_HWFAULT;
	Gate_FAULT <= Gate_HWFAULT;
--Faults : process(A(3 DOWNTO 0),CLK, HWFAULT)
--begin
--	if(RISING_EDGE(CLK)) THEN
--		FAULT(0) <= HWFAULT(0);
--		FAULT(1) <= HWFAULT(1);
--		FAULT(2) <= HWFAULT(2);
--		FAULT(3) <= HWFAULT(3);
--		FAULT(4) <= HWFAULT(4);
--		FAULT(5) <= HWFAULT(5);
--		FAULT(6) <= '0';
--		FAULT(7) <= '0';
--		FAULT(8) <= '0';
--		FAULT(9) <= '0';
--		FAULT(10) <= '0';
--		FAULT(11) <= '0';
--		FAULT(12) <= '0';
--		FAULT(13) <= '0';
--		FAULT(14) <= '0';
--		FAULT(15) <= '0';
--	end if;
--end process;
		
	
		
	
	-- if and clk should be used?
	--FAULT_sig <= '0' when HWFAULT="0000000000000000" else '1';	
	--FAULT_sig <= '0' when nPROT_temp="1111111111111111" else '1';	
end behav;