
#include <exec/libraries.h>
#include <exec/emulation.h>
#include <proto/libblitter.h>

#include <hardware/custom.h>

#define __USE_INLINE__

#include <stdio.h>
#include <proto/exec.h>

#include "blitzen/blitzen.h"

extern void _libblitter_BLTSIZH(struct LibBlitterIFace *Self,  struct Custom * custom);
extern void _libblitter_BLTSIZE(struct LibBlitterIFace *Self,  struct Custom * custom);

STATIC APTR stub_Open_ppc(ULONG *regarray);
STATIC APTR stub_Close_ppc(ULONG *regarray);
STATIC APTR stub_Expunge_ppc(ULONG *regarray);
STATIC ULONG stub_Reserved_ppc(ULONG *regarray);
STATIC void stub_BLTSIZH_ppc(ULONG *regarray);
STATIC void stub_BLTSIZE_ppc(ULONG *regarray);

const struct EmuTrap stub_Open = { TRAPINST, TRAPTYPE, (void *) stub_Open_ppc };
const struct EmuTrap stub_Close = { TRAPINST, TRAPTYPE, (void *) stub_Close_ppc };
const struct EmuTrap stub_Expunge = { TRAPINST, TRAPTYPE, (void *) stub_Expunge_ppc };
const struct EmuTrap stub_Reserved = { TRAPINST, TRAPTYPE, (void *) stub_Reserved_ppc };
const struct EmuTrap stub_BLTSIZH = { TRAPINST, TRAPTYPE, (void *) stub_BLTSIZH_ppc };
const struct EmuTrap stub_BLTSIZE = { TRAPINST, TRAPTYPE, (void *) stub_BLTSIZE_ppc };

const ULONG VecTable68K[] = {
	(ULONG) &stub_Open,
	(ULONG) &stub_Close,
	(ULONG) &stub_Expunge,
	(ULONG) &stub_Reserved,
	(ULONG) &stub_BLTSIZH,
	(ULONG) &stub_BLTSIZE,
	(ULONG)-1
};

STATIC APTR stub_Open_ppc(ULONG *regarray)
{
	struct Library *Base = (struct Library *) regarray[REG68K_A6/4];
	struct ExtendedLibrary *ExtLib = (struct ExtendedLibrary *) ((ULONG)Base + Base->lib_PosSize);
	struct LibraryManagerInterface *Self = (struct LibraryManagerInterface *) ExtLib->ILibrary;

	regarray[REG68K_D0/4] = (ULONG) Self -> Open( 0);

	return (APTR) regarray[REG68K_D0/4];
}

STATIC APTR stub_Close_ppc(ULONG *regarray)
{
	struct Library *Base = (struct Library *) regarray[REG68K_A6/4];
	struct ExtendedLibrary *ExtLib = (struct ExtendedLibrary *) ((ULONG)Base + Base->lib_PosSize);
	struct LibraryManagerInterface *Self = (struct LibraryManagerInterface *) ExtLib->ILibrary;

	regarray[REG68K_D0/4] = (ULONG) Self -> Close();

	return (APTR) regarray[REG68K_D0/4];
}

STATIC APTR stub_Expunge_ppc(ULONG *regarray)
{
	return NULL;
}

STATIC ULONG stub_Reserved_ppc(ULONG *regarray)
{
	return 0UL;
}

STATIC void stub_BLTSIZH_ppc(ULONG *regarray)
{
	 _libblitter_BLTSIZH(NULL,(struct Custom *) regarray[REG68K_A6/4]);;
}

STATIC void stub_BLTSIZE_ppc(ULONG *regarray)
{
	 _libblitter_BLTSIZE(NULL, (struct Custom *) regarray[REG68K_A6/4]);;
}

