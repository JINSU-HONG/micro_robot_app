#ifndef	_W5300_H_
#define	_W5300_H_
/**
 * \file    w5300.h
 *    Definition register of W5300 and basic I/O functions.
 *
 * This file defines the memory map and values of W5300 register.\n
 * Also, it defines the basic I/O function to access register of W5300. 
 *
 * \author MidnightCow
 * \date 15/05/2008
 * \version 1.1.0
 *
 * ----------  -------  -----------  ----------------------------
 * Date        Version  Author       Description
 * ----------  -------  -----------  ----------------------------
 * 24/03/2008  1.0.0    MidnigthCow  Release with W5300 launching
 * ----------  -------  -----------  ----------------------------
 * 01/05/2008  1.0.1    MidnightCow  Modify a logical error in iinchip_irq(). Refer to M_01052008
 * ----------  -------  -----------  ----------------------------
 * 15/05/2008  1.1.0    MidnightCow  Refer to M_15052008
 *                                   Delete getSn_DPORTR() because \ref Sn_DPORTR is write-only. 
 *                                   Replace 'Sn_DHAR2' with 'Sn_DIPR' in \ref getSn_DIPR().
 * ----------  -------  -----------  ---------------------------- 
 * 08/08/2008  1.2.0    MidnightCow  Refer to M_08082008
 *                                   Add IINCHIP_CRITICAL_SECTION_ENTER() & IINCHIP_CRITICAL_SECTION_EXIT() to wiz_read_buf() and wiz_write_buf().
 *                                   Modify the description of \ref Sn_SSR and \ref close().</td>
 * ----------  -------  -----------  ---------------------------- 
 */

 
#include "iinchip_conf.h"
#include "types.h"

/*
#define SHIFT_ADDR(addr) ((((addr>>6)<<12) + (addr & 0x003F)) & 0xFFFF)
*/
//#define SHIFT_ADDR(addr) (((((((addr)>>6)<<12) + ((addr) & 0x003F)) & 0xFFFF)) + ((addr) & 0xFF0000))
#define SHIFT_ADDR(addr) ((((addr) & 0x3FFFF) << 1) | ((addr) & 0x300000))
#define HEAD_FIRST_DATA 0xC0A8
 
/** 
 *  Mode register. 
 */
#define MR              SHIFT_ADDR(__DEF_IINCHIP_MAP_BASE__)
#define MR0             MR
#define MR1             SHIFT_ADDR(__DEF_IINCHIP_MAP_BASE__ + 0x01)

/**
  *  Indirect mode address register.
 */ 
#define IDM_AR          SHIFT_ADDR(__DEF_IINCHIP_MAP_BASE__ + 0x02)
#define IDM_AR0         IDM_AR
#define IDM_AR1         SHIFT_ADDR(__DEF_IINCHIP_MAP_BASE__ + 0x03)

/**
  *  Indirect mode data register.
 */ 
#define IDM_DR          SHIFT_ADDR(__DEF_IINCHIP_MAP_BASE__ + 0x04)
#define IDM_DR0         IDM_DR
#define IDM_DR1         SHIFT_ADDR(__DEF_IINCHIP_MAP_BASE__ + 0x05)

/**
 *  Interrupt register
 */
#define IR              SHIFT_ADDR(COMMON_REG_BASE + 0x02)
#define IR0             IR
#define IR1             SHIFT_ADDR(COMMON_REG_BASE + 0x03)

/**
 *  Interrupt mask register
 */
#define IMR             SHIFT_ADDR(COMMON_REG_BASE + 0x04)
#define IMR0            IMR
#define IMR1            SHIFT_ADDR(COMMON_REG_BASE + 0x05)


//#define ICFGR           SHIFT_ADDR(COMMON_REG_BASE + 0x06)
//#define ICFGR0          ICFGR
//#define ICFGR1          SHIFT_ADDR(COMMON_REG_BASE + 0x07)

/**
 *  Source hardware address register
 */
#define SHAR            SHIFT_ADDR(COMMON_REG_BASE + 0x08)
#define SHAR0           SHAR
#define SHAR1           SHIFT_ADDR(COMMON_REG_BASE + 0x09)
#define SHAR2           SHIFT_ADDR(COMMON_REG_BASE + 0x0A)
#define SHAR3           SHIFT_ADDR(COMMON_REG_BASE + 0x0B)
#define SHAR4           SHIFT_ADDR(COMMON_REG_BASE + 0x0C)
#define SHAR5           SHIFT_ADDR(COMMON_REG_BASE + 0x0D)


/**
 *  Gateway IP address register
 */
#define GAR             SHIFT_ADDR(COMMON_REG_BASE + 0x10)
#define GAR0            GAR
#define GAR1            SHIFT_ADDR(COMMON_REG_BASE + 0x11)
#define GAR2            SHIFT_ADDR(COMMON_REG_BASE + 0x12)
#define GAR3            SHIFT_ADDR(COMMON_REG_BASE + 0x13)

/**
 *  Subnet mask register
 */
#define SUBR            SHIFT_ADDR(COMMON_REG_BASE + 0x14)
#define SUBR0           SUBR
#define SUBR1           SHIFT_ADDR(COMMON_REG_BASE + 0x15)
#define SUBR2           SHIFT_ADDR(COMMON_REG_BASE + 0x16)
#define SUBR3           SHIFT_ADDR(COMMON_REG_BASE + 0x17)

/**
 *  Source IP address register
 */
#define SIPR            SHIFT_ADDR(COMMON_REG_BASE + 0x18)
#define SIPR0           SIPR
#define SIPR1           SHIFT_ADDR(COMMON_REG_BASE + 0x19)
#define SIPR2           SHIFT_ADDR(COMMON_REG_BASE + 0x1A)
#define SIPR3           SHIFT_ADDR(COMMON_REG_BASE + 0x1B)

/**
 *  Retransmittion timeout-period register 
 */
#define RTR             SHIFT_ADDR(COMMON_REG_BASE + 0x1C)
#define RTR0            RTR
#define RTR1            SHIFT_ADDR(COMMON_REG_BASE + 0x1D)

/**
 *  Retransmittion retry count reigster
 */
#define RCR             SHIFT_ADDR(COMMON_REG_BASE + 0x1E)
#define RCR0            RCR
#define RCR1            SHIFT_ADDR(COMMON_REG_BASE + 0x1F)

/**
 *  Transmit memory size of each SOCKET reigster
 */
#define TMS01R          SHIFT_ADDR(COMMON_REG_BASE + 0x20)
#define TMS23R          SHIFT_ADDR(COMMON_REG_BASE + 0x22) /**< Refer to TMS01R. */
#define TMS45R          SHIFT_ADDR(COMMON_REG_BASE + 0x24) /**< Refer to TMS01R. */
#define TMS67R          SHIFT_ADDR(COMMON_REG_BASE + 0x26) /**< Refer to TMS01R. */

#define TMSR0           TMS01R
#define TMSR1           SHIFT_ADDR(COMMON_REG_BASE + 0x21)
#define TMSR2           SHIFT_ADDR(COMMON_REG_BASE + 0x22)
#define TMSR3           SHIFT_ADDR(COMMON_REG_BASE + 0x23)
#define TMSR4           SHIFT_ADDR(COMMON_REG_BASE + 0x24)
#define TMSR5           SHIFT_ADDR(COMMON_REG_BASE + 0x25)
#define TMSR6           SHIFT_ADDR(COMMON_REG_BASE + 0x26)
#define TMSR7           SHIFT_ADDR(COMMON_REG_BASE + 0x27)


/**
 *  Transmit memory size of each SOCKET reigster
 */
#define RMS01R          SHIFT_ADDR(COMMON_REG_BASE + 0x28)
#define RMS23R          SHIFT_ADDR(COMMON_REG_BASE + 0x2A)   /**< Refer to RMS01R. */
#define RMS45R          SHIFT_ADDR(COMMON_REG_BASE + 0x2C)   /**< Refer to RMS01R. */
#define RMS67R          SHIFT_ADDR(COMMON_REG_BASE + 0x2E)   /**< Refer to RMS01R. */

#define RMSR0           RMS01R
#define RMSR1           SHIFT_ADDR(COMMON_REG_BASE + 0x29)
#define RMSR2           SHIFT_ADDR(COMMON_REG_BASE + 0x2A)
#define RMSR3           SHIFT_ADDR(COMMON_REG_BASE + 0x2B)
#define RMSR4           SHIFT_ADDR(COMMON_REG_BASE + 0x2C)
#define RMSR5           SHIFT_ADDR(COMMON_REG_BASE + 0x2D)
#define RMSR6           SHIFT_ADDR(COMMON_REG_BASE + 0x2E)
#define RMSR7           SHIFT_ADDR(COMMON_REG_BASE + 0x2F)



/**
 *  Memory type register
 */
#define MTYPER          SHIFT_ADDR(COMMON_REG_BASE + 0x30)
#define MTYPER0         MTYPER
#define MTYPER1         SHIFT_ADDR(COMMON_REG_BASE + 0x31)

/**
 *  Authentication type register
 */
#define PATR            SHIFT_ADDR(COMMON_REG_BASE + 0x32)
#define PATR0           PATR
#define PATR1           SHIFT_ADDR(COMMON_REG_BASE + 0x33)

//#define PPPALGOR      SHIFT_ADDR(COMMON_REG_BASE + 0x34)
//#define PPPALGOR0     PPPALGOR
//#define PPPALGOR1     SHIFT_ADDR(COMMON_REG_BASE + 0x35)

/**
 *  PPP link control protocol request timer register
 */
#define PTIMER          SHIFT_ADDR(COMMON_REG_BASE + 0x36)
#define PTIMER0         PTIMER
#define PTIMER1         SHIFT_ADDR(COMMON_REG_BASE + 0x37)

/**
 *  PPP LCP magic number register
 */
#define PMAGICR         SHIFT_ADDR(COMMON_REG_BASE + 0x38)
#define PMAGICR0        PMAGICR
#define PMAGICR1        SHIFT_ADDR(COMMON_REG_BASE + 0x39)

//#define PSTATER       SHIFT_ADDR(COMMON_REG_BASE + 0x3A)
//#define PSTATER0      PSTATER
//#define PSTATER1      SHIFT_ADDR(COMMON_REG_BASE + 0x3B)

/**
 *  PPPoE session ID register
 */
#define PSIDR           SHIFT_ADDR(COMMON_REG_BASE + 0x3C)
#define PSIDR0          PSIDR
#define PSIDR1          SHIFT_ADDR(COMMON_REG_BASE + 0x3D)

/**
 *  PPPoE destination hardware address register
 */
#define PDHAR           SHIFT_ADDR(COMMON_REG_BASE + 0x40)
#define PDHAR0          PDHAR
#define PDHAR1          SHIFT_ADDR(COMMON_REG_BASE + 0x41)
#define PDHAR2          SHIFT_ADDR(COMMON_REG_BASE + 0x42)
#define PDHAR3          SHIFT_ADDR(COMMON_REG_BASE + 0x43)
#define PDHAR4          SHIFT_ADDR(COMMON_REG_BASE + 0x44)
#define PDHAR5          SHIFT_ADDR(COMMON_REG_BASE + 0x45)

/**
 *  Unreachable IP address register 
 *
 * RESET : 0.0.0.0 \n 
 * When trying to transmit UDP data to destination port number which is not open, 
 * W5300 can receive ICMP (Destination port unreachable) packet. \n
 * In this case, IR(IR_DPUR) becomes '1'. 
 * And destination IP address and unreachable port number of ICMP packet
 * can be acquired through UIPR and UPORTR.
 */
#define UIPR            SHIFT_ADDR(COMMON_REG_BASE + 0x48)
#define UIPR0           UIPR
#define UIPR1           SHIFT_ADDR(COMMON_REG_BASE + 0x49)
#define UIPR2           SHIFT_ADDR(COMMON_REG_BASE + 0x4A)
#define UIPR3           SHIFT_ADDR(COMMON_REG_BASE + 0x4B)

/**
 *  Unreachable port number register
 */
#define UPORTR          SHIFT_ADDR(COMMON_REG_BASE + 0x4C)
#define UPORTR0         UPORTR
#define UPORTR1         SHIFT_ADDR(COMMON_REG_BASE + 0x4D)



/**
 *  Fragment MTU register
 */
#define FMTUR           SHIFT_ADDR(COMMON_REG_BASE + 0x4E)
#define FMTUR0          FMTUR
#define FMTUR1          SHIFT_ADDR(COMMON_REG_BASE + 0x4F)

//#define Sn_RTCR(n)      SHIFT_ADDR(COMMON_REG_BASE + 0x50 + n*2)
//#define Sn_RTCR0(n)     Sn_RTCR(n)
//#define Sn_RTCR1(n)     SHIFT_ADDR(COMMON_REG_BASE + 0x50 + n*2 + 1)

/**
 *  PIN 'BRDYn' configure register
 */
#define Pn_BRDYR(n)     SHIFT_ADDR(COMMON_REG_BASE + 0x60 + n*4)
#define Pn_BRDYR0(n)    Pn_BRDYR(n)
#define Pn_BRDYR1(n)    SHIFT_ADDR(COMMON_REG_BASE + 0x60 + n*4 + 1)

/**
 *  PIN 'BRDYn' buffer depth Register
 */
#define Pn_BDPTHR(n)    SHIFT_ADDR(COMMON_REG_BASE + 0x60 + n*4 + 2)
#define Pn_BDPTHR0(n)   Pn_BDPTHR(n)
#define Pn_BDPTHR1(n)   SHIFT_ADDR(COMMON_REG_BASE + 0x60 + n*4 + 3)

/**
 *  W5300 identification register
 */
#define IDR             SHIFT_ADDR(COMMON_REG_BASE + 0xFE)
#define IDR1            SHIFT_ADDR(COMMON_REG_BASE + 0xFF)


/**
 *  SOCKETn mode register
 */
#define Sn_MR(n)        SHIFT_ADDR(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x00)
#define Sn_MR0(n)       Sn_MR(n)
#define Sn_MR1(n)       SHIFT_ADDR(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x01)

/**
 *  SOCKETn command register
 */                        
#define Sn_CR(n)        SHIFT_ADDR(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x02)
#define Sn_CR0(n)       Sn_CR(n)
#define Sn_CR1(n)       SHIFT_ADDR(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x03)

/**
 *  SOCKETn interrupt mask register
 */
#define Sn_IMR(n)       SHIFT_ADDR(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x04)
#define Sn_IMR0(n)      Sn_IMR(n)
#define Sn_IMR1(n)      SHIFT_ADDR(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x05)

/**
 *  SOCKETn interrupt register
 */
#define Sn_IR(n)        SHIFT_ADDR(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x06)
#define Sn_IR0(n)       Sn_IR(n)
#define Sn_IR1(n)       SHIFT_ADDR(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x07)

/**
 *  SOCKETn status register
 */
#define Sn_SSR(n)       SHIFT_ADDR(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x08)
#define Sn_SSR0(n)      Sn_SSR(n)
#define Sn_SSR1(n)      SHIFT_ADDR(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x09)

/**
 *  SOCKETn source port register
 */
#define Sn_PORTR(n)     SHIFT_ADDR(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x0A)
#define Sn_PORTR0(n)    Sn_PORTR(n)
#define Sn_PORTR1(n)    SHIFT_ADDR(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x0B)

/**
 *  SOCKETn destination hardware address register
 */
#define Sn_DHAR(n)      SHIFT_ADDR(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x0C)
#define Sn_DHAR0(n)     Sn_DHAR(n)
#define Sn_DHAR1(n)     SHIFT_ADDR(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x0D)
#define Sn_DHAR2(n)     SHIFT_ADDR(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x0E)
#define Sn_DHAR3(n)     SHIFT_ADDR(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x0F)
#define Sn_DHAR4(n)     SHIFT_ADDR(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x10)
#define Sn_DHAR5(n)     SHIFT_ADDR(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x11)

/**
 *  SOCKETn destination port register
 */
#define Sn_DPORTR(n)    SHIFT_ADDR(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x12)
#define Sn_DPORTR0(n)   Sn_DPORTR(n)
#define Sn_DPORTR1(n)   SHIFT_ADDR(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x13)


/**
 *  SOCKETn destination IP address register
 */
#define Sn_DIPR(n)      SHIFT_ADDR(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x14)
#define Sn_DIPR0(n)     Sn_DIPR(n)
#define Sn_DIPR1(n)     SHIFT_ADDR(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x15)
#define Sn_DIPR2(n)     SHIFT_ADDR(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x16)
#define Sn_DIPR3(n)     SHIFT_ADDR(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x17)

/**
 *  SOCKETn maximum segment size register
 */
#define Sn_MSSR(n)      SHIFT_ADDR(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x18)
#define Sn_MSSR0(n)     Sn_MSSR(n)
#define Sn_MSSR1(n)     SHIFT_ADDR(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x19)

/**
 *  SOCKETn protocol of IP header field register
 */
#define Sn_PROTOR(n)		SHIFT_ADDR(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x1A)
/**
 *  SOCKETn keep alive timer register
 */
#define Sn_KPALVTR(n)   Sn_PROTOR(n)
#define Sn_PROTOR1(n)   SHIFT_ADDR(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x1B)

/**
 *  SOCKETn IP type of service(TOS) register
 */
#define Sn_TOSR(n)      SHIFT_ADDR(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x1C)
#define Sn_TOSR0(n)     Sn_TOSR(n)
#define Sn_TOSR1(n)     SHIFT_ADDR(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x1D)

/**
 *  SOCKETn IP time to live(TTL) register
 */
#define Sn_TTLR(n)      SHIFT_ADDR(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x1E)
#define Sn_TTLR0(n)     Sn_TTLR(n)
#define Sn_TTLR1(n)     SHIFT_ADDR(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x1F)

/**
 *  SOCKETn TX write size register
 */
#define Sn_TX_WRSR(n)		SHIFT_ADDR(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x20)
#define Sn_TX_WRSR0(n)		Sn_TX_WRSR(n)
#define Sn_TX_WRSR1(n)		SHIFT_ADDR(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x21)
#define Sn_TX_WRSR2(n)		SHIFT_ADDR(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x22)
#define Sn_TX_WRSR3(n)		SHIFT_ADDR(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x23)

/**
 *  SOCKETn TX free size register
 */
#define Sn_TX_FSR(n)       SHIFT_ADDR(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x24)
#define Sn_TX_FSR0(n)      Sn_TX_FSR(n)
#define Sn_TX_FSR1(n)      SHIFT_ADDR(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x25)
#define Sn_TX_FSR2(n)      SHIFT_ADDR(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x26)
#define Sn_TX_FSR3(n)      SHIFT_ADDR(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x27)

/**
 *  SOCKETn RX received size register
 */
#define Sn_RX_RSR(n)       SHIFT_ADDR(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x28)
#define Sn_RX_RSR0(n)      Sn_RX_RSR(n)
#define Sn_RX_RSR1(n)      SHIFT_ADDR(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x29)
#define Sn_RX_RSR2(n)      SHIFT_ADDR(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x2A)
#define Sn_RX_RSR3(n)      SHIFT_ADDR(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x2B)

/**
 *  SOCKETn fragment register
 */
#define Sn_FRAGR(n)        SHIFT_ADDR(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x2C)
#define Sn_FRAGR0(n)       Sn_FRAGR(n)
#define Sn_FRAGR1(n)       SHIFT_ADDR(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x2D)

/**
 *  SOCKETn TX FIFO register
 */
#define Sn_TX_FIFOR(n)     SHIFT_ADDR(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x2E)
#define Sn_TX_FIFOR0(n)    Sn_TX_FIFO(n)
#define Sn_TX_FIFOR1(n)    SHIFT_ADDR(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x2F)

/**
 *  SOCKET n RX FIFO register
 */
#define Sn_RX_FIFOR(n)     SHIFT_ADDR(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x30)
#define Sn_RX_FIFOR0(n)    Sn_RX_FIFO(n)
#define Sn_RX_FIFOR1(n)    SHIFT_ADDR(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x31)


//#define Sn_TX_SADR(n)      SHIFT_ADDR(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x32)
//#define Sn_TX_SADR0(n)     Sn_TX_SADR(n)
//#define Sn_TX_SADR1(n)     SHIFT_ADDR(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x33)

//#define Sn_RX_SADR(n)      SHIFT_ADDR(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x34)
//#define Sn_RX_SADR0(n)     Sn_RX_SADR(n)
//#define Sn_RX_SADR1(n)     SHIFT_ADDR(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x35)

//#define Sn_TX_RD(n)        SHIFT_ADDR(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x36)
//#define Sn_TX_RD0(n)       (Sn_TX_RD(n) + 1)
//#define Sn_TX_RD1(n)       SHIFT_ADDR(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x37)

//#define Sn_TX_WR(n)        SHIFT_ADDR(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x38)
//#define Sn_TX_WR0(n)       Sn_TX_WR(n)
//#define Sn_TX_WR1(n)       SHIFT_ADDR(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x39)

//#define Sn_TX_ACK(n)       SHIFT_ADDR(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x3A)
//#define Sn_TX_ACK0(n)      Sn_TX_ACK(n)
//#define Sn_TX_ACK1(n)      SHIFT_ADDR(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x3B)

//#define Sn_RX_RD(n)        SHIFT_ADDR(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x3C)
//#define Sn_RX_RD0(n)	     Sn_RX_RD(n)
//#define Sn_RX_RD1(n)	     SHIFT_ADDR(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x3D)

//#define Sn_RX_WR(n)        SOCKET_REG_BASE + SHIFT_ADDR(n * SOCKET_REG_SIZE + 0x3E)
//#define Sn_RX_WR0(n)        Sn_RX_WR(n)
//#define Sn_RX_WR1(n)       SHIFT_ADDR(SOCKET_REG_BASE + n * SOCKET_REG_SIZE + 0x3F)



/************************************/
/* The bit of MR regsiter defintion */
/************************************/
#define MR_DBW             (1 << 15)            /**< Data bus width bit of MR. */
#define MR_MPF             (1 << 14)            /**< Mac layer pause frame bit of MR. */
#define MR_WDF(X)          ((X & 0x07) << 11)   /**< Write data fetch time bit of  MR. */
#define MR_RDH             (1 << 10)            /**< Read data hold time bit of MR. */
#define MR_FS              (1 << 8)             /**< FIFO swap bit of MR. */
#define MR_RST             (1 << 7)             /**< S/W reset bit of MR. */
#define MR_MT              (1 << 5)             /**< Memory test bit of MR. */
#define MR_PB              (1 << 4)             /**< Ping block bit of MR. */
#define MR_PPPoE           (1 << 3)             /**< PPPoE bit of MR. */
#define MR_DBS             (1 << 2)             /**< Data bus swap of MR. */
#define MR_IND             (1 << 0)             /**< Indirect mode bit of MR. */


/************************************/ 
/* The bit of IR regsiter defintion */ 
/************************************/ 
#define IR_IPCF            (1 << 7)             /**< IP conflict bit of IR. */
#define IR_DPUR            (1 << 6)             /**< Destination port unreachable bit of IR. */
#define IR_PPPT            (1 << 5)             /**< PPPoE terminate bit of IR. */
#define IR_FMTU            (1 << 4)             /**< Fragment MTU bit of IR. */
#define IR_SnINT(n)        (0x01 << n)          /**< SOCKETn interrupt occurrence bit of IR. */

/*****************************************/ 
/* The bit of Pn_BRDYR regsiter defintion*/ 
/*****************************************/ 
#define Pn_PEN             (1 << 7)             /**< PIN 'BRDYn' enable bit of Pn_BRDYR. */
#define Pn_MT              (1 << 6)             /**< PIN memory type bit of Pn_BRDYR. */
#define Pn_PPL             (1 << 5)             /**< PIN Polarity bit of Pn_BRDYR. */
#define Pn_SN(n)           ((n & 0x07) << 0)    /**< PIN Polarity bit of Pn_BRDYR. */


/***************************************/ 
/* The bit of Sn_MR regsiter defintion */ 
/***************************************/ 
#define Sn_MR_ALIGN        (1 << 8)             /**< Alignment bit of Sn_MR. */
#define Sn_MR_MULTI        (1 << 7)             /**< Multicasting bit of Sn_MR. */
#define Sn_MR_MF           (1 << 6)             /**< MAC filter bit of Sn_MR. */
#define Sn_MR_IGMPv        (1 << 5)             /**< IGMP version bit of Sn_MR. */
#define Sn_MR_ND           (1 << 5)             /**< No delayed ack bit of Sn_MR. */
#define Sn_MR_CLOSE        0x00                 /**< Protocol bits of Sn_MR. */
#define Sn_MR_TCP          0x01                 /**< Protocol bits of Sn_MR. */
#define Sn_MR_UDP          0x02                 /**< Protocol bits of Sn_MR. */
#define Sn_MR_IPRAW        0x03                 /**< Protocol bits of Sn_MR. */
#define Sn_MR_MACRAW       0x04                 /**< Protocol bits of Sn_MR. */
#define Sn_MR_PPPoE        0x05                 /**< Protocol bits of Sn_MR. */


/******************************/ 
/* The values of CR defintion */ 
/******************************/
#define Sn_CR_OPEN         0x01                 /**< OPEN command value of Sn_CR. */
#define Sn_CR_LISTEN       0x02                 /**< LISTEN command value of Sn_CR. */
#define Sn_CR_CONNECT      0x04                 /**< CONNECT command value of Sn_CR. */
#define Sn_CR_DISCON       0x08                 /**< DISCONNECT command value of Sn_CR. */
#define Sn_CR_CLOSE        0x10                 /**< CLOSE command value of Sn_CR. */
#define Sn_CR_SEND         0x20                 /**< SEND command value of Sn_CR. */
#define Sn_CR_SEND_MAC     0x21                 /**< SEND_MAC command value of Sn_CR. */ 
#define Sn_CR_SEND_KEEP    0x22                 /**< SEND_KEEP command value of Sn_CR */
#define Sn_CR_RECV         0x40                 /**< RECV command value of Sn_CR */
#define Sn_CR_PCON         0x23                 /**< PCON command value of Sn_CR */
#define Sn_CR_PDISCON      0x24                 /**< PDISCON command value of Sn_CR */ 
#define Sn_CR_PCR          0x25                 /**< PCR command value of Sn_CR */
#define Sn_CR_PCN          0x26                 /**< PCN command value of Sn_CR */
#define Sn_CR_PCJ          0x27                 /**< PCJ command value of Sn_CR */


/*********************************/ 
/* The values of Sn_IR defintion */ 
/*********************************/
#define Sn_IR_PRECV        0x80                 /**< PPP receive bit of Sn_IR */
#define Sn_IR_PFAIL        0x40                 /**< PPP fail bit of Sn_IR */
#define Sn_IR_PNEXT        0x20                 /**< PPP next phase bit of Sn_IR */
#define Sn_IR_SENDOK       0x10                 /**< Send OK bit of Sn_IR */
#define Sn_IR_TIMEOUT      0x08                 /**< Timout bit of Sn_IR */
#define Sn_IR_RECV         0x04                 /**< Receive bit of Sn_IR */
#define Sn_IR_DISCON       0x02                 /**< Disconnect bit of Sn_IR */
#define Sn_IR_CON          0x01                 /**< Connect bit of Sn_IR */

/**********************************/ 
/* The values of Sn_SSR defintion */ 
/**********************************/
#define SOCK_CLOSED        0x00                 /**< SOCKETn is released */
#define SOCK_ARP           0x01                 /**< ARP-request is transmitted in order to acquire destination hardware address. */
#define SOCK_INIT          0x13                 /**< SOCKETn is open as TCP mode. */
#define SOCK_LISTEN        0x14                 /**< SOCKETn operates as "TCP SERVER" and waits for connection-request (SYN packet) from "TCP CLIENT". */
#define SOCK_SYNSENT       0x15                 /**< Connect-request(SYN packet) is transmitted to "TCP SERVER". */
#define SOCK_SYNRECV       0x16                 /**< Connect-request(SYN packet) is received from "TCP CLIENT". */
#define SOCK_ESTABLISHED   0x17                 /**< TCP connection is established. */
#define SOCK_FIN_WAIT      0x18                 /**< SOCKETn is closing. */
#define SOCK_CLOSING       0x1A                 /**< SOCKETn is closing. */
#define SOCK_TIME_WAIT     0x1B                 /**< SOCKETn is closing. */
#define SOCK_CLOSE_WAIT    0x1C                 /**< Disconnect-request(FIN packet) is received from the peer. */
#define SOCK_LAST_ACK      0x1D                 /**< SOCKETn is closing. */
#define SOCK_UDP           0x22                 /**< SOCKETn is open as UDP mode. */
#define SOCK_IPRAW         0x32                 /**< SOCKETn is open as IPRAW mode. */
#define SOCK_MACRAW        0x42                 /**< SOCKET0 is open as MACRAW mode. */
#define SOCK_PPPoE         0x5F                 /**< SOCKET0 is open as PPPoE mode. */

/* IP PROTOCOL */
#define IPPROTO_IP         0   /* Dummy for IP */
#define IPPROTO_ICMP       1   /* Control message protocol */
#define IPPROTO_IGMP       2   /* Internet group management protocol */
#define IPPROTO_GGP        3   /* Gateway^2 (deprecated) */
#define IPPROTO_TCP        6   /* TCP */
#define IPPROTO_PUP        12  /* PUP */
#define IPPROTO_UDP        17  /* UDP */
#define IPPROTO_IDP        22  /* XNS idp */
#define IPPROTO_ND         77  /* UNOFFICIAL net disk protocol */
#define IPPROTO_RAW        255 /* Raw IP packet */

/***********************
 * Basic I/O  Function *
 ***********************/
/**
 * It reads a value from a register
 */
uint16   IINCHIP_READ(uint32 addr);

/**
 * It writes a value to a register
 */
void     IINCHIP_WRITE(uint32 addr,uint16 data);

/** 
 * It gets MR value.
 */
uint16   getMR(void);

/**
 * It sets MR value
 */
void     setMR(uint16 val);


/***********************************
 * COMMON Register Access Function *
 ***********************************/

/**
 * It gets IR value
 */
uint16   getIR(void);

/**
 * It sets IR value
 */
void     setIR(uint16 val);

/**
 * It gets IMR value
 */
uint16   getIMR(void);

/**
 * It sets IMR value
 */
void     setIMR(uint16 mask);

/**
 * It gets the source hardware address
 */
void     getSHAR(uint8 * addr);

/**
 * It sets the source hardware address
 */
void     setSHAR(uint8 * addr);

/**
 * It gets the gateway IP address
 */
void     getGAR(uint8 * addr);

/**
 * It sets the gateway IP address
 */
void     setGAR(uint8 * addr);    // set gateway address

/**
 * It gets the subnet mask address
 */
void     getSUBR(uint8 * addr);

/**
 * It sets the subnet mask address to global variable
 */
void     setSUBR(); // set subnet mask address

/**
 * It sets the subnet mask address from global variable
 */
void     saveSUBR(uint8 * addr); // set subnet mask address to SUBR

/**
 * It sets the subnet mask address "0.0.0.0"
 */
void     clearSUBR(); // set subnet mask address "0.0.0.0"

/**
 * It gets the source IP address
 */
void     getSIPR(uint8 * addr);

/**
 * It sets the source IP address
 */
void     setSIPR(uint8 * addr); // set local IP address

/**
 * It gets RTR value
 */
uint16   getRTR(void); 

/**
 * It sets RTR value
 */
void     setRTR(uint16 timeout); // set retry duration for data transmission, connection, closing ...

/**
 * It gets RCR value
 */
uint8    getRCR(void);
/**
 * It sets RCR value
 */
void     setRCR(uint8 retry); 

/**
 * It gets PATR value
 */
uint16   getPATR(void);

/**
 * It gets PTIMER value
 */
uint8    getPTIMER(void);

/**
 * It sets PTIMER value
 */
void     setPTIMER(uint8 time);

/**
 * It gets PMAGICR value
 */
uint8    getPMAGICR(void);

/**
 * It sets PTIMER value
 */
void     setPMAGICR(uint8 magic);

/**
 *  It gets PSIDR value
 */
uint16   getPSIDR(void);

/**
 *  It gets the PPPoE server hardware address
 */
void     getPDHAR(uint8* addr);

/**
 *  It gets the unreachable destination IP address of ICMP message.
 */
void     getUIPR(uint8* addr);

/**
 *  It gets the unreachable destination port number of ICMP message.
 */
uint16   getUPORTR(void);

/**
 *  It gets the fragmented MTU value of ICMP message.
 */
uint16   getFMTUR(void);

/**
 *  It gets Pn_BRDYR value.
 */
uint8    getPn_BRDYR(uint8 p);

/**
 *  It sets Pn_BRDYR value.
 */
void     setPn_BRDYR(uint8 p, uint8 cfg);

/**
 *  It gets the buffer depth of PIN "BRDYn".
 */
uint16   getPn_BDPTHR(uint8 p);

/**
 *  It sets the buffer depth of PIN "BRDYn".
 */
void     setPn_BDPTHR(uint8 p, uint16 depth);

/**
 *  It gets the ID of W5300.
 */
uint16   getIDR(void);



/***********************************
 * SOCKET Register Access Function *
 ***********************************/

/**
 *  It gets Sn_MR value.
 */
uint16   getSn_MR(SOCKET s);

/**
 *  It sets Sn_MR value.
 */
void     setSn_MR(SOCKET s, uint16 mode); 

/**
 *  It gets Sn_CR value.
 */
uint8    getSn_CR(SOCKET s);
/**
 *  It sets Sn_CR value.
 */
void     setSn_CR(SOCKET s, uint16 com);

/**
 *  It gets Sn_IMR value.
 */
uint8    getSn_IMR(SOCKET s);

/**
 *  It sets Sn_IMR value.
 */
void     setSn_IMR(SOCKET s, uint8 mask);

/**
 *  It gets Sn_IR value.
 */
uint8    getSn_IR(SOCKET s);

/**
 *  It sets Sn_IR value.
 */
void     setSn_IR(SOCKET s, uint8 ir);

/**
 *  It gets Sn_SSR value.
 */
uint8    getSn_SSR(SOCKET s);

/**
 *  It gets Sn_DHAR value.
 */
void     getSn_DHAR(SOCKET s, uint8* addr);

/**
 *  It sets Sn_DHAR value.
 */
void     setSn_DHAR(SOCKET s, uint8* addr);

// M_15052008 : Delete this function.
/*
 *  It gets Sn_DPORTR value.
 */
//uint16   getSn_DPORTR(SOCKET s);

/**
 *  It sets Sn_DPORTR value.
 */
void     setSn_DPORTR(SOCKET s, uint16 port);

/**
 *  It gets Sn_DIPR value.
 */
void     getSn_DIPR(SOCKET s, uint8* addr);

/**
 *  It sets Sn_DIPR value.
 */
void     setSn_DIPR(SOCKET s, uint8* addr);

/**
 *  It gets Sn_MSSR value.
 */
uint16   getSn_MSSR(SOCKET s);

/**
 *  It sets Sn_MSSR value.
 */
void     setSn_MSSR(SOCKET s, uint16 mss);

/**
 *  It gets Sn_KPALVTR value.
 */
uint8    getSn_KPALVTR(SOCKET s);

/**
 *  It sets Sn_KPALVTR value.
 */
void     setSn_KPALVTR(SOCKET s, uint8 time);

/**
 *  It gets Sn_TX_WRSR value.
 */
uint32   getSn_TX_WRSR(SOCKET s);

/**
 *  It gets Sn_KPALVTR value.
 */
void     setSn_TX_WRSR(SOCKET s, uint32 size);

/**
 *  It gets Sn_TX_FSR value.
 */
uint32   getSn_TX_FSR(SOCKET s);

/**
 *  It gets Sn_RX_RSR value.
 */
uint32   getSn_RX_RSR(SOCKET s);

/**
 *  It sets Sn_TX_FIFOR value.
 */
void     setSn_TX_FIFOR(SOCKET s, uint16 data);

/**
 *  It gets Sn_RX_FIFOR value.
 */
uint16   getSn_RX_FIFOR(SOCKET s);

/**
 *  It gets Sn_PROTOR value.
 */
uint8    getSn_PROTOR(SOCKET s);

/**
 *  It sets Sn_PROTOR value.
 */
void     setSn_PROTOR(SOCKET s, uint8 pronum);

/**
 *  It gets Sn_TOSR value.
 */
uint8    getSn_TOSR(SOCKET s);

/**
 *  It sets Sn_TOSR value.
 */
void     setSn_TOSR(SOCKET s, uint8 tos);

/**
 *  It gets Sn_TTLR value.
 */
uint8    getSn_TTLR(SOCKET s);

/**
 *  It sets Sn_TTLR value.
 */
void     setSn_TTLR(SOCKET s, uint8 ttl);

/**
 *  It gets Sn_FRAGR value.
 */
uint8    getSn_FRAGR(SOCKET s);
/**
 *  It sets Sn_FRAGR value.
 */
void     setSn_FRAGR(SOCKET s, uint8 frag);



/*******
 * ETC *
 *******/

/* Initialization & Interrupt request routine */

/**
 *  It initializes W5300.
 */
void     iinchip_init(void); 

/**
 *  It handles the interrupt of W5300.
 */
#ifdef __DEF_IINCHIP_INT__
   void     iinchip_irq(void);
#endif


/* Interanl memory operation */

/**
 *  It allocate internal TX/RX meory of each SOCKET.
 */
uint8    sysinit(uint8* tx_size, uint8* rx_size); // setting tx/rx buf size


/**
 *  It copies data to interna TX memory
 */
uint32   wiz_write_buf(SOCKET s,uint8* buf,uint32 len);


/**
 *  It copies data to your buffer from interna RX memory
 */
uint32   wiz_read_buf(SOCKET s, uint8* buf,uint32 len);


/**
 *  It gets the max size of internal TX memory of each SOCKET
 */
uint32   getIINCHIP_TxMAX(SOCKET s);

/**
 *  It gets the max size of internal RX memory of each SOCKET
 */
uint32   getIINCHIP_RxMAX(SOCKET s);



#ifdef __DEF_IINCHIP_PPP__
   /**
    *  It initializes to PPPoE of W5300
    */
   uint8    pppinit(uint8 *id, uint8 idlen, uint8 *passwd, uint8 passwdlen);
   /**
    *  It terminates PPPoE connection 
    */   
   void    pppterm(uint8 *mac, uint16 sessionid);
#endif

/**
 *  Delay function
 */
void  wait_1us(uint32 us);
/**
 *  Delay function
 */
void  wait_1ms(uint32 ms);
/**
 *  Delay function
 */
void  wait_10ms(uint32 ms);
#endif
