/**
 * Copyright (c) 2014 - 2021, Nordic Semiconductor ASA
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
/** @file
 * @defgroup uart_example_main main.c
 * @{
 * @ingroup uart_example
 * @brief UART Example Application main file.
 *
 * This file contains the source code for a sample application using UART.
 *
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "app_uart.h"
#include "app_error.h"
#include "nrf_delay.h"
#include "nrf.h"
#include "bsp.h"
#include "UART.h"
#include "twi.h"


/**
 * @brief Function for main application entry.
 */
int main(void)
{
    //Initialize peripherals.
    bsp_board_init(BSP_INIT_LEDS);
    init_uart_nRF_PC();
    init_twi();
    
printf("\n\
***********************************************************************\r\n\
************************* APPLICATION STARTED *************************\r\n\
***********************************************************************\r\n");
    nrf_delay_ms(20);
    display_help();

    while(true)
    {
      uint8_t cr = '\0';
      uint8_t cmd[16] = {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};
      uint8_t i = 0;

      while(app_uart_get(&cr) ==  NRF_SUCCESS) //scan for user input
      {
        cmd[i] = cr;
        i++;
        nrf_delay_ms(1);
      }
      //display help message
      if(cmd[0] == 'h' && cmd[1] == 'e' && cmd[2] == 'l' && cmd[3] == 'p')                                                                
      {
        display_help();
        continue;
      }

      //scan for TWI(I2C) devices
      else if(cmd[0] == 's' && cmd[1] == 'c' && cmd[2] == 'a' && cmd[3] == 'n')                                                          
      {
        twi_scan();
        continue;
      }

      //toggle LEDs on
      else if(cmd[0] == 'l' && cmd[1] == 'e' && cmd[2] == 'd' && cmd[3] == ' ' && cmd[4] == 'o' && cmd[5] == 'n')                        
      {
        bsp_board_leds_on();
        printf("\nToggled LEDs on.\r\n");
        continue;
      }

      //toggle LEDs off
      else if(cmd[0] == 'l' && cmd[1] == 'e' && cmd[2] == 'd' && cmd[3] == ' ' && cmd[4] == 'o' && cmd[5] == 'f' && cmd[6] == 'f')       
      {
        bsp_board_leds_off();
        printf("\nToggled LEDs off.\r\n");
        continue;
      }

      //reset the system
      else if(cmd[0] == 'r' && cmd[1] == 'e' && cmd[2] == 'b' && cmd[3] == 'o' && cmd[4] == 'o' && cmd[5] == 't')                        
      {
        printf("\nSystem will now reboot.\r\n");
        nrf_delay_ms(100);
        NVIC_SystemReset();
      }

      //check BLE MAC address
      else if(cmd[0] == 'b' && cmd[1] == 'l' && cmd[2] == 'e' && cmd[3] == ' ' && cmd[4] == 'm' && cmd[5] == 'a' && cmd[6] == 'c')       
      {
        continue;
      }

      //EEPROM read
      else if(cmd[0] == 'e' && cmd[1] == 'e' && cmd[2] == 'p' && cmd[3] == 'r' && cmd[4] == 'o' && cmd[5] == 'm' && cmd[6] == ' ' && cmd[7] == 'r' && cmd[8] == 'e' && cmd[9] == 'a' && cmd[10] == 'd')       
      {
        eeprom_cmd_read();
        continue;
      }

      //EEPROM write
      else if(cmd[0] == 'e' && cmd[1] == 'e' && cmd[2] == 'p' && cmd[3] == 'r' && cmd[4] == 'o' && cmd[5] == 'm' && cmd[6] == ' ' && cmd[7] == 'w' && cmd[8] == 'r' && cmd[9] == 'i' && cmd[10] == 't' && cmd[11] == 'e')       
      {
        eeprom_cmd_write();
        continue;
      }

      //EEPROM erase all
      else if(cmd[0] == 'e' && cmd[1] == 'e' && cmd[2] == 'p' && cmd[3] == 'r' && cmd[4] == 'o' && cmd[5] == 'm' && cmd[6] == ' ' && cmd[7] == 'e' && cmd[8] == 'r' && cmd[9] == 'a' && cmd[10] == 's' && cmd[11] == 'e')       
      {
        eeprom_eraseall();
        continue;
      }

      //EEPROM memory dump
      if(cmd[0] == 'e' && cmd[1] == 'e' && cmd[2] == 'p' && cmd[3] == 'r' && cmd[4] == 'o' && cmd[5] == 'm' && cmd[6] == ' ' && cmd[7] == 'd' && cmd[8] == 'u' && cmd[9] == 'm' && cmd[10] == 'p')       
      {
        eeprom_dump();
        continue;
      }
    } // while(true)
}









































/** @} */
