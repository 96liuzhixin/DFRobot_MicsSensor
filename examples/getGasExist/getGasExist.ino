 /*!
  * @file  getGasExist.ino
  * @brief Reading Gas concentration, A concentration of one part per million (PPM).
  * @n step: we must first determine the iic device address, will dial the code switch A0, A1 (ADDRESS_0 for [0 0]), (ADDRESS_1 for [1 0]), (ADDRESS_2 for [0 1]), (ADDRESS_3 for [1 1]).
  *
  * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  * @licence     The MIT License (MIT)
  * @author      ZhixinLiu(zhixin.liu@dfrobot.com)
  * @version     V1.0
  * @date        2021-01-13
  * @get         from https://www.dfrobot.com
  * @url         https://github.com/dfrobot/DFRobot_MicsSensor
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
  while(!Mics.begin()){
    Serial.println("NO Deivces !");
    delay(1000);
  } Serial.println("Device connected successfully !");

  // Gets the power mode of the sensor
  uint8_t mode = Mics.getPowerState();
  if(mode == SLEEP_MODE){
    Serial.println("The sensor is sleep mode");
    // The sensor is in sleep mode when power is on, so it needs to wake up the sensor. The data obtained in sleep mode is wrong
    Mics.wakeUpMode();
    Serial.println("wake up sensor success！");
  }else{
    Serial.println("The sensor is wake up mode");
  }

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
  Type of detection gas
    CO       = 0x01  (Carbon Monoxide)
    CH4      = 0x02  (Methane)
    C2H5OH   = 0x03  (Ethanol)
    C3H8     = 0x04  (Propane)
    C4H10    = 0x05  (Iso Butane)
    H2       = 0x06  (Hydrogen)
    H2S      = 0x07  (Hydrothion)
    NH3      = 0x08  (Ammonia)
    NO       = 0x09  (Nitric Oxide)
    NO2      = 0x0A  (Nitrogen Dioxide)
*/
  int8_t gasFlag = Mics.readGasExist(CO);
  if(gasFlag == EXIST){
    Serial.println("The gas exists!");
  }else{
    Serial.println("The gas does not exist!");
  }
  delay(1000);
  //Mics.sleepMode();
}