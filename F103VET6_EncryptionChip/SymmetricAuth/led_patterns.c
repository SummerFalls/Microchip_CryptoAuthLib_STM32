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
* @ 名称: led_patterns.c
* @ 作者: SummerFalls
* @ 日期: 2019-5-24
* @ 版本: V1.0
* @ 描述:
*/

#include "main.h"
#include "GTek_Include.h"


// 第一次配置芯片时快速闪烁
const led_pattern provision_pattern[] = {
    { 1,    LED_PATTERN_SHORT_DELAY_MSEC }, { 0, LED_PATTERN_SHORT_DELAY_MSEC },
    { 0xFF, 0xFFFF                       } /* Last element   for repeat */
};


// 成功时每快闪3次后停顿2秒
const led_pattern success_pattern[] = {
    { 1,    LED_PATTERN_SHORT_DELAY_MSEC }, { 0, LED_PATTERN_SHORT_DELAY_MSEC },
    { 1,    LED_PATTERN_SHORT_DELAY_MSEC }, { 0, LED_PATTERN_SHORT_DELAY_MSEC },
    { 1,    LED_PATTERN_SHORT_DELAY_MSEC }, { 0, LED_PATTERN_SHORT_DELAY_MSEC },
    { 0,    LED_PATTERN_LONG_DELAY_MSEC  }, { 0, LED_PATTERN_LONG_DELAY_MSEC },
    { 0xFF, 0xFFFF                       } /* Last element   for repeat */
};

// 失败时每隔0.5秒闪一次灯
const led_pattern fail_pattern[] = {
    { 1,    LED_PATTERN_MID_DELAY_MSEC }, { 0, LED_PATTERN_MID_DELAY_MSEC },
    { 1,    LED_PATTERN_MID_DELAY_MSEC }, { 0, LED_PATTERN_MID_DELAY_MSEC },
    { 0xFF, 0xFFFF                      } /* Last element   for repeat */
};

const led_pattern *g_active_pattern;
static uint8_t g_pattern_index;
static uint16_t g_current_state_time;


// 更新LED闪烁样式
void update_led_pattern(const led_pattern *pattern)
{
    /* Following lines need to be protected for context switching if play_led_pattern gets called from interrupt */
    if (pattern == NULL) {
        LL_GPIO_ResetOutputPin(LED2_GPIO_Port, LED2_Pin);
    }

    if (g_active_pattern != pattern) {
        g_active_pattern = pattern;
        g_current_state_time = 0;
        g_pattern_index = 0;
    }
}

/* This needs to be called on every time unit i.e. base for counts */
void play_led_pattern(void)
{
    if (g_current_state_time) {
        g_current_state_time--;
    } else if (g_active_pattern) {
        /* drive led with status */
        if (g_active_pattern[g_pattern_index].led_state) {
            LL_GPIO_ResetOutputPin(LED2_GPIO_Port, LED2_Pin);
        } else {
            LL_GPIO_SetOutputPin(LED2_GPIO_Port, LED2_Pin);
        }

        if (g_active_pattern[g_pattern_index].state_time_unit_count) {
            g_current_state_time = g_active_pattern[g_pattern_index].state_time_unit_count;
            g_pattern_index++;

            if (g_active_pattern[g_pattern_index].led_state == 0xFF) {
                g_pattern_index = 0;
            }
        } else {
            update_led_pattern(NULL);
        }
    }
}
