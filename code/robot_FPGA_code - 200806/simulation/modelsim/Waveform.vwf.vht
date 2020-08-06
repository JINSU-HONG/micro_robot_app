-- Copyright (C) 2020  Intel Corporation. All rights reserved.
-- Your use of Intel Corporation's design tools, logic functions 
-- and other software and tools, and any partner logic 
-- functions, and any output files from any of the foregoing 
-- (including device programming or simulation files), and any 
-- associated documentation or information are expressly subject 
-- to the terms and conditions of the Intel Program License 
-- Subscription Agreement, the Intel Quartus Prime License Agreement,
-- the Intel FPGA IP License Agreement, or other applicable license
-- agreement, including, without limitation, that your use is for
-- the sole purpose of programming logic devices manufactured by
-- Intel and sold by Intel or its authorized distributors.  Please
-- refer to the applicable agreement for further details, at
-- https://fpgasoftware.intel.com/eula.

-- *****************************************************************************
-- This file contains a Vhdl test bench with test vectors .The test vectors     
-- are exported from a vector file in the Quartus Waveform Editor and apply to  
-- the top level entity of the current Quartus project .The user can use this   
-- testbench to simulate his design using a third-party simulation tool .       
-- *****************************************************************************
-- Generated on "07/29/2020 00:03:07"
                                                             
-- Vhdl Test Bench(with test vectors) for design  :          FPGA_20140329
-- 
-- Simulation tool : 3rd Party
-- 

LIBRARY ieee;                                               
USE ieee.std_logic_1164.all;                                

ENTITY FPGA_20140329_vhd_vec_tst IS
END FPGA_20140329_vhd_vec_tst;
ARCHITECTURE FPGA_20140329_arch OF FPGA_20140329_vhd_vec_tst IS
-- constants                                                 
-- signals                                                   
SIGNAL A : STD_LOGIC_VECTOR(19 DOWNTO 0);
SIGNAL D : STD_LOGIC_VECTOR(15 DOWNTO 0);
SIGNAL DIO_FPGA0 : STD_LOGIC;
SIGNAL DIO_FPGA1 : STD_LOGIC;
SIGNAL DIO_FPGA2 : STD_LOGIC;
SIGNAL DIO_FPGA3 : STD_LOGIC;
SIGNAL DIO_FPGA4 : STD_LOGIC;
SIGNAL DIO_FPGA5 : STD_LOGIC;
SIGNAL DIO_FPGA6 : STD_LOGIC;
SIGNAL EM1CLK : STD_LOGIC;
SIGNAL EM1WAIT : STD_LOGIC;
SIGNAL nEM1CS2 : STD_LOGIC;
SIGNAL nEM1CS4 : STD_LOGIC;
SIGNAL nEM1OE : STD_LOGIC;
SIGNAL nEM1RNW : STD_LOGIC;
SIGNAL nEM1WE : STD_LOGIC;
SIGNAL nRST : STD_LOGIC;
SIGNAL nSPISTEB_UN : STD_LOGIC;
SIGNAL SPICLKB_UN : STD_LOGIC;
SIGNAL SPISIMOB1 : STD_LOGIC;
SIGNAL SPISIMOB2 : STD_LOGIC;
SIGNAL SPISIMOB3 : STD_LOGIC;
SIGNAL SPISIMOB4 : STD_LOGIC;
SIGNAL SPISIMOB5 : STD_LOGIC;
SIGNAL SPISIMOB6 : STD_LOGIC;
SIGNAL SPISIMOB7 : STD_LOGIC;
SIGNAL SPISIMOB8 : STD_LOGIC;
SIGNAL SPISIMOB9 : STD_LOGIC;
SIGNAL SPISOMIB1 : STD_LOGIC;
SIGNAL SPISOMIB2 : STD_LOGIC;
SIGNAL SPISOMIB3 : STD_LOGIC;
SIGNAL SPISOMIB4 : STD_LOGIC;
SIGNAL SPISOMIB5 : STD_LOGIC;
SIGNAL SPISOMIB6 : STD_LOGIC;
SIGNAL SPISOMIB7 : STD_LOGIC;
SIGNAL SPISOMIB8 : STD_LOGIC;
SIGNAL SPISOMIB9 : STD_LOGIC;
COMPONENT FPGA_20140329
	PORT (
	A : IN STD_LOGIC_VECTOR(19 DOWNTO 0);
	D : INOUT STD_LOGIC_VECTOR(15 DOWNTO 0);
	DIO_FPGA0 : OUT STD_LOGIC;
	DIO_FPGA1 : OUT STD_LOGIC;
	DIO_FPGA2 : OUT STD_LOGIC;
	DIO_FPGA3 : OUT STD_LOGIC;
	DIO_FPGA4 : OUT STD_LOGIC;
	DIO_FPGA5 : OUT STD_LOGIC;
	DIO_FPGA6 : IN STD_LOGIC;
	EM1CLK : IN STD_LOGIC;
	EM1WAIT : OUT STD_LOGIC;
	nEM1CS2 : IN STD_LOGIC;
	nEM1CS4 : IN STD_LOGIC;
	nEM1OE : IN STD_LOGIC;
	nEM1RNW : IN STD_LOGIC;
	nEM1WE : IN STD_LOGIC;
	nRST : IN STD_LOGIC;
	nSPISTEB_UN : OUT STD_LOGIC;
	SPICLKB_UN : OUT STD_LOGIC;
	SPISIMOB1 : OUT STD_LOGIC;
	SPISIMOB2 : OUT STD_LOGIC;
	SPISIMOB3 : OUT STD_LOGIC;
	SPISIMOB4 : OUT STD_LOGIC;
	SPISIMOB5 : OUT STD_LOGIC;
	SPISIMOB6 : OUT STD_LOGIC;
	SPISIMOB7 : OUT STD_LOGIC;
	SPISIMOB8 : OUT STD_LOGIC;
	SPISIMOB9 : OUT STD_LOGIC;
	SPISOMIB1 : IN STD_LOGIC;
	SPISOMIB2 : IN STD_LOGIC;
	SPISOMIB3 : IN STD_LOGIC;
	SPISOMIB4 : IN STD_LOGIC;
	SPISOMIB5 : IN STD_LOGIC;
	SPISOMIB6 : IN STD_LOGIC;
	SPISOMIB7 : IN STD_LOGIC;
	SPISOMIB8 : IN STD_LOGIC;
	SPISOMIB9 : IN STD_LOGIC
	);
END COMPONENT;
BEGIN
	i1 : FPGA_20140329
	PORT MAP (
-- list connections between master ports and signals
	A => A,
	D => D,
	DIO_FPGA0 => DIO_FPGA0,
	DIO_FPGA1 => DIO_FPGA1,
	DIO_FPGA2 => DIO_FPGA2,
	DIO_FPGA3 => DIO_FPGA3,
	DIO_FPGA4 => DIO_FPGA4,
	DIO_FPGA5 => DIO_FPGA5,
	DIO_FPGA6 => DIO_FPGA6,
	EM1CLK => EM1CLK,
	EM1WAIT => EM1WAIT,
	nEM1CS2 => nEM1CS2,
	nEM1CS4 => nEM1CS4,
	nEM1OE => nEM1OE,
	nEM1RNW => nEM1RNW,
	nEM1WE => nEM1WE,
	nRST => nRST,
	nSPISTEB_UN => nSPISTEB_UN,
	SPICLKB_UN => SPICLKB_UN,
	SPISIMOB1 => SPISIMOB1,
	SPISIMOB2 => SPISIMOB2,
	SPISIMOB3 => SPISIMOB3,
	SPISIMOB4 => SPISIMOB4,
	SPISIMOB5 => SPISIMOB5,
	SPISIMOB6 => SPISIMOB6,
	SPISIMOB7 => SPISIMOB7,
	SPISIMOB8 => SPISIMOB8,
	SPISIMOB9 => SPISIMOB9,
	SPISOMIB1 => SPISOMIB1,
	SPISOMIB2 => SPISOMIB2,
	SPISOMIB3 => SPISOMIB3,
	SPISOMIB4 => SPISOMIB4,
	SPISOMIB5 => SPISOMIB5,
	SPISOMIB6 => SPISOMIB6,
	SPISOMIB7 => SPISOMIB7,
	SPISOMIB8 => SPISOMIB8,
	SPISOMIB9 => SPISOMIB9
	);
END FPGA_20140329_arch;
