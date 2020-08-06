onerror {exit -code 1}
vlib work
vcom -work work jy_eh.vho
vcom -work work Waveform.vwf.vht
vsim -novopt -c -t 1ps -sdfmax FPGA_20140329_vhd_vec_tst/i1=jy_eh_vhd.sdo -L cycloneive -L altera -L altera_mf -L 220model -L sgate -L altera_lnsim work.FPGA_20140329_vhd_vec_tst
vcd file -direction jy_eh.msim.vcd
vcd add -internal FPGA_20140329_vhd_vec_tst/*
vcd add -internal FPGA_20140329_vhd_vec_tst/i1/*
proc simTimestamp {} {
    echo "Simulation time: $::now ps"
    if { [string equal running [runStatus]] } {
        after 2500 simTimestamp
    }
}
after 2500 simTimestamp
run -all
quit -f



