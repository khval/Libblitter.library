/* :ts=4
 *  $VER: doBlitter.c $Revision$ (11-Aug-2021)
 *
 *  This file is part of libblitter.
 *
 *  Copyright (c) 2021 LiveForIt Software.
 *  GPL2 License..
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

#pragma pack(push,2)
#include <hardware/custom.h>
#pragma pack(pop)

#include <proto/libblitter.h>
#include <stdarg.h>

#include "../blitzen/blitzen.h"

/**********************************************************************
*   NAME
*      doBlitter -- Description
*
*   SYNOPSIS
*      void doBlitter( struct Custom * custum);
*
*   FUNCTION
*
*   INPUTS
*       context - 
*       custum - 
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
********************************************************************/

extern void do_blitter ( struct blitterContext *bC );

void _libblitter_doBlitter(struct LibBlitterIFace *Self,
       struct Custom * custom)
{
	struct blitstate bstate;

	uint16 *dptr = (uint16 *) custom -> bltdpt;

	CustomToBlitsate( custom,  &bstate );
	blitzenBlit(  bstate );

}

