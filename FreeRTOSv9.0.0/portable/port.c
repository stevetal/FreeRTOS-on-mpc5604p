/*
    FreeRTOS V7.3.0 - Copyright (C) 2012 Real Time Engineers Ltd.

    FEATURES AND PORTS ARE ADDED TO FREERTOS ALL THE TIME.  PLEASE VISIT
    http://www.FreeRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS tutorial books are available in pdf and paperback.        *
     *    Complete, revised, and edited pdf reference manuals are also       *
     *    available.                                                         *
     *                                                                       *
     *    Purchasing FreeRTOS documentation will not only help you, by       *
     *    ensuring you get running as quickly as possible and with an        *
     *    in-depth knowledge of how to use FreeRTOS, it will also help       *
     *    the FreeRTOS project to continue with its mission of providing     *
     *    professional grade, cross platform, de facto standard solutions    *
     *    for microcontrollers - completely free of charge!                  *
     *                                                                       *
     *    >>> See http://www.FreeRTOS.org/Documentation for details. <<<     *
     *                                                                       *
     *    Thank you for using FreeRTOS, and thank you for your support!      *
     *                                                                       *
    ***************************************************************************


    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation AND MODIFIED BY the FreeRTOS exception.
    >>>NOTE<<< The modification to the GPL is included to allow you to
    distribute a combined work that includes FreeRTOS without being obliged to
    provide the source code for proprietary components outside of the FreeRTOS
    kernel.  FreeRTOS is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
    or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
    more details. You should have received a copy of the GNU General Public
    License and the FreeRTOS license exception along with FreeRTOS; if not it
    can be viewed here: http://www.freertos.org/a00114.html and also obtained
    by writing to Richard Barry, contact details for whom are available on the
    FreeRTOS WEB site.

    1 tab == 4 spaces!

    ***************************************************************************
     *                                                                       *
     *    Having a problem?  Start by reading the FAQ "My application does   *
     *    not run, what could be wrong?"                                     *
     *                                                                       *
     *    http://www.FreeRTOS.org/FAQHelp.html                               *
     *                                                                       *
    ***************************************************************************


    http://www.FreeRTOS.org - Documentation, training, latest versions, license
    and contact details.

    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
    including FreeRTOS+Trace - an indispensable productivity tool.

    Real Time Engineers ltd license FreeRTOS to High Integrity Systems, who sell
    the code with commercial support, indemnification, and middleware, under
    the OpenRTOS brand: http://www.OpenRTOS.com.  High Integrity Systems also
    provide a safety engineered and independently SIL3 certified version under
    the SafeRTOS brand: http://www.SafeRTOS.com.
*/


#include "MPC5604P.h"
#include "Exceptions.h"
#include "IntcInterrupts.h"

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"

/*-----------------------------------------------------------*/
#define TICK_INTERVAL  ((configCPU_CLOCK_HZ / configTICK_RATE_HZ ) - 1UL)
#define SYS_TIMER_PIT_CHANNEL            0

// Defined by the linker EABI
extern unsigned long _SDA2_BASE_[];
extern unsigned long _SDA_BASE_[];


//extern void vPortTickISR(void);

/*
 * Function to start the scheduler running by starting the highest
 * priority task that has thus far been created.
 */
extern void vPortStartFirstTask( void );
/*
 * Setup the system timer to generate the tick interrupt.
 */
void prvPortTimerSetup( void );
/*-----------------------------------------------------------*/

void vPortTickISR(void);

/* 
 * Initialise the stack of a task to look exactly as if the task had been
 * interrupted.
 * 
 * See the header file portable.h.
 */
 
 __asm unsigned long GetMSR(void)
 {
	nofralloc	 
    mfmsr   r3
    se_blr
 }
portSTACK_TYPE *pxPortInitialiseStack( portSTACK_TYPE *pxTopOfStack, pdTASK_CODE pxCode, void *pvParameters )
{
      register portSTACK_TYPE msr, srr1;
      portSTACK_TYPE *pxBackchain;

      //MFMSR(msr);
      //srr1 = portINITIAL_MSR | msr;
      
      msr = GetMSR();
      srr1 = msr | (1 << 15); // External interrupt enable

      /* Place a known value at the bottom of the stack for debugging */
  	*pxTopOfStack = 0xDEADBEEF;
      pxTopOfStack--;

      *pxTopOfStack = 0x0L; /*padding bytes to meet EABI 16 byte alignment */
      pxTopOfStack--;
      
      /* Create a root frame header */
      *pxTopOfStack = 0x0L; /* Root lr save word */
      pxTopOfStack--;
      *pxTopOfStack = 0x0L; /* Root backchain */
      pxTopOfStack--;

      pxBackchain = pxTopOfStack;

      *pxTopOfStack = 0x1FL;                                                    /* r31  - 0x9C */
      pxTopOfStack--;
      *pxTopOfStack = 0x1EL;                                                    /* r30  - 0x98 */
      pxTopOfStack--;
      *pxTopOfStack = 0x1DL;                                                    /* r29  - 0x94 */
      pxTopOfStack--;
      *pxTopOfStack = 0x1CL;                                                    /* r28  - 0x90 */
      pxTopOfStack--;
      *pxTopOfStack = 0x1BL;                                                    /* r27  - 0x8C */
      pxTopOfStack--;
      *pxTopOfStack = 0x1AL;                                                    /* r26  - 0x88 */
      pxTopOfStack--;
      *pxTopOfStack = 0x19L;                                                    /* r25  - 0x84 */
      pxTopOfStack--;
      *pxTopOfStack = 0x18L;                                                    /* r24  - 0x80 */
      pxTopOfStack--;
      *pxTopOfStack = 0x17L;                                                    /* r23  - 0x7C */
      pxTopOfStack--;
      *pxTopOfStack = 0x16L;                                                    /* r22  - 0x78 */
      pxTopOfStack--;
      *pxTopOfStack = 0x15L;                                                    /* r21  - 0x74 */
      pxTopOfStack--;
      *pxTopOfStack = 0x14L;                                                    /* r20  - 0x70 */
      pxTopOfStack--;
      *pxTopOfStack = 0x13L;                                                    /* r19  - 0x6C */
      pxTopOfStack--;
      *pxTopOfStack = 0x12L;                                                    /* r18  - 0x68 */
      pxTopOfStack--;
      *pxTopOfStack = 0x11L;                                                    /* r17  - 0x64 */
      pxTopOfStack--;
      *pxTopOfStack = 0x10L;                                                    /* r16  - 0x60 */
      pxTopOfStack--;
      *pxTopOfStack = 0xFL;                                                     /* r15  - 0x5C */
      pxTopOfStack--;
      *pxTopOfStack = 0xEL;                                                     /* r14  - 0x58 */
      pxTopOfStack--;
      *pxTopOfStack = 0xCL;                                                     /* r12  - 0x54 */
      pxTopOfStack--;
      *pxTopOfStack = 0xBL;                                                     /* r11  - 0x50 */
      pxTopOfStack--;
      *pxTopOfStack = 0xAL;                                                     /* r10  - 0x4C */
      pxTopOfStack--;
      *pxTopOfStack = 0x9L;                                                     /* r09  - 0x48 */
      pxTopOfStack--;
      *pxTopOfStack = 0x8L;                                                     /* r08  - 0x44 */
      pxTopOfStack--;
      *pxTopOfStack = 0x7L;                                                     /* r07  - 0x40 */
      pxTopOfStack--;
      *pxTopOfStack = 0x6L;                                                     /* r06  - 0x33C */
      pxTopOfStack--;
      *pxTopOfStack = 0x5L;                                                     /* r05  - 0x38 */
      pxTopOfStack--;
      *pxTopOfStack = 0x4L;                                                     /* r04  - 0x34 */
      pxTopOfStack--;
      *pxTopOfStack = ( portSTACK_TYPE ) pvParameters;                          /* r03  - 0x30 */
      pxTopOfStack--;
      *pxTopOfStack = 0x0L;                                                     /* r00  - 0x2C */
      pxTopOfStack--;

      *pxTopOfStack = 0x0L;                                                     /* XER  - 0x28 */
      pxTopOfStack--;

      *pxTopOfStack = 0x0L;                                                     /* CTR  - 0x24 */
      pxTopOfStack--;

      *pxTopOfStack = ( portSTACK_TYPE ) pxCode;                                /* LR   - 0x20 */
      pxTopOfStack--;

      *pxTopOfStack = 0x0L;                                                     /* CR   - 0x1C */
      pxTopOfStack--;

      *pxTopOfStack = srr1;                                                     /* SRR1 - 0x18 */
      pxTopOfStack--;

      *pxTopOfStack = ( portSTACK_TYPE ) pxCode;                                /* SRR0 - 0x14 */
      pxTopOfStack--;

      *pxTopOfStack = 0x0L;                                                     /* Pad - 0x10 */
      pxTopOfStack--;
      
      *pxTopOfStack = 0x0L;                                                     /* Pad - 0x0C */
      pxTopOfStack--;
      
      *pxTopOfStack = 0x0L;                                                     /* Pad - 0x08 */
      pxTopOfStack--;

      *pxTopOfStack = 0x0L;                                                     /* LR save word - 0x04 */
      pxTopOfStack--;

      *pxTopOfStack = ( portSTACK_TYPE ) pxBackchain;                           /* SP(r1) - 0x00 */

      return pxTopOfStack;   

}
/*-----------------------------------------------------------*/

portBASE_TYPE xPortStartScheduler( void )
{
    EXCEP_InitExceptionHandlers();
    INTC_InitINTCInterrupts();
    INTC.CPR.B.PRI = 0;
    

    prvPortTimerSetup();

    vPortStartFirstTask();

    /* Should not get here as the tasks are now running! */
    return pdFALSE;
}
/*-----------------------------------------------------------*/

void vPortEndScheduler( void )
{
    /* Not implemented. */
    for( ;; );
}
/*-----------------------------------------------------------*/

void prvPortTimerSetup(void)
{
    PIT.PITMCR.R = 1;           //enable PIT
    PIT.CH[SYS_TIMER_PIT_CHANNEL].LDVAL.R     = TICK_INTERVAL;
    PIT.CH[SYS_TIMER_PIT_CHANNEL].TCTRL.B.TIE = 1;
    PIT.CH[SYS_TIMER_PIT_CHANNEL].TCTRL.B.TEN = 1;
    INTC_InstallINTCInterruptHandler(vPortTickISR, 59, 15);
}
/*-----------------------------------------------------------*/

void vPortTimerReset(void)
{
    if( PIT.CH[SYS_TIMER_PIT_CHANNEL].TFLG.B.TIF == 1 )
        PIT.CH[SYS_TIMER_PIT_CHANNEL].TFLG.B.TIF = 1;
}

void vPortTickISR(void)
{
    xTaskIncrementTick();
#if (configUSE_PREEMPTION == 1)
    vTaskSwitchContext();
#endif
    vPortTimerReset();
}
