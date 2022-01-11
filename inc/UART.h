#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "app_uart.h"
#include "app_error.h"
#include "nrf_delay.h"
#include "nrf.h"
#include "bsp.h"
#include "boards.h"
#include "nrf_uart.h"

#define txBuffer     256                         
#define rxBuffer     256

/* Declaring functions. */
void uart_error_handler(app_uart_evt_t * p_event);  //Error handler for UART initialization.
void init_uart_nRF_PC();                            //Initialize the UART between nRF52840 and PC.
void display_help();                                //Print a list of serial commands for the user.






