#include "central.h"
#include "console.h"
I2C_CTRL_VARS I2Cctrl;

//-----------------------------------------------------------------------------
//
//-------------------------------------------------
void I2Cctrl_Init(uchar adr)
{
  memset(&I2Cctrl, 0, sizeof(I2Cctrl));
  I2C_SetSlaveRxHnd(I2Cctrl_RxHnd);
  I2C_SetSlaveRxBuf(&I2Cctrl.ReqBuf, (uchar)sizeof(I2Cctrl.ReqBuf));
  I2C_SetLocalAdr(adr, adr);
  i2c_ctrl_init_long_cmd(I2C_CMD_Init);
}

//-----------------------------------------------------------------------------
//
//-------------------------------------------------
char I2Cctrl_RxHnd(void *data, uchar size)
{
// ulint v;
 char r;
 I2C_CTRL_REQ *req;

  req = (I2C_CTRL_REQ *)data;

  if (size < 5) {
    i2c_ctrl_make_err_rsp(I2CCMD_Err_RxDataSize);
    return 1;
  }

  if (!i2c_ctrl_check_lrc(data, size)) {
    i2c_ctrl_make_err_rsp(I2CCMD_Err_Lrc);
    return 1;
  }

  if (req->Version != I2C_CTRL_Version) {
    i2c_ctrl_make_err_rsp(I2CCMD_Err_Version);
    return 1;
  }

  if (I2Cctrl.ExecCmd) {
    i2c_ctrl_make_err_rsp(I2CCMD_Err_Busy);
    return 1;
  }

  memcpy(&I2Cctrl.Req, data, sizeof(I2C_CTRL_REQ));
  //v = __reverse(*((ulint *)req->Data));

  r = 1;
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
    case I2C_CMD_SetMode       :
      if (req->SubCmd) 
        i2c_ctrl_init_long_cmd(req->Cmd);
      else 
        i2c_ctrl_make_short_cmd_rsp(Ok);
    break;
    //------------------------------------------------------
    case I2C_CMD_BootGetFWinfo :
    case I2C_CMD_BootErase     :
    case I2C_CMD_BootWrite     :
      i2c_ctrl_init_long_cmd(req->Cmd);
    break;
    //------------------------------------------------------
    default                    :
      i2c_ctrl_make_err_rsp(I2CCMD_Err_UnknownCmd);
    break;
  }

  return r;
}

//-----------------------------------------------------------------------------
//
//-------------------------------------------------
void I2Cctrl_Processor(void)
{
 int ret;
  switch (I2Cctrl.ExecCmd) {
    //------------------------------------------------------
    case I2C_CMD_SetMode       :
      ret = 1;//check_appl_present(1);

      if (ret > 0) {
        __disable_interrupt();
        ((void (*)())0x0000)();
      }

      i2c_ctrl_make_short_cmd_rsp(ret);
      I2Cctrl.ExecCmd = 0;
    break;
    //------------------------------------------------------
    case I2C_CMD_BootGetFWinfo :
      i2c_ctrl_make_fw_info();
      I2Cctrl.ExecCmd = 0;
    break;
    //------------------------------------------------------
    case I2C_CMD_BootErase     :
      i2c_ctrl_boot_erase();
      I2Cctrl.ExecCmd = 0;
    break;
    //------------------------------------------------------
    case I2C_CMD_BootWrite     :
      i2c_ctrl_boot_write();
      I2Cctrl.ExecCmd = 0;
    break;
    //------------------------------------------------------
    case I2C_CMD_Init          :
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
  rsp->Status  = I2Cctrl_Status_Boot | (I2Cctrl.ExecCmd?I2Cctrl_Status_Busy:0) | 
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

  rsp->Status  = I2Cctrl_Status_Boot|flags;
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
  rsp->Status |= I2Cctrl_Status_Boot|(I2Cctrl.ExecCmd?I2Cctrl_Status_Busy:0);

  size = rsp->Size + 4;
  ((uchar *)rsp)[size] = i2c_ctrl_lrc(rsp, size);

  I2C_SetSlaveTxBuf(rsp, sizeof(I2C_CTRL_RSP));
  I2C_SetSlaveTxDataSize(size + 1);
}

//-----------------------------------------------------------------------------
//
//-------------------------------------------------
void i2c_ctrl_make_ver_info(void)
{
/*	usint size;
	size = strlen_P((const __farflash s8 *)&Help[0][0]) + 1;
	if (size > I2C_CTRL_RspDataSize) 
	{
    	i2c_ctrl_make_short_cmd_rsp(I2CCMD_Err_TxDataSize);
		return;
	}
	memcpy_P(I2Cctrl.Rsp.Data, (const __farflash s8 *)&Help[0][0], size);
	i2c_ctrl_make_cmd_rsp(0, NULL, size);
*/
}

//-----------------------------------------------------------------------------
//
//-------------------------------------------------
void i2c_ctrl_make_fw_info(void)
{
  STREAM s;
/*  IMAGE *p;
  uchar i, loaded;
  sint r;

// | (uchar) loaded cnt | 
// | (uchar) number | (usint) start | (usint) size | (sint) status | (uchar x CFG_ImageName) name |

  //--- calculate loaded images count ----------------------
  loaded = 0;
  p = &Sys.Cfg.Image[0];

  for (i=0; i<CFG_ImagesCount; i++) { if (p->Loaded) loaded++; p++; }

  stream_init(&s, I2Cctrl.Rsp.Data, sizeof(I2Cctrl.Rsp.Data));
  stream_put_uchar(&s, loaded);

  p = &Sys.Cfg.Image[0];
  //--- check loaded images --------------------------------
  for (i=0; i<CFG_ImagesCount; i++) {
    if (p->Loaded) {
      r = check_image_crc(p)?Ok:COMMON_Err_ImageCrc;
      stream_put_uchar(&s, i);
      stream_put_usint(&s, p->Start);
      stream_put_usint(&s, get_pages_count(p->Size));
      stream_put_sint(&s, r);

      stream_put_or_get(&s, p->Name, sizeof(p->Name), 1);
    }
    p++;
  }*/
//  i2c_ctrl_make_cmd_rsp(0, NULL, stream_get_processed(&s));
}

//-----------------------------------------------------------------------------
//
//-------------------------------------------------
void i2c_ctrl_boot_erase(void)
{
  sint ret;
  uchar n;

  n = I2Cctrl.Req.SubCmd;

  //--- erasing all images ---------------------------------
  if (n == 0xff) 
    ret = 1;//erase_image(-1);
  else
    ret = 1;//erase_image(n);

  i2c_ctrl_make_short_cmd_rsp(ret);
}


//-----------------------------------------------------------------------------
//
//-------------------------------------------------
sint i2c_ctrl_boot_prepare(void)
{
  usint img, start, size;
  STREAM s;
/*
  if (I2Cctrl.Req.Size != 6) return I2CCMD_Err_CmdArg;

  //--- get parameters -------------------------------------
  stream_init(&s, I2Cctrl.Req.Data, I2Cctrl.Req.Size);

  img   = stream_get_usint(&s);
  start = stream_get_usint(&s);
  size  = stream_get_usint(&s);

  //--- checking parameters --------------------------------
  if ((img   >= CFG_ImagesCount            ) ||
      (start >= FLASH_SectorsCount         ) ||
      (size  > (FLASH_SectorsCount - start))   ) return I2CCMD_Err_CmdArg;

  if (check_dl_image(img, start, size) != Ok) return COMMON_Err_DlOverlap;

  //--- erasing old image ----------------------------------
  erase_image(img);

  Sys.ActualImage          = &Sys.Cfg.Image[img];
  Sys.Cfg.Image[img].Start = start;

  Flash_Init(start, size);

  I2Cctrl.BootWrite = i2c_ctrl_boot_header;
*/
  return Ok;
}

//-----------------------------------------------------------------------------
//
//-------------------------------------------------
sint i2c_ctrl_boot_header(uchar *p, usint s) 
{
 uchar img_correct;
/* DL_HEADER hdr;

  memcpy(&hdr, p, sizeof(DL_HEADER));
  img_correct = 0;

  if (hdr.Ver != 1) return COMMON_Err_BadDlImage;

  if (!hdr.Crypted && (hdr.HdrCrc == crc_calc((uchar *)&hdr,sizeof(DL_HEADER)-2))) {
    img_correct = 1;
    memcpy(&Sys.ActualImage->Name,hdr.Name,sizeof(hdr.Name)+sizeof(hdr.Size)+sizeof(hdr.Crc));
  }

  p += sizeof(DL_HEADER);
  s -= sizeof(DL_HEADER);

  Flash_AddInit(img_correct,hdr.Size);
  I2Cctrl.BootWrite = Flash_Write;*/
  return Flash_Write(p,s);
}

//-----------------------------------------------------------------------------
//
//-------------------------------------------------
void i2c_ctrl_boot_write(void)
{
 sint r;
 /*IMAGE *img;

  r = I2CCMD_Err_CmdArg;

  switch (I2Cctrl.Req.SubCmd) {
    case 0 :
      r = i2c_ctrl_boot_prepare();
    break;
    case 1 :
      r = I2Cctrl.BootWrite(I2Cctrl.Req.Data, I2Cctrl.Req.Size);
    break;
    case 2 :
      r = I2Cctrl.BootWrite(I2Cctrl.Req.Data, I2Cctrl.Req.Size);

      if (r > 0)
        r = Flash_EndWrite();

      if (r > 0) {
        img = Sys.ActualImage;
        if (Flash.ImgCorrect && check_image_crc(img)) {
          img->Loaded = 1;
          cfg_save();
        }
        else
          r = COMMON_Err_BadDlImage;
      }
    break;
    default :
      r = I2CCMD_Err_CmdArg;
    break;
  }

  Err_DisplayMessage(r);*/
  i2c_ctrl_make_short_cmd_rsp(r);
}
