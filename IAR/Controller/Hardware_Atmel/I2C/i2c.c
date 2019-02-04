#include "..\..\System\main.h"
#include "inavr.h"
#include <iom128.h>
//-----------------------------------------------------------------------------
void i2c_set_bitrate(usint bitrateKHz)
{
  uchar bitrate_div;
   ClearBit(TWSR,TWPS0);
   ClearBit(TWSR,TWPS1);
  // calculate bitrate division
  bitrate_div = ((CPU_CLOCK/1000l)/bitrateKHz);
  if (bitrate_div >= 16)
   bitrate_div = (bitrate_div-16)/2;
  TWBR = bitrate_div;
}
//-----------------------------------------------------------------------------
static void i2c_start(void)
{
 TWCR = (TWCR&TWCR_CMD_MASK)|(Bit(TWINT)|Bit(TWSTA));
}
//-----------------------------------------------------------------------------
static void i2c_stop(void)
{
 // leave with TWEA on for slave receiving
 TWCR = (TWCR&TWCR_CMD_MASK)|(Bit(TWINT)|Bit(TWEA)|Bit(TWSTO));
}
//-----------------------------------------------------------------------------
static void i2c_wait_for_complete(void)
{
 while(!CheckBit(TWCR,TWINT)) __watchdog_reset();
}

//-----------------------------------------------------------------------------
static void i2c_write_byte(uchar data)
{
 TWDR = data;
 TWCR = (TWCR&TWCR_CMD_MASK)|Bit(TWINT);
}

//-----------------------------------------------------------------------------
static void i2c_start_read_byte(uchar ack)
{
 // begin receive over i2c
 TWCR = (TWCR&TWCR_CMD_MASK)|Bit(TWINT)|(ack?Bit(TWEA):0);
}

//-----------------------------------------------------------------------------
static uchar i2c_get_status(void)
{
  uchar st;
  st = (TWSR&0xf8);
  return st;
}
//-----------------------------------------------------------------------------
void I2C_Init(void)
{
// TWCR = Bit(TWINT)|Bit(TWEN);
 i2c_set_bitrate(400);
 TWCR = Bit(TWEN);
}
//-----------------------------------------------------------------------------
sint I2C_NiMasterWrite(uchar adr,
                       uchar *write_data1, uchar write_data1_size,
                       uchar *write_data2, uchar write_data2_size )
{
 sint r;
  r = Ok;
#ifdef __NO_FRAM
	return 0;
#endif
  // disable TWI interrupt
  ClearBit(TWCR,TWIE);

  // send start condition
  i2c_start();
  i2c_wait_for_complete();

  // send device address with write
  i2c_write_byte(adr&0xfe);
  i2c_wait_for_complete();

  // check if device is present and live
  if (i2c_get_status() != I2Cst_MT_AdrAck) r = I2C_Err_NoDevice;

  // send data 1
  while (r == Ok && write_data1_size--) {
    i2c_write_byte(*write_data1++);
    i2c_wait_for_complete();
    if (i2c_get_status() != I2Cst_MT_DataAck) r = I2C_Err_Write;
  }

  // send data 2
  while (r == Ok && write_data2_size--) {
    i2c_write_byte(*write_data2++);
    i2c_wait_for_complete();
    if (i2c_get_status() != I2Cst_MT_DataAck) r = I2C_Err_Write;
  }

  // transmit stop condition
  i2c_stop();
  while(CheckBit(TWCR,TWSTO));

  // enable TWI interrupt
  //SetBit(TWCR,TWIE);

  return r;
}
//-----------------------------------------------------------------------------
sint I2C_NiMasterRead(uchar adr,
                      uchar *write_data, uchar write_data_size,
                      uchar *read_data, uchar read_data_size   )
{
 sint r;
#ifdef __NO_FRAM
	return 0;
#endif
  r = Ok;

  // disable TWI interrupt
  ClearBit(TWCR,TWIE);

  // send start condition
  i2c_start();
  i2c_wait_for_complete();

  if (write_data_size) {
    // send device address with write
    i2c_write_byte(adr&0xfe);
    i2c_wait_for_complete();

    // check if device is present and live
    if (i2c_get_status() != I2Cst_MT_AdrAck) r = I2C_Err_NoDevice;

    while (r == Ok && write_data_size--) {
      i2c_write_byte(*write_data++);
      i2c_wait_for_complete();
      if (i2c_get_status() != I2Cst_MT_DataAck) r = I2C_Err_Read;
    }

    if (r == Ok) {
      // send start condition
      i2c_start();
      i2c_wait_for_complete();
    }
  }

  if (r == Ok) {
    // send device address with read
    i2c_write_byte(adr|0x01);
    i2c_wait_for_complete();

    // check if device is present and live
    if (i2c_get_status() != I2Cst_MR_AdrAck) r = I2C_Err_NoDevice;

    // accept receive data and ack it
    while (read_data_size--) {
      i2c_start_read_byte(read_data_size);
      i2c_wait_for_complete();
      *read_data++ = TWDR;
    }
  }

  // transmit stop condition
  i2c_stop();
  while(CheckBit(TWCR,TWSTO));

  // enable TWI interrupt
  //SetBit(TWCR,TWIE);

  return r;
}
//-----------------------------------------------------------------------------

