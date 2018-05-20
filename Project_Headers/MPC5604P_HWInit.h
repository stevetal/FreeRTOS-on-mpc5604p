/**
 * FILE : MPC560xP_HWInit.h
 * 
 * COPYRIGHT (c) 2007-2012 Freescale Semiconductor, Inc. All rights reserved.
 *
 * DESCRIPTION: This file contains defines and declaration of utility functions needed
 * to initialize several modules.
 *  
 * VERSION: 1.2
 */

#ifndef _MPC560xP_HWINIT_H_
#define _MPC560xP_HWINIT_H_

/*----------------------------------------------------------------------------*/
/* Includes                                                                   */
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/* This macro allows to use C defined address with the inline assembler */
#define MAKE_HLI_COMPATIBLE(hli_name, c_expr) enum { hli_name=/*lint -e30*/((int)(c_expr)) };

/*----------------------------------------------------------*/
/* MPC560xP derivative specific hardware initialization     */
/*----------------------------------------------------------*/ 
__asm void INIT_Derivative(void); 

/*----------------------------------------------------------*/
/* MPC560xP boards specific hardware initializations        */
/*----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/* Used Board selection                                      */
/*-----------------------------------------------------------*/

/* Supported Boards */
#define NO_EXTERNAL_MEMORY    0

/* Used board */
#define INIT_USED_BOARD NO_EXTERNAL_MEMORY

#ifndef INIT_USED_BOARD
#pragma error INIT_USED_BOARD should be defined !
#endif

/*----------------------------------------------------------*/
/* Function declarations                                    */
/*----------------------------------------------------------*/

/* call this function to setup the external bus, 
   chip selects and MMU entries for the selected board
*/
__asm void INIT_ExternalBusAndMemory(void);

#ifdef __cplusplus
}
#endif

#endif
