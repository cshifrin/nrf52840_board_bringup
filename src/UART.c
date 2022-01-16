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
  printf("  \n-------------------------------------------------------------\r\n");
  nrf_delay_ms(5);
  printf("  |    COMMAND     |               DESCRIPTION                |\r\n");
  nrf_delay_ms(5);
  printf("  -------------------------------------------------------------\r\n");
  nrf_delay_ms(5);
  printf("  |  help          |  display this help message               |\r\n");
  nrf_delay_ms(5);
  printf("  |  scan          |  scan for TWI (I2C) addresses            |\r\n");
  nrf_delay_ms(5);
  printf("  |  led on        |  toggle onboard LEDs on                  |\r\n");
  nrf_delay_ms(5);
  printf("  |  led off       |  toggle onboard LEDs off                 |\r\n");
  nrf_delay_ms(5);
  printf("  |  reboot        |  reboot the system                       |\r\n");
  nrf_delay_ms(5);
  printf("  |  ble mac       |  check BLE MAC address                   |\r\n");
  nrf_delay_ms(5);
  printf("  |  eeprom read   |  eeprom read 12 (read from addr 12)      |\r\n");
  nrf_delay_ms(5);
  printf("  |  eeprom write  |  eeprom write 12 bob (write to addr 12)  |\r\n");
  nrf_delay_ms(5);
  printf("  |  eeprom delete |  eeprom delete 12 (delete entry 12)      |\r\n");
  nrf_delay_ms(5);
  printf("  |  eeprom dump   |  memory dump                             |\r\n");
  nrf_delay_ms(5);
  printf("  |  eeprom erase  |  erase all                               |\r\n");
  nrf_delay_ms(5);
  printf("  |  x  -  tbd     |                                          |\r\n");
  nrf_delay_ms(5);
  printf("  |  x  -  tbd     |                                          |\r\n");
  nrf_delay_ms(5);
  printf("  |  x  -  tbd     |                                          |\r\n");
  nrf_delay_ms(5);
  printf("  -------------------------------------------------------------\r\n");
}

/**
 * Concatenate two integers to be used as an address.
 */
int concatenate(int x, int y)
{
    unsigned pow = 10;
    while(y >= pow)
        pow *= 10;
    return x * pow + y;
}




