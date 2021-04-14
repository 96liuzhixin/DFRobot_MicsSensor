#include "DFRobot_MicsSensor.h"

DFRobot_Mics::DFRobot_Mics()
{
}

DFRobot_Mics::~DFRobot_Mics()
{
}


bool DFRobot_Mics::calibrationSensor(uint8_t minute)
{
  uint32_t tempTime  = 0;
  uint32_t tempOX    = 0; 
  uint32_t tempRED   = 0;
  uint16_t oxData[1]    = {0x00};
  uint16_t redData[1]   = {0x00};
  uint16_t powerData[1] = {0x00};
  uint32_t delayTime    = 0;
  uint32_t excessTime   = 0;
  if(__flag == 0){
    __flag = 1;
    __nowTime = millis();
  }
  delayTime  = minute * 60000;
  excessTime = millis() - __nowTime;
  if(excessTime < delayTime){
    return false;
  }
  if(getSensorData(oxData ,redData, powerData) == ERROR){
    return false;
  }
  __r0_ox  = powerData[0] - oxData[0];
  __r0_red = powerData[0] - redData[0];
  return true;
}

int16_t DFRobot_Mics::readSensorData(uint8_t mode)
{
  uint16_t oxData[1]    = {0x00};
  uint16_t redData[1]   = {0x00};
  uint16_t powerData[1] = {0x00};
  if(getSensorData(oxData ,redData, powerData) == ERROR){
    return ERROR;
  }
  float RS_R0_RED_data = (float)(powerData[0] - redData[0]);
  float RS_R0_OX_data = (float)(powerData[0] - oxData[0]);
  if(mode == OX_MODE){
    return RS_R0_OX_data;
  }else if(mode == RED_MODE){
    return RS_R0_RED_data;
  }else{
    return ERROR;
  }
}


void DFRobot_Mics::sleepMode(void)
{
  uint8_t regData = SLEEP_MODE;
  writeData(POWER_MODE_REGISTER, &regData, 1);
  delay(100);
}

void DFRobot_Mics::wakeUpMode(void)
{
  uint8_t regData = WAKE_UP_MODE;
  writeData(POWER_MODE_REGISTER, &regData, 1);
  delay(100);
}

uint8_t DFRobot_Mics::getPowerState(void)
{
  uint8_t regData;
  readData(POWER_MODE_REGISTER, &regData, (uint8_t)1);
  return regData;
}

int8_t DFRobot_Mics::readGasExist(uint8_t gas)
{
  uint16_t oxData[1]    = {0x00};
  uint16_t redData[1]   = {0x00};
  uint16_t powerData[1] = {0x00};
  if(getSensorData(oxData ,redData, powerData) == ERROR){
    return ERROR;
  }
  float RS_R0_RED_data = (float)(powerData[0] - redData[0]) / (float)__r0_red;
  float RS_R0_OX_data = (float)(powerData[0] - oxData[0]) / (float)__r0_ox;
  switch(gas)
  {
    case C3H8:
      if(existPropane(RS_R0_RED_data)){
        return EXIST;
      }else{
        return NO_EXIST;
      }
      break;
    case C4H10:
      if(existIsoButane(RS_R0_RED_data)){
        return EXIST;
      }else{
        return NO_EXIST;
      }
      break;
    case H2S:
      if(existHydrothion(RS_R0_RED_data)){
        return EXIST;
      }else{
        return NO_EXIST;
      }
      break;
    case NO:
      if(existNitricOxide(RS_R0_RED_data)){
        return EXIST;
      }else{
        return NO_EXIST;
      }
      break;
    case CO:
      if(existCarbonMonoxide(RS_R0_RED_data)){
        return EXIST;
      }else{
        return NO_EXIST;
      }
      break;
    case CH4:
      if(existMethane(RS_R0_RED_data)){
        return EXIST;
      }else{
        return NO_EXIST;
      }
      break;
    case C2H5OH:
      if(existEthanol(RS_R0_RED_data)){
        return EXIST;
      }else{
        return NO_EXIST;
      }
      break;
    case H2:
      if(existHydrogen(RS_R0_RED_data)){
        return EXIST;
      }else{
        return NO_EXIST;
      }
      break;
    case NH3:
      if(existAmmonia(RS_R0_RED_data)){
        return EXIST;
      }else{
        return NO_EXIST;
      }
      break;
    case NO2:
      if(existNitrogenDioxide(RS_R0_OX_data)){
        return EXIST;
      }else{
        return NO_EXIST;
      }
      break;
    default:
      return ERROR;
      break;
  }
}

float DFRobot_Mics::readGasData(uint8_t type)
{
  uint16_t oxData[1]    = {0x00};
  uint16_t redData[1]   = {0x00};
  uint16_t powerData[1] = {0x00};
  if(getSensorData(oxData ,redData, powerData) == ERROR){
    return ERROR;
  }
  float RS_R0_RED_data = (float)(powerData[0] - redData[0]) / (float)__r0_red;
  float RS_R0_OX_data = (float)(powerData[0] - oxData[0]) / (float)__r0_ox;
  switch(type){
    case CO:
      return getCarbonMonoxide(RS_R0_RED_data);
      break;
    case CH4:
      return getMethane(RS_R0_RED_data);
      break;
    case C2H5OH:
      return getEthanol(RS_R0_RED_data);
      break;
    case H2:
      return getHydrogen(RS_R0_RED_data);
      break;
    case NH3:
      return getAmmonia(RS_R0_RED_data);
      break;
    case NO2:
      return getNitrogenDioxide(RS_R0_OX_data);
      break;
    default:
      return ERROR;
      break;
  }
}

float DFRobot_Mics::getCarbonMonoxide(float data)
{
  if(data > 0.425)
    return 0.0;
  float co = (0.425 - data) / 0.000405;
  if(co > 1000.0)
    return 1000.0;
  if(co < 1.0) 
    return 0.0;
  return co;
}

float DFRobot_Mics::getEthanol(float data)
{
  if(data > 0.306)
    return 0.0;
  float ethanol = (0.306 - data) / 0.00057;
  if(ethanol < 10.0) 
    return 0.0;
  if(ethanol > 500.0) 
    return 500.0;
  return ethanol;
}

float DFRobot_Mics::getMethane(float data)
{
  if(data > 0.786)
    return 0.0;
  float methane = (0.786 - data) / 0.000023;
  if(methane < 1000.0) methane = 0.0;
  if(methane > 25000.0) methane = 25000.0;
  return methane;
}


float DFRobot_Mics::getNitrogenDioxide(float data)
{
  if(data < 1.1) return 0;
  float nitrogendioxide = (data - 0.045) / 6.13;
  if(nitrogendioxide < 0.1)
    return 0.0;
  if(nitrogendioxide > 10.0)
    return 10.0;
  return nitrogendioxide;
}

float DFRobot_Mics::getHydrogen(float data)
{
  if(data > 0.279)
    return 0.0;
  float hydrogen = (0.279 - data) / 0.00026;
  if(hydrogen < 1.0) 
    return 0.0;
  if(hydrogen > 1000.0) 
    return 1000.0;
  return hydrogen;
}

float DFRobot_Mics::getAmmonia(float data)
{
  if(data > 0.8)
    return 0.0;
  float ammonia = (0.8 - data) / 0.0015;
  if(ammonia < 1.0) 
    return 0.0;
  if(ammonia > 500.0) 
    return 500.0;
  return ammonia;
}

bool DFRobot_Mics::existIsoButane(float data)
{
  if(data > 0.65){
    return false;
  }else{
    return true;
  }
}

bool DFRobot_Mics::existPropane(float data)
{
  if(data > 0.18){
    return false;
  }else{
    return true;
  }
}

bool DFRobot_Mics::existHydrothion(float data)
{
  if(data > 0.58 && data < 0.69){
    return true;
  }
  if(data < 0.201){
    return true;
  }
  return false;
}

bool DFRobot_Mics::existNitricOxide(float data)
{
  if(data > 0.8){
    return false;
  }else{
    return true;
  }
}

bool DFRobot_Mics::existCarbonMonoxide(float data)
{
  if(data > 0.425){
    return false;
  }else{
    return true;
  }
}

bool DFRobot_Mics::existMethane(float data)
{
  if(data > 0.786){
    return false;
  }else{
    return true;
  }
}

bool DFRobot_Mics::existEthanol(float data)
{
  if(data > 0.306){
    return false;
  }else{
    return true;
  }
}

bool DFRobot_Mics::existHydrogen(float data)
{
  if(data > 0.279){
    return false;
  }else{
    return true;
  }
}

bool DFRobot_Mics::existAmmonia(float data)
{
  if(data > 0.8){
    return false;
  }else{
    return true;
  }
}

bool DFRobot_Mics::existNitrogenDioxide(float data)
{
  if(data < 1.1){
    return false;
  }else{
    return true;
  }
}

int16_t DFRobot_Mics::getSensorData(uint16_t *oxData ,uint16_t *redData ,uint16_t *powerData)
{
  uint8_t recv_data[20] = {0x00};
  if(readData(OX_REGISTER_HIGH ,recv_data ,(uint8_t)6) == ERROR){
    return ERROR;
  }
  oxData[0]    = (((uint16_t)recv_data[0] << 8) + (uint16_t)recv_data[1]);
  redData[0]   = (((uint16_t)recv_data[2] << 8) + (uint16_t)recv_data[3]);
  powerData[0] = (((uint16_t)recv_data[4] << 8) + (uint16_t)recv_data[5]);
  return 0;
}

DFRobot_Mics_I2C::DFRobot_Mics_I2C(TwoWire *pWire, uint8_t addr)
{
  _pWire = pWire;
  this->_I2C_addr = addr;
}

bool DFRobot_Mics_I2C::begin()
{
  _pWire->begin();
  _pWire->beginTransmission(_I2C_addr);
  if(_pWire->endTransmission() == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void DFRobot_Mics_I2C::writeData(uint8_t Reg ,uint8_t *Data ,uint8_t len)
{
  _pWire->beginTransmission(this->_I2C_addr);
  _pWire->write(Reg);
  for(uint8_t i = 0; i < len; i++)
  {
    _pWire->write(Data[i]);
  }
  _pWire->endTransmission();
}

int16_t DFRobot_Mics_I2C::readData(uint8_t Reg,uint8_t *Data,uint8_t len)
{
  int i=0;
  _pWire->beginTransmission(this->_I2C_addr);
  _pWire->write(Reg);
  if(_pWire->endTransmission() != 0)
  {
    return ERROR;
  }
  _pWire->requestFrom((uint8_t)this->_I2C_addr,(uint8_t)len);
  while (_pWire->available())
  {
    Data[i++]=_pWire->read();
  }
  return 0;
}
