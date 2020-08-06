#include "F28x_Project.h"
#include "easy2837xS_sci_v8.4.h"
#include "F2837xS_Init_Func.h"
#include "F2837xS_fault.h"
#include "F2837xS_variable.h"
#include "F2837xS_da.h"
#include "cc.h"

#include "socket.h"
#include "xscale.h"
#include "w5300.h"

typedef uint8 SOCKET;

void reset_iinchip();

uint8 ip_veri[4] = {0,0,0,0};                   // for setting SIP register
uint8 gw_veri[4] = {0,0,0,0};                     // for setting GAR register
uint8 sn_veri[4] = {0,0,0,0};                     // for setting SUBR register
uint8 mac_veri[6] = {0,0,0,0,0,0}; 	   // for setting SHAR register

uint16 sock_flags[4] = {0, 0, 0, 0};

uint16 idr_veri = 0;
uint16 port_veri = 0;

int receive_veri = 0;
int len_veri = 0;

float time_a;
float time_udp;

long loopCnt = 0;

void main(void)
{
	InitSysCtrl();

	DINT;
	InitPieCtrl();

	IER = 0x0000;
	IFR = 0x0000;

	InitPieVectTable();
	EALLOW;
	PieVectTable.EPWM2_INT = &cc;

	EDIS;

	InitGpio();
	Gpio_setup();
	InitXbar();

	InitAdc();
	//InitIntDac();
	InitSpiDac();

	InitEPwm();
	InitCpuTimers();
	Emif1Initialize();

	ConfigCpuTimer(&CpuTimer1, 200, 1000000);
	CpuTimer1Regs.TCR.all = 0x4000; // Use write-only instruction to set TSS bit = 0

	// IER flag
	IER |= M_INT1|M_INT2|M_INT3|M_INT10|M_INT9;

	// Enable PIE
	PieCtrlRegs.PIEIER1.bit.INTx7 = 1;//CPUTimer0
	PieCtrlRegs.PIEIER3.bit.INTx2 = 1;//EPWM2_INT

    EALLOW;
	PieCtrlRegs.PIECTRL.bit.ENPIE = 1;
	EDIS;

	EINT;
	ERTM;

	// Sampling time
	Tsamp = 2.*maxCount_ePWM * SYS_CLK_PRD; // 1.* for double sampling 2.* for single sampling
	INV_Tsamp = 1./Tsamp;

	ASync_cs2_config();
	ASync_cs3_config();
	easyDSP_SCI_Init();
	InitParameters();
	InitController();

    /* initiate W5300 */
	reset_iinchip();
    iinchip_init();
    delaycc(200e-3);

    /* allocate internal TX/RX Memory of W5300 */
    if(!sysinit(tx_mem_conf,rx_mem_conf))
    {
        //MEMORY CONFIG ERR
		test_fault_a = 99;
        while(1);
    }

    //setMR(getMR()|MR_FS); // If Little-endian, set MR_FS.

	/* configure network information */
	setSHAR(mac_set);
	setGAR(gw_set);                                     // set gateway IP address
	saveSUBR(sn_set);
	setSUBR();                                    // set subnet mask address
	setSIPR(ip_set);                                    // set source IP address

    /* verify network information */
    getSHAR(mac_veri);                                      // get source hardware address
    getGAR(gw_veri);                                        // get gateway IP address
    getSUBR(sn_veri);                                     // get subnet mask address
    getSIPR(ip_veri);
    idr_veri = getIDR();

    InitFlags();

    // help inv8

	//DIN_SPI1_8
	GPIO_SetupPinMux(10, GPIO_MUX_CPU1, 0);
	GPIO_SetupPinOptions(10, GPIO_OUTPUT, GPIO_PULLUP);
	GpioDataRegs.GPASET.bit.GPIO10 = 0x1;
}

void reset_iinchip() {
	GpioDataRegs.GPACLEAR.bit.GPIO25=0x1;
	delaycc(5e-6);
	GpioDataRegs.GPASET.bit.GPIO25=0x1;
}
