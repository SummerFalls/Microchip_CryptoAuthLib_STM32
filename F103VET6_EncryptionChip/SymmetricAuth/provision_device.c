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
* @ 名称: provision_device.c
* @ 作者: SummerFalls
* @ 日期: 2019-5-23
* @ 版本: V1.0
* @ 描述:
*/

#include "configuration.h"

#ifdef IP_PROTECTION_LOAD_CONFIG
#include "main.h"
#include "GTek_Include.h"
#ifndef CRYPTOAUTH_DEVICE
#error "未选择加密芯片型号, 请在 configuration.h 中选择"
#endif

uint32_t ATCA_ProvisionCnt = 0;

#if (CRYPTOAUTH_DEVICE == DEVICE_ATSHA204A)

// ATSHA204A Configuration to store the symmetric diversified key
const uint8_t sha204_configdata[ATCA_SHA_CONFIG_SIZE] = {
    // block 0
    // Not Written: First 16 bytes are not written
    0x01, 0x23, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0xEE, 0x55, 0x00, 0x00,
    // I2C_Address, CheckMacConfig, OtpMode, SelectorMode
    0xC8, 0x00, 0xAA, 0x00,
    // SlotConfig
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x84, 0x80, 0x00, 0x00,
    // block 1
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    // Use Flags
    0xFF, 0x00, 0xFF, 0x00,
    0xFF, 0x00, 0xFF, 0x00,
    0xFF, 0x00, 0xFF, 0x00,
    // block 2
    0xFF, 0x00, 0xFF, 0x00,
    // Last Key Use
    0x7F, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF,
    // Not Written: UserExtra, Selector, LockData, LockConfig (word offset = 5)
    0x00, 0x00, 0x55, 0x55,
};

#elif (CRYPTOAUTH_DEVICE == DEVICE_ATECC508A)
// ATECC508A Configuration to store the symmetric diversified key
const uint8_t ecc508_configdata[ATCA_ECC_CONFIG_SIZE] = {
    // block 0
    // Not Written: First 16 bytes are not written
    0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF,
    // I2C_Address, Reserved17, OtpMode, ChipMode
    0xC0, 0x00, 0xAA, 0x00,
    // SlotConfig
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x84, 0x80, 0x00, 0x00,
    // block 1
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    // Counter0
    0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x00, 0x00, 0x00,
    // Counter1
    0xFF, 0xFF, 0xFF, 0xFF,
    // block 2
    0x00, 0x00, 0x00, 0x00,
    // LastKeyUse
    0x03, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF,
    // Not Written: UserExtra, Selector, LockData, LockConfig (word offset = 5)
    0x00, 0x00, 0x00, 0x00,
    // SlotLocked[2], Rfu90[2]
    0xFF, 0xFF, 0x00, 0x00,
    // X509Format
    0x00, 0x00, 0x00, 0x00,
    // block 3
    // KeyConfig
    0x1C, 0x00, 0x1C, 0x00,
    0x1C, 0x00, 0x1C, 0x00,
    0x1C, 0x00, 0x1C, 0x00,
    0x1C, 0x00, 0x1C, 0x00,
    0x3C, 0x00, 0x3C, 0x00,
    0x3C, 0x00, 0x3C, 0x00,
    0x3C, 0x00, 0x3C, 0x00,
    0x3C, 0x00, 0x1C, 0x00
};
#elif (CRYPTOAUTH_DEVICE == DEVICE_ATECC608A)
// ATECC608A Configuration to store the symmetric diversified key
const uint8_t ecc608_configdata[ATCA_ECC_CONFIG_SIZE] = {
    0x01,            0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00,
    ECC608A_ADDRESS, 0x00, 0x00, 0x01, 0x85, 0x00, 0x82, 0x00, 0x85, 0x20, 0x85, 0x20, 0x85, 0x20, 0x8F, 0x46,
    0x8F,            0x0F, 0x9F, 0x8F, 0x0F, 0x0F, 0x8F, 0x0F, 0x0F, 0x8F, 0x0F, 0x8F, 0x0F, 0x8F, 0x0F, 0x0F,
    0x0D,            0x1F, 0x0F, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00,            0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xF7, 0x00, 0x69, 0x76, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00,            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x0E, 0x60, 0x00, 0x00, 0x00, 0x00,
    0x53,            0x00, 0x53, 0x00, 0x73, 0x00, 0x73, 0x00, 0x73, 0x00, 0x38, 0x00, 0x7C, 0x00, 0x1C, 0x00,
    0x3C,            0x00, 0x1A, 0x00, 0x1C, 0x00, 0x10, 0x00, 0x1C, 0x00, 0x30, 0x00, 0x12, 0x00, 0x30, 0x00
};
#endif

// Function to configure the device configuration zone and the symmetric diversified key in the slot
ATCA_STATUS device_provision(uint8_t slot)
{
    ATCA_STATUS status;
    uint8_t sn[ATCA_SERIAL_NUM_SIZE];    
    bool is_locked;
    uint8_t master_key[ATCA_KEY_SIZE];
#ifdef USE_ATCAH_DERIVE_KEY
    uint8_t symmetric_key[ATCA_KEY_SIZE];
    atca_temp_key_t temp_key_derive;
    struct atca_derive_key_in_out derivekey_params;
#endif

    do {
#if (CRYPTOAUTH_DEVICE == DEVICE_ATECC608A)

        if ((status = detect_crypto_device()) != ATCA_SUCCESS) {
            break;
        }

#endif

        // Check current status of configuration lock status
        if ((status = atcab_is_locked(LOCK_ZONE_CONFIG, &is_locked)) != ATCA_SUCCESS) {
            printf("--> 指令执行失败_0...\r\n");
            break;
        }

        // Write configuration if it is not already locked
        if (!is_locked) {

            printf("--> Config Zone 未被配置过...\r\n");
            printf("--> 将要烧写密钥的Data Slot ID: %u\r\n", slot);
//            printf("--> 按下按钮进行加密芯片密钥烧录...\r\n");

            // Update the led pattern with provision led pattern
            update_led_pattern(provision_pattern);

            // Wait for the button to be pressed
//            while (LL_GPIO_IsInputPinSet(KEY_S2_GPIO_Port, KEY_S2_Pin) == 1);
//            delay_ms(100);
            printf("\r\n--> 开始烧录...\r\n");

            // Trigger Configuration write
#if (CRYPTOAUTH_DEVICE == DEVICE_ATSHA204A)

            if ((status = atcab_write_config_zone(sha204_configdata)) != ATCA_SUCCESS) {
                printf("--> Config Zone 写入失败...\r\n");
                break;
            } else {
                printf("--> Config Zone 写入成功...\r\n");
            }

#elif (CRYPTOAUTH_DEVICE == DEVICE_ATECC508A)

            if ((status = atcab_write_config_zone(ecc508_configdata)) != ATCA_SUCCESS) {
                printf("--> Config Zone 写入失败...\r\n");
                break;
            } else {
                printf("--> Config Zone 写入成功...\r\n");
            }

#elif (CRYPTOAUTH_DEVICE == DEVICE_ATECC608A)

            if ((status = atcab_write_config_zone(ecc608_configdata)) != ATCA_SUCCESS) {
                printf("--> Config Zone 写入失败...\r\n");
                break;
            } else {
                printf("--> Config Zone 写入成功...\r\n");
            }

            if (cfg_ateccx08a_i2c_default.atcai2c.slave_address != ecc608_configdata[16]) {
                atcab_wakeup();
                atcab_sleep();
                cfg_ateccx08a_i2c_default.atcai2c.slave_address = ecc608_configdata[16];
                atcab_init(&cfg_ateccx08a_i2c_default);
                printf("--> ATECC608A 已配置新的 I2C 从设备地址: 0x%02X\r\n", cfg_ateccx08a_i2c_default.atcai2c.slave_address);
            }

#endif


            // Lock Configuration Zone on completing configuration
            if ((status = atcab_lock_config_zone()) != ATCA_SUCCESS) {
                printf("--> Config Zone 锁定失败...\r\n");
                break;
            } else {
                printf("--> Config Zone 锁定成功...\r\n");
            }
        } else {
            printf("--> Config Zone 已被配置并锁定过...\r\n");
        }


        // Check current status of data zone lock status
        if ((status = atcab_is_locked(LOCK_ZONE_DATA, &is_locked)) != ATCA_SUCCESS) {
            printf("--> 指令执行失败_1...\r\n");
            break;
        }

        // Write shared secret if it is not already locked
        if (!is_locked) {

            // Read the serial number from the device
            if ((status = atcab_read_serial_number(sn)) != ATCA_SUCCESS) {
                printf("--> 读取序列号失败...\r\n");
                break;
            } else {
//                printf("--> 序列号: 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X\r\n", sn[0], sn[1], sn[2], sn[3], sn[4], sn[5], sn[6], sn[7], sn[8]);
            }
            
            get_master_key(master_key);

#ifdef USE_ATCAH_DERIVE_KEY
            memset(&temp_key_derive, 0, sizeof(temp_key_derive));
            temp_key_derive.valid = 1;
            // 32 bytes TempKey ( SN[0:8] with padded 23 zeros used in symmetric key calculation)
            memcpy(temp_key_derive.value, sn, sizeof(sn));

            // Parameters used deriving the symmetric key
            derivekey_params.mode = 0;
            derivekey_params.target_key_id = slot;
            derivekey_params.parent_key = master_key;
            derivekey_params.sn = sn;
            derivekey_params.target_key = symmetric_key;
            derivekey_params.temp_key = &temp_key_derive;

            // calculate the symmetric_diversified_key
            // 通过 master_key 混合其它变量进行SHA-256计算产生一个对称密钥
            if ((status = atcah_derive_key(&derivekey_params)) != ATCA_SUCCESS) {
                printf("--> 对称密钥计算失败...\r\n");
                break;
            } else {
                printf("--> 对称密钥计算成功...\r\n");
            }

            // Store the symmetric diversified key in device
            // 将计算出来的对称密钥存储在 Data Slot 中
            if ((status = atcab_write_zone(ATCA_ZONE_DATA, slot, 0, 0, symmetric_key, ATCA_KEY_SIZE)) != ATCA_SUCCESS) {
#else
            // 将 master_key 直接存储在 Data Slot 中
            if ((status = atcab_write_zone(ATCA_ZONE_DATA, slot, 0, 0, master_key, ATCA_KEY_SIZE)) != ATCA_SUCCESS) {
#endif
                printf("--> Data Zone Slot[%u]: 密钥写入失败...\r\n", slot);
                break;
            } else {
                printf("--> Data Zone Slot[%u]: 密钥写入成功...\r\n", slot);
            }

            // Lock the data zone of the device
            if ((status = atcab_lock_data_zone()) != ATCA_SUCCESS) {
                printf("--> Data Zone 锁定失败...\r\n");
                break;
            } else {
                printf("--> Data Zone 锁定成功...\r\n");
            }

#if (CRYPTOAUTH_DEVICE == DEVICE_ATECC508A) || (CRYPTOAUTH_DEVICE == DEVICE_ATECC608A)

            if ((status = atcab_lock_data_slot(slot)) != ATCA_SUCCESS) {
                printf("--> Data Zone Slot[%u]: 锁定失败...\r\n", slot);
                break;
            } else {
                printf("--> Data Zone Slot[%u]: 锁定成功...\r\n", slot);
            }

#endif

            update_led_pattern(NULL);

//            printf("加密芯片密钥烧录成功...\r\n");
//            printf("按下按钮以继续...");

            // Press the button to start proceeding
//            while (LL_GPIO_IsInputPinSet(KEY_S2_GPIO_Port, KEY_S2_Pin) == 1);
//            delay_ms(100);
//            printf("OK\r\n");
            ATCA_ProvisionCnt++;
            printf("--> 第 %u 片加密芯片烧写成功...\r\n", ATCA_ProvisionCnt);
        } else {
            printf("--> Data Zone   已被配置并锁定过...\r\n\r\n");
        }

    } while (0);

    return status;
}

#if (CRYPTOAUTH_DEVICE == DEVICE_ATECC608A)
ATCA_STATUS detect_crypto_device(void)
{
    ATCA_STATUS status;

    uint8_t addr_list[] = { ECC608A_DEFAULT_ADDRESS, ECC608A_ADDRESS };

    for (uint8_t addr_index = 0; addr_index < (sizeof(addr_list) / sizeof(addr_list[0])); addr_index++) {
        cfg_ateccx08a_i2c_default.atcai2c.slave_address = addr_list[addr_index];

        if ((status = atcab_init(&cfg_ateccx08a_i2c_default)) == ATCA_SUCCESS) {
            /* ECC608A with addr_list[addr_index] address is found */
            break;
        }
    }

    return status;
}
#endif

#endif
