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

#include "../uae_inc/sysdeps.h"
#include "../uae_inc/newcpu.h"
#include "../uae_inc/blitter.h"

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
	struct blitterContext _context;

//	_context.oldvblts = custom -> oldvblts;
//	_context.blinea_shift = custom -> blinea_shift;
//	_context.blinea = custom -> blinea;
//	_context.blineb = custom -> blineb;
//	_context.blitline = custom -> blitline;
//	_context.blitfc = custom -> blitfc;
//	_context.blitfill = custom -> blitfill;
//	_context.blitife = custom -> blitife;
//	_context.blitsing = custom -> blitsing;
//	_context.blitdesc = custom -> blitdesc;
//	_context.blitonedot = custom -> blitonedot;
//	_context.blitsign = custom -> blitsign;
//	_context.bltwait = custom -> bltwait;
//	_context.bltstate = custom -> bltstate;

	_context.bltcon0 = custom -> bltcon0;
	_context.bltcon1 = custom -> bltcon1;
	_context.bltapt = custom -> bltapt;
	_context.bltbpt = custom -> bltbpt;
	_context.bltcpt = custom -> bltcpt;
	_context.bltdpt = custom -> bltdpt;
	_context.bltsize = custom -> bltsize;

	do_blitter ( &_context );

	custom -> bltcon0 = _context.bltcon0;
	custom -> bltcon1 = _context.bltcon1;
	custom -> bltapt = _context.bltapt;
	custom -> bltbpt = _context.bltbpt;
	custom -> bltcpt = _context.bltcpt;
	custom -> bltdpt = _context.bltdpt;
	custom -> bltsize = _context.bltsize;

}

