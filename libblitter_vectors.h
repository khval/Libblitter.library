
/* This file was generated by idltool 53.24. Do not edit */

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

/* forward declaration */
struct LibBlitterIFace;

extern ULONG                VARARGS68K _libblitter_Obtain(struct LibBlitterIFace *);
extern ULONG                VARARGS68K _libblitter_Release(struct LibBlitterIFace *);
extern void                 VARARGS68K _libblitter_blit_init(struct LibBlitterIFace *, struct blitcontext * context);
extern void                 VARARGS68K _libblitter_doBlitter(struct LibBlitterIFace *, struct blitcontext * context, struct Custom * custum);
