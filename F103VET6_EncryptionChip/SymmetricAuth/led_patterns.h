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
* @ 名称: led_patterns.h
* @ 作者: SummerFalls
* @ 日期: 2019-5-24
* @ 版本: V1.0
* @ 描述:
*/

#ifndef LED_PATTERNS_H_
#define LED_PATTERNS_H_

#include <stdint.h>

#define LED_PATTERN_SHORT_DELAY_MSEC    100
#define LED_PATTERN_MID_DELAY_MSEC      500
#define LED_PATTERN_LONG_DELAY_MSEC     1000

typedef struct {
    uint8_t  led_state;
    uint16_t state_time_unit_count;    /* zero value terminates the pattern */
} led_pattern;

extern const led_pattern provision_pattern[];
extern const led_pattern success_pattern[];
extern const led_pattern fail_pattern[];

void update_led_pattern(const led_pattern *pattern);
void play_led_pattern(void);

#endif /* LED_PATTERNS_H_ */
