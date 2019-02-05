#include "defines.h"
//-----------------------------------------------------------------------------
//
//-------------------------------------------------
char I2Cctrl_RxHnd(void *data, uchar size)
{
 sint ret;
 ulint v;
 I2C_CTRL_REQ *req;

  req = (I2C_CTRL_REQ *)data;

  if (size < 5) {
    Err_DisplayMessage(i2c_ctrl_make_err_rsp(I2CCMD_Err_RxDataSize));
    return 1;
  }

  if (!i2c_ctrl_check_lrc(data, size)) {
    Err_DisplayMessage(i2c_ctrl_make_err_rsp(I2CCMD_Err_Lrc));
    return 1;
  }

  if (req->Version != I2C_CTRL_Version) {
    Err_DisplayMessage(i2c_ctrl_make_err_rsp(I2CCMD_Err_Version));
    return 1;
  }

  if (I2Cctrl.ExecCmd) {
    Err_DisplayMessage(i2c_ctrl_make_err_rsp(I2CCMD_Err_Busy));
    return 1;
  }

  v = __reverse(*((ulint *)req->Data));
  memcpy(&I2Cctrl.Req, data, sizeof(I2C_CTRL_REQ));

  switch (req->Cmd) {
    //------------------------------------------------------
    case I2C_CMD_GetSysStatus  :
      i2c_ctrl_make_short_cmd_rsp(Ok);
    break;
    //------------------------------------------------------
    case I2C_CMD_GetLastResult :
      i2c_ctrl_set_cmd_rsp();
    break;
    //------------------------------------------------------
    case I2C_CMD_GetVersion    :
      i2c_ctrl_make_ver_info();
    break;
    //------------------------------------------------------
    default                    :
      Err_DisplayMessage(i2c_ctrl_make_err_rsp(I2CCMD_Err_UnknownCmd));
    break;
  }
  return 1;
}

//-----------------------------------------------------------------------------
//
//-------------------------------------------------
void I2Cctrl_Processor(void)
{
 ulint v;
 int ret;

  v = __reverse(*((ulint *)I2Cctrl.Req.Data));

  switch (I2Cctrl.ExecCmd) {
    //------------------------------------------------------
    case I2C_CMD_SetMode       :
//      Delay(100);
      WDTCR = Bit(WDCE)|Bit(WDE);
      WDTCR = Bit(WDE)|0x00;
      while(1);
    //------------------------------------------------------
    case I2C_CMD_Init          :
      i2c_ctrl_make_short_cmd_rsp(Ok);
      I2Cctrl.ExecCmd = 0;
    break;
  }
}

//-----------------------------------------------------------------------------
//
//-------------------------------------------------
uchar i2c_ctrl_lrc(void *data, uchar size)
{
 uchar *d, c;
  d = (uchar *)data;

  c = 0;
  while (size--) c ^= *d++;

  return c;
}

//-----------------------------------------------------------------------------
//
//-------------------------------------------------
uchar i2c_ctrl_check_lrc(void *data, uchar size)
{
  if (i2c_ctrl_lrc(data, size-1) != ((uchar *)data)[size-1]) return 0;
  return 1;
}

//-----------------------------------------------------------------------------
//
//-------------------------------------------------
void i2c_ctrl_init_long_cmd(uchar cmd)
{
 I2Cctrl.ExecCmd = cmd;
 i2c_ctrl_make_err_rsp(I2CCMD_Err_Busy);
}

//-----------------------------------------------------------------------------
//
//-------------------------------------------------
sint i2c_ctrl_make_err_rsp(sint r)
{
 I2C_CTRL_ERR_RSP *rsp;

  rsp = &I2Cctrl.ErrRsp;

  rsp->Version = I2C_CTRL_Version;
  rsp->Status  = I2Cctrl_Status_Work | (I2Cctrl.ExecCmd?I2Cctrl_Status_Busy:0) |
                                       ((r<0)?I2Cctrl_Status_Error:0);
  rsp->_res_   = 0;
  rsp->Size    = 2;
  rsp->Result  = __reverse((signed int)r);
  rsp->Lrc     = i2c_ctrl_lrc(rsp, 6);

  I2C_SetSlaveTxBuf(rsp, sizeof(I2C_CTRL_ERR_RSP));
  I2C_SetSlaveTxDataSize(7);

  return r;
}

//-----------------------------------------------------------------------------
//
//-------------------------------------------------
sint i2c_ctrl_make_short_cmd_rsp(sint r)
{
 sint v;

  v = __reverse((signed int)r);
  return i2c_ctrl_make_cmd_rsp((r<0)?I2Cctrl_Status_Error:0, &v, sizeof(v));
}

//-----------------------------------------------------------------------------
//
//-------------------------------------------------
sint i2c_ctrl_make_cmd_rsp(uchar flags, void *data, uchar size)
{
 I2C_CTRL_RSP *rsp;

  if (size > I2C_CTRL_RspDataSize) return I2CCMD_Err_TxDataSize;
  rsp = &I2Cctrl.Rsp;

  rsp->Status  = flags;
  rsp->_res_   = 0;
  rsp->Size    = size;
  if (data) memcpy(rsp->Data, data, size);

  i2c_ctrl_set_cmd_rsp();
  return Ok;
}

//-----------------------------------------------------------------------------
//
//-------------------------------------------------
void i2c_ctrl_set_cmd_rsp(void)
{
 uchar size;
 I2C_CTRL_RSP *rsp;

  rsp = &I2Cctrl.Rsp;

  rsp->Version = I2C_CTRL_Version;

  rsp->Status &= ~I2Cctrl_Status_Busy;
  rsp->Status |= I2Cctrl_Status_Work|(I2Cctrl.ExecCmd?I2Cctrl_Status_Busy:0);

  size = rsp->Size + 4;
  ((uchar *)rsp)[size] = i2c_ctrl_lrc(rsp, size);

  I2C_SetSlaveTxBuf(rsp, sizeof(I2C_CTRL_RSP));
  I2C_SetSlaveTxDataSize(size + 1);
}

//-----------------------------------------------------------------------------
//
//-------------------------------------------------
E_VITERBI_RATE i2c_ctrl_ulint2vr(ulint c)
{
  switch (c) {
    case 1 : return eVfix_1_2;
    case 2 : return eVfix_2_3;
    case 3 : return eVfix_3_4;
    case 4 : return eVfix_5_6;
    case 5 : return eVfix_7_8;
  }
  return eVauto;
}

//-----------------------------------------------------------------------------
//
//-------------------------------------------------
uchar i2c_ctrl_vr2uchar(E_VITERBI_RATE vr)
{
  switch (vr) {
    case eVfix_1_2 : return 1;
    case eVfix_2_3 : return 2;
    case eVfix_3_4 : return 3;
    case eVfix_5_6 : return 4;
    case eVfix_7_8 : return 5;
  }
  return 0;
}

//-----------------------------------------------------------------------------
//
//-------------------------------------------------
uchar i2c_ctrl_int2uchar(E_INTERFACE i)
{
  switch (i) {
    case eInt_HardDown : return INT_HardDown;
    case eInt_AdmDown  : return INT_AdmDown;
    case eInt_Trying   : return INT_Trying;
    case eInt_Down     : return INT_Down;
    case eInt_Up       : return INT_Up;
  }
  return INT_Unknown;
}

//-----------------------------------------------------------------------------
//
//-------------------------------------------------
void i2c_ctrl_get_interface(void)
{

}

//-----------------------------------------------------------------------------
//
//-------------------------------------------------
void i2c_ctrl_make_ver_info(void)
{

}
