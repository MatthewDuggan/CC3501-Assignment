/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : Term.c
**     Project     : AssignmentBreadboard
**     Processor   : MK20DN128VLH5
**     Component   : Term
**     Version     : Component 02.061, Driver 03.22, CPU db: 3.00.000
**     Repository  : Kinetis
**     Compiler    : GNU C Compiler
**     Date/Time   : 2020-10-27, 19:17, # CodeGen: 14
**     Abstract    :
**This components generates low-level console IO routines for selected UART.
**     Settings    :
**          Component name                                 : Term
**          Asynchro serial communication                  : AsynchroForTerminal
**          CPU clock/speed selection                      : 
**            High speed mode                              : This component enabled
**            Low speed mode                               : This component disabled
**            Slow speed mode                              : This component disabled
**     Contents    :
**         CRLF         - void Term_CRLF(void);
**         SendStr      - void Term_SendStr(uint8_t *str);
**         SendNum      - void Term_SendNum(int32_t number);
**         SendFloatNum - byte Term_SendFloatNum(TPE_Float number);
**         SendChar     - void Term_SendChar(char_t Val);
**         Cls          - void Term_Cls(void);
**         MoveTo       - void Term_MoveTo(uint8_t x, uint8_t y);
**         ReadChar     - void Term_ReadChar(char_t *c);
**         KeyPressed   - bool Term_KeyPressed(void);
**
**     Copyright : 1997 - 2015 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file Term.c
** @version 03.22
** @brief
**This components generates low-level console IO routines for selected UART.
*/         
/*!
**  @addtogroup Term_module Term module documentation
**  @{
*/         


/* MODULE Term. */
#include "Term.h"
#include "Inhr1.h"


#define COLUMNS  80U                   /* Number of columns */
#define ROWS     24U                   /* Number of rows */

/* Internal method prototypes */
static void SendESCPrefix(void);
static void LongToStr(char_t* s, int32_t n);
static byte FloatToStr(char_t* s, TPE_Float n);

/*
** ===================================================================
**     Method      :  Term_SendChar (component Term)
**     Description :
**         Send char to terminal.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Val             - Char to send
**     Returns     : Nothing
** ===================================================================
*/
void Term_SendChar(char_t Val)
{
  while (Inhr1_SendChar((uint8_t)Val) == ERR_TXFULL){} /* Send char */
}

/*
** ===================================================================
**     Method      :  Term_SendESCPrefix (component Term)
**
**     Description :
**         The method sends first (common) part of an excape sequence.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
static void SendESCPrefix(void)
{
  while (Inhr1_SendChar(0x1BU) == ERR_TXFULL){} /* Send the part of the escape sequence ('ESC') */
  while (Inhr1_SendChar(0x5BU) == ERR_TXFULL){} /* Send the part of the escape sequence ('[') */
}

/*
** ===================================================================
**     Method      :  Term_ReadChar (component Term)
**     Description :
**         Read char from terminal.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * c               - Pointer to a char variable
**     Returns     : Nothing
** ===================================================================
*/
void Term_ReadChar(char_t *c)
{
  while(Inhr1_RecvChar((uint8_t *)c) != ERR_OK){} /* Receive char */
}

/*
** ===================================================================
**     Method      :  Term_KeyPressed (component Term)
**     Description :
**         Test if char was received from the terminal.
**     Parameters  : None
**     Returns     :
**         ---             - Return <true> if user pressed some key
** ===================================================================
*/
bool Term_KeyPressed(void)
{
  return (bool)((Inhr1_GetCharsInRxBuf() == 0U) ? FALSE : TRUE); /* Result number of chars in receive buffer */
}

/*
** ===================================================================
**     Method      :  Term_CRLF (component Term)
**     Description :
**         Send CRLF to terminal.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void Term_CRLF(void)
{
  while (Inhr1_SendChar(0x0DU) == ERR_TXFULL){} /* Send the part of the escape sequence ('CR') */
  while (Inhr1_SendChar(0x0AU) == ERR_TXFULL){} /* Send the part of the escape sequence ('LF') */
}

/*
** ===================================================================
**     Method      :  Term_SendStr (component Term)
**     Description :
**         Send string to terminal.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * str             - Pointer to a string variable
**     Returns     : Nothing
** ===================================================================
*/
void Term_SendStr(void *str)
{
  uint8_t *ptr =  ((uint8_t *) str);
  while (*ptr != 0x00U) {
    while (Inhr1_SendChar(*ptr) == ERR_TXFULL){} /* Send char */
    ptr++;                             /* Increment the pointer */
  }
}

/*
** ===================================================================
**     Method      :  Term_LongToStr (component Term)
**
**     Description :
**         The method converts long int number to string.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
static void LongToStr(char_t* s, int32_t n)
{
  uint8_t i=0U, j;
  char_t tmp;
  uint8_t Tmp;
  bool sign = (bool)((n < 0) ? TRUE : FALSE);
  uint32_t u_n;

  u_n = (uint32_t)n;
  if (sign){
    u_n = (u_n ^ 0xFFFFFFFFUL) + 1U;
  }
  if (u_n == 0U){
    s[i++] = '0';
  }
  while (u_n > 0U) {
    Tmp = (uint8_t)((u_n % 10U) + 0x30U);
    s[i++] = (char_t)(Tmp);
    u_n /= 10U;
  }
  if (sign){
    s[i++] = '-';
  }
  for(j=0U; j<(i/2U); j++) {
    tmp = s[j];
    s[j] = s[(i-j)-1U];
    s[(i-j)-1U] = tmp;
  }
  s[i] = '\0';
}

/*
** ===================================================================
**     Method      :  Term_SendNum (component Term)
**     Description :
**         Send number to terminal.
**     Parameters  :
**         NAME            - DESCRIPTION
**         number          - Long number
**     Returns     : Nothing
** ===================================================================
*/
void Term_SendNum(int32_t number)
{
  char_t str[15];                      /* Temporary variable */
  uint8_t i=0U;                        /* Temporary variable */

  LongToStr(str, number);              /* Conversion number to the string */
  while (str[i] != '\0') {
    while (Inhr1_SendChar((Inhr1_TComData)str[i]) == ERR_TXFULL){} /* Send char */
    i++;                               /* Increase the variable */
  }
}

/*
** ===================================================================
**     Method      :  Term_FloatToStr (component Term)
**
**     Description :
**         The method converts float number to string.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
static byte FloatToStr(char_t* s, TPE_Float n)
{
  char_t tmp;
  uint8_t i=4U, j;
  bool sign = (bool)((n < 0.0F) ? TRUE : FALSE);
  uint32_t Integral;
  uint16_t fract;
  TPE_Float tmp_f;
  uint8_t Tmp;

  if (sign){
    n *= -1.0F;
  }
  if (n > 4294967295.0F) {
    return ERR_RANGE;
  }
  Integral = (uint32_t)n;
  tmp_f = (n-(TPE_Float)Integral)*10000.0F;
  fract = (uint16_t)tmp_f;
  for(j=0U; j<4U; j++) {
    Tmp = (uint8_t)((fract % 10U) + 0x30U);
    s[j] = (char_t)(Tmp);
    fract /= 10U;
  }
  s[i++] = '.';
  if (i > 14U) {
    return ERR_RANGE;
  }
  if (Integral == 0U){
    s[i++] = '0';
    if (i > 14U) {
      return ERR_RANGE;
    }
  }
  while (Integral > 0U) {
    Tmp = (uint8_t)((Integral % 10U) + 0x30U);
    s[i++] = (char_t)(Tmp);
    if (i > 14U) {
      return ERR_RANGE;
    }
    Integral /= 10U;
  }
  if (sign){
    s[i++] = '-';
    if (i > 14U) {
      return ERR_RANGE;
    }
  }
  for(j=0U; j<(i/2U); j++) {
    tmp = s[j];
    s[j] = s[(i-j)-1U];
    s[(i-j)-1U] = tmp;
  }
  s[i] = '\0';
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  Term_SendFloatNum (component Term)
**     Description :
**         Send a float number to the terminal. Due to the
**         transformations the maximum float number is limited
**         according to the following conditions: 
**         - positive number: 9 digits for integer part with 4 digits
**         for fractional part. 
**         - negative numbers: 8 digits for integer part with 4 digits
**         for fractional part.
**     Parameters  :
**         NAME            - DESCRIPTION
**         number          - Float variable
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_RANGE - Float number exceeds maximal
**                           number limitation.
** ===================================================================
*/
byte Term_SendFloatNum(TPE_Float number)
{
  char_t str[15];
  uint8_t i=0U;
  byte err;

  err = FloatToStr(str, number);       /* Conversion number to the string */
  if (err == ERR_RANGE) {
    return ERR_RANGE;
  }
  while (str[i] != '\0') {
    while (Inhr1_SendChar((Inhr1_TComData)str[i]) == ERR_TXFULL){} /* Send char */
    i++;                               /* Increase the variable */
  }
  return(err);
}

/*
** ===================================================================
**     Method      :  Term_Cls (component Term)
**     Description :
**         Clear the terminal window.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void Term_Cls(void)
{
  SendESCPrefix();
  while (Inhr1_SendChar(0x32U) == ERR_TXFULL){} /* Send the part of the escape sequence ('2') */
  while (Inhr1_SendChar(0x4AU) == ERR_TXFULL){} /* Send the part of the escape sequence ('J') */
}

/*
** ===================================================================
**     Method      :  Term_MoveTo (component Term)
**     Description :
**         Move cursor to position x, y. Range of coordinates can be
**         from 1 to the size, which depends on the used terminal.
**         Position [1,1] represents the upper left corner.
**     Parameters  :
**         NAME            - DESCRIPTION
**         x               - Column number
**         y               - Row number
**     Returns     : Nothing
** ===================================================================
*/
void Term_MoveTo(uint8_t x,uint8_t y)
{
  SendESCPrefix();                     /* Send the escape prefix */
  Term_SendNum((int32_t) y);           /* Send number of line */
  while (Inhr1_SendChar(0x3BU) == ERR_TXFULL){} /* Send the part of the escape sequence (';') */
  Term_SendNum((int32_t) x);           /* Send number of column */
  while (Inhr1_SendChar(0x48U) == ERR_TXFULL){} /* Send the part of the escape sequence ('H') */
}


/* END Term. */

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

