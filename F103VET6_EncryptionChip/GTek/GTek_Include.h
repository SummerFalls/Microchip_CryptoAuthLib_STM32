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
* @ 名称: GTek_Include.h
* @ 作者: SummerFalls
* @ 日期: 2019-5-21
* @ 版本: V1.0
* @ 描述: 全局通用头文件引用，针对不同 .c 源文件经常需要
*         引用共同的头文件的情况，请直接引用本头文件即可。
*/

#ifndef __GTEK_INCLUDE_H
#define __GTEK_INCLUDE_H

/* ------- 标准库头文件引用 ------- */
#include <stdint.h> /* 数据类型 */

#include <stdio.h>  /* 输入输出 */
#include <stdlib.h> /* 常用实用函数 */
#include <stddef.h> /* 常用定义 */
#include <stdbool.h>/* 布尔类型定义 */
#include <string.h> /* 字符串处理 */
#include <stdarg.h> /* 不定参数 */
#include <ctype.h>  /* 字符处理 */

#include <locale.h> /* 本地化 */
#include <time.h>   /* 日期和时间 */

#include <limits.h> /* 整型特性 */
#include <float.h>  /* 浮点数特性 */
#include <math.h>   /* 数学计算 */

#include <assert.h> /* 诊断 */
#include <errno.h>  /* 错误监测 */

#include <setjmp.h> /* 非本地跳转 */
#include <signal.h> /* 信号处理 */


//#include "GTek_LED.h"
//#include "GTek_UART.h"
#include "GTek_Delay.h"

#include "i2c_bitbang_stm32.h"
#include "cryptoauthlib.h"
#include "symmetric_authentication.h"
#include "configuration.h"
#include "provision_device.h"
#include "host_random.h"
#include "led_patterns.h"
#include "atca_host.h"

#include "stm32f1xx.h"

#endif /* __GTEK_INCLUDE_H */
/* -------------------------------------------- END OF FILE -------------------------------------------- */
