# DFRobot_MicsSensor
DFRobot's AlcoholSensor

## DFRobot_MicsSensor Library for Arduino
---------------------------------------------------------
Arduino library is provided for reading alcohol concentrations through I2C or uart.
Used to read the alcohol concentrations of the current module


## Table of Contents

* [Installation](#installation)
* [Methods](#methods)
* [Compatibility](#compatibility)
* [History](#history)
* [Credits](#credits)

<snippet>
<content>

## Installation

To use this library download the zip file, uncompress it to a folder named DFRobot_MicsSensor.
Download the zip file first to use this library and uncompress it to a folder named DFRobot_MicsSensor.

## Methods

```C++
 /*
  * @brief read Sersor ADC data.
  * @param type is OX_MODE(Oxidation ADC)
  *                RED_MODE(Restore ADC)
  * @return ADC data.
  */
   int16_t readSensorData(uint8_t type);

 /*
  * @brief read Gas concentration data.
  * @param type is Methane          (CH4)
  *                Ethanol          (C2H5OH)
  *                Hydrogen         (H2)
  *                Ammonia          (NH3)
  *                Carbon Monoxide  (CO)
  *                Nitrogen Dioxide (NO2)
  * @return Gas concentration: one part per million (PPM).
  */
   float readGasData(uint8_t type);

 /*
  * @brief Read if gas is present.
  * @param GAs is  Hydrothion       (H2S)
  *                Nitric Oxide     (NO)
  *                Propane          (C3H8)
  *                Iso Butane       (C4H10)
  *                Methane          (CH4)
  *                Ethanol          (C2H5OH)
  *                Hydrogen         (H2)
  *                Ammonia          (NH3)
  *                Carbon Monoxide  (CO)
  *                Nitrogen Dioxide (NO2)
  * @return EXIST is gas exist,NO_EXIST is gas no exist.
  */
   int8_t readGasExist(uint8_t gas);
  
```
## Compatibility

MCU                | Work Well | Work Wrong | Untested  | Remarks
------------------ | :----------: | :----------: | :---------: | -----
FireBeetle-ESP32  |      √       |             |            | 
FireBeetle-ESP8266  |      √       |             |            | 
ATMEGA2560  |      √       |             |            | 
Arduino uno |       √      |             |            | 
Leonardo  |      √       |              |             | 

## History

- January 13, 2021 - Version 1.0 released.


## Credits

Written by ZhixinLiu(zhixin.liu@dfrobot.com), 2021. (Welcome to our [website](https://www.dfrobot.com/))