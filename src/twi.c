#include <string.h>
#include <ctype.h>
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
            nrf_delay_ms(5);
            printf("about to break \r\n");
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



//-------------------------------------------------------------------------------------------------------------------------------------

ret_code_t eeprom_write2(uint16_t addr, uint8_t const * pdata, size_t size)
{
    ret_code_t ret;
  
    if (size > EEPROM_WRITE_MAX_BYTES)
    {
        printf("ERROR: Writing too many bytes.\r\n");
        return NRF_ERROR_NOT_FOUND;
    }

    if ((addr / (EEPROM_WRITE_MAX_BYTES)) != ((addr + size - 1) / (EEPROM_WRITE_MAX_BYTES)))
    {
        printf("ERROR: Written data must be on same page.\r\n");
        return NRF_ERROR_NOT_FOUND;
    }
    do
    {
        uint8_t buffer[EEPROM_ADDR_LEN_BYTES + EEPROM_WRITE_MAX_BYTES]; /* Addr + data */

        memcpy(buffer, &addr, EEPROM_ADDR_LEN_BYTES);
        memcpy(buffer + EEPROM_ADDR_LEN_BYTES, pdata, size);
        ret = nrf_drv_twi_tx(&m_twi, EEPROM_ADDR, buffer, size + EEPROM_ADDR_LEN_BYTES, false);
    }while (0);
    return ret;
}


ret_code_t eeprom_read2(uint16_t addr, uint8_t * pdata, size_t size)
{
    ret_code_t ret;
    if (size > EEPROM_SIZE)
    {
        printf("ERROR: EEPROM not big enough for attempted read.\r\n");
        return NRF_ERROR_NOT_FOUND;
    }
    do
    {
       uint16_t addr16 = addr;
       ret = nrf_drv_twi_tx(&m_twi, EEPROM_ADDR, (uint8_t *)&addr16, EEPROM_ADDR_LEN_BYTES, true);
       if (NRF_SUCCESS != ret)
       {
           break;
       }
       ret = nrf_drv_twi_rx(&m_twi, EEPROM_ADDR, pdata, size);
    }while (0);
    return ret;
}


size_t safe_strlen(char const * str, size_t nmax)
{
    size_t n=0;
    while ('\0' != *str++)
    {
        ++n;
        if (0 == --nmax)
            break;
    }
    return n;
}


void eeprom_cmd_eraseall(void)
{
    ret_code_t err_code;
    uint8_t clear_val = 0xff;
    size_t addr;

    for (addr = 0; addr < EEPROM_SIZE; ++addr)
    {
        err_code = eeprom_write2(addr, &clear_val, 1);
        nrf_delay_ms(5);
        if (NRF_SUCCESS != err_code)
        {
            printf("TWI Communication Error\r\n");
            return;
        }
    }
    printf("EEPROM successfully erased.\r\n");
}


void eeprom_cmd_dump(void)
{
    printf("\n\t\t    MEMORY DUMP (EEPROM)\r\n");
    uint8_t buff[IN_LINE_PRINT_CNT + 1];

    for (uint16_t addr = 0; addr < EEPROM_SIZE; addr += IN_LINE_PRINT_CNT)
    {
        nrf_delay_ms(2);
        ret_code_t err_code;
        err_code = eeprom_read2(addr, buff, IN_LINE_PRINT_CNT);
        buff[IN_LINE_PRINT_CNT] = '\0';
        if (NRF_SUCCESS != err_code)
        {
            printf("Error: EEPROM transmission error detected.\n");
            return;
        }

        printf("%.3X: ", addr);
        for (uint8_t i = 0; i < IN_LINE_PRINT_CNT; i++)
        {
            printf("%.2x ", buff[i]);
            if (!isprint((int)buff[i]))
            {
                buff[i] = '.';
            }
        }
        nrf_delay_ms(5);
        printf("%s", buff);
        
        if(addr % 64 == 0)
        {
            printf("  (new page)\r\n");
        }
        else
        {
            printf("\n");
        }

        printf("\r\n");
    }
}


void eeprom_cmd_write(void)
{
    uint16_t addr = 0;
    char data[13] = "chris shifrin";

    while (1)
    {
        ret_code_t err_code;
        size_t to_write = safe_strlen(data + addr, EEPROM_WRITE_MAX_BYTES);
        if (0 == to_write)
            break;
        err_code = eeprom_write2(addr, (uint8_t const *)data + addr, 15);
        if (NRF_SUCCESS != err_code)
        {
            printf("ERROR: Communication error.\r\n");
            return;
        }
        addr += to_write;
    }
    printf("EEPROM write successful.\r\n");
}






























