transcript on
if {[file exists rtl_work]} {
	vdel -lib rtl_work -all
}
vlib rtl_work
vmap work rtl_work

vlog -vlog01compat -work work +incdir+C:/Users/user/Desktop/robot_FPGA_code\ -\ 190528/db {C:/Users/user/Desktop/robot_FPGA_code - 190528/db/pll_altpll.v}
vcom -93 -work work {C:/Users/user/Desktop/robot_FPGA_code - 190528/Reset_Gen.vhd}
vcom -93 -work work {C:/Users/user/Desktop/robot_FPGA_code - 190528/pll.vhd}
vcom -93 -work work {C:/Users/user/Desktop/robot_FPGA_code - 190528/da_test.vhd}

