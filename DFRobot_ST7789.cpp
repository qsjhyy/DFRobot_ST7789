/*!
 * @file DFRobot_ST7789.cpp
 * @brief (仿写、学习)定义DFRobot_ST7789
 * @copyright Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence The MIT License (MIT)
 * @author [qsj](qsj.huang@dfrobot.com)
 * @version V0.1
 * @date 2021-03-30
 * @get from https://www.dfrobot.com
 * @url https://github.com/qsjhyy/DFRobot_ST7789
 */
#include <DFRobot_ST7789.h>

DFRobot_ST7789::DFRobot_ST7789(SPIClass *pSpi, uint8_t dcPin, uint8_t csPin, uint8_t resPin)
{
  // 引脚初始化
  _pSpi = pSpi;
  _csPin   = csPin;
  _dcPin   = dcPin;
  _resPin  = resPin;
  
  //屏幕尺寸
  _width = 240;
  _height = 240;
  
  mySPISettings = SPISettings(24000000, MSBFIRST, SPI_MODE2);
}

// pgm_read_byte(), 该模块的功能为程序提供了访问存储在设备程序空间(flash memory)中的数据的接口。
void DFRobot_ST7789::displayInit(const uint8_t *cmd_addr)
{
  uint8_t  numCommands, numArgs;
  uint16_t ms;
  
  //digitalWrite(_dc, HIGH);
  numCommands = pgm_read_byte(cmd_addr++);   // 读取命令列表第一个数据（表示列表中有几条命令的数据）
  while (numCommands--) {
    writecommand(pgm_read_byte(cmd_addr++));   // 写入命令
    numArgs = pgm_read_byte(cmd_addr++);
    ms = numArgs & ST_CMD_DELAY;
    numArgs &= (uint8_t)~ST_CMD_DELAY;
    
    while (numArgs--) {
      writedata(pgm_read_byte(cmd_addr++), 8);   // 写入数据
    }
    if (ms) {
      ms = pgm_read_byte(cmd_addr++);
      if (ms == 255)
        ms = 500;
      delay(ms);   // 延时
    }
  }
}

void DFRobot_ST7789::st7789_init()   // 芯片初始化
{
  // 引脚和SPI的设定
  _pSpi->begin();
  pinMode(_csPin, OUTPUT);
  pinMode(_dcPin, OUTPUT);
  pinMode(_resPin, OUTPUT);

  _pSpi->beginTransaction(mySPISettings);

  // 屏幕重启
  digitalWrite(_csPin, LOW);
  digitalWrite(_resPin, HIGH);
  delay(50);
  digitalWrite(_resPin, LOW);
  delay(50);
  digitalWrite(_resPin, HIGH);
  delay(50);
  
  displayInit(cmd_240x240);//*cmd_addr cmd_240x240

  writedata(ST7789_MADCTL_RGB, 8);//0x00

}

// brief 初始化屏幕
void DFRobot_ST7789::setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
  writecommand(ST7789_CA_SET);
  writedata(x0, 16);
  writedata(x1, 16);

  writecommand(ST7789_RA_SET);
  writedata(y0, 16);
  writedata(y1, 16);

  writecommand(ST7789_RAM_WR); 
}

// 填充矩形
void  DFRobot_ST7789::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
  if ((x >= _width) || (y >= _height)) return;
  if ((x + w - 1) >= _width)  w = _width  - x;
  if ((y + h - 1) >= _height) h = _height - y;

  setAddrWindow(x, y, x + w - 1, y + h - 1);

  for (y = h; y > 0; y--){
    for (x = w; x > 0; x--){
      writedata(color, 16);
    }
  }
}

// 全屏填充
void DFRobot_ST7789::fillScreen(uint16_t color)
{
  fillRect(0, 0, _width, _height, color);
}

// dc值决定是写入命令还是写入数据
void DFRobot_ST7789::writecommand(int cmd)
{
  digitalWrite(_dcPin, LOW);
  _pSpi->beginTransaction(mySPISettings);
  digitalWrite(_csPin, LOW);
  
  uint8_t _cmd = (uint8_t)cmd;
  _pSpi->transfer(_cmd);
  
  digitalWrite(_csPin, HIGH);
  _pSpi->endTransaction();
}

void DFRobot_ST7789::writedata(uint16_t data, size_t size)
{
  _pSpi->beginTransaction(mySPISettings);
  digitalWrite(_dcPin, HIGH);
  digitalWrite(_csPin, LOW);
  
  if(16 == size){
    uint8_t high8bytes = data >> 8, low8bytes = data & 0xFF;
    _pSpi->transfer(high8bytes);
    _pSpi->transfer(low8bytes);
  }else{
    uint8_t _data = (uint8_t )data;
    _pSpi->transfer(_data);
  }
  
  digitalWrite(_csPin, HIGH);
  _pSpi->endTransaction();
}
