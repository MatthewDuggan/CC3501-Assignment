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
#include "CS1.h"
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
	float dt; // change in time

	int previousTime = time;
	float gyroPitch = 0;
	float gyroRoll = 0; // assume starting flat
	float gyroYaw = 0; // assume starting position of nose is 0
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

	char msg[2] = {0x6B, 0}; // use MPU-6050's internal oscillator
	word sent;

	for(;;){
		// READ RAW DATA FROM ACCELEROMETER
		unsigned char acc_data[6];
		if (ERR_OK != I2C_SendChar(0x3B)){
			send_string("\r\nThere was a connection problem. Check wiring/PCB ");
			Term_SendStr("\r\nThere was a connection problem. Check wiring/PCB ");
			while(1);
		}
		word recv;
		if (ERR_OK != I2C_RecvBlock(&acc_data, 6, &recv)) {
			// did not read the data
		} else {
			// read successfully
		}

		// READ RAW DATA FROM GYROSCOPE
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

		// convert data to signed number
		// acc data values are used in trig ratios so do not need to be converted to general use values
		float accX = (signed short)(acc_data[0]<<8 | acc_data[1]) * 1.0;
		float accY = (signed short)(acc_data[2]<<8| acc_data[3]) * 1.0;
		float accZ = (signed short)(acc_data[4]<<8| acc_data[5]) * 1.0;
		// dividing by 131 converts raw gyro data to deg/s as per section 4.2 of MPU6050 datasheet
		float gyroX = 1.3 + (signed short)(gyro_data[0]<<8 | gyro_data[1])/131.0; // ~-1.3deg/s error on breakout board
		float gyroY = 0.2 + (signed short)(gyro_data[2]<<8 | gyro_data[3])/131.0; // ~-0.2deg/s error on breakout board
		float gyroZ = 0.9 + (signed short)(gyro_data[4]<<8 | gyro_data[5])/131.0; // ~-0.9deg/s error on breakout board - still some drift as no acc/mag component for breakout board


		// convert accelerometer data to pitch and roll
		float accPitch = atan2(accY, accZ) * (180/PI) - 1.5 ; // error of +1.5deg when flat
		float accRoll = (-1) * atan2(accX, accZ) * (180/PI) - 3; //error of +3deg when flat

		// convert gyro data to pitch and roll
		// keep track of time and get dt
		Timer_GetTimeMS(&time);
		dt = (time - previousTime)/1000.0;
		Timer_Reset();
		Timer_GetTimeMS(&time);
		previousTime = time;

		// calculate change in gyro angle
		float gyroPitchChange = dt*gyroX;
		float gyroRollChange = dt*gyroY;
		float gyroYawChange = dt*gyroZ;

		// convert to gyro pitch and roll
		gyroPitch = gyroPitch + gyroPitchChange;
		gyroRoll = gyroRoll + gyroRollChange;
		gyroYaw = gyroYaw - gyroYawChange;

		// use mostly gyro pitch and roll but add some accelerometer to compensate for gyro drift
		float pitch = 0.7*gyroPitch + 0.3*accPitch;
		float roll = 0.7*gyroRoll + 0.3*accRoll;
		float yaw = gyroYaw;

		if (abs(accPitch) < 5){
			pitch = accPitch;
			gyroPitch = accPitch; // eliminate gyro drift when accelerometer pitch is very small
		}
		if (abs(accRoll) < 5){
			roll = accRoll;
			gyroRoll = accRoll; // eliminate gyro drift when accelerometer roll is very small
		}

		// TODO: Get magnetometer data and convert to yaw (PCB)

		// convert Euler angle data to string
		char pitchStr[5];
		char rollStr[5];
		char yawStr[5];
		sprintf(pitchStr, "%d", (int)pitch);
		sprintf(rollStr, "%d", (int)roll);
		sprintf(yawStr, "%d", (int)yaw);

		// send data via terminal for Matlab plotting
		send_string("\r\n");
		send_string(pitchStr);
		send_string("/");
		send_string(rollStr);
		send_string("/");
		send_string(yawStr);

		// send data via bluetooth
		Term_SendStr("\r\n");
		Term_SendNum(pitch);
		Term_SendStr("/");
		Term_SendNum(roll);
		Term_SendStr("/");
		Term_SendNum(yaw);
		Term_SendStr("/"); // need trailing delimiter for Matlab live plotting script

		Timer_GetTimeMS(&time);
		int currentTime = time;
		do {
			Timer_GetTimeMS(&time);
		} while ((time - currentTime) < 100);


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
