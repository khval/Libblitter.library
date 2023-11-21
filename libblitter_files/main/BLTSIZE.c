/* :ts=4
 *  $VER: BLTSIZE.c $Revision$ (21-Nov-2023)
 *
 *  This file is part of libblitter.
 *
 *  Copyright (c) 2023 LiveForIt Software.
 *  Freeware License..
 *
 * $Id$
 *
 * $Log$
 *
 *
 */


#include <exec/exec.h>
#include <proto/exec.h>
#include <dos/dos.h>
#include <exec/types.h>
#include <libraries/libblitter.h>
#include <hardware/custom.h>
#include <proto/libblitter.h>
#include <stdarg.h>

#pragma pack(push,2)
#include <hardware/custom.h>
#pragma pack(pop)

#include <proto/libblitter.h>
#include <stdarg.h>

#include "../blitzen/blitzen.h"

/****** libblitter/main/BLTSIZE ******************************************
*
*   NAME
*      BLTSIZE -- Description
*
*   SYNOPSIS
*      void BLTSIZE(struct Custom * custom);
*
*   FUNCTION
*
*   INPUTS
*       custom - 
*
*   RESULT
*       This function does not return a result
*
*   EXAMPLE
*
*   NOTES
*
*   BUGS
*
*   SEE ALSO
*
*****************************************************************************
*
*/

#define BLTSIZV  0x05c
#define BLTSIZH  0x05e
#define BLTSIZE  0x058

extern void blitzenWrite( uint16 reg, uint16 value, BOOL *handled, struct blitstate *bs );

void _libblitter_BLTSIZE(struct LibBlitterIFace *Self,
       struct Custom * custom)
{
	BOOL handled;

	uint16 *dptr = (uint16 *) custom -> bltdpt;
	struct blitstate bstate;
	bzero( &bstate, sizeof(struct blitstate) );

	CustomToBlitsate( custom,  &bstate );
	blitzenWrite( BLTSIZE, custom -> bltsize, &handled, &bstate );

	blitzenBlit(  &bstate );
}

