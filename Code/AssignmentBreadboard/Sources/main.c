/* ###################################################################
 **     Filename    : main.c
 **     Project     : AssignmentBreadboard
 **     Processor   : MK20DN128VLH5
 **     Version     : Driver 01.01
 **     Compiler    : GNU C Compiler
 **     Date/Time   : 2020-10-20, 21:30, # CodeGen: 0
 **     Abstract    :
 **         Main module.
 **         This module contains user's application code.
 **     Settings    :
 **     Contents    :
 **         No public methods
 **
 ** ###################################################################*/
/*!
 ** @file main.c
 ** @version 01.01
 ** @brief
 **         Main module.
 **         This module contains user's application code.
 */
/*!
 **  @addtogroup main_module main module documentation
 **  @{
 */
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "Term.h"
#include "Inhr1.h"
#include "ASerialLdd1.h"
#include "BTUART.h"
#include "ASerialLdd2.h"
#include "I2C.h"
#include "IntI2cLdd1.h"
#include "Timer.h"
#include "RealTimeLdd1.h"
#include "TU1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* User includes (#include below this line is not maintained by Processor Expert) */
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
	/* Write your local variable definition here */

	/*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
	PE_low_level_init();
	/*** End of Processor Expert internal initialization.                    ***/

	/* Write your code here */
	void send_string(const char *str){
		size_t len, i;
		len = strlen(str);
		byte err;
		for (i = 0; i < len; i += 1){
			do {
				err = BTUART_SendChar(str[i]);
			} while (err != ERR_OK);
		}

	}

	// TURN ON IMU by passing 0 to reg 0x6B
	char msg[2] = {0x6B, 0};
	word sent;

	for(;;){
		// READ RAW DATA FROM ACCELEROMETER
		unsigned char data[6];
		if (ERR_OK != I2C_SendChar(0x3B)){
			// did not transmit address}
		}
		word recv;
		if (ERR_OK != I2C_RecvBlock(&data, 7, &recv)) {
			// did not read the data
		} else {
			// read successfully
		}

		// convert
		char Xstr[5];
		char Ystr[5];
		char Zstr[5];
		sprintf(Xstr, "%d", (signed char)data[0]);
		sprintf(Ystr, "%d", (signed char)data[2]);
		sprintf(Zstr, "%d", (signed char)data[4]);

		// send acc data
		send_string("\r\nX = ");
		send_string(Xstr);
		send_string(", Y = ");
		send_string(Ystr);
		send_string(", Z = ");
		send_string(Zstr);


		// wait for .1 second
		int time;
		Timer_Reset();
		do {
			Timer_GetTimeMS(&time);
		} while (time < 100);
		Timer_Reset();

	}



	/*** Don't write any code pass this line, or it will be deleted during code generation. ***/
	/*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
#ifdef PEX_RTOS_START
	PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
#endif
	/*** End of RTOS startup code.  ***/
	/*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
	for(;;){}
	/*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
 ** @}
 */
/*
 ** ###################################################################
 **
 **     This file was created by Processor Expert 10.5 [05.21]
 **     for the Freescale Kinetis series of microcontrollers.
 **
 ** ###################################################################
 */
