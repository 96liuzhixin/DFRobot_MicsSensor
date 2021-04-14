#ifndef __DFROBOT_MICS_H__
#define __DFROBOT_MICS_H__
#include <Arduino.h>
#include <Wire.h>

#define           ADDRESS_0                 0x75
#define           ADDRESS_1                 0x76
#define           ADDRESS_2                 0x77
#define           ADDRESS_3                 0x78           // iic slave Address

#define           OX_REGISTER_HIGH          0x04           //
#define           OX_REGISTER_LOW           0x05           //
#define           RED_REGISTER_HIGH         0x06           //
#define           RED_REGISTER_LOW          0x07           //
#define           POWER_REGISTER_HIGH       0x08           //
#define           POWER_REGISTER_LOW        0x09           //
#define           POWER_MODE_REGISTER       0x0a           //

#define           SLEEP_MODE                0x00
#define           WAKE_UP_MODE              0x01

#define           OX_MODE                   0x00
#define           RED_MODE                  0x01

#define           ERROR                     -1
#define           EXIST                     0x00
#define           NO_EXIST                  0x02

#define           CO                        0x01          // Carbon Monoxide
#define           CH4                       0x02          // Methane
#define           C2H5OH                    0x03          // Ethanol
#define           C3H8                      0x04          // Propane
#define           C4H10                     0x05          // Iso Butane
#define           H2                        0x06          // Hydrogen
#define           H2S                       0x07          // Hydrothion
#define           NH3                       0x08          // Ammonia
#define           NO                        0x09          // Nitric Oxide
#define           NO2                       0x0A          // Nitrogen Dioxide


class DFRobot_Mics{
public:
  DFRobot_Mics();
  ~DFRobot_Mics();
  bool     calibrationSensor(uint8_t minute);
  int16_t  readSensorData(uint8_t mode);
  float    readGasData(uint8_t type);
  int8_t   readGasExist(uint8_t gas);
  void     sleepMode(void);
  void     wakeUpMode(void);
  uint8_t  getPowerState(void);
private:
  int16_t  __r0_ox   = 0;
  int16_t  __r0_red  = 0;
  uint32_t __nowTime = 0;
  uint8_t  __flag    = 0;
  int16_t  getSensorData(uint16_t *oxData ,uint16_t *redData ,uint16_t *powerData);
  float    getCarbonMonoxide(float data);
  float    getMethane(float data);
  float    getEthanol(float data);
  float    getHydrogen(float data);
  float    getAmmonia(float data);
  float    getNitrogenDioxide(float data);
  bool     existPropane(float data);
  bool     existNitricOxide(float data);
  bool     existIsoButane(float data);
  bool     existHydrothion(float data);
  bool     existCarbonMonoxide(float data);
  bool     existMethane(float data);
  bool     existEthanol(float data);
  bool     existHydrogen(float data);
  bool     existAmmonia(float data);
  bool     existNitrogenDioxide(float data);
  virtual void writeData(uint8_t Reg ,uint8_t *Data ,uint8_t len) = 0;
  virtual int16_t readData(uint8_t Reg ,uint8_t *Data ,uint8_t len) = 0;
};

class DFRobot_Mics_I2C:public DFRobot_Mics{
public:
  DFRobot_Mics_I2C(TwoWire *pWire=&Wire ,uint8_t addr = ADDRESS_3);
  bool begin(void);
protected:
  virtual void writeData(uint8_t Reg ,uint8_t *Data ,uint8_t len);
  virtual int16_t readData(uint8_t Reg ,uint8_t *Data ,uint8_t len);
private:
  TwoWire *_pWire;
  uint8_t _I2C_addr;
};

#endif