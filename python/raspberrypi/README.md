# DFRobot mics concentration sensor

This RaspberryPi mics sensor board can communicate with RaspberryPi via I2C.<br>
mics sensor Long service life.<br>

## DFRobot mics Library for RaspberryPi

Provide the Raspberry Pi library for the DFRobot_micsSensor module.

## Table of Contents

* [Summary](#summary)
* [Feature](#feature)
* [Installation](#installation)
* [Methods](#methods)
* [History](#history)
* [Credits](#credits)

## Summary

mics module.

## Feature

1. The module has two modes, one is active data acquisition and the other is passive data acquisition. <br>
2. You can measure the concentration of (co no no2 h2 ch4 c2h5oh) in the air. <br>

## Installation

This Sensor should work with DFRobot_NicsSensor on RaspberryPi. <br>
Run the program:

```
$> python get_mics_data.py
$> python get_mics_data.py
$> python get_mics_data.py
```

## Methods

```py

  def read_gas_exist(self ,gas_type):
    '''
      @brief Detect the presence of gas
      @param gas_type is gas type
      @return Whether gas is present
    '''

  def read_sensor_data(self ,mode):
    '''
      @brief set the mode to read the data
      @param mode OX_MODE or RED_MODE
      @return adc data
    '''

  def read_gas_data(self ,gas_type):
    '''
      @brief get the gas data ,units of PPM
      @param gas_type is gas type
      @return gas concentration, (units PPM)
    '''

  def calibrationSensor(self ,minute):
    '''
      @brief calibration sensor
      @param minute is calibration time
    '''

```
## History

January 14, 2021 - Version 1.0 released.

## Credits

Written by ZhixinLiu(zhixin.liu@dfrobot.com), 2021. (Welcome to our website)