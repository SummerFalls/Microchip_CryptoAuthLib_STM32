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
* @ 名称: host_random.c
* @ 作者: SummerFalls
* @ 日期: 2019-5-23
* @ 版本: V1.0
* @ 描述:
*/

#include "main.h"
#include "GTek_Include.h"
#include "adc.h"

// Function to calculate the ADC value
uint16_t calculate_adc(void)
{
    uint16_t result;

    /* ADC 校准 */
    HAL_ADCEx_Calibration_Start(&hadc1);

    /* 开始 ADC 转换 */
    HAL_ADC_Start(&hadc1);

    /* 等待转换结束 */
    HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);

    /* 检查转换是否结束 */
    if (HAL_IS_BIT_SET(HAL_ADC_GetState(&hadc1), HAL_ADC_STATE_REG_EOC)) {
        result = HAL_ADC_GetValue(&hadc1);
        //App_Printf("MCU温度: %.1f\r\n", ((result * 3300 / 4096 - 760) / 2.5 + 25));
    } else {
        //App_Printf("MCU温度获取失败\r\n");
    }

    return result;
}

// Function that calculates the ADC value from different analog sources and updates that value as Seed for the random number
void random_seed_init(void)
{
    uint32_t rand_seed = 0;

    rand_seed |= (uint32_t)(calculate_adc() & 0x00FF) << 0;
    rand_seed |= (uint32_t)(calculate_adc() & 0x00FF) << 8;
    rand_seed |= (uint32_t)(calculate_adc() & 0x00FF) << 16;
    rand_seed |= (uint32_t)(calculate_adc() & 0x00FF) << 24;

    srand(rand_seed);
}

// Function to calculate 20 byte random number from host
void host_generate_random_number(uint8_t *rand_num)
{
    size_t i;
#if 1
    int num;

    for (i = 0; i < 20; i += sizeof(int)) {
        num = rand();
        memcpy(&rand_num[i], &num, sizeof(num));
    }
#else
    for (i = 0; i < 20; i++) {
        rand_num[i] = 0x00;
    }
#endif
}
