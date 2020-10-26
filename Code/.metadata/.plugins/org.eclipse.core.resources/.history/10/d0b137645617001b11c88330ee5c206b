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
#include <math.h>

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
	/* Write your local variable definition here */
	int time;

	float PI = 3.14159265359;

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
		// READ RAW DATA FROM ACCELEROMETER TODO: when changing to PCB - register addresses will change, slave addresses will change (one for gyro, one for acc/mag)
		unsigned char acc_data[6];
		if (ERR_OK != I2C_SendChar(0x3B)){
			// did not transmit address}
		}
		word recv;
		if (ERR_OK != I2C_RecvBlock(&acc_data, 6, &recv)) {
			// did not read the data
		} else {
			// read successfully
		}

		// READ RAW DATA FROM GYROSCOPE - TODO: put these in a function
		unsigned char gyro_data[6];
		if (ERR_OK != I2C_SendChar(0x43)){
			// did not transmit address}
		}
		word recv2;
		if (ERR_OK != I2C_RecvBlock(&gyro_data, 6, &recv2)) {
			// did not read the data
		} else {
			// read successfully
		}

		// convert data to signed number TODO: use all bits
		float accX = acc_data[0] * 1.0;
		float accY = acc_data[2] * 1.0;
		float accZ = acc_data[4] * 1.0;
		signed char gyroX = (signed char)gyro_data[0];
		signed char gyroY = (signed char)gyro_data[2];
		signed char gyroZ = (signed char)gyro_data[4];

		// convert accelerometer data to pitch and roll TODO: get working correctly; currently only works properly tilting in one direction either way for pitch/roll
		int accPitch = atan2(accY, accZ) * (180/PI); // deg
		int accRoll = atan2(accX, accZ) * (180/PI);

		// TODO: convert acc data to pitch and roll using eg. arctan(accX/accZ)
		// TODO: convert gyro data to yaw/pitch/roll
		// TODO: combine the data

		// convert accelerometer data to string TODO: put in function

		char accXstr[5];
		char accYstr[5];
		char accZstr[5];
		sprintf(accXstr, "%d", accX);
		sprintf(accYstr, "%d", accY);
		sprintf(accZstr, "%d", accZ);

		// convert gyroscope data to string
		char gyroXstr[5];
		char gyroYstr[5];
		char gyroZstr[5];
		sprintf(gyroXstr, "%d", gyroX);
		sprintf(gyroYstr, "%d", gyroY);
		sprintf(gyroZstr, "%d", gyroZ);

		// convert other data to string
		char pitchStr[5];
		char rollStr[5];
		sprintf(pitchStr, "%d", accPitch);
		sprintf(rollStr, "%d", accRoll);

		// send data TODO: convert creating & sending string into a separate function
		//		send_string("\r\n");
		//		send_string(accXstr);
		//		send_string("/");
		//		send_string(accYstr);
		//		send_string("/");
		//		send_string(accZstr);
		//		send_string("/");
		//		send_string(pitchStr);
		//		send_string("/");
		//		send_string(rollStr);

		send_string("\r\n");
		send_string(gyroXstr);
		send_string("/");
		send_string(gyroYstr);
		send_string("/");
		send_string(gyroZstr);





		// wait for .1 second TODO: get delay working properly - just passes straight through

		Timer_Reset();

		do {
			Timer_GetTimeMS(&time);
		} while (time < 100);
		//Timer_Reset();
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
