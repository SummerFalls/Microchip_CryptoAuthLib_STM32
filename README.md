[![FOSSA Status](https://app.fossa.com/api/projects/git%2Bgithub.com%2FSummerFalls%2FMicrochip_CryptoAuthLib_STM32.svg?type=small)](https://app.fossa.com/projects/git%2Bgithub.com%2FSummerFalls%2FMicrochip_CryptoAuthLib_STM32?ref=badge_small)

``` c
      ____________________________
     /                           /\
    /                          _/ /\
   /   Encryption IC Burner   / \/
  /                           /\
 /___________________________/ /
 \___________________________\/
  \ \ \ \ \ \ \ \ \ \ \ \ \ \ \
```

# Microchip_CryptoAuthLib_STM32
Microchip 加密芯片 CryptoAuthLib 库在STM32上的移植以及对称IP保护使用示例

![加密芯片批量烧录&验证串口调试信息打印](https://github.com/SummerFalls/Microchip_CryptoAuthLib_STM32/blob/master/SerialDebugInfo.png)


# 硬件 & 软件 需求
本工程可直接编译并烧录运行于`反客STM32F103VET6最小系统开发板`上，当然也可根据你自己的芯片型号进行移植，通过配合使用STM32CubeMX，移植工作将非常方便快捷。

**注意:**
 - 1.在Keil中编译时，需要使能目标设置中的 GNU extensions
 - 2.若自己移植到其它MCU，使用GCC编译器的IDE也许会更好，例如 TrueStudio/STM32CubeIDE


## 硬件需求:
 - STM32F103VET6
 - 杜邦线若干
 - SOIC8编程烧录座

## 软件需求:
 - Keil uVision5.27
 - STM32CubeMX 5.3.0 及以上
 - [CryptoAuthLib](https://github.com/MicrochipTech/cryptoauthlib)
 - 串口调试工具 putty/SSCOM/超级终端...

# 参考程序
 - [cryptoauth_usecase_ipprotection_symmetric](https://github.com/MicrochipTech/cryptoauth_usecase_ipprotection_symmetric)
 
## License
[![FOSSA Status](https://app.fossa.com/api/projects/git%2Bgithub.com%2FSummerFalls%2FMicrochip_CryptoAuthLib_STM32.svg?type=large)](https://app.fossa.com/projects/git%2Bgithub.com%2FSummerFalls%2FMicrochip_CryptoAuthLib_STM32?ref=badge_large)
 
# 扩展项目示例（emWin & FreeRTOS）
![带LCD显示屏版本](https://github.com/SummerFalls/Microchip_CryptoAuthLib_STM32/blob/master/F103VET6_EncryptionChip_GUI_Ver.jpg)
