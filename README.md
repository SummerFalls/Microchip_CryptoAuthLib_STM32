# Microchip_CryptoAuthLib_STM32
Microchip 加密芯片 CryptoAuthLib 库在STM32上的移植以及对称IP保护使用示例


# 硬件 & 软件 需求
本工程可直接编译并烧录运行于NUCLEO-F302R8开发板上，当然也可根据你自己的芯片型号进行移植，通过配合使用STM32CubeMX，移植工作将非常方便快捷。

**注意:**
 - 1.在Keil中编译时，需要使能目标设置中的 GNU extensions。
 - 2.若自己移植到其它MCU，使用GCC编译器的IDE也许会更好，例如 TrueStudio/STM32CubeIDE


## 硬件需求:
 - NUCLEO-F302R8 - Development Board(芯片: STM32F302R8T6)
 - 杜邦线若干
 - SOIC8编程烧录座

## 软件需求:
 - Keil uVision5
 - STM32CubeMX 5.2.0 及以上
 - [CryptoAuthLib](https://github.com/MicrochipTech/cryptoauthlib)
 - 串口调试工具 putty/SSCOM/超级终端...

# 参考程序
 - [cryptoauth_usecase_ipprotection_symmetric](https://github.com/MicrochipTech/cryptoauth_usecase_ipprotection_symmetric)
