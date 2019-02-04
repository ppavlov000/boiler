//=============================================================================
// Copyright (C) 2003 Atmel Corporation
//
// File:			loader.h
// Compiler:		IAR Atmel AVR C/EC++ Compiler
// Output Size:
// Based on work by:ØE, VU
// Created:			4-Feb-2003	JP (Atmel Finland)
// Modified:
//
// Support Mail:	avr@atmel.com
//
// Description:		Loader receives encrypted data frames (generated using
//					'create' tool and sent by 'update' tool), decrypts them and
//					executes the commands described in frames.
//
//					For more information, refer to the Application Note
//					Documentation.
//
// Other Info:		
//=============================================================================


#ifndef LOADER_H
#define LOADER_H

#include "bootldr.h"

//=============================================================================
// To minimize the target size, the following types are differently declared
// depending on the target AVR.

#if BUFFER_SIZE < 256
	typedef unsigned char frameindex_t;
#else
	typedef unsigned int frameindex_t;
#endif

#if MEM_SIZE < 65536
	#define BOOTFLASH __flash
	#define APPFLASH __flash
#else
	#define BOOTFLASH __farflash
	#define APPFLASH __hugeflash
#endif

__C_task extern void loader(void);


#endif // LOADER_H
