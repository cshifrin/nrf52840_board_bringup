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

/* Scan for input through serial console. */
void uart_checker()
{
  uint8_t cr;

  if(app_uart_get(&cr) ==  NRF_SUCCESS)
  {
    if(cr == 'h')       //display help message
    {
      display_help();
    }
    if(cr == 's')       //scan for TWI(I2C) devices
    {
      twi_scan();
    }
    if(cr == 'c')       //toggle LEDs on
    {
      bsp_board_leds_on();
      printf("\nToggled LEDs on.\r\n");
    }
    if(cr == 'v')       //toggle LEDs off
    {
      bsp_board_leds_off();
      printf("\nToggled LEDs off.\r\n");
    }
    if(cr == 'r')       //reset the system
    {
      printf("\nSystem will now reboot.\r\n");
      nrf_delay_ms(100);
      NVIC_SystemReset();
    }
    if(cr == 'b')       //check BLE MAC address
    {
      ;
    }
    if(cr == 'o')       //EEPROM read
    {
      eeprom_cmd_read();
    }
    if(cr == 'p')       //EEPROM write
    {
      eeprom_cmd_write();
    }
    if(cr == 'e')       //EEPROM erase all
    {
      eeprom_cmd_clear();;
    }
    if(cr == 'd')       //EEPROM memory dump
    {
      eeprom_mem_dump();
    }
  }
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
  printf("  | d  -  erase all   (EEPROM)         |\r\n");
  nrf_delay_ms(20); 
  printf("  | x  -  memory dump (EEPROM)         |\r\n");
  printf("  | x  -  tbd                          |\r\n");
  printf("  | x  -  tbd                          |\r\n");
  printf("  | x  -  tbd                          |\r\n");
  printf("  | x  -  tbd                          |\r\n");
  printf("  --------------------------------------\r\n");
}




