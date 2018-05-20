;
;    FreeRTOS V7.3.0 - Copyright (C) 2012 Real Time Engineers Ltd.
;
;    FEATURES AND PORTS ARE ADDED TO FREERTOS ALL THE TIME.  PLEASE VISIT
;    http://www.FreeRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.
;
;    ***************************************************************************
;     *                                                                       *
;     *    FreeRTOS tutorial books are available in pdf and paperback.        *
;     *    Complete, revised, and edited pdf reference manuals are also       *
;     *    available.                                                         *
;     *                                                                       *
;     *    Purchasing FreeRTOS documentation will not only help you, by       *
;     *    ensuring you get running as quickly as possible and with an        *
;     *    in-depth knowledge of how to use FreeRTOS, it will also help       *
;     *    the FreeRTOS project to continue with its mission of providing     *
;     *    professional grade, cross platform, de facto standard solutions    *
;     *    for microcontrollers - completely free of charge!                  *
;     *                                                                       *
;     *    >>> See http://www.FreeRTOS.org/Documentation for details. <<<     *
;     *                                                                       *
;     *    Thank you for using FreeRTOS, and thank you for your support!      *
;     *                                                                       *
;    ***************************************************************************
;
;
;    This file is part of the FreeRTOS distribution.
;
;    FreeRTOS is free software; you can redistribute it and/or modify it under
;    the terms of the GNU General Public License (version 2) as published by the
;    Free Software Foundation AND MODIFIED BY the FreeRTOS exception.
;    >>>NOTE<<< The modification to the GPL is included to allow you to
;    distribute a combined work that includes FreeRTOS without being obliged to
;    provide the source code for proprietary components outside of the FreeRTOS
;    kernel.  FreeRTOS is distributed in the hope that it will be useful, but
;    WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
;    or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
;    more details. You should have received a copy of the GNU General Public
;    License and the FreeRTOS license exception along with FreeRTOS; if not it
;    can be viewed here: http://www.freertos.org/a00114.html and also obtained
;    by writing to Richard Barry, contact details for whom are available on the
;    FreeRTOS WEB site.
;
;    1 tab == 4 spaces!
;
;    ***************************************************************************
;     *                                                                       *
;     *    Having a problem?  Start by reading the FAQ "My application does   *
;     *    not run, what could be wrong?"                                     *
;     *                                                                       *
;     *    http://www.FreeRTOS.org/FAQHelp.html                               *
;     *                                                                       *
;    ***************************************************************************
;
;
;    http://www.FreeRTOS.org - Documentation, training, latest versions, license
;    and contact details.
;
;    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
;    including FreeRTOS+Trace - an indispensable productivity tool.
;
;    Real Time Engineers ltd license FreeRTOS to High Integrity Systems, who sell
;    the code with commercial support, indemnification, and middleware, under
;    the OpenRTOS brand: http://www.OpenRTOS.com.  High Integrity Systems also
;    provide a safety engineered and independently SIL3 certified version under
;    the SafeRTOS brand: http://www.SafeRTOS.com.
;
;
; (C) Copyright 2013
; Promwad Innovation Company <www.promwad.com>
; Written-by: Vladimir Trubilov <vladimir.trubilov@promwad.com>

    .section .text_vle

    .extern vTaskSwitchContext
    .extern pxCurrentTCB
    .extern timer

    .global vPortYield
    .global vPortTickISR
    .global vPortISRHandler
    .global vPortStartFirstTask

    .equ INTC_IACKR,    0xFFF48010    ; XPC5xxx: Interrupt Acknowledge Reg. addr.
    .equ INTC_EOIR,     0xFFF48018    ; XPC5xxx: End Of Interrupt Reg. addr.

/*
   STACK FRAME DESIGN: Depth: (0x98, or 152 bytes modulo 8 bytes = 19)
              ************* ______________
     0x9C     *  GPR31    *    ^
     0x98     *  GPR30    *    |
     0x94     *  GPR29    *    |
     0x90     *  GPR28    *    |
     0x8C     *  GPR27    *    |
     0x88     *  GPR26    *    |
     0x84     *  GPR25    *    |
     0x80     *  GPR24    *    |
     0x7C     *  GPR23    *    |
     0x78     *  GPR22    *    |
     0x74     *  GPR21    *    |
     0x70     *  GPR20    *    |
     0x6C     *  GPR19    *    |
     0x68     *  GPR18    *    |
     0x64     *  GPR17    *    |
     0x60     *  GPR16    *    |
     0x5C     *  GPR15    *    |
     0x58     *  GPR14    *    |
     0x54     *  GPR12    *    |
     0x50     *  GPR11    *    |
     0x4C     *  GPR10    *    |
     0x48     *  GPR9     *    |
     0x44     *  GPR8     *    |
     0x40     *  GPR7     *  GPRs (32 bit)
     0x3C     *  GPR6     *    |
     0x38     *  GPR5     *    |
     0x34     *  GPR4     *    |
     0x30     *  GPR3     *    |
     0x2C     *  GPR0     * ___v__________
     0x28     *  XER      *    ^
     0x24     *  CTR      *    |
     0x20     *  LR       *    |
     0x1C     *  CR       * locals & padding for 16 byte alignment
     0x18     *  SRR1     *    |
     0x14     *  SRR0     *    |
     0x10     *  padding  *    |
     0x0C     *  padding  *    |
     0x08     *  padding  * ___v__________
     0x04     *  LR save  * Reserved for calling function
     0x00     *  SP       * Backchain (same as gpr1 in GPRs)
              *************
*/

    .equ CONTEXT_SIZE, 156

; context switch macro
.macro portSAVE_CONTEXT   
    e_stw         r1,-0xA0 (r1)       # store backchain
    e_subi        r1,r1,0xA0          # allocate stack
    e_stmw        r14, 0x58 (r1)      # save r14-r31 by store word multiple
    e_stmvgprw    0x2C (r1)           # save r0, r3-r12 by e_stmvgprw 0x24 (r1)
    e_stmvsprw    0x1C (r1)           # save CR, LR, CTR, XER by e_stmvsprw 0x14 (r1)
    e_stmvsrrw    0x14 (r1)           # save SRR0, SRR1 by e_stmvsrrw 0x0C (r1)
.endm

; context switch macro
.macro portRESTORE_CONTEXT
    e_lmvsrrw     0x14 (r1)           # load SRR0, SRR1 by e_lmvsrrw 0x0C (r1)
    e_lmvsprw     0x1C (r1)           # load CR, LR, CTR, XER by e_lmvsprw 0x14 (r1)
    e_lmvgprw     0x2C (r1)           # load r0, r3-r12 by e_lmvgprw 0x24 (r1)
    e_lmw         r14, 0x58 (r1)      # load word multiple r14-r31
    e_add16i      r1, r1, 0xA0        # Reclaim stack space
.endm


 # Macro to put task stack pointer into the TCB  (r3 used as scratch register)
 .macro portPUSH_TASK
    e_lis     r3, pxCurrentTCB@ha
    e_lwz     r3, pxCurrentTCB@l(r3)
    se_stw    r1, 0x00 (r3)          # store stack pointer
 .endm

    # Macro to get the task stack pointer from the TCB (r3 used as scratch register)
 .macro portPOP_TASK
    e_lis     r3, pxCurrentTCB@ha
    e_lwz     r3, pxCurrentTCB@l(r3)
    se_lwz    r1, 0x00 (r3)    # load stack pointer
 .endm


    .align  16
vPortYield:
    portSAVE_CONTEXT
    portPUSH_TASK
    
    e_bl      vTaskSwitchContext
    
    portPOP_TASK
    portRESTORE_CONTEXT
    
    se_rfi



;    .align  16
;vPortTickISR:
;    portSAVE_CONTEXT
;
;    e_bl      vTaskIncrementTick
;
;   #if configUSE_PREEMPTION == 1
;       bl vTaskSwitchContext
;   #endif
;
;    e_bl      vPortTimerReset
;
;    portRESTORE_CONTEXT
;    se_blr




    .align  16  
vPortISRHandler:
    portSAVE_CONTEXT
    portPUSH_TASK
    
    e_lis     r3,  INTC_IACKR@h
    e_or2i    r3,  INTC_IACKR@l
    e_lwz     r3,  0(r3)           ; load the base adress of Vector Table
    e_lwz     r3,  0(r3)
    mtctr     r3                   ; load ISR handler in CTR

    wrteei    1

    se_bctrl                       ; branch to handler

    wrteei    0

    mbar      0                    ; complete all pending operations
    e_lis     r3,  INTC_EOIR@h
    e_or2i    r3,  INTC_EOIR@l
    e_stw     r3,  0(r3)           ; write 0 to INTC_EOIR

    portPOP_TASK
    portRESTORE_CONTEXT
    se_rfi




    .align  16
vPortStartFirstTask: 
    portPOP_TASK
    portRESTORE_CONTEXT

    ; Return into the first task 
    se_rfi


    ; end of assembler code
    .end
