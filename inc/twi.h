#include <stdio.h>
#include "boards.h"
#include "app_util_platform.h"
#include "app_error.h"
#include "nrf_drv_twi.h"
#include "nrf_delay.h"

#ifdef __cplusplus
extern "C" {
#endif


/* Establish the TWI instance. */
#define TWI_INSTANCE_ID     	0

/* Maximum number of TWI addresses. */
#define TWI_ADDRESSES      		127

/* Configuration settings for AT24C EEPROM. */
#define EEPROM_ADDR				0x50
#define EEPROM_MEM_ADDR_LEN 	2

/* Return value for accessing AT24CXX */
#define AT24C_WRITE_SUCCESS     0
#define AT24C_WRITE_FAIL        1
#define AT24C_READ_SUCCESS      0
#define AT24C_READ_FAIL         1
	
/* TWI instance. */
static const nrf_drv_twi_t m_twi = NRF_DRV_TWI_INSTANCE(TWI_INSTANCE_ID);

/* Tx and Rx buffers for EEPROM. */
uint16_t tx_buf_eeprom[256];
uint16_t rx_buf_eeprom[256];

/* Declaring functions. */
void init_twi(void);                  										// Initialize the TWI.
void twi_scan(void);                  										// Scan for connected TWI devices.
ret_code_t eeprom_read(size_t addr, uint8_t * pdata, size_t size);			// Read specific location in EEPROM.
ret_code_t eeprom_write(size_t addr, uint8_t const * pdata, size_t size);	// Write to specific location in EEPROM.	
void eeprom_mem_dump(void);													// Perform a memory dump of EEPROM to console.
void eeprom_print_hex(uint8_t data);										// Print the data value in HEX.
void eeprom_print_addr(size_t addr);										// Print the address in HEX.


#ifdef __cplusplus
}
#endif