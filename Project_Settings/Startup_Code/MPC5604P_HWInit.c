/*
 * FILE : MPC560xP_HWInit.c
 *    
 * COPYRIGHT (c) 2007-2012 Freescale Semiconductor, Inc. All rights reserved.
 *     
 * DESCRIPTION: This file contains MPC560xP derivatives basic initializations.
 *  This includes initializing SRAM and disabling SWT.
 *  
 *  For more on Qorivva MCUs module initializations please consult the Qorivva cookbook AN2865.  
 *
 * VERSION: 1.2
 */

#include "MPC5604P.h"   /* MCU platform development header */
#include "MPC5604P_HWInit.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Symbol L2SRAM_LOCATION is defined in the application linker command file (.lcf)
   It represents the start of the L2SRAM.
*/
/*lint -esym(752, L2SRAM_LOCATION) */
extern long L2SRAM_LOCATION;

/* Symbol L2SRAM_CNT is defined in the application linker command file (.lcf)
   It represents the how many writes with stmw,128 bytes each, are needed to cover
   the whole L2SRAM.
*/
extern long L2SRAM_CNT;

/*----------------------------------------------------------------*/
/* Function implementations                                       */
/*----------------------------------------------------------------*/

MAKE_HLI_COMPATIBLE(SR_WSC_1, 0xc520) /*50464*/
MAKE_HLI_COMPATIBLE(SR_WSC_2, 0xd928) /*55592*/
MAKE_HLI_COMPATIBLE(CR_VALUE, 0x8000010A)
MAKE_HLI_COMPATIBLE(SWT_SR, &SWT.SR.R) /* Address of the SWT SR */
MAKE_HLI_COMPATIBLE(SWT_CR, &SWT.CR.R) /* Address of the SWT MCR */

/*------------------------------------------------------------------*/
/* FUNCTION     : INIT_Derivative                                   */
/* PURPOSE      : This function initializes the derivative.         */
/* SEQUENCE:                                                        */
/* - disables system WDT and Core WDT                               */
/* - initializes the internal SRAM for ROM targets                  */
/*------------------------------------------------------------------*/
__asm void INIT_Derivative(void) 
{
nofralloc
    /* Disable the system watchdog timer */
    /* Clear the soft lock bit SWT_CR.SLKSWT_CR: */
    /* SR --> 0x0000c520 */
    lis r4, 0
    ori r4, r4, SR_WSC_1@l
    lis r3, SWT_SR@ha
    stw r4, SWT_SR@l(r3)
    /* SR --> 0x0000d928 */
    lis r4, 0
    ori r4, r4, SR_WSC_2@l
    stw r4, SWT_SR@l(r3)

    /* Disable watchdog, SWT.CR.WEN = 0*/
    lis r4, CR_VALUE@h
    ori r4, r4, CR_VALUE@l
    lis r3, SWT_CR@ha
    stw r4, SWT_CR@l(r3)

#if defined(ROM_VERSION)
    /* SRAM initialization code*/
    lis r11,L2SRAM_LOCATION@h
    ori r11,r11,L2SRAM_LOCATION@l

    /* Loops to cover L2SRAM, stmw allows 128 bytes (32 GPRS x 4 bytes) writes */
    lis r12,L2SRAM_CNT@h
    ori r12,r12,L2SRAM_CNT@l
    mtctr r12

    init_l2sram_loop:
        stmw r0, 0(r11)        /* Write 32 GPRs to SRAM*/
        addi r11,r11,128       /* Inc the ram ptr; 32 GPRs * 4 bytes = 128B */
        bdnz init_l2sram_loop  /* Loop for L2SRAM_CNT times */
#endif
    blr
}

__asm void INIT_ExternalBusAndMemory(void)
{
nofralloc
    blr
}

#ifdef __cplusplus
}
#endif
