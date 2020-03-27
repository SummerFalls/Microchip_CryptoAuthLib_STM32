# :beers: Microchip_CryptoAuthLib_STM32 ![Project](https://img.shields.io/badge/Project-Microchip__CryptoAuthLib__STM32-blue)

[![FOSSA Status](https://app.fossa.com/api/projects/git%2Bgithub.com%2FSummerFalls%2FMicrochip_CryptoAuthLib_STM32.svg?type=small)](https://app.fossa.com/projects/git%2Bgithub.com%2FSummerFalls%2FMicrochip_CryptoAuthLib_STM32?ref=badge_small)
![GitHub code size in bytes](https://img.shields.io/github/languages/code-size/SummerFalls/Microchip_CryptoAuthLib_STM32?label=%E4%BB%A3%E7%A0%81%E5%A4%A7%E5%B0%8F)
<a href="https://github.com/SummerFalls/Microchip_CryptoAuthLib_STM32/releases"><img alt="GitHub release (latest by date)" src="https://img.shields.io/github/v/release/SummerFalls/Microchip_CryptoAuthLib_STM32"></a>
<a href="https://github.com/SummerFalls/Microchip_CryptoAuthLib_STM32/graphs/contributors"><img alt="Contributors" src="https://img.shields.io/github/contributors/SummerFalls/Microchip_CryptoAuthLib_STM32.svg?style=flat"></a>
<a href="https://github.com/SummerFalls/Microchip_CryptoAuthLib_STM32/blob/master/LICENSE"><img alt="License" src="https://img.shields.io/github/license/SummerFalls/Microchip_CryptoAuthLib_STM32.svg?style=flat"></a>
<a title="Hits" target="_blank" href="https://github.com/SummerFalls/Microchip_CryptoAuthLib_STM32"><img src="https://hits.b3log.org/b3log/hits.svg"></a>

```c
      ____________________________
     /                           /\
    /                          _/ /\
   /   Encryption IC Burner   / \/
  /                           /\
 /___________________________/ /
 \___________________________\/
  \ \ \ \ \ \ \ \ \ \ \ \ \ \ \
```

## :wink: 简介

Microchip 加密芯片 CryptoAuthLib 库在STM32上的移植以及对称IP保护使用示例

![加密芯片批量烧录&验证串口调试信息打印](./SerialDebugInfo.png)

## :dark_sunglasses: 硬件 & 软件 需求

本工程可直接编译并烧录运行于`反客STM32F103VET6最小系统开发板`上，当然也可根据你自己的芯片型号进行移植，通过配合使用STM32CubeMX，移植工作将非常方便快捷。

**注意:**

1. 在Keil中编译时，需要使能目标设置中的 GNU extensions
2. 若自己移植到其它MCU，使用GCC编译器的IDE也许会更好，例如 TrueStudio/STM32CubeIDE

### 硬件需求

- STM32F103VET6
- 杜邦线若干
- SOIC8编程烧录座

### 软件需求

- Keil uVision5.27
- STM32CubeMX 5.3.0 及以上
- [CryptoAuthLib](https://github.com/MicrochipTech/cryptoauthlib)
- 串口调试工具 putty/SSCOM/超级终端...

## :checkered_flag: 参考程序

- [cryptoauth_usecase_ipprotection_symmetric](https://github.com/MicrochipTech/cryptoauth_usecase_ipprotection_symmetric)

## :star: License

MIT License

Copyright (c) 2019 SummerFalls

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

[![FOSSA Status](https://app.fossa.com/api/projects/git%2Bgithub.com%2FSummerFalls%2FMicrochip_CryptoAuthLib_STM32.svg?type=large)](https://app.fossa.com/projects/git%2Bgithub.com%2FSummerFalls%2FMicrochip_CryptoAuthLib_STM32?ref=badge_large)

## :bulb: 扩展项目示例（emWin & FreeRTOS）

![带LCD显示屏版本](./F103VET6_EncryptionChip_GUI_Ver.jpg)
