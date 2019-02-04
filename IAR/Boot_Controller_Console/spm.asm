//=============================================================================
// Copyright Atmel Corporation 2003. All Rights Reserved.
//
// File:			spm.asm
// Compiler:		IAR Atmel AVR Assembler
// Output Size:
// Created:			4-Feb-2003	JP (Atmel Finland)
// Modified:	
//
// Support Mail:	avr@atmel.com
//
// Description:		Self-programming routines written in assembly
//
// Other Info:		The following symbols are defined in
//					  Project->Options...->AAVR->Preprocessor:
//
//						INCLUDE_FILE
//						__RAMPZ__
//						__MEMSPM__
//
//=============================================================================

NAME	spm(16)
PUBLIC	spmWriteWord
PUBLIC	spmWriteLockBits
PUBLIC	spmErasePage
PUBLIC	spmProgramPage
PUBLIC	spmEEWriteByte

#define __ENABLE_BIT_DEFINITIONS__
#include INCLUDE_FILE

//=============================================================================
// I/O registers used


RSEG	CODE

//=============================================================================
// Writes one word to a temporary page buffer

spmWriteWord:
	#ifdef __RAMPZ__
		movw	r1:r0, r21:r20
	#else
		movw	r1:r0, r19:r18
	#endif
	ldi		r22, (1 << SPMEN)
	rjmp	spmSPM

//=============================================================================
// Writes Lock Bits

spmWriteLockBits:
	mov		r0, r16
	ldi		r22, (1 << BLBSET) | (1 << SPMEN)
	rjmp	spmSPM


//=============================================================================
// Erases one flash page

spmErasePage:
	ldi		r22, (1 << PGERS) | (1 << SPMEN)
	rjmp	spmSPM


//=============================================================================
// Programs the temporary buffer to flash memory

spmProgramPage:
	ldi		r22, (1 << PGWRT) | (1 << SPMEN)


//=============================================================================
// Executes self-programming command

spmSPM:
	movw	r31:r30, r17:r16

	rcall	spmWait

	in		r20, SREG
	cli

	#ifdef __RAMPZ__
		in		r21, RAMPZ
		out		RAMPZ, r18
	#endif

	#ifdef __MEMSPM__
		sts		SPMREG, r22
	#else		
		out		SPMREG, r22
	#endif
	
	#ifdef __RAMPZ__
		espm
	#else
		spm
	#endif
		
	dw		0xFFFF
	nop
		
	#ifdef __RAMPZ__
		out		RAMPZ, r21
	#endif
	
	out		SREG, r20
	ret

spmWait:
	#ifdef __MEMSPM__
		lds		r23, SPMREG
		andi	r23, (1 << SPMEN)
		brne	spmWait	
	#else
		in		r23, SPMREG
		sbrc	r23, SPMEN
		rjmp	spmWait
	#endif

	ret


//=============================================================================
// Writes one byte to EEPROM memory

spmEEWriteByte:
	rcall	spmWait
	rcall	spmEEWriteByteComplete

	out		EEARL, r16
	out		EEARH, r17
	out		EEDR, r18

	sbi		EECR, EEMWE
	sbi		EECR, EEWE
		
spmEEWriteByteComplete:
	sbic	EECR, EEWE
	rjmp	spmEEWriteByteComplete
	ret


END
