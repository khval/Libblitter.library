#ifndef INLINE4_LIBBLITTER_H
#define INLINE4_LIBBLITTER_H

/*
** This file was auto generated by idltool 53.35.
**
** It provides compatibility to OS3 style library
** calls by substituting functions.
**
** Do not edit manually.
*/ 

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef EXEC_EXEC_H
#include <exec/exec.h>
#endif
#ifndef EXEC_INTERFACES_H
#include <exec/interfaces.h>
#endif

#ifndef LIBRARIES_LIBBLITTER_H
#include <libraries/libblitter.h>
#endif
#ifndef HARDWARE_CUSTOM_H
#include <hardware/custom.h>
#endif
#include <interfaces/libblitter.h>

/* Inline macros for Interface "main" */
#define BLTSIZH(custom) ILibBlitter->BLTSIZH((custom))
#define BLTSIZE(custom) ILibBlitter->BLTSIZE((custom))

#endif /* INLINE4_LIBBLITTER_H */
