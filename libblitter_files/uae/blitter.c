 /*
  * UAE - The Un*x Amiga Emulator
  *
  * Custom chip emulation
  *
  * (c) 1995 Bernd Schmidt, Alessandro Bissacco
  */

#include "sysconfig.h"
#include "sysdeps.h"
#include "options.h"
#include "memory.h"
#include "custom.h"
#include "blitter.h"
#include "blit.h"

#if 0
#include "events.h"
#include "uae.h"
#include "newcpu.h"
#endif

#if 1
#include "hardware/custom.h"
struct Custom *custom;

struct a_bad_day
{
	uae_u16 (*wget) (uae_u32 address);

} chipmem_bank = {NULL};

struct one_more_bad_day
{
	int active;
	int oldcycles;
	int evtime;
} *event_blitter;

struct wtf_is_this 
{
	int immediate_blits;
} currprefs;

#define DMA_BLITTER 0xFEEDF00D

#define write_log(x,...)

// make compiler happy... don't care how....

#define SPCFLAG_BLTNASTY
#define CYCLE_UNIT 1
#define DMA_BLITPRI

#endif



// will remove this line when... it compiles... (should be a argument for functions that needs it.)
// Library is shared, don't wont the data to be overwritten, by a different program... (program will think it has exclusive rights!)

struct blitterContext *bC = NULL;			


static uae_u8 blit_filltable[256][4][2];
uae_u32 blit_masktable[BLITTER_MAX_WORDS];

static uae_u8 blit_cycle_diagram_start[][10] =
{
    { 0, 1, 0 },		/* 0 */
    { 0, 2, 4,0 },		/* 1 */
    { 0, 2, 3,0 },		/* 2 */
    { 2, 3, 3,0, 0,3,4 },	/* 3 */
    { 0, 3, 2,0,0 },		/* 4 */
    { 2, 3, 2,0, 0,2,4 },	/* 5 */
    { 0, 3, 2,3,0 },		/* 6 */
    { 3, 4, 2,3,0, 0,2,3,4 },	/* 7 */
    { 0, 2, 1,0 },		/* 8 */
    { 2, 2, 1,0, 1,4 },		/* 9 */
    { 0, 2, 1,3 },		/* A */
    { 3, 3, 1,3,0, 1,3,4 },	/* B */
    { 2, 3, 1,2, 0,1,2 },	/* C */
    { 3, 3, 1,2,0, 1,2,4 },	/* D */
    { 0, 3, 1,2,3 },		/* E */
    { 4, 4, 1,2,3,0, 1,2,3,4 }	/* F */
};

void build_blitfilltable (void)
{
    unsigned int d, fillmask;
    int i;

    for (i = 0; i < BLITTER_MAX_WORDS; i++)
	blit_masktable[i] = 0xFFFF;

    for (d = 0; d < 256; d++) {
	for (i = 0; i < 4; i++) {
	    int fc = i & 1;
	    uae_u8 data = d;
	    for (fillmask = 1; fillmask != 0x100; fillmask <<= 1) {
		uae_u16 tmp = data;
		if (fc) {
		    if (i & 2)
			data |= fillmask;
		    else
			data ^= fillmask;
		}
		if (tmp & fillmask) fc = !fc;
	    }
	    blit_filltable[d][i][0] = data;
	    blit_filltable[d][i][1] = fc;
	}
    }
}

static void blitter_dofast (void)
{
    int i,j;
    uaecptr bltadatptr = 0, bltbdatptr = 0, bltcdatptr = 0, bltddatptr = 0;
    uae_u8 mt = bltcon0 & 0xFF;

    blit_masktable[0] = blt_info.bltafwm;
    blit_masktable[blt_info.hblitsize - 1] &= blt_info.bltalwm;

    if (bltcon0 & 0x800) {
	bltadatptr = (uaecptr) bC->bltapt;
	bC -> bltapt += (bC -> blt_info.hblitsize*2 + bC -> blt_info.bltamod)*bC -> blt_info.vblitsize;
    }
    if (bltcon0 & 0x400) {
	bltbdatptr = (uaecptr) bC->bltbpt;
	bltbpt += (blt_info.hblitsize*2 + blt_info.bltbmod)*blt_info.vblitsize;
    }
    if (bltcon0 & 0x200) {
	bltcdatptr = (uaecptr) bC->bltcpt;
	bltcpt += (blt_info.hblitsize*2 + blt_info.bltcmod)*blt_info.vblitsize;
    }
    if (bltcon0 & 0x100) {
	bltddatptr = (uaecptr) bC->bltdpt;
	bltdpt += (blt_info.hblitsize*2 + blt_info.bltdmod)*blt_info.vblitsize;
    }

    if (blitfunc_dofast[mt] && ! bC -> blitfill)
	(*blitfunc_dofast[mt])(bltadatptr, bltbdatptr, bltcdatptr, bltddatptr, &blt_info);
    else {
	uae_u32 blitbhold = blt_info.bltbhold;
	uae_u32 preva = 0, prevb = 0;
	uaecptr dstp = 0;
	int dodst = 0;

	/*if (!blitfill) write_log ("minterm %x not present\n",mt); */
	for (j = 0; j < blt_info.vblitsize; j++) {
	    bC -> blitfc = !!(bC -> bltcon1 & 0x4);
	    for (i = 0; i < bC -> blt_info.hblitsize; i++) {
		uae_u32 bltadat, blitahold;
		if (bltadatptr) {
		    blt_info.bltadat = bltadat = chipmem_agnus_wget (bltadatptr);
		    bltadatptr += 2;
		} else
		    bltadat = blt_info.bltadat;
		bltadat &= blit_masktable[i];
		blitahold = (((uae_u32)preva << 16) | bltadat) >> blt_info.blitashift;
		preva = bltadat;

		if (bltbdatptr) {
		    uae_u16 bltbdat;
		    blt_info.bltbdat = bltbdat = chipmem_agnus_wget (bltbdatptr);
		    bltbdatptr += 2;
		    blitbhold = (((uae_u32)prevb << 16) | bltbdat) >> blt_info.blitbshift;
		    prevb = bltbdat;
		}
		if (bltcdatptr) {
		    blt_info.bltcdat = chipmem_agnus_wget (bltcdatptr);
		    bltcdatptr += 2;
		}
		if (dodst)
		    chipmem_agnus_wput (dstp, blt_info.bltddat);
		blt_info.bltddat = blit_func (blitahold, blitbhold, blt_info.bltcdat, mt) & 0xFFFF;
		if (bC -> blitfill) {
		    uae_u16 d = bC -> blt_info.bltddat;
		    int ifemode = bC -> blitife ? 2 : 0;
		    int fc1 = blit_filltable[d & 255][ifemode + bC -> blitfc][1];
		    bC -> blt_info.bltddat = (blit_filltable[d & 255][ifemode + bC -> blitfc][0]
					+ (blit_filltable[d >> 8][ifemode + fc1][0] << 8));
		    bC -> blitfc = blit_filltable[d >> 8][ifemode + fc1][1];
		}
		if (blt_info.bltddat)
		    blt_info.blitzero = 0;
		if (bltddatptr) {
		    dodst = 1;
		    dstp = bltddatptr;
		    bltddatptr += 2;
		}
	    }
	    if (bltadatptr) bltadatptr += blt_info.bltamod;
	    if (bltbdatptr) bltbdatptr += blt_info.bltbmod;
	    if (bltcdatptr) bltcdatptr += blt_info.bltcmod;
	    if (bltddatptr) bltddatptr += blt_info.bltdmod;
	}
	if (dodst)
	    chipmem_agnus_wput (dstp, blt_info.bltddat);
	blt_info.bltbhold = blitbhold;
    }
    blit_masktable[0] = 0xFFFF;
    blit_masktable[blt_info.hblitsize - 1] = 0xFFFF;

    bltstate = BLT_done;
}

static void blitter_dofast_desc (void)
{
    int i,j;
    uaecptr bltadatptr = 0, bltbdatptr = 0, bltcdatptr = 0, bltddatptr = 0;
    uae_u8 mt = bltcon0 & 0xFF;

    blit_masktable[0] = bC->blt_info.bltafwm;
    blit_masktable[bC->blt_info.hblitsize - 1] &= bC->blt_info.bltalwm;

    if (bltcon0 & 0x800) {
	bltadatptr = (uaecptr) bC->bltapt;
	bC->bltapt -= (bC->blt_info.hblitsize*2 + bC->blt_info.bltamod)*bC->blt_info.vblitsize;
    }
    if (bltcon0 & 0x400) {
	bltbdatptr = (uaecptr) bC->bltbpt;
	bC->bltbpt -= (bC->blt_info.hblitsize*2 + bC->blt_info.bltbmod)*bC->blt_info.vblitsize;
    }
    if (bltcon0 & 0x200) {
	bltcdatptr = (uaecptr) bC->bltcpt;
	bC->bltcpt -= (bC->blt_info.hblitsize*2 + bC->blt_info.bltcmod)*bC->blt_info.vblitsize;
    }
    if (bltcon0 & 0x100) {
	bltddatptr = (uaecptr) bC->bltdpt;
	bC->bltdpt -= (bC->blt_info.hblitsize*2 + bC->blt_info.bltdmod)*bC->blt_info.vblitsize;
    }
    if (blitfunc_dofast_desc[mt] && !bC -> blitfill)
	(*blitfunc_dofast_desc[mt])(bltadatptr, bltbdatptr, bltcdatptr, bltddatptr, &bC -> blt_info);
    else {
	uae_u32 blitbhold = bC -> blt_info.bltbhold;
	uae_u32 preva = 0, prevb = 0;
	uaecptr dstp = 0;
	int dodst = 0;

/*	if (!blitfill) write_log ("minterm %x not present\n",mt);*/
	for (j = 0; j < blt_info.vblitsize; j++) {
	    bC -> blitfc = !!( bC -> bltcon1 & 0x4);
	    for (i = 0; i < bC -> blt_info.hblitsize; i++) {
		uae_u32 bltadat, blitahold;
		if (bltadatptr) {
		    blt_info.bltadat = bltadat = chipmem_agnus_wget (bltadatptr);
		    bltadatptr -= 2;
		} else
		    bltadat = blt_info.bltadat;
		bltadat &= blit_masktable[i];
		blitahold = (((uae_u32)bltadat << 16) | preva) >> blt_info.blitdownashift;
		preva = bltadat;
		if (bltbdatptr) {
		    uae_u16 bltbdat;
		    blt_info.bltbdat = bltbdat = chipmem_agnus_wget (bltbdatptr);
		    bltbdatptr -= 2;
		    blitbhold = (((uae_u32)bltbdat << 16) | prevb) >> blt_info.blitdownbshift;
		    prevb = bltbdat;
		}
		if (bltcdatptr) {
		    blt_info.bltcdat = chipmem_agnus_wget (bltcdatptr);
		    bltcdatptr -= 2;
		}
		if (dodst)
		    chipmem_agnus_wput (dstp, blt_info.bltddat);
		blt_info.bltddat = blit_func (blitahold, blitbhold, blt_info.bltcdat, mt) & 0xFFFF;
		if (bC -> blitfill) {
		    uae_u16 d = bC->blt_info.bltddat;
		    int ifemode = bC -> blitife ? 2 : 0;
		    int fc1 = blit_filltable[d & 255][ifemode + bC -> blitfc][1];
		    blt_info.bltddat = (blit_filltable[d & 255][ifemode + bC -> blitfc][0]
					+ (blit_filltable[d >> 8][ifemode + fc1][0] << 8));
		    bC -> blitfc = blit_filltable[d >> 8][ifemode + fc1][1];
		}
		if (blt_info.bltddat)
		    blt_info.blitzero = 0;
		if (bltddatptr) {
		    dodst = 1;
		    dstp = bltddatptr;
		    bltddatptr -= 2;
		}
	    }
	    if (bltadatptr) bltadatptr -= blt_info.bltamod;
	    if (bltbdatptr) bltbdatptr -= blt_info.bltbmod;
	    if (bltcdatptr) bltcdatptr -= blt_info.bltcmod;
	    if (bltddatptr) bltddatptr -= blt_info.bltdmod;
	}
	if (dodst)
	    chipmem_agnus_wput (dstp, blt_info.bltddat);
	blt_info.bltbhold = blitbhold;
    }
    blit_masktable[0] = 0xFFFF;
    blit_masktable[blt_info.hblitsize - 1] = 0xFFFF;

    bltstate = BLT_done;
}

STATIC_INLINE void blitter_read (void)
{
    if (bC->bltcon0 & 0x200) {
	if (! dmaen (DMA_BLITTER))
	    return;
	bC -> blt_info.bltcdat = chipmem_bank.wget (bltcpt);
    }
    bC -> bltstate = BLT_work;
}

STATIC_INLINE void blitter_write (void)
{
    if (bC -> blt_info.bltddat)
	bC -> blt_info.blitzero = 0;
    /* D-channel state has no effect on linedraw, but C must be enabled or nothing is drawn! */
    if (bltcon0 & 0x200) {
	if (!dmaen (DMA_BLITTER))
	    return;
	chipmem_agnus_wput (bltdpt, blt_info.bltddat);
    }
    bC -> bltstate = BLT_next;
}

STATIC_INLINE void blitter_line_incx (void)
{
    if (++blinea_shift == 16) {
	blinea_shift = 0;
	bltcpt += 2;
    }
}

STATIC_INLINE void blitter_line_decx (void)
{
    if (blinea_shift-- == 0) {
	blinea_shift = 15;
	bltcpt -= 2;
    }
}

STATIC_INLINE void blitter_line_decy (void)
{
    bltcpt -= bC -> blt_info.bltcmod;
    bC -> blitonedot = 0;
}

STATIC_INLINE void blitter_line_incy (void)
{
    bC -> bltcpt += bC -> blt_info.bltcmod;
    bC -> blitonedot = 0;
}

static void blitter_line (void)
{
    uae_u16 blitahold = (bC -> blinea & bC -> blt_info.bltafwm) >> blinea_shift;
    uae_u16 blitbhold = bC -> blineb & 1 ? 0xFFFF : 0;
    uae_u16 blitchold = bC -> blt_info.bltcdat;

    if (bC -> blitsing && bC -> blitonedot)
	blitahold = 0;
    bC -> blitonedot = 1;
    bC -> blt_info.bltddat = blit_func (blitahold, blitbhold, blitchold, bC -> bltcon0 & 0xFF);
    if (!bC -> blitsign) {
	if (bC -> bltcon0 & 0x800)
	    bC -> bltapt += (uae_s16)bC -> blt_info.bltamod;
	if (bltcon1 & 0x10) {
	    if (bltcon1 & 0x8)
		blitter_line_decy ();
	    else
		blitter_line_incy ();
	} else {
	    if (bltcon1 & 0x8)
		blitter_line_decx ();
	    else
		blitter_line_incx ();
	}
    } else {
	if (bltcon0 & 0x800)
	    bltapt += (uae_s16)blt_info.bltbmod;
    }
    if (bltcon1 & 0x10) {
	if (bltcon1 & 0x4)
	    blitter_line_decx ();
	else
	    blitter_line_incx ();
    } else {
	if (bltcon1 & 0x4)
	    blitter_line_decy ();
	else
	    blitter_line_incy ();
    }
    bC->blitsign = 0 > (uae_s16) bC->bltapt;
    bC->bltstate = BLT_write;
}

STATIC_INLINE void blitter_nxline (void)
{
    bC -> blineb = (bC -> blineb << 1) | (bC -> blineb >> 15);
    bC -> blt_info.vblitsize--;
    bC -> bltstate = BLT_read;
}

static void blit_init (void)
{
    bC -> blt_info.blitzero = 1;
    bC -> blitline = bC -> bltcon1 & 1;
    bC -> blt_info.blitashift = bC -> bltcon0 >> 12;
    bC -> blt_info.blitdownashift = 16 - bC -> blt_info.blitashift;
    bC -> blt_info.blitbshift = bC -> bltcon1 >> 12;
    bC -> blt_info.blitdownbshift = 16 - bC -> blt_info.blitbshift;

    if (bC->blitline) {
	if (bC->blt_info.hblitsize != 2)
	    write_log ("weird hblitsize in linemode: %d\n", bC->blt_info.hblitsize);

	bC->blitsing = bC->bltcon1 & 0x2;
	bC->blinea = bC->blt_info.bltadat;
	bC->blineb = (bC->blt_info.bltbdat >> bC->blt_info.blitbshift) | (bC->blt_info.bltbdat << (16-bC->blt_info.blitbshift));
#if 0
	if (blineb != 0xFFFF && blineb != 0)
	    write_log ("%x %x %d %x\n", blineb, blt_info.bltbdat, blt_info.blitbshift, bltcon1);
#endif
	bC->blitsign = bC->bltcon1 & 0x40;
	bC->blitonedot = 0;
    } else {
	bC->blitfc = !!(bC->bltcon1 & 0x4);
	bC->blitife = bC->bltcon1 & 0x8;
	bC->blitfill = bC->bltcon1 & 0x18;
	if ((bC->bltcon1 & 0x18) == 0x18) {
	    /* Digital "Trash" demo does this; others too. Apparently, no
	     * negative effects. */
	    static int warn = 1;
	    if (warn)
		write_log ("warning: weird fill mode (further messages suppressed)\n");
	    warn = 0;
	}
	bC->blitdesc = bC->bltcon1 & 0x2;
	if (bC->blitfill && !bC->blitdesc) {
	    static int warn = 1;
	    if (warn)
		write_log ("warning: blitter fill without desc (further messages suppressed)\n");
	    warn = 0;
	}
    }
}

static void actually_do_blit (void)
{
    if (bC->blitline) {
	do {
	    blitter_read ();
	    blitter_line ();
	    blitter_write ();
	    bltdpt = bltcpt;
	    blitter_nxline ();
	    if (blt_info.vblitsize == 0)
		bC->bltstate = BLT_done;
	    
	} while (bC->bltstate != BLT_done);
    } else {
	if (bC->blitdesc)
	    blitter_dofast_desc ();
	else
	    blitter_dofast ();
    }
    blitter_done_notify ();
}

void blitter_handler (void)
{
    if (!dmaen(DMA_BLITTER)) {
	event_blitter -> active = 1;
	event_blitter -> oldcycles = get_cycles ();
	event_blitter -> evtime = 10 * CYCLE_UNIT + get_cycles (); /* wait a little */
	return; /* gotta come back later. */
    }
    actually_do_blit ();

    INTREQ(0x8040);
    event_blitter -> active = 0;
    unset_special (SPCFLAG_BLTNASTY);
}

static long int blit_cycles;
static long blit_firstline_cycles;
static long blit_first_cycle;
static int blit_last_cycle;
static uae_u8 *blit_diag;

void do_blitter (void)
{
    int ch = (bltcon0 & 0x0f00) >> 8;
    blit_diag = blit_cycle_diagram_start[ch];

    blit_firstline_cycles = blit_first_cycle = get_cycles ();
    blit_last_cycle = 0;
    if (!currprefs.immediate_blits) {
	if (!bC->blitline) {
	    blit_cycles = blit_diag[1];
	    blit_firstline_cycles += blit_cycles * blt_info.hblitsize * CYCLE_UNIT;
	    blit_cycles *= blt_info.vblitsize * blt_info.hblitsize;
	} else
	     blit_cycles = 20; /* Desert Dream demo freezes if line draw is too fast */
    } else
	blit_cycles = 1;

    blit_init();

    event_blitter -> active = 1;
    event_blitter -> oldcycles = get_cycles ();
    event_blitter -> evtime = blit_cycles * CYCLE_UNIT + get_cycles ();
    events_schedule();

    unset_special (SPCFLAG_BLTNASTY);
    if (dmaen(DMA_BLITPRI))
	set_special (SPCFLAG_BLTNASTY);

}

void maybe_blit (int modulo)
{
    static int warned = 0;
    if (bltstate == BLT_done)
	return;

    if (!warned) {
	warned = 1;
	write_log ("warning: Program does not wait for blitter\n");
    }
    if (!event_blitter -> active)
	write_log ("FOO!!?\n");

    if (modulo && get_cycles() < blit_firstline_cycles)
	return;
    blitter_handler ();
}

int blitnasty (void)
{
    int cycles, ccnt;
    if (!(regs.spcflags & SPCFLAG_BLTNASTY))
	return 0;
    if (bltstate == BLT_done)
	return 0;
    if (!dmaen(DMA_BLITTER))
	return 0;
    cycles = (get_cycles () - blit_first_cycle) / CYCLE_UNIT;
    ccnt = 0;
    while (blit_last_cycle < cycles) {
	int c;
	if (blit_last_cycle < blit_diag[0])
	    c = blit_diag[blit_last_cycle + 2];
	else
	    c = blit_diag[((blit_last_cycle - blit_diag[0]) % blit_diag[1]) + 2 + blit_diag[0]];
	blit_last_cycle ++;
	if (!c)
	    return 0;
	ccnt++;
    }
    return ccnt;
}
