# -*- coding:utf-8 -*-
""" 
  @file get_gas_exist.py
  @brief Read if gas is present.
  @n step: we must first determine the i2c device address, will dial the code switch A0, A1 (ADDRESS_0 for [0 0]), (ADDRESS_1 for [1 0]), (ADDRESS_2 for [0 1]), (ADDRESS_3 for [1 1]).
  @n       Then wait for the calibration to succeed.
  @n       The calibration time is approximately three minutes.
  @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  @licence     The MIT License (MIT)
  @author      [ZhixinLiu](zhixin.liu@dfrobot.com)
  version  V1.0
  date  2021-01-14
  @get from https://www.dfrobot.com
  @url https://github.com/DFRobot/DFRobot_MicsSensor
"""
import sys
sys.path.append("../..")
from DFRobot_Mics import *

CALIBRATION_TIME      = 0x03       # calibration time
I2C_MODE              = 0x01       # default use I2C1
'''
   # The first  parameter is to select i2c0 or i2c1
   # The second parameter is the i2c device address
   # The default address for i2c is ADDRESS_3
   # ADDRESS_0                 = 0x75
   # ADDRESS_1                 = 0x76
   # ADDRESS_2                 = 0x77
   # ADDRESS_3                 = 0x78
'''
mics = DFRobot_Mics_I2C (I2C_MODE ,ADDRESS_3)
time.sleep(1)
'''
  # The default calibration time of the sensor is three minutes
    # CALIBRATION_TIME = 0x03
'''
mics.calibrationSensor(CALIBRATION_TIME)

while(1):
  '''
    # Type of detection gas
      # CO       = 0x01  (Carbon Monoxide)
      # CH4      = 0x02  (Methane)
      # C2H5OH   = 0x03  (Ethanol)
      # C3H8     = 0x04  (Propane)
      # C4H10    = 0x05  (Iso Butane)
      # H2       = 0x06  (Hydrogen)
      # H2S      = 0x07  (Hydrothion)
      # NH3      = 0x08  (Ammonia)
      # NO       = 0x09  (Nitric Oxide)
      # NO2      = 0x0A  (Nitrogen Dioxide)
  '''
  if mics.read_gas_exist(CO) == ERROR:
    print "This gas does not exist!"
  else:
    print "This gas exists!"
  time.sleep(1)