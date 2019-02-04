#ifndef _I2C_H_
#define _I2C_H_
//-----------------------------------------------------------------------------
#define TWCR_CMD_MASK         0x0f
#define TWSR_STATUS_MASK      0xF8
//-----------------------------------------------------------------------------
#define I2Cst_MT_StartOk           0x08
#define I2Cst_MT_RestartOk         0x10
#define I2Cst_MT_AdrAck            0x18
#define I2Cst_MT_NoAdrAck          0x20
#define I2Cst_MT_DataAck           0x28
#define I2Cst_MT_NoDataAck         0x30
#define I2Cst_MT_ArbLost           0x38
//-----------------------------------------------------------------------------
#define I2Cst_MR_StartOk           0x08
#define I2Cst_MR_RestartOk         0x10
#define I2Cst_MR_ArbLostOrNoAck    0x38
#define I2Cst_MR_AdrAck            0x40
#define I2Cst_MR_NoAdrAck          0x48
#define I2Cst_MR_DataAck           0x50
#define I2Cst_MR_NoDataAck         0x58

//-----------------------------------------------------------------------------
#define I2Cst_SR_AdrOk             0x60
#define I2Cst_SR_ArbLost_AdrOk     0x68
#define I2Cst_SR_GenAdrOk          0x70
#define I2Cst_SR_ArbLost_GenAdrOk  0x78
#define I2Cst_SR_Adr_Data_Ack      0x80
#define I2Cst_SR_Adr_Data_NoAck    0x88
#define I2Cst_SR_GenAdr_Data_Ack   0x90
#define I2Cst_SR_GenAdr_Data_NoAck 0x98
#define I2Cst_SR_StopOrRepStop     0xA0
//-----------------------------------------------------------------------------
#define I2Cst_ST_AdrOk             0xA8
#define I2Cst_ST_ArbLost_AdrOk     0xB0
#define I2Cst_ST_Data_Ack          0xB8
#define I2Cst_ST_Data_NoAck        0xC0
#define I2Cst_ST_LastData_Ack      0xC8

//-----------------------------------------------------------------------------
#define I2Cst_NoInfo               0xF8
#define I2Cst_BusError             0x00

//-----------------------------------------------------------------------------
#define ERRORS_I2C 	-450
#define Ok 5

#define I2C_Err_NoDevice   (ERRORS_I2C-0) //no acknowledge of slave address
#define I2C_Err_Write      (ERRORS_I2C-1) //error after acknowledge slave address
#define I2C_Err_Read       (ERRORS_I2C-2) //error write offset before read
//-----------------------------------------------------------------------------
#define I2C_RX_BUFF_MAX    10
#define I2C_TX_BUFF_MAX    10
//-----------------------------------------------------------------------------
typedef struct {
  u8 	RxBuf[I2C_RX_BUFF_MAX];
  u8	RxSize;

  u8 	TxBuf[I2C_TX_BUFF_MAX];
  u8 	TxPtr;
  u8 	TxSize;

  u8	Addr;	
  u8	Command;	// R/W
  u8 	Done;		// 1 - exchange done
}I2C_VARS;
//-----------------------------------------------------------------------------
void I2C_Init(void);
sint I2C_NiMasterWrite(uchar adr,
                       uchar *write_data1, uchar write_data1_size,
                       uchar *write_data2, uchar write_data2_size );
sint I2C_NiMasterRead(uchar adr,
                      uchar *write_data, uchar write_data_size,
                      uchar *read_data, uchar read_data_size   );

void i2c_set_bitrate(usint bitrateKHz);
#endif

