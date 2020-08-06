library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.numeric_std.all;

ENTITY da_test is

port(
		
		
		CLK 	: in std_logic;
		D :  in std_logic_vector(15 downto 0);
		A : in std_logic_vector(3 downto 0);
		SPISOMIB0 : in std_logic;
		SPISOMIB1 : in std_logic;
		SPISOMIB2 : in std_logic;
		SPISOMIB3 : in std_logic;
		SPISOMIB4 : in std_logic;
		SPISOMIB5 : in std_logic;
		SPISOMIB6 : in std_logic;
		SPISOMIB7 : in std_logic;
		
		
		
		nEM1OE : in std_logic;
		nEM1WE : in std_logic;
		nINV_SEND : in std_logic;
		--nINV0_CS: in std_logic;
		nINV0_CS : in std_logic_vector(7 downto 0);
		nINV1_CS: in std_logic_vector(7 downto 0);
		nINV2_CS: in std_logic_vector(7 downto 0);
		nINV3_CS: in std_logic_vector(7 downto 0);
		nINV4_CS: in std_logic_vector(7 downto 0);
		nINV5_CS: in std_logic_vector(7 downto 0);
		nINV6_CS: in std_logic_vector(7 downto 0);
		nINV7_CS: in std_logic_vector(7 downto 0);


		
	--	ENB : in std_logic;
		nSYNC : out std_logic;
		Data0 : out std_logic;
		Data1 : out std_logic;
		Data2 : out std_logic;
		Data3 : out std_logic;
		Data4 : out std_logic;
		Data5 : out std_logic;
		Data6 : out std_logic;
		Data7 : out std_logic;
				
		
	
		SCLK : out std_logic;
		temp : out std_logic_vector(15 downto 0);
		temptest : out std_logic

		
	--	nDA0_init : in std_logic;
	--	nDA0_init_off : in std_logic;
	--	nDA_BZ : out std_logic_vector(15 downto 0);
	--	nDA_init_BZ : out std_logic_vector(15 downto 0);
	--	nDA0_mode0 : in std_logic;
	--	nDA0_mode1 : in std_logic

	);
end da_test;

architecture behav of da_test is
	type row_t is array(0 to 15) of std_logic_vector(15 downto 0);
	signal nSYNC_temp : std_logic; 
	signal nSYNC_temp2 : std_logic; 
	signal nSYNC_temp3 : std_logic; 
	signal nSYNC_init_temp : std_logic;
	signal CLK_out_temp : std_logic;
	signal CLK_out : std_logic;
	signal CLK_out1 : std_logic;

	
	--signal Din : std_logic_vector(15 downto 0);
	--signal Din2 : std_logic_vector(15 downto 0);
	signal Dout : std_logic_vector(15 downto 0);

	signal Data_temp0 : std_logic;
	signal Data_temp1 : std_logic;
	signal Data_temp2 : std_logic;
	signal Data_temp3 : std_logic;
	signal Data_temp4 : std_logic;
	signal Data_temp5 : std_logic;
	signal Data_temp6 : std_logic;
	signal Data_temp7 : std_logic;
	
	
	
	
	
	
	signal data_matrix : std_logic_vector(15 downto 0);
	
	signal INV0_CS_TX : row_t:= (others => (others =>'0'));
	signal INV1_CS_TX : row_t:= (others => (others =>'0'));
	signal INV2_CS_TX : row_t:= (others => (others =>'0'));
	signal INV3_CS_TX : row_t:= (others => (others =>'0'));
	signal INV4_CS_TX : row_t:= (others => (others =>'0'));
	signal INV5_CS_TX : row_t:= (others => (others =>'0'));
	signal INV6_CS_TX : row_t:= (others => (others =>'0'));
	signal INV7_CS_TX : row_t:= (others => (others =>'0'));
	
	signal INV0_CS_RX : row_t:= (others => (others =>'0'));
	signal INV1_CS_RX : row_t:= (others => (others =>'0'));
	signal INV2_CS_RX : row_t:= (others => (others =>'0'));
	signal INV3_CS_RX : row_t:= (others => (others =>'0'));
	signal INV4_CS_RX : row_t:= (others => (others =>'0'));
	signal INV5_CS_RX : row_t:= (others => (others =>'0'));
	signal INV6_CS_RX : row_t:= (others => (others =>'0'));
	signal INV7_CS_RX : row_t:= (others => (others =>'0'));
	
		
	signal alert : std_logic;
	signal output_temp: std_logic;
	
	--signal nDA_BZ_temp : std_logic_vector(15 downto 0) := (others =>'1');
	--signal nDA_BZ_init_temp : std_logic_vector(15 downto 0) := (others =>'1');
	--shared variable cnt : std_logic_vector(1 downto 0);
	--shared variable holdtime : integer :=1;
	--shared variable holdtime : integer :=6;
	
	shared variable holdtime : integer :=1;
   shared variable Data_num : integer :=6;
	shared variable da_start : integer := 0;
	--shared variable da_init : integer := 0;
	shared variable da_mode : integer := 1;
	shared variable syncdelay : integer := 0;
	
	
	
	
	
	begin 
	Matrix_stack :process(nINV0_CS,nINV1_CS,nINV2_CS,nINV3_CS,nINV4_CS,nINV5_CS,nINV6_CS,nINV7_CS,nEM1WE,A,D)

		begin
		
	  	if(nEM1WE = '0') then 
		   case(nINV0_CS) is
					when "11111110" => INV0_CS_TX(0) <= D;
					when "11111101" => INV0_CS_TX(1) <= D;
					when "11111011" => INV0_CS_TX(2) <= D;
					when "11110111" => INV0_CS_TX(3) <= D;
					when "11101111" => INV0_CS_TX(4) <= D;
					when "11011111" => INV0_CS_TX(5) <= D;
					when "10111111" => INV0_CS_TX(6) <= D;
					when "01111111" => INV0_CS_TX(7) <= D;
			
					WHEN OTHERS	=>  data_matrix(0) <= '0';
			end case;
		

		   case(nINV1_CS) is
					when "11111110" => INV1_CS_TX(0) <= D;
					when "11111101" => INV1_CS_TX(1) <= D;
					when "11111011" => INV1_CS_TX(2) <= D;
					when "11110111" => INV1_CS_TX(3) <= D;
					when "11101111" => INV1_CS_TX(4) <= D;
					when "11011111" => INV1_CS_TX(5) <= D;
					when "10111111" => INV1_CS_TX(6) <= D;
					when "01111111" => INV1_CS_TX(7) <= D;
			
					WHEN OTHERS	=>  data_matrix(0) <= '0';
			end case;		
		
		   case(nINV2_CS) is
					when "11111110" => INV2_CS_TX(0) <= D;
					when "11111101" => INV2_CS_TX(1) <= D;
					when "11111011" => INV2_CS_TX(2) <= D;
					when "11110111" => INV2_CS_TX(3) <= D;
					when "11101111" => INV2_CS_TX(4) <= D;
					when "11011111" => INV2_CS_TX(5) <= D;
					when "10111111" => INV2_CS_TX(6) <= D;
					when "01111111" => INV2_CS_TX(7) <= D;
					
					WHEN OTHERS	=>  data_matrix(0) <= '0';
			end case;		
					
			case(nINV3_CS) is
					when "11111110" => INV3_CS_TX(0) <= D;
					when "11111101" => INV3_CS_TX(1) <= D;
					when "11111011" => INV3_CS_TX(2) <= D;
					when "11110111" => INV3_CS_TX(3) <= D;
					when "11101111" => INV3_CS_TX(4) <= D;
					when "11011111" => INV3_CS_TX(5) <= D;
					when "10111111" => INV3_CS_TX(6) <= D;
					when "01111111" => INV3_CS_TX(7) <= D;
		
					WHEN OTHERS	=>  data_matrix(0) <= '0';
			end case;	
			
			
			case(nINV4_CS) is
					when "11111110" => INV4_CS_TX(0) <= D;
					when "11111101" => INV4_CS_TX(1) <= D;
					when "11111011" => INV4_CS_TX(2) <= D;
					when "11110111" => INV4_CS_TX(3) <= D;
					when "11101111" => INV4_CS_TX(4) <= D;
					when "11011111" => INV4_CS_TX(5) <= D;
					when "10111111" => INV4_CS_TX(6) <= D;
					when "01111111" => INV4_CS_TX(7) <= D;
					
					WHEN OTHERS	=>  data_matrix(0) <= '0';
			end case;	
			
								
			case(nINV5_CS) is
					when "11111110" => INV5_CS_TX(0) <= D;
					when "11111101" => INV5_CS_TX(1) <= D;
					when "11111011" => INV5_CS_TX(2) <= D;
					when "11110111" => INV5_CS_TX(3) <= D;
					when "11101111" => INV5_CS_TX(4) <= D;
					when "11011111" => INV5_CS_TX(5) <= D;
					when "10111111" => INV5_CS_TX(6) <= D;
					when "01111111" => INV5_CS_TX(7) <= D;

					WHEN OTHERS	=>  data_matrix(0) <= '0';
			end case;	
			
					
			case(nINV6_CS) is
					when "11111110" => INV6_CS_TX(0) <= D;
					when "11111101" => INV6_CS_TX(1) <= D;
					when "11111011" => INV6_CS_TX(2) <= D;
					when "11110111" => INV6_CS_TX(3) <= D;
					when "11101111" => INV6_CS_TX(4) <= D;
					when "11011111" => INV6_CS_TX(5) <= D;
					when "10111111" => INV6_CS_TX(6) <= D;
					when "01111111" => INV6_CS_TX(7) <= D;
		
					WHEN OTHERS	=>  data_matrix(0) <= '0';
			end case;	
			
			case(nINV7_CS) is
					when "11111110" => INV7_CS_TX(0) <= D;
					when "11111101" => INV7_CS_TX(1) <= D;
					when "11111011" => INV7_CS_TX(2) <= D;
					when "11110111" => INV7_CS_TX(3) <= D;
					when "11101111" => INV7_CS_TX(4) <= D;
					when "11011111" => INV7_CS_TX(5) <= D;
					when "10111111" => INV7_CS_TX(6) <= D;
					when "01111111" => INV7_CS_TX(7) <= D;

					WHEN OTHERS	=>  data_matrix(0) <= '0';
			end case;	
			
				
			
		end if;		
			
						
		
	
	end process;
		


	Matrix_read :process(nINV0_CS,nINV1_CS,nINV2_CS,nINV3_CS,nINV4_CS,nINV5_CS,nINV6_CS,nINV7_CS,nEM1OE)
		begin 
			
		if(nEM1OE = '0') then 
		   case(nINV0_CS) is
					when "11111110" => Dout <= INV0_CS_RX(0);
					when "11111101" => Dout <= INV0_CS_RX(1);
					when "11111011" => Dout <= INV0_CS_RX(2);
					when "11110111" => Dout <= INV0_CS_RX(3);
					when "11101111" => Dout <= INV0_CS_RX(4);
					when "11011111" => Dout <= INV0_CS_RX(5);
					when "10111111" => Dout <= INV0_CS_RX(6);
					when "01111111" => Dout <= INV0_CS_RX(7);
		
					WHEN OTHERS	=> data_matrix(1) <= '0';
			end case;
			
			case(nINV1_CS) is
					when "11111110" => Dout <= INV1_CS_RX(0);
					when "11111101" => Dout <= INV1_CS_RX(1);
					when "11111011" => Dout <= INV1_CS_RX(2);
					when "11110111" => Dout <= INV1_CS_RX(3);
					when "11101111" => Dout <= INV1_CS_RX(4);
					when "11011111" => Dout <= INV1_CS_RX(5);
					when "10111111" => Dout <= INV1_CS_RX(6);
					when "01111111" => Dout <= INV1_CS_RX(7);
					WHEN OTHERS	=> data_matrix(1) <= '0';
			end case;
			

			case(nINV2_CS) is
					when "11111110" => Dout <= INV2_CS_RX(0);
					when "11111101" => Dout <= INV2_CS_RX(1);
					when "11111011" => Dout <= INV2_CS_RX(2);
					when "11110111" => Dout <= INV2_CS_RX(3);
					when "11101111" => Dout <= INV2_CS_RX(4);
					when "11011111" => Dout <= INV2_CS_RX(5);
					when "10111111" => Dout <= INV2_CS_RX(6);
					when "01111111" => Dout <= INV2_CS_RX(7);
		
					WHEN OTHERS	=> data_matrix(1) <= '0';
			end case;
			
			
			
			case(nINV3_CS) is
					when "11111110" => Dout <= INV3_CS_RX(0);
					when "11111101" => Dout <= INV3_CS_RX(1);
					when "11111011" => Dout <= INV3_CS_RX(2);
					when "11110111" => Dout <= INV3_CS_RX(3);
					when "11101111" => Dout <= INV3_CS_RX(4);
					when "11011111" => Dout <= INV3_CS_RX(5);
					when "10111111" => Dout <= INV3_CS_RX(6);
					when "01111111" => Dout <= INV3_CS_RX(7);
			
					WHEN OTHERS	=> data_matrix(1) <= '0';
			end case;
					

			case(nINV4_CS) is
					when "11111110" => Dout <= INV4_CS_RX(0);
					when "11111101" => Dout <= INV4_CS_RX(1);
					when "11111011" => Dout <= INV4_CS_RX(2);
					when "11110111" => Dout <= INV4_CS_RX(3);
					when "11101111" => Dout <= INV4_CS_RX(4);
					when "11011111" => Dout <= INV4_CS_RX(5);
					when "10111111" => Dout <= INV4_CS_RX(6);
					when "01111111" => Dout <= INV4_CS_RX(7);
	
					WHEN OTHERS	=> data_matrix(1) <= '0';
			end case;
		
			case(nINV5_CS) is
					when "11111110" => Dout <= INV5_CS_RX(0);
					when "11111101" => Dout <= INV5_CS_RX(1);
					when "11111011" => Dout <= INV5_CS_RX(2);
					when "11110111" => Dout <= INV5_CS_RX(3);
					when "11101111" => Dout <= INV5_CS_RX(4);
					when "11011111" => Dout <= INV5_CS_RX(5);
					when "10111111" => Dout <= INV5_CS_RX(6);
					when "01111111" => Dout <= INV5_CS_RX(7);
		
					WHEN OTHERS	=> data_matrix(1) <= '0';
			end case;
		
		
			case(nINV6_CS) is
					when "11111110" => Dout <= INV6_CS_RX(0);
					when "11111101" => Dout <= INV6_CS_RX(1);
					when "11111011" => Dout <= INV6_CS_RX(2);
					when "11110111" => Dout <= INV6_CS_RX(3);
					when "11101111" => Dout <= INV6_CS_RX(4);
					when "11011111" => Dout <= INV6_CS_RX(5);
					when "10111111" => Dout <= INV6_CS_RX(6);
					when "01111111" => Dout <= INV6_CS_RX(7);

					WHEN OTHERS	=> data_matrix(1) <= '0';
			end case;
		
		
			case(nINV7_CS) is
					when "11111110" => Dout <= INV7_CS_RX(0);
					when "11111101" => Dout <= INV7_CS_RX(1);
					when "11111011" => Dout <= INV7_CS_RX(2);
					when "11110111" => Dout <= INV7_CS_RX(3);
					when "11101111" => Dout <= INV7_CS_RX(4);
					when "11011111" => Dout <= INV7_CS_RX(5);
					when "10111111" => Dout <= INV7_CS_RX(6);
					when "01111111" => Dout <= INV7_CS_RX(7);
		
					WHEN OTHERS	=> data_matrix(1) <= '0';
			end case;
		
		
		
		
	end if;
	
	end process;




	da_soc : process(nINV_SEND)--,nDA0_init,nDA0_init_off)
		begin

			if(nINV_SEND = '0') then
				da_start := 1;
			else
				da_start := 0;
			end if;
			
		end process;
	

		
		SYNC_temp_gen : process(CLK)
		variable temp_cnt2 : integer := 0;
		variable temp_cnt3 : integer := 0;
		variable da_start_temp3 : integer :=0;
		variable CLK_CNT : integer := 0;
		variable da_off_cnt3 : integer := 0;

		begin 
			IF(CLK'EVENT and CLK='1') then
			--
				if(da_start = 1) then 
				
					CASE (da_mode) IS
						when 0 => da_start_temp3 := 2;
						when 1 => da_start_temp3 := 1;
						WHEN OTHERS	=> da_start_temp3 :=0;
					end case;
						
				end if;
						
				if(da_start_temp3=1) then
					
					if(temp_cnt3 = 1) then 
							alert <='1';
					else 
							alert <= '0';
					end if;
					
					if(temp_cnt3 < (holdtime+1)*20) then
					--if(temp_cnt3 < (holdtime+1)*5) then
					
				   	nSYNC_temp3<='1';
						--nSYNC_temp<='0';
						
						temp_cnt3 :=temp_cnt3 + 1;
				
					elsif(temp_cnt3 > (holdtime+1)*20-1 and temp_cnt3 < (holdtime+17)*20+10 ) then
					 -- elsif(temp_cnt3 > holdtime*5 and temp_cnt3 < (holdtime+17)*5+2 ) then
						
						nSYNC_temp3<='0';
						
						temp_cnt3:=temp_cnt3+1;
					end if;
					
					if(temp_cnt3 = (holdtime+17)*20+10 ) then
					--if(temp_cnt3 = (holdtime+17)*5+2 ) then
							
					--	if(cnt4=5) 
						--	cnt4 :=0;
							temp_cnt3 := 0;
							da_off_cnt3 := da_off_cnt3+1;
						--da_start_temp := 0;
					end if;
					
					if(da_off_cnt3 = data_num) then
						da_start_temp3 := 0;
						da_off_cnt3 :=0;
						--nDA_BZ_temp <= "1111111111111111";
					end if;
				
				else
					nSYNC_temp3 <= '1';
				end if;
				
			
			if (nSYNC_temp3='0')then
			   
			    if (CLK_CNT<10) then
				--	if (CLK_CNT<2) then
				  	  CLK_out1 <= '0';
					  CLK_CNT:=CLK_CNT+1;
				 elsif(CLK_CNT>9 and CLK_CNT<20) then
				--   elsif(CLK_CNT>1 and CLK_CNT<5) then
				
						CLK_out1 <= '1';
						CLK_CNT:=CLK_CNT+1;
				 end if;
			     
				  if (CLK_CNT=20) then
				      CLK_CNT:=0;
				  end if;
			else
				CLK_CNT:=0;
				CLK_out1 <= '0';
			end if;
			
			
			
			
			end if;
			
		end process;		
		
		

	
		Data_insert : process(CLK_out1)
		
		variable cnt_num : integer :=0;
		variable cnt_data : integer :=0;
		variable TX_cnt : integer :=0;
	
		begin 

		IF(CLK_out1'EVENT and CLK_out1='1') then
				
			if(nSYNC_temp3 = '0' ) then 
			
					if(cnt_data<16) then
					
						Data_temp0 <= INV0_CS_TX(TX_cnt)(15-cnt_data);
						Data_temp1 <= INV1_CS_TX(TX_cnt)(15-cnt_data);
						Data_temp2 <= INV2_CS_TX(TX_cnt)(15-cnt_data);
						Data_temp3 <= INV3_CS_TX(TX_cnt)(15-cnt_data);
						Data_temp4 <= INV4_CS_TX(TX_cnt)(15-cnt_data);
						Data_temp5 <= INV5_CS_TX(TX_cnt)(15-cnt_data);
						Data_temp6 <= INV6_CS_TX(TX_cnt)(15-cnt_data);
						Data_temp7 <= INV7_CS_TX(TX_cnt)(15-cnt_data);
											
						cnt_data:=cnt_data+1;
						
				   end if;
					
					if (cnt_data=16) then
						if (TX_cnt < (data_num-1) ) then                     ----   TX data number
						  TX_cnt:=TX_cnt + 1;
						  cnt_data := 0;
						else
						  TX_cnt:=0;
						  cnt_data := 0;
						end if;
					end if;		
			else
				--	Data_temp0 <= '0';
				--	Data_temp1 <= '0';
				--	Data_temp2 <= '0';
				--	Data_temp3 <= '0';
				--	Data_temp4 <= '0';
				--	Data_temp5 <= '0';
				--	Data_temp6 <= '0';
				--	Data_temp7 <= '0';
									
			end if;
		end if;
								
		
		end process;
		
		
		
		
		Data_insert2 : process(CLK_out1,SPISOMIB0,SPISOMIB1,SPISOMIB2,SPISOMIB3,SPISOMIB4,SPISOMIB5,SPISOMIB6,SPISOMIB7)
		variable cnt_data2 : integer :=0;
		variable RX_cnt : integer :=0;
				
		begin 
									
			--IF(CLK_out_temp'EVENT and CLK_out_temp='1') then
			IF(CLK_out1'EVENT and CLK_out1='0') then
				if(nSYNC_temp3 = '0' ) then 
			
					if(cnt_data2<16) then
							INV0_CS_RX(RX_cnt)(15-cnt_data2)<= SPISOMIB0;
							INV1_CS_RX(RX_cnt)(15-cnt_data2)<= SPISOMIB1;
							INV2_CS_RX(RX_cnt)(15-cnt_data2)<= SPISOMIB2;
							INV3_CS_RX(RX_cnt)(15-cnt_data2)<= SPISOMIB3;
							INV4_CS_RX(RX_cnt)(15-cnt_data2)<= SPISOMIB4;
							INV5_CS_RX(RX_cnt)(15-cnt_data2)<= SPISOMIB5;
							INV6_CS_RX(RX_cnt)(15-cnt_data2)<= SPISOMIB6;
							INV7_CS_RX(RX_cnt)(15-cnt_data2)<= SPISOMIB7;
			
							cnt_data2:=cnt_data2+1;
					end if;
					
					if(cnt_data2=16)  then
						 if (RX_cnt < (data_num-1) ) then					--   ---- RX data number
						     RX_cnt:=RX_cnt + 1;
							  cnt_data2 := 0;
						 else
						     RX_cnt:=0;
							  cnt_data2 := 0;
						 end if;
				   end if;
			   
				else
							
				end if;
			end if;

				
				
			
			
		
		end process;
		
		
			
		nSYNC <= nSYNC_temp3;
		
		Data0 <= Data_temp0;
		Data1 <= Data_temp1;
		Data2 <= Data_temp2;
		Data3 <= Data_temp3;
		Data4 <= Data_temp4;
		Data5 <= Data_temp5;
		Data6 <= Data_temp6;
		Data7 <= Data_temp7;

				
		
		
		SCLK <= CLK_out1;
		
		temp <= Dout;
		temptest <=  nSYNC_temp3;

	
	
		
		
	
		
	
		
end behav;