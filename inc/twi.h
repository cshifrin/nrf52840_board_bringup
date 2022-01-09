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
#define TWI_INSTANCE_ID     		0

/* Maximum number of TWI addresses. */
#define TWI_ADDRESSES      			127

/* Configuration settings for AT24C EEPROM. */
#define EEPROM_ADDR					0x50
#define EEPROM_MEM_ADDR_LEN 		2
#define EEPROM_WRITE_MAX_BYTES		200
#define EEPROM_READ_MAX_BYTES   	200
#define EEPROM_ADDR_LEN_BYTES  	    2
#define EEPROM_SIZE					(320u)
#define IN_LINE_PRINT_CNT		    (16u) 

	
/* TWI instance. */
static const nrf_drv_twi_t m_twi = NRF_DRV_TWI_INSTANCE(TWI_INSTANCE_ID);

/* Tx and Rx buffers for EEPROM. */
uint16_t tx_buf_eeprom[256];
uint16_t rx_buf_eeprom[256];

/* Declaring functions. */
void init_twi(void);                  											// Initialize the TWI.
void twi_scan(void);                  											// Scan for connected TWI devices.
ret_code_t eeprom_read(size_t addr, uint8_t * pdata, size_t size);				// Read specific location in EEPROM.
ret_code_t eeprom_write(size_t addr, uint8_t const * pdata, size_t size);		// Write to specific location in EEPROM.	
void eeprom_mem_dump(void);														// Perform a memory dump of EEPROM to console.
void eeprom_print_hex(uint8_t data);											// Print the data value in HEX.
void eeprom_print_addr(size_t addr);											// Print the address in HEX.
void eeprom_cmd_clear(void);
ret_code_t eeprom_read2(uint16_t addr, uint8_t * pdata, size_t size);		
ret_code_t eeprom_write2(uint16_t addr, uint8_t const * pdata, size_t size);	
void eeprom_cmd_read(void);	
void eeprom_cmd_write(void);



#ifdef __cplusplus
}
#endif