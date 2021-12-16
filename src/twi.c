#include "twi.h"

/* Initialize the TWI. */
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

/* Scan for connected TWI devices. */
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
 * Read a specific memory location's data in EEPROM.
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
 * Write to a specific memory location in EEPROM.
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

void do_print_data(void)
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

        print_addr(addr);
        nrf_delay_ms(5);
        for(n=0; n<16; ++n)
        {
            print_hex(buff[n]);
        }

        //safe_putc(' ');
        //safe_putc(' ');

        //for(n=0; n<16; ++n)
        //{
        //    safe_putc((char)buff[n]);
        //    printf("\r\n");
        //}
        printf("\r\n");
        UNUSED_VARIABLE(putc('\n', stdout));
    }
    UNUSED_VARIABLE(fflush(stdout));
}

void print_hex(uint8_t data)
{
    printf("%.2x ", (unsigned int)data);
}

void safe_putc(char c)
{
    if(!isprint((int)c))
    {
        c = '.';
    }
    UNUSED_VARIABLE(putc(c, stdout));
}


void print_addr(size_t addr)
{
    printf("%.2x: ", (unsigned int)addr);
}



























































