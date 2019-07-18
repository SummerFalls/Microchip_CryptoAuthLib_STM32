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
* @ 名称: configuration.h
* @ 作者: SummerFalls
* @ 日期: 2019-5-24
* @ 版本: V1.0
* @ 描述:
*/

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

// 测试用
// 型号: ATSHA204A 新 SN[0:8] 0x01 0x23 0x77 0xEE 0x79 0x3F 0xA1 0xE0 0xEE
// 型号: ATSHA204A 旧 SN[0:8] 0x01 0x23 0x48 0xD2 0x64 0x40 0xC1 0x04 0xEE
// 型号: ATECC508A 旧 SN[0:8] 0x01 0x23 0x0C 0x97 0x4A 0x3E 0x60 0xF8 0xEE

/*
NOTE 1: 定义验证时是否使用 DERIVE_KEY，如果使用，
        则调用 atcah_derive_key() 函数通过 master_key 混合其它变量进行SHA-256计算产生一个对称密钥。

NOTE 2: 如果验证时要使用 DERIVE_KEY，则要求在加密芯片第一次配置时也进行 DERIVE_KEY 的使用，
        即调用 atcah_derive_key() 函数通过 master_key 产生对称密钥，并将对称密钥写入加密芯片的Data Slot中。
        
NOTE 3: 受该宏影响的文件: provision_device.c    symmetric_authentication.c
*/
#define USE_ATCAH_DERIVE_KEY

#define DEVICE_ATSHA204A 0
#define DEVICE_ATECC508A 1
#define DEVICE_ATECC608A 2 // ATECC608A 的配置信息暂时为默认，所以暂时不用该宏

// 设置是否进行加密芯片配置以写入密钥等信息
#define IP_PROTECTION_LOAD_CONFIG       1

// 选择需要验证的加密芯片
#define CRYPTOAUTH_DEVICE               DEVICE_ATSHA204A

// 设置用来验证的 symmetric key(对称密钥) 所存储的 Data Slot，范围: 0 ~ 15
#define CRYPTOAUTH_DEVICE_AUTH_KEY_SLOT 4

// 对于验证操作的最小等待周期 (单位: ms)
#define AUTHENTICATION_MIN_MSEC         1500

// 对于验证操作的最大等待周期 (单位: ms) 介于 AUTHENTICATION_MIN_MSEC 和 AUTHENTICATION_MIN_MSEC + AUTHENTICATION_RANGE_MSEC 之间
#define AUTHENTICATION_RANGE_MSEC       3000

#endif /* CONFIGURATION_H_ */
