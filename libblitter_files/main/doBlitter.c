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
#include <hardware/custom.h>
#include <proto/libblitter.h>
#include <stdarg.h>

/****** libblitter/main/doBlitter ******************************************
*
*   NAME
*      doBlitter -- Description
*
*   SYNOPSIS
*      void doBlitter(struct blitcontext * context, struct Custom * custum);
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
*****************************************************************************
*
*/

void _libblitter_doBlitter(struct LibBlitterIFace *Self,
       struct blitcontext * context,
       struct Custom * custum)
{

}

