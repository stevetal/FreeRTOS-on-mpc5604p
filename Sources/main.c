

/* FreeRTOS includes */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "MPC5604P.h"



#define LED1_pin 52
#define LED2_pin 53
#define LED3_pin 54
#define LED4_pin 55

#define mainCHECK_DELAY                     ( ( portTickType ) 5000 / portTICK_RATE_MS )
#define portTASK_FUNCTION( vFunction, pvParameters ) void vFunction( void *pvParameters )


static void InitHardware()
{
	 CGM.CMU_0_CSR.R = 0x00000004;   
   	
	  ME.MER.R = 0x0000001D;          /* Enable DRUN, RUN0, SAFE, RESET modes */
	                                  /* Initialize PLL before turning it on: */	                                    
	  CGM.FMPLL[0].CR.R = 0x02400100;    /* 8 MHz xtal: Set PLL0 to 64 MHz */     
	  ME.RUN[0].R = 0x001F0074;       /* RUN0 cfg: 16MHzIRCON,OSC0ON,PLL0ON,syclk=PLL */  
	  ME.RUNPC[0].R = 0x00000010; 	  /* Peri. Cfg. 0 settings: only run in RUN0 mode */
	  ME.PCTL[16].R = 0x0000;         /* FlexCAN0:  select ME.RUNPC[0] */
	  ME.PCTL[4].R = 0x0000;          /* DSPI0:     select ME.RUNPC[0] */	  	  
	                                  /* Mode Transition to enter RUN0 mode: */
	  ME.MCTL.R = 0x40005AF0;         /* Enter RUN0 Mode & Key */
	  ME.MCTL.R = 0x4000A50F;         /* Enter RUN0 Mode & Inverted Key */  	  
	  while (ME.IS.B.I_MTC != 1) {}    /* Wait for mode transition to complete */    
	  ME.IS.R = 0x00000001;           /* Clear Transition flag */ 
	  
	   SWT.SR.R = 0x0000c520;     /* Write keys to clear soft lock bit */
	   SWT.SR.R = 0x0000d928; 
	   SWT.CR.R = 0x8000010A;     /* Clear watchdog enable (WEN) */  
	   
	   CGM.AC2SC.R = 0x04000000;  /* MPC56xxP Safety Port: Select PLL0 for aux clk 0  */
	   CGM.AC2DC.R = 0x80000000;  /* MPC56xxP Safety Port: Enable aux clk 0 div by 1 */
	   
	    SIU.PCR[LED1_pin].B.PA  = 0;  	        
	    /* output buffer enable */
	    SIU.PCR[LED1_pin].B.OBE = 1;  
	    
	    SIU.PCR[LED2_pin].B.PA  = 0;  	        
	    /* output buffer enable */
	    SIU.PCR[LED2_pin].B.OBE = 1; 
	    
	    SIU.PCR[LED3_pin].B.PA  = 0;  	        
	    /* output buffer enable */
	    SIU.PCR[LED3_pin].B.OBE = 1; 
	    
	    SIU.PCR[LED4_pin].B.PA  = 0;  	        
	    /* output buffer enable */
	    SIU.PCR[LED4_pin].B.OBE = 1; 
}

 portTASK_FUNCTION( LED1Task, pvParameters )  
{
    (void)pvParameters;

    for( ;; ) 
    {
    	 SIU.GPDO[LED1_pin].R ^= 1;
          vTaskDelay( 200 );
    }
}

 portTASK_FUNCTION( LED2Task, pvParameters )
{
    (void)pvParameters;

    for( ;; ) 
    {
    	 SIU.GPDO[LED2_pin].R ^= 1;
          vTaskDelay( 500 );
    }
}

 portTASK_FUNCTION( LED3Task, pvParameters )
{
    (void)pvParameters;

    for( ;; ) 
    {
    	 SIU.GPDO[LED3_pin].R ^= 1;
          vTaskDelay( 800 );
    }
}

 portTASK_FUNCTION( LED4Task, pvParameters )
{
    (void)pvParameters;

    for( ;; ) 
    {
    	 SIU.GPDO[LED4_pin].R ^= 1;
          vTaskDelay( 1000 );
    }
}

void main( void )
{	
    /* Hardware initialization code */
	InitHardware();
	
    /* Start the error checking task */
    xTaskCreate( LED1Task, ( const char * const )"LED1", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL );
    xTaskCreate( LED2Task, ( const char * const )"LED2", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL );
    xTaskCreate( LED3Task, ( const char * const )"LED3", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL );
    xTaskCreate( LED4Task, ( const char * const )"LED4", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL );


    /* Start the FreeRTOS scheduler */
    vTaskStartScheduler();

    /* Should never reach here */
    for ( ;; );
}
/*---------------------------------------------------------------------------*/






