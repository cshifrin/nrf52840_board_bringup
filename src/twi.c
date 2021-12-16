#include "twi.h"

/**
 * Initialize the TWI.
 */
void init_twi(void)
{
    ret_code_t err_code;

    const nrf_drv_twi_config_t twi_config = 
    {
      .scl                = SCL_PIN_NUMBER,
      .sda                = SDA_PIN_NUMBER,
      .frequency          = NRF_DRV_TWI_FREQ_100K,
      .interrupt_priority = APP_IRQ_PRIORITY_LOWEST,
      .clear_bus_init     = false
    };

    err_code = nrf_drv_twi_init(&m_twi, &twi_config, NULL, NULL);
    APP_ERROR_CHECK(err_code);
    nrf_drv_twi_enable(&m_twi);
}

/** 
 * Scan for connected TWI devices.
 */
void twi_scan(void)
{
    ret_code_t err_code;
    uint8_t address;
    uint8_t sample_data;
    bool device_found = false;

    printf("\nScanning for TWI devices...\r\n");

    for (address = 0; address < TWI_ADDRESSES; address++)
    {
        err_code = nrf_drv_twi_rx(&m_twi, address, &sample_data, sizeof(sample_data));
        if (err_code == NRF_SUCCESS)
        {
            device_found = true;
            printf("TWI device found at address 0x%x.\r\n", address);
        }
    }

    if (!device_found)
    {
        printf("No TWI device found.\r\n");
    }
}

/** 
 * Read specific location in EEPROM.
 */
ret_code_t eeprom_read(size_t addr, uint8_t * pdata, size_t size)
{
    ret_code_t ret;

    do
    {
       uint8_t addr8 = (uint8_t)addr;
       ret = nrf_drv_twi_tx(&m_twi, EEPROM_ADDR, &addr8, 1, true);
       if(NRF_SUCCESS != ret)
       {
           break;
       }
       ret = nrf_drv_twi_rx(&m_twi, EEPROM_ADDR, pdata, size);
    }while(0);
    return ret;
}

/**
 * Write to specific location in EEPROM.
 */
ret_code_t eeprom_write(size_t addr, uint8_t const * pdata, size_t size)
{
    ret_code_t ret;

    do
    {
        uint8_t addr8 = (uint8_t)addr;
        ret = nrf_drv_twi_tx(&m_twi, EEPROM_ADDR, &addr8, 1, true);
        if(NRF_SUCCESS != ret)
        {
            break;
        }
        ret = nrf_drv_twi_tx(&m_twi, EEPROM_ADDR, pdata, size, false);
    }while(0);

    return ret;
}

/**
 * Perform a memory dump of EEPROM to console.
 */
void eeprom_mem_dump(void)
{
    size_t addr;
    uint8_t buff[16];

    printf("\n\t\tMEMORY DUMP (EEPROM)\r\n");
    for(addr=0; addr<320; addr+=16)
    {
        unsigned int n;
        ret_code_t err_code;
        err_code = eeprom_read(addr, buff, 16);
        APP_ERROR_CHECK(err_code);

        eeprom_print_addr(addr);
        nrf_delay_ms(5);
        for(n=0; n<16; ++n)
        {
            eeprom_print_hex(buff[n]);
        }

        printf("\r\n");
        UNUSED_VARIABLE(putc('\n', stdout));
    }
    UNUSED_VARIABLE(fflush(stdout));
}

/**
 * Print the data value in HEX.
 */
void eeprom_print_hex(uint8_t data)
{
    printf("%.2x ", (unsigned int)data);
}

/**
 * Print the address in HEX.
 */
void eeprom_print_addr(size_t addr)
{
    printf("%.2X: ", (unsigned int)addr);
}





























































