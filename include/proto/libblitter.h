#ifndef PROTO_LIBBLITTER_H
#define PROTO_LIBBLITTER_H

/*
**	$Id$
**
**	Prototype/inline/pragma header file combo
**
**	Copyright (c) 2010 Hyperion Entertainment CVBA.
**	All Rights Reserved.
*/

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef LIBRARIES_LIBBLITTER_H
#include <libraries/libblitter.h>
#endif
#ifndef HARDWARE_CUSTOM_H
#include <hardware/custom.h>
#endif

/****************************************************************************/

#ifndef __NOLIBBASE__
 #if defined(__cplusplus) && defined(__USE_AMIGAOS_NAMESPACE__)
  extern struct AmigaOS::Library * LibBlitterBase;
 #else
  extern struct Library * LibBlitterBase;
 #endif
#endif /* __NOLIBBASE__ */

/****************************************************************************/

#ifdef __amigaos4__
 #include <interfaces/libblitter.h>
 #ifdef __USE_INLINE__
  #include <inline4/libblitter.h>
 #endif /* __USE_INLINE__ */
 #ifndef CLIB_LIBBLITTER_PROTOS_H
  #define CLIB_LIBBLITTER_PROTOS_H 1
 #endif /* CLIB_LIBBLITTER_PROTOS_H */
 #ifndef __NOGLOBALIFACE__
  #if defined(__cplusplus) && defined(__USE_AMIGAOS_NAMESPACE__)
   extern struct AmigaOS::LibBlitterIFace * ILibBlitter;
  #else
   extern struct LibBlitterIFace * ILibBlitter;
  #endif
 #endif /* __NOGLOBALIFACE__ */
#else /* __amigaos4__ */
 #ifndef CLIB_LIBBLITTER_PROTOS_H
  #include <clib/libblitter_protos.h>
 #endif /* CLIB_LIBBLITTER_PROTOS_H */
 #if defined(__GNUC__)
  #ifndef __PPC__
   #include <inline/libblitter.h>
  #else /* __PPC__ */
   #include <ppcinline/libblitter.h>
  #endif /* __PPC__ */
 #elif defined(__VBCC__)
  #ifndef __PPC__
   #include <inline/libblitter_protos.h>
  #endif /* __PPC__ */
 #else /* __GNUC__ */
  #include <pragmas/libblitter_pragmas.h>
 #endif /* __GNUC__ */
#endif /* __amigaos4__ */

/****************************************************************************/

#endif /* PROTO_LIBBLITTER_H */
