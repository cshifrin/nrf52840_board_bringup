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
    nrf_delay_ms(20);
    printf("Test to see if initialized correctly.\r\n");
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