#ifndef LIBBLITTER_INTERFACE_DEF_H
#define LIBBLITTER_INTERFACE_DEF_H
/*
** This file is machine generated from idltool
** Do not edit
*/ 

#include <exec/types.i>
#include <exec/exec.i>
#include <exec/interfaces.i>

STRUCTURE LibBlitterIFace, InterfaceData_SIZE
	    FPTR ILibBlitter_Obtain
	    FPTR ILibBlitter_Release
	    FPTR LibBlitterIFace_Expunge_UNIMPLEMENTED
	    FPTR LibBlitterIFace_Clone_UNIMPLEMENTED
	    FPTR ILibBlitter_blit_init
	    FPTR ILibBlitter_doBlitter
	LABEL LibBlitterIFace_SIZE

#endif
