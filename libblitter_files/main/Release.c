/* :ts=4
 *  $VER: Release.c $Revision$ (11-Aug-2021)
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

/****** libblitter/main/Release ******************************************
*
*   NAME
*      Release -- Description
*
*   SYNOPSIS
*      ULONG Release(void);
*
*   FUNCTION
*
*   INPUTS
*
*   RESULT
*       The result ...
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

ULONG _libblitter_Release(struct LibBlitterIFace *Self)
{
    return Self -> Data.RefCount--;
}

