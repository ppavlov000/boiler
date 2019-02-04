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

//  printf_P(sptr "\n\r  i2c cmd received: ");

//mem_dump((usint)data, size, 0);
//printf_P(sptr "\n\r");

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
//      printf_P(sptr "\tget system status\n\r");
      i2c_ctrl_make_short_cmd_rsp(Ok);
    break;
    //------------------------------------------------------
    case I2C_CMD_GetLastResult :
//      printf_P(sptr "\tget last result\n\r");
      i2c_ctrl_set_cmd_rsp();
    break;
    //------------------------------------------------------
    case I2C_CMD_GetVersion    :
//      printf_P(sptr "\tget version\n\r");
      i2c_ctrl_make_ver_info();
    break;
/*    //------------------------------------------------------
    case I2C_CMD_SetMode       :
      if (req->SubCmd) {
        printf_P(sptr "\tset work mode\n\r");
        i2c_ctrl_make_short_cmd_rsp(Ok);
      }
      else {
        printf_P(sptr "\tentering boot mode...");
        i2c_ctrl_init_long_cmd(req->Cmd);
      }
    break;
    //------------------------------------------------------
    case I2C_CMD_SetInterface  :
//      printf_P(Mcfg_SetTuner);
//      if (req->SubCmd) printf_P(Mcmd_Up);
//      else             printf_P(Mcmd_AdmDown);
//      printf_P(M_NewLine);
//
//      i2c_ctrl_init_long_cmd(req->Cmd);
    break;
    //------------------------------------------------------
    case I2C_CMD_SetSysClk     :
//      printf_P(Mcfg_SetTunerSysClk,v);
//      ret = Hynix_SetSystemClock(v);
//      i2c_ctrl_make_short_cmd_rsp(ret);
//      Err_DisplayMessage(ret);
    break;
    //------------------------------------------------------
    case I2C_CMD_SetFreq       :
//      printf_P(Mcfg_SetTunerFreq,v);
//      ret = Hynix_SetFreq(v);
//      i2c_ctrl_make_short_cmd_rsp(ret);
//      Err_DisplayMessage(ret);
    break;
    //------------------------------------------------------
    case I2C_CMD_SetFComp      :
//      printf_P(Mcfg_SetTunerCompFreq,v);
//      i2c_ctrl_init_long_cmd(req->Cmd);
    break;
    //------------------------------------------------------
    case I2C_CMD_SetAcq        :
//      printf_P(Mcfg_SetTunerAcqRange,v);
//      ret = Hynix_SetAcqRange(v);
//      i2c_ctrl_make_short_cmd_rsp(ret);
      Err_DisplayMessage(ret);
    break;
    //------------------------------------------------------
    case I2C_CMD_SetRate       :
      printf_P(Mcfg_SetTunerRate,v);
      ret = Hynix_SetSymbolRate(v);
      i2c_ctrl_make_short_cmd_rsp(ret);
      Err_DisplayMessage(ret);
    break;
    //------------------------------------------------------
    case I2C_CMD_SetPRate      :
      printf_P(Mcfg_SetTunerPRate);
      printf_P(CliCmd_GetViterbiRateMsg(i2c_ctrl_ulint2vr(v)));
      printf_P(M_NewLine);
      ret = Hynix_SetViterbiRate(i2c_ctrl_ulint2vr(v));
      i2c_ctrl_make_short_cmd_rsp(ret);
      Err_DisplayMessage(ret);
    break;
    //------------------------------------------------------
    case I2C_CMD_SetLnbPower   :
      printf_P(Mcfg_SetLnbPower);
      switch (req->SubCmd) {
        case 1  : printf_P(Mcmd_13v); HDM_LnbPower18(0); HDM_LnbPowerOn(1); break;
        case 2  : printf_P(Mcmd_18v); HDM_LnbPower18(1); HDM_LnbPowerOn(1); break;
        default : printf_P(Mcmd_Off);                    HDM_LnbPowerOn(0); break;
      }
      printf_P(M_NewLine);
      i2c_ctrl_make_short_cmd_rsp(Ok);
    break;
    //------------------------------------------------------
    case I2C_CMD_SetLnbTone    :
      printf_P(Mcfg_SetLnb22kHz);
      printf_P(req->SubCmd?Mcmd_On:Mcmd_Off);
      printf_P(M_NewLine);
      i2c_ctrl_init_long_cmd(req->Cmd);
    break;
    //------------------------------------------------------
    case I2C_CMD_GetIntStatus  :
      printf_P(sptr "\tget interface\n\r");
      i2c_ctrl_get_interface();
    break;
    //------------------------------------------------------
    case I2C_CMD_ClearStc      :
      printf_P(sptr "\tclear stc\n\r");
      i2c_ctrl_init_long_cmd(req->Cmd);
    break;
*/    //------------------------------------------------------
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
    //break;
    //------------------------------------------------------
/*    case I2C_CMD_SetInterface  :
      ret = Hynix_SetInterface(I2Cctrl.Req.SubCmd?eInt_Trying:eInt_AdmDown);
      Err_DisplayMessage(ret);
      i2c_ctrl_make_short_cmd_rsp(ret);
      I2Cctrl.ExecCmd = 0;
    break;
    //------------------------------------------------------
    case I2C_CMD_SetFComp      :
      ret = PLL_SetRefFreq(v);
      Err_DisplayMessage(ret);
      i2c_ctrl_make_short_cmd_rsp(ret);
      I2Cctrl.ExecCmd = 0;
    break;
    //------------------------------------------------------
    case I2C_CMD_SetLnbTone    :
      ret = HDM_Turn22kHz(I2Cctrl.Req.SubCmd);
      Err_DisplayMessage(ret);
      i2c_ctrl_make_short_cmd_rsp(ret);
      I2Cctrl.ExecCmd = 0;
    break;
    //------------------------------------------------------
    case I2C_CMD_ClearStc      :
      Hynix_ClearStc();
      i2c_ctrl_make_short_cmd_rsp(Ok);
      I2Cctrl.ExecCmd = 0;
    break;*/
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
 uchar v;
 STREAM s;
/*
  HDM_RefreshOtherData();

  stream_init(&s, I2Cctrl.Rsp.Data, sizeof(I2Cctrl.Rsp.Data));

  stream_put_uchar(&s, i2c_ctrl_int2uchar(Hynix.Interface));

  v = 0;
  if (Hynix.Pll.Status    &PLL_Lock_Ok         ) v |= 0x01;
  if (Hynix.Hdm.LockStatus&HDM_Lock_Qpsk       ) v |= 0x02;
  if (Hynix.Hdm.LockStatus&HDM_Lock_ViterbiNode) v |= 0x04;
  if (Hynix.Hdm.LockStatus&HDM_Lock_Frame      ) v |= 0x08;
  if (Hynix.Hdm.LockStatus&HDM_Lock_ViterbiByte) v |= 0x10;
  if (Hynix.Hdm.Spectrum == eSpectrum_Invert   ) v |= 0x20;
  stream_put_uchar(&s, v);

  stream_put_uchar(&s, i2c_ctrl_vr2uchar(Hynix.Hdm.ViterbiRate));

  stream_put_ulint(&s, __reverse((ulint)Hynix.Pll.Freq                    ));
  stream_put_ulint(&s, __reverse((ulint)(Hynix.Pll.Freq+Hynix.Hdm.Drift)  ));
  stream_put_ulint(&s, __reverse((ulint)(Hynix.SymbolRate + Hynix.Hdm.STF)));
  stream_put_ulint(&s, __reverse((ulint)Hynix.Stc.CorrectedErrors         ));
  stream_put_ulint(&s, __reverse((ulint)Hynix.Stc.UncorrectedErrors       ));
  stream_put_ulint(&s, __reverse((ulint)Hynix.Stc.UnlockCnt               ));
  stream_put_ulint(&s, __reverse((ulint)Hynix.Hdm.BerCalcAvr              ));
  stream_put_ulint(&s, __reverse((ulint)Hynix.Hdm.NoisePower.Value        ));
  stream_put_lint (&s, __reverse( (lint)Hynix.Hdm.NAgc.Value              ));
  stream_put_lint (&s, __reverse( (lint)Hynix.Hdm.WAgc.Value              ));

  i2c_ctrl_make_cmd_rsp(0, NULL, stream_get_processed(&s));

  ClearBit(DDRD,bitSysReq);
  */
}

//-----------------------------------------------------------------------------
//
//-------------------------------------------------
void i2c_ctrl_make_ver_info(void)
{
/* usint size;

  size = strlen_P(M_Version) + 1;

  if (size > I2C_CTRL_RspDataSize) {
    i2c_ctrl_make_short_cmd_rsp(I2CCMD_Err_TxDataSize);
    return;
  }
  memcpy_P(I2Cctrl.Rsp.Data, M_Version, size);
  i2c_ctrl_make_cmd_rsp(0, NULL, size);
  */
}
