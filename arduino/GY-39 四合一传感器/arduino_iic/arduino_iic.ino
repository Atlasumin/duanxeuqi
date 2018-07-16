#include <Wire.h>
//#include <i2cmaster.h>
/////////////////////////////////
/*
GY-39-----mini
VCC----VCC
SCL(CT)----SCL
SDA(DR)----SDA
GND--GND
*/
//////////////////////////////////
#define uint16_t unsigned int
#define iic_add  0x5b //先定好头地址
typedef struct
{
    uint32_t P;
    uint16_t Temp;
    uint16_t Hum;
    uint16_t Alt;
} bme;

bme Bme;
  uint32_t Lux;

void i2c_speed(uint16_t scl_speed)
{
  /* 初始化TWI时钟: 时钟-40 kHz, TWPS = 0 => 预分频器 = 1 */
  
  TWSR = 0;                         /* 无预分频器 */
  TWBR = ((F_CPU/scl_speed)-16)/2;  /* 稳定运行的要求必须 >10 */

}
void setup() {
       Serial.begin(115200);
       Wire.begin();
       i2c_speed(40000);
       delay(1); 
}
void loop() {
    //获得到的值需要除以100
    get_bme();
      Serial.print("温度: ");
        Serial.print( (float)Bme.Temp/100);
      Serial.print(" 气压: ");
        Serial.print( ((float)Bme.P)/100);
      Serial.print(" 湿度: ");
        Serial.print( (float)Bme.Hum/100);
      Serial.print(" 海拔:");
        Serial.print( Bme.Alt);
        Serial.println("m");
    get_lux();
      Serial.print( "Lux: ");
      Serial.println( ((float)Lux)/100);
      Serial.println("lux");
    delay(1000); 
}
void get_bme(void)//获取bme中的温度，气压，湿度，海拔
{
    uint16_t data_16[2]={0};
    uint8_t data[10]={0};
    iic_read(0x04,data,10);
    Bme.Temp=(data[0]<<8)|data[1];//从寄存器中读取温度，根据其地址所在位截取
      data_16[0]=(data[2]<<8)|data[3];
      data_16[1]=(data[4]<<8)|data[5];
    Bme.P=(((uint32_t)data_16[0])<<16)|data_16[1];//从寄存器中读取气压，根据其地址所在位截取
    Bme.Hum=(data[6]<<8)|data[7];//从寄存器中读取湿度，根据其地址所在位截取
    Bme.Alt=(data[8]<<8)|data[9];//从寄存器中读取海拔，根据其地址所在位截取
}
void get_lux(void)//获取光照强度值
{     
    uint16_t data_16[2]={0};
    uint8_t data[10]={0};

    iic_read(0x00,data,4);
      data_16[0]=(data[0]<<8)|data[1];
      data_16[1]=(data[2]<<8)|data[3];
    Lux=(((uint32_t)data_16[0])<<16)|data_16[1];
    //根据光照所在的地址位来获取数值
}
void iic_read(unsigned char reg,unsigned char *data,uint8_t len )
{
   Wire.beginTransmission(iic_add);  
   Wire.write(reg); 
   Wire.endTransmission(false);
   delayMicroseconds(10);
   if(len>4)
     Wire.requestFrom(iic_add,10);     
   else
     Wire.requestFrom(iic_add,4);
   for (uint8_t i = 0; i < len; i++)
    {  
       data[i] = Wire.read(); 
   }
  
}
