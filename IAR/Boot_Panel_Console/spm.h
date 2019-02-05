//=============================================================================
// Copyright Atmel Corporation 2003. All Rights Reserved.
//
// File:			spm.h
// Compiler:		IAR Atmel AVR Assembler
// Output Size:
// Created:			4-Feb-2003	JP (Atmel Finland)
// Modified:
//
// Support Mail:	avr@atmel.com
//
// Description:		Self-programming routines written in assembly
//
// Other Info:
//=============================================================================


#ifndef SPM_H
#define SPM_H

#define MEM_SIZE 0x20000

#if MEM_SIZE < 65536
	#define BOOTFLASH __flash
	#define APPFLASH __flash
#else
	#define BOOTFLASH __farflash
	#define APPFLASH __hugeflash
#endif
#include "Include\types.h"

extern void spmWriteWord(u8 APPFLASH *addr, u16 data);
extern int  spmReadWord(u8 APPFLASH *addr);
extern void spmErasePage(u8 APPFLASH *addr);
extern void spmProgramPage(u8 APPFLASH *addr);
extern void spmEEWriteByte(u8 addr, u8 data);
extern void spmWriteLockBits(u8 data);

//#define spmRemoveProtection spmWriteLockBits(0x3f);
#define spmEnableFullProtection spmWriteLockBits(0x28);
#define spmEnableBootProtection spmWriteLockBits(0x2C);
#endif  // SPM_H
