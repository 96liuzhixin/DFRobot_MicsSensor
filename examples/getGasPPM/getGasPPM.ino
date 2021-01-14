 /*!
  * @file  getGasPPM.ino
  * @brief Reading Gas concentration, A concentration of one part per million (PPM).
  * @n step: we must first determine the iic device address, will dial the code switch A0, A1 (ADDRESS_0 for [0 0]), (ADDRESS_1 for [1 0]), (ADDRESS_2 for [0 1]), (ADDRESS_3 for [1 1]).
  *
  * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  * @licence     The MIT License (MIT)
  * @author      ZhixinLiu(zhixin.liu@dfrobot.com)
  * @version     V1.0
  * @date        2021-01-13
  * @get         from https://www.dfrobot.com
  * @url         https://github.com/dfrobot/DFRobot_Mics
  */

#include "DFRobot_MicsSensor.h"

#define COLLECT_NUMBER     5                      // collect number, the collection range is 1-100
#define CALIBRATION_TIME   3                      // Default calibration time is three minutes
#define Mics_I2C_ADDRESS   ADDRESS_3
/*   iic slave Address, The default is ADDRESS_3
       ADDRESS_0               0x75             // i2c device address
       ADDRESS_1               0x76
       ADDRESS_2               0x77
       ADDRESS_3               0x78
*/
DFRobot_Mics_I2C Mics(&Wire ,Mics_I2C_ADDRESS);

void setup() 
{
  Serial.begin(115200);
  while(!Mics.begin())
  {
    Serial.println("NO Deivces !");
    delay(1000);
  }
  Serial.println("Device connected successfully !");
  
  Serial.println("Start calibration Sensor!");
  /* Do not touch the sensor probe when calibrating the sensor.
     Place the sensor in clean air. 
     The default calibration time is three minutes.
  */
  while(!Mics.calibrationSensor(CALIBRATION_TIME)){
    Serial.println("Please wait calibration!");
    delay(1000);
  }
  Serial.println("calibration success!");
}

void loop() 
{
/*
  Gas type
    Methane          (CH4)    (1000 - 25000)PPM
    Ethanol          (C2H5OH) (10   - 500)PPM
    Hydrogen         (H2)     (1    - 1000)PPM
    Ammonia          (NH3)    (1    - 500)PPM
    Carbon Monoxide  (CO)     (1    - 1000)PPM
    Nitrogen Dioxide (NO2)    (0.1  - 10)PPM
*/
  float gasdata = Mics.readGasData(H2);
  if(gasdata == ERROR){
    Serial.println("error! Please try again ");
  }else{
    Serial.print(gasdata,1);
    Serial.println(" PPM");
  }
  delay(1000);
}