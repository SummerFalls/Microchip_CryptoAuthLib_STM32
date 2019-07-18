#ifndef HAL_I2C_BITBANG_H_
#define HAL_I2C_BITBANG_H_

#include "i2c_bitbang_stm32.h"

/**
 * \defgroup hal_ Hardware abstraction layer (hal_)
 *
 * \brief These methods define the hardware abstraction layer for
 *        communicating with a CryptoAuth device using I2C bit banging.
 */

/**
 * \brief This enumeration lists flags for I2C read or write addressing.
 */
enum i2c_read_write_flag {
    I2C_WRITE = (uint8_t)0x00,  //!< write command flag
    I2C_READ  = (uint8_t)0x01   //!< read command flag
};

/**
 * \brief This is the hal_data for ATCA HAL.
 */
typedef struct atcaI2Cmaster {
    uint32_t pin_sda;
    uint32_t pin_scl;
    int      ref_ct;
    //! for conveniences during interface release phase
    int bus_index;
} ATCAI2CMaster_t;

#endif /* HAL_AT88CK900X_I2C_H_ */
