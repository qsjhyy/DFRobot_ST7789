/*!
 * @file DFRobot_ST7789.h
 * @brief (仿写、学习)定义DFRobot_ST7789
 * @copyright Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence The MIT License (MIT)
 * @author [qsj](qsj.huang@dfrobot.com)
 * @version V0.1
 * @date 2021-03-30
 * @get from https://www.dfrobot.com
 * @url https://github.com/qsjhyy/DFRobot_ST7789
 */
#ifndef __DFROBOT_ST7789_H__
#define __DFROBOT_ST7789_H__

#include <Arduino.h>
#include <SPI.h>

// 打开这个宏，可以看到程序的详细运行过程
#define ENABLE_DBG
/*
__LINE__ 编译时的行号，十进制数
__FUNCTION__ 编译时的函数名，字符串类型
__VA_ARGS__ 可变参数宏，用于可变参数的函数，如printf()。作用类似"..."，这里就用它来替换DBG(…)里的省略号，可以打印出DBG()里的参数
*/
#ifdef ENABLE_DBG
#define DBG(...) {Serial.print("[");Serial.print(__FUNCTION__); Serial.print("(): "); Serial.print(__LINE__); Serial.print(" ] "); Serial.println(__VA_ARGS__);}
#else
#define DBG(...)
#endif

// 定义屏幕的宽和高（尺寸）
#define ST7789_TFT_WIDTH   240
#define ST7789_TFT_HEIGHT  240

#define ST7789_240x240_XSTART 0
#define ST7789_240x240_YSTART 0

#define ST_CMD_DELAY    0x80  

#define ST7789_NOP      0x00  // 该命令为空命令
#define ST7789_SW_RESET 0x01  // Software Reset，软件复位 
#define ST7789_RDD_ID   0x04  // Read Display ID，显示id 
#define ST7789_RDD_ST   0x09  // Read Display Status，显示状态 

#define ST7789_SLP_IN   0x10  // Sleep in，进入睡眠模式 
#define ST7789_SLP_OUT  0x11  // Sleep Out
#define ST7789_PTL_ON   0x12  // Partial Display Mode On，部分显示模式开启
#define ST7789_NOR_ON   0x13  // Normal Display Mode On，正常显示模式开启

#define ST7789_INV_OFF  0x20  // Display Inversion，显示反转关
#define ST7789_INV_ON   0x21  
#define ST7789_DIS_OFF  0x28  // Display，显示关闭
#define ST7789_DIS_ON   0x29  
#define ST7789_CA_SET   0x2A  // Column Address Set，设置列地址
#define ST7789_RA_SET   0x2B  // Row Address Set，设置行地址
#define ST7789_RAM_WR   0x2C  // Memory Write，内存写入
#define ST7789_RAM_RD   0x2E  // Memory Read，内存读取

#define ST7789_PTL_AR   0x30  // Partial Area，局部区域 4个参数
#define ST7789_COL_MOD  0x3A  // Set color mode，颜色模式 接口像素格式

#define ST7789_MADCTL     0x36  // Memory Data Access Control，内存数据访问控制
#define ST7789_MADCTL_MY  0x80  // D7:
#define ST7789_MADCTL_MX  0x40  // D6：
#define ST7789_MADCTL_MV  0x20  // D5：
#define ST7789_MADCTL_ML  0x10  // D4：
#define ST7789_MADCTL_RGB 0x00  // D3:

static SPISettings mySPISettings;

// 屏幕初始化命令列表
// 定义较大的全局常量（比如此数组）时，使用 PROGMEM 关键字，告诉编译器 “ 把这个信息存到程序存储空间 ”，而不是存到“ 动态内存 ”。
static const uint8_t PROGMEM cmd_240x240[] = {
    9, // 总共9个7789屏幕的初始化命令
  ST7789_SW_RESET, ST_CMD_DELAY,      // 1: 软件复位, 无参数, 为写入命令延时:
    150,
  ST7789_SLP_OUT,  ST_CMD_DELAY,      // 2: 退出睡眠模式, 无参数, 为写入命令延时:
    255,
  ST7789_COL_MOD,  1 + ST_CMD_DELAY,  // 3: 设置颜色模式, 无参数 + 延时:
    0x55,
    10,
  ST7789_MADCTL,   1,                 // 4: 内存数据访问控制 (directions), 1 参数, 没有延时:
    0x00,
  ST7789_CA_SET,   4,                 // 5: 设置列地址, 4 参数, 没有延时:
    0x00,
    ST7789_240x240_XSTART,
    (ST7789_TFT_WIDTH + ST7789_240x240_XSTART) >> 8,
    (ST7789_TFT_WIDTH + ST7789_240x240_XSTART) & 0xFF,
  ST7789_RA_SET,   4,                 // 6: 设置行地址, 4 参数, 没有延时:
    0x00,
    ST7789_240x240_YSTART,
    (ST7789_TFT_HEIGHT + ST7789_240x240_YSTART) >> 8,
    (ST7789_TFT_HEIGHT + ST7789_240x240_YSTART) & 0xFF,
  ST7789_INV_ON,   ST_CMD_DELAY,      // 7: 显示反转开, 无参数, 为写入命令延时:
    10,
  ST7789_NOR_ON,   ST_CMD_DELAY,      // 8: 正常显示模式开启, 无参数, 为写入命令延时:
    10,
  ST7789_DIS_ON,   ST_CMD_DELAY,      // 9: 打开注屏幕, 无参数, 为写入命令延时:
    255
};

class DFRobot_ST7789
{
public:
  /**
  * @brief 构造函数
  * @param pSpi SPI.h里定义了extern SPIClass SPI;因此取SPI对象的地址就能够指向并使用SPI中的方法
  * @param csPin 是指定cs接的数字引脚
  * @param resPin 是ST7789的重置/初始化引脚
  * @param dcPin 是ST7789通讯时判断写入的是命令还是数据的引脚
  */
  DFRobot_ST7789(SPIClass *pSpi=&SPI, uint8_t dcPin=2, uint8_t csPin=3, uint8_t resPin=4);
  
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
  
protected:
  /**
  * @brief 通过SPI总线对ST7789写入命令
  * @param pBuf 要写入命令的存放缓存
  */
  void writecommand(int cmd);
  
  /**
  * @brief 通过SPI总线对ST7789写入数据
  * @param pBuf 要写入数据的存放缓存
  * @param size 要写入数据的长度
  */
  void writedata(uint16_t data, size_t size);
  
private:
  SPIClass *_pSpi;   // SPI通信方式的指针
  uint16_t _width, _height;   // 屏幕尺寸
  uint8_t _csPin, _dcPin, _resPin;   // 片选引脚，命令/数据引脚，复位/初始化引脚
};
#endif
