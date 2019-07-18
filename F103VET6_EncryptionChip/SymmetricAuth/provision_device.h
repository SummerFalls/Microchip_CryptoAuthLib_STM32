//       ____
//      /___/\_
//     _\   \/_/\__
//   __\       \/_/\
//   \   __    __ \ \        MIT License. Copyright (c) 2019 SummerFalls.
//  __\  \_\   \_\ \ \   __
// /_/\\   __   __  \ \_/_/\
// \_\/_\__\/\__\/\__\/_\_\/
//    \_\/_/\       /_\_\/
//       \_\/       \_\/
/*
* @ 名称: provision_device.h
* @ 作者: SummerFalls
* @ 日期: 2019-5-23
* @ 版本: V1.0
* @ 描述:
*/

#ifndef PROVISION_DEVICE_H_
#define PROVISION_DEVICE_H_

#include <stdint.h>
#include "cryptoauthlib.h"

#define ECC608A_DEFAULT_ADDRESS 0xC0 // Default I2C address for unconfigured ECC608A crypto devices
#define ECC608A_ADDRESS         0x6A // I2C address for configured ECC608A crypto devices.

ATCA_STATUS device_provision(uint8_t slot);

ATCA_STATUS detect_crypto_device(void);


#endif /* PROVISION_DEVICE_H_ */
