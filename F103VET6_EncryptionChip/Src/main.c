/* USER CODE BEGIN Header */
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
* @ 名称: main.c
* @ 作者: SummerFalls
* @ 日期: 2019-5-23
* @ 版本: V1.0
* @ 描述:
*/

/*******************************************************************************
* @brief  : 工程编译后 Flash 与 RAM 占用情况计算
* @FLASH  : Total ROM Size (Code + RO Data + RW Data)
* @RAM    : Total RW  Size (RW Data + ZI Data)
* @note   : 可通过 map 文件查看详细情况
*******************************************************************************/
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "GTek_Include.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
volatile uint32_t g_ticks_msec = 0;          // Tracks elapsed time in milliseconds
volatile uint32_t g_auth_interval_msec = 1;  // Interval until next authentication check in milliseconds
volatile static bool g_do_auth = false;      // Indicates the authentication sequence should be performed
volatile uint8_t I2C_BusIdx = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
static ATCA_STATUS cryptoauthlib_init(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

// Function to get the master secret key .
void get_master_key(uint8_t *master_key)
{
    // The master secret key should be securely stored in application.
    uint8_t master_secret_key[] = {
        0x37, 0x80, 0xE6, 0x3D, 0x49, 0x68, 0xAD, 0xE5,
        0xD8, 0x22, 0xC0, 0x13, 0xFC, 0xC3, 0x23, 0x84,
        0x5D, 0x1B, 0x56, 0x9F, 0xE7, 0x05, 0xB6, 0x00,
        0x06, 0xFE, 0xEC, 0x14, 0x5A, 0x0D, 0xB1, 0xE3,
    };

    memcpy(master_key, master_secret_key, sizeof(master_secret_key));
}

// Systick callback handler called every 1ms, which sets the g_do_auth after
// the random interval (g_auth_interval_msec) for authentication to happen and
// also performs the led blinking operation
void SysTick_Handler_Callback(void)
{
    g_ticks_msec++;

    if (g_ticks_msec % g_auth_interval_msec == 0) {
        g_do_auth = true;
        g_ticks_msec = 0;
        g_auth_interval_msec = (rand() % AUTHENTICATION_RANGE_MSEC) + AUTHENTICATION_MIN_MSEC;
    }

    play_led_pattern();
}

// Initialize the CryptoAuthLib library with the particular interface and device
// TODO: 批量烧录方案思路分析
// 修改思路:
// 在 atcab_init() 函数执行之前，就得先完成GPIO PORT口的映射，
// 因为在该函数的最深层调用函数: hal_i2c_init() -> i2c_enable() 函数中就已经对相应的GPIO口进行操作
// 将 i2c_bitbang_stm32.h 中相关 PORT 宏定义常量改为变量，在 atcab_init() 之前对PORT变量进行映射到对应的 I2C 总线PORT口
// 步骤: (例如需要批量烧录 3 片加密芯片)
// 1. 设置当前需要进行通讯的 I2C 总线为第几条
// 2. 映射 port_sda 和 port_scl 到对应的 PORT 口
// 3. 调用 atcab_init(); 初始化加密芯片相关API和对象实例，并初始化 I2C 总线
// 4. atcab_release()函数，每烧录完一片加密芯片，需要释放对应实例，因为 atcab_init() 时申请了 "堆 Heap" 内存
static ATCA_STATUS cryptoauthlib_init(void)
{
    ATCA_STATUS status;

#if (CRYPTOAUTH_DEVICE == DEVICE_ATSHA204A)
    // 1. 设置当前需要进行通讯的 I2C 总线为第几条
    cfg_atsha204a_i2c_default.atcai2c.bus = I2C_BusIdx;

    // 2. atcab_init() 前，映射 SDA 和 SCL 的 PORT 口
    port_sda = i2c_buses_default.port_sda[cfg_atsha204a_i2c_default.atcai2c.bus]; // I2C1_SDA_GPIO_Port
    port_scl = i2c_buses_default.port_scl[cfg_atsha204a_i2c_default.atcai2c.bus]; // I2C1_SCL_GPIO_Port

    // 3. 初始化加密芯片相关API和对象实例，并初始化 I2C 总线
    status = atcab_init(&cfg_atsha204a_i2c_default);
#elif (CRYPTOAUTH_DEVICE == DEVICE_ATECC508A)
    status = atcab_init(&cfg_ateccx08a_i2c_default);
#elif (CRYPTOAUTH_DEVICE == DEVICE_ATECC608A)
    cfg_ateccx08a_i2c_default.atcai2c.slave_address = ECC608A_ADDRESS;
    cfg_ateccx08a_i2c_default.devtype = ATECC608A;
    status = atcab_init(&cfg_ateccx08a_i2c_default);
#endif

    return status;
}

// Function to be called by application at random interval to perform authentication
state authenticate_application(void)
{
    static state auth_status = NOT_AUTHENTICATED;
    uint8_t master_key[ATCA_KEY_SIZE];
    uint8_t host_nonce[NONCE_NUMIN_SIZE];

    if (!g_do_auth) {
        return auth_status;
    }

    get_master_key(master_key);
    host_generate_random_number(host_nonce);

    if (symmetric_authenticate(CRYPTOAUTH_DEVICE_AUTH_KEY_SLOT, master_key, host_nonce) == ATCA_SUCCESS) {
        auth_status = AUTHENTICATED;
        update_led_pattern(success_pattern);
    } else {
        auth_status = NOT_AUTHENTICATED;
        update_led_pattern(fail_pattern);
    }

    g_do_auth = false;

    return auth_status;
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
    uint8_t sn[ATCA_SERIAL_NUM_SIZE];
  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
    LL_SYSTICK_EnableIT();
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
    printf("外设初始化完成...\r\n\r\n");

    //    __ASM volatile("BKPT #0");

    // Update the seed value for use with rand()
    random_seed_init();

    switch (CRYPTOAUTH_DEVICE) {
        case DEVICE_ATSHA204A:
            printf("--> 当前程序适用芯片: ATSHA204A\r\n\r\n");
            break;

        case DEVICE_ATECC508A:
            printf("--> 当前程序适用芯片: ATECC508A\r\n\r\n");
            break;

        case DEVICE_ATECC608A:
            printf("--> 当前程序适用芯片: ATECC608A\r\n\r\n");
            break;
    }

#ifdef USE_ATCAH_DERIVE_KEY
    printf("--> 当前程序是否使用 DERIVE_KEY: \tYES!\r\n\r\n");
#else
    printf("--> 当前程序是否使用 DERIVE_KEY: \tNO!\r\n\r\n");
#endif
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
    while (1) {
        printf("--> 按下按钮开始配置加密芯片...");

        while (LL_GPIO_IsInputPinSet(KEY_S2_GPIO_Port, KEY_S2_Pin) == 1);

        printf("OK\r\n");
        delay_ms(1000);

        for (I2C_BusIdx = 0; I2C_BusIdx < MAX_I2C_BUSES; I2C_BusIdx++) {
            printf("------------------- START -------------------\r\n\r\n");

            printf("********* 当前处理第 %02u 片加密芯片 *********\r\n", I2C_BusIdx);

            // 初始化 CryptoAuthlib 加密库，申请 "堆 Heap" 内存，用于存放相关对象实例
            cryptoauthlib_init();

            if (atcab_read_serial_number(sn) != ATCA_SUCCESS) {
                printf("--> 读取序列号失败，请核对芯片型号是否与程序相符合...\r\n\r\n");
            } else {
                printf("--> 当前芯片序列号: 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X\r\n", sn[0], sn[1], sn[2], sn[3], sn[4], sn[5], sn[6], sn[7], sn[8]);
            }

            // Provision the device with the configuration and shared secret data
#if IP_PROTECTION_LOAD_CONFIG

            if (device_provision(CRYPTOAUTH_DEVICE_AUTH_KEY_SLOT) != ATCA_SUCCESS) {
                printf("--> 加密芯片配置失败...\r\n");
                printf("--> 检查设备然后复位重试...\r\n");
            }

#endif

            // Initialize the time for the authentication to perform
            g_auth_interval_msec = (rand() % AUTHENTICATION_RANGE_MSEC) + AUTHENTICATION_MIN_MSEC;

            // Forcing to do Authentication at the start
            g_do_auth = true;

            if (authenticate_application() == NOT_AUTHENTICATED) {
                printf("--> 加密芯片验证失败，1秒后重试...\r\n\r\n");
                delay_ms(1000);
            } else {

                switch (CRYPTOAUTH_DEVICE) {
                    case DEVICE_ATSHA204A:
                        printf("--> 加密芯片 ATSHA204A 验证成功...\r\n\r\n");
                        break;

                    case DEVICE_ATECC508A:
                        printf("--> 加密芯片 ATECC508A 验证成功...\r\n\r\n");
                        break;

                    case DEVICE_ATECC608A:
                        printf("--> 加密芯片 ATECC608A 验证成功...\r\n\r\n");
                        break;
                }
            }

            printf("------------------- END -------------------\r\n\r\n");

            // 每烧录完一片加密芯片，需要释放对应实例，因为 atcab_init() 时申请了 "堆 Heap" 内存
            atcab_release();
        }

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    }

  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_2);

   if(LL_FLASH_GetLatency() != LL_FLASH_LATENCY_2)
  {
    Error_Handler();  
  }
  LL_RCC_HSI_SetCalibTrimming(16);
  LL_RCC_HSI_Enable();

   /* Wait till HSI is ready */
  while(LL_RCC_HSI_IsReady() != 1)
  {
    
  }
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSI_DIV_2, LL_RCC_PLL_MUL_16);
  LL_RCC_PLL_Enable();

   /* Wait till PLL is ready */
  while(LL_RCC_PLL_IsReady() != 1)
  {
    
  }
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_2);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);

   /* Wait till System clock is ready */
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {
  
  }
  LL_SetSystemCoreClock(64000000);
  LL_RCC_SetADCClockSource(LL_RCC_ADC_CLKSRC_PCLK2_DIV_8);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
       tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
