#include "UART.h"
#include "twi.h"


/* Error handler for UART initialization. */
void uart_error_handler(app_uart_evt_t * p_event)
{
}

/* Initialize the UART between nRF52840 and PC. */
void init_uart_nRF_PC()
{
    uint8_t err_code;

    const app_uart_comm_params_t comm_params =
      {
          RX_PIN_NUMBER,
          TX_PIN_NUMBER,
          RTS_PIN_NUMBER,
          CTS_PIN_NUMBER,
          HWFC,
          false,
          NRF_UART_BAUDRATE_115200
      };

    APP_UART_FIFO_INIT(&comm_params,
                         rxBuffer,
                         txBuffer,
                         uart_error_handler,
                         APP_IRQ_PRIORITY_LOWEST,
                         err_code);

    APP_ERROR_CHECK(err_code);
}

/* Print a list of serial commands for the user. */
void display_help(void)
{
  printf("  \n--------------------------------------\r\n");
  printf("  |                HELP                |\r\n");
  printf("  --------------------------------------\r\n");
  printf("  | h  -  display this help message    |\r\n");
  printf("  | s  -  scan for TWI (I2C) addresses |\r\n");
  printf("  | c  -  toggle onboard LEDs on       |\r\n");
  nrf_delay_ms(20); //delay so UART can keep up
  printf("  | v  -  toggle onboard LEDs off      |\r\n");
  printf("  | r  -  reboot the system            |\r\n");
  printf("  | b  -  check BLE MAC address        |\r\n");
  printf("  | o  -  read        (EEPROM)         |\r\n");
  printf("  | p  -  write       (EEPROM)         |\r\n");
  printf("  | d  -  memory dump (EEPROM)         |\r\n");
  nrf_delay_ms(20); 
  printf("  | e  -  erase all   (EEPROM)         |\r\n");
  printf("  | x  -  tbd                          |\r\n");
  printf("  | x  -  tbd                          |\r\n");
  printf("  | x  -  tbd                          |\r\n");
  printf("  | x  -  tbd                          |\r\n");
  printf("  --------------------------------------\r\n");
}



