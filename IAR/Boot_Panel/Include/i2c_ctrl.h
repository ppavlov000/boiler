#ifndef _I2C_CTRL_H_
#define _I2C_CTRL_H_

//--- general section --------------------------------------
#define I2C_CMD_GetSysStatus  1
#define I2C_CMD_GetLastResult 2
#define I2C_CMD_GetVersion    3

#define I2C_CMD_SetMode       10
//--- boot section -----------------------------------------
#define I2C_CMD_BootGetFWinfo 50
#define I2C_CMD_BootErase     51
#define I2C_CMD_BootWrite     52

//--- application section ----------------------------------
#define I2C_CMD_GetIntStatus  100

#define I2C_CMD_SetStatusIE   110

#define I2C_CMD_SetInterface  120
#define I2C_CMD_SetSysClk     121
#define I2C_CMD_SetFreq       122
#define I2C_CMD_SetFComp      123
#define I2C_CMD_SetAcq        124
#define I2C_CMD_SetRate       125
#define I2C_CMD_SetPRate      126
#define I2C_CMD_SetLnbPower   127
#define I2C_CMD_SetLnbTone    128

#define I2C_CMD_ClearStc      130

#define I2C_CMD_Init          255

//-------------------------------------------------------------------------------------------------------
// REQ              cmd                     sub cmd      data size  data       RSP  busy  data size  data
//-------------------------------------------------------------------------------------------------------
// get sys status   I2C_CMD_GetSysStatus    x            0          -               0     0          -
// get last result  I2C_CMD_GetLastResult   x            0          -               0     4          lint
//
// mode boot        I2C_CMD_SetMode         0            0          -               0     4          lint
// mode work        I2C_CMD_SetMode         1            0          -               0     4          lint
//-------------------------------------------------------------------------------------------------------
// boot get FW info I2C_CMD_BootGetFWinfo   x            0          -               1     
// boot erase       I2C_CMD_BootErase       n (255-all)  0          -               1
// boot write prep. I2C_CMD_BootWrite       0            6          3 x usint       1
// boot write data  I2C_CMD_BootWrite       1            <= 128     data            1
// boot write last  I2C_CMD_BootWrite       2            <= 128     data            1
//-------------------------------------------------------------------------------------------------------
// get interface    I2C_CMD_GetIntStatus    x            0          -
//
// interrupt off    I2C_CMD_SetStatusIE     0            0          -
// interrupt on     I2C_CMD_SetStatusIE     1            0          -
//
// interface up     I2C_CMD_SetInterface    1            0          -
// interface down   I2C_CMD_SetInterface    0            0          -
// system clock     I2C_CMD_SetSysClk       x            4          ulint
// frequency        I2C_CMD_SetFreq         x            4          ulint
// f.comp           I2C_CMD_SetFComp        x            4          ulint
// acquisition      I2C_CMD_SetAcq          x            4          ulint
// rate             I2C_CMD_SetRate         x            4          ulint
// punctured rate   I2C_CMD_SetPRate        x            4          ulint
// LNB power off    I2C_CMD_SetLnbPower     0            0          -
// LNB power 13     I2C_CMD_SetLnbPower     1            0          -
// LNB power 18     I2C_CMD_SetLnbPower     2            0          -
// LNB tone off     I2C_CMD_SetLnbTone      0            0          -
// LNB tone on      I2C_CMD_SetLnbTone      1            0          -
//
// clear stc        I2C_CMD_ClearStc        x            0          -
//-------------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// RSP      bit  description    1      0
// Status   7    mode           work   boot
//          6    busy           busy   ready
//          5    -             
//          4    -             
//          3    -             
//          2    -             
//          1    -             
//          0    last result    error  ok

#define I2Cctrl_Status_Error     0x01
#define I2Cctrl_Status_Busy      0x40
#define I2Cctrl_Status_Boot      0x00
#define I2Cctrl_Status_Work      0x80

//-----------------------------------------------------------------------------
#define I2C_CTRL_Version          1
#define I2C_CTRL_ReqDataSize      128
#define I2C_CTRL_RspDataSize      128
//-----------------------------------------------------------------------------
typedef struct {
  uchar Version;
  uchar Cmd;
  uchar SubCmd;
  uchar Size;
  uchar Data[I2C_CTRL_ReqDataSize];
  uchar Lrc;
} I2C_CTRL_REQ;

//-----------------------------------------------------------------------------
typedef struct {
  uchar Version;
  uchar Status;
  uchar _res_;
  uchar Size;
  uchar Data[I2C_CTRL_RspDataSize];
  uchar Lrc;
} I2C_CTRL_RSP;

//-----------------------------------------------------------------------------
typedef struct {
  uchar Version;
  uchar Status;
  uchar _res_;
  uchar Size;
  sint  Result;
  uchar Lrc;
} I2C_CTRL_ERR_RSP;

//-----------------------------------------------------------------------------
typedef struct {
  I2C_CTRL_REQ ReqBuf;
  I2C_CTRL_REQ Req;

  I2C_CTRL_ERR_RSP ErrRsp;
  I2C_CTRL_RSP     Rsp;

  volatile uchar ExecCmd;      // if not zero - system busy

  sint (*BootWrite)(uchar *, usint);

} I2C_CTRL_VARS;

//-----------------------------------------------------------------------------
#define I2CCMD_Err_Version      (ERRORS_I2CCMD-1)
#define I2CCMD_Err_RxDataSize   (ERRORS_I2CCMD-2)
#define I2CCMD_Err_Lrc          (ERRORS_I2CCMD-3)
#define I2CCMD_Err_UnknownCmd   (ERRORS_I2CCMD-4)
#define I2CCMD_Err_TxDataSize   (ERRORS_I2CCMD-5)
#define I2CCMD_Err_CmdArg       (ERRORS_I2CCMD-7)
#define I2CCMD_Err_Busy         (ERRORS_I2CCMD-6)

//-----------------------------------------------------------------------------
void I2Cctrl_Init(uchar adr);
char I2Cctrl_RxHnd(void *data, uchar size);
void I2Cctrl_Processor(void);

uchar i2c_ctrl_lrc(void *data, uchar size);
uchar i2c_ctrl_check_lrc(void *data, uchar size);
void  i2c_ctrl_init_long_cmd(uchar cmd);
sint  i2c_ctrl_make_err_rsp(sint r);
sint  i2c_ctrl_make_short_cmd_rsp(sint r);
sint  i2c_ctrl_make_cmd_rsp(uchar flags, void *data, uchar size);
void  i2c_ctrl_set_cmd_rsp(void);

void  i2c_ctrl_make_ver_info(void);
void  i2c_ctrl_make_fw_info(void);
void  i2c_ctrl_boot_erase(void);
sint  i2c_ctrl_boot_prepare(void);
sint  i2c_ctrl_boot_header(uchar *p, usint s);
void  i2c_ctrl_boot_write(void);

#endif
