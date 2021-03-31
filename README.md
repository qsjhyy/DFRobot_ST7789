# DFRobot_Sensor
这是一个实习生培训用最简单的的Arduino的库
这里需要显示拍照图片，可以一张图片，可以多张图片（不要用SVG图）

如果以后有事物就在数据手册上抄一下芯片的描述
这里写模块介绍，做到读完这段，就能对模块有初步了解，让客户懂的用这个模块能干什么（数据手册通常比较官方，这里你可以举例子，更场景化）<br>
这个模块的优点，告诉用户为什么要购买这个模块
这里需要显示拍照图片，可以一张图片，可以多张图片（不要用SVG图）

![正反面svg效果图](https://github.com/ouki-wang/DFRobot_Sensor/raw/master/resources/images/SEN0245svg1.png)


## 产品链接（链接到英文商城）
    SKU：产品名称
    
## Table of Contents

* [Summary](#summary)
* [Installation](#installation)
* [Methods](#methods)
* [Compatibility](#compatibility)
* [History](#history)
* [Credits](#credits)

## Summary

这里填写当前Arduino软件库完成了基础功能，特色功能

## Installation

To use this library, first download the library file, paste it into the \Arduino\libraries directory, then open the examples folder and run the demo in the folder.

## Methods

```C++
  
  /**
  * @brief ST7789初始化
  * @param reg  寄存器地址 8bits
  * @param pBuf 要写入数据的存放缓存
  * @param size 要写入数据的长度
  */
  void st7789_init(void);
  
  /**
  * @brief 屏幕初始化命令函数
  * @param cmd_addr 就是初始化命令列表cmd_240x240[]的地址
  */
  void displayInit(const uint8_t *cmd_addr);
  
  /**
  * @brief 初始化屏幕
  * @param x0 列开始的位置
  * @param x1 列结束的位置
  * @param y0 行开始的位置
  * @param y1 行结束的位置
  */
  void setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
  
  /**
  * @brief 填充矩形
  * @param x 矩形列开始的位置
  * @param y 矩形行开始的位置
  * @param w 矩形的长
  * @param h 矩形的高
  * @param color 填充的颜色
  */
  void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
  
  /**
  * @brief 全屏填充
  * @param color 填充的颜色
  */
  void fillScreen(uint16_t color);
```

## Compatibility

MCU                | Work Well    | Work Wrong   | Untested    | Remarks
------------------ | :----------: | :----------: | :---------: | -----
Arduino uno        |      √       |              |             | 
Mega2560        |      √       |              |             | 
Leonardo        |      √       |              |             | 
mPython/ESP32        |      √       |              |             | 
micro:bit        |      √       |              |             | 


## History

- data 2021-3-30
- version V0.1


## Credits

Written by qsj(qsj.huang@dfrobot.com), 2021. (Welcome to our [website](https://www.dfrobot.com/))





