# -*- coding:utf-8 -*-
""" 
  @file get_mics_adc_data.py
  @brief Read sensor red and ox adc.
  @n step: we must first determine the i2c device address, will dial the code switch A0, A1 (ADDRESS_0 for [0 0]), (ADDRESS_1 for [1 0]), (ADDRESS_2 for [0 1]), (ADDRESS_3 for [1 1]).
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

I2C_MODE         = 0x01            # default use I2C1
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

while(1):
  '''
    # read sensor adc data
      # OX_MODE   = 0x00
      # RED_MODE  = 0x01
  '''
  mics_adc_data = mics.read_sensor_data(OX_MODE);
  print "mics adc is %d"%mics_adc_data
  time.sleep(1)