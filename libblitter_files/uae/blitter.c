 /*
  * UAE - The Un*x Amiga Emulator
  *
  * Custom chip emulation
  *
  * (c) 1995 Bernd Schmidt, Alessandro Bissacco
  */

#include "sysconfig.h"
#include "sysdeps.h"
#include "newcpu.h"
#include "options.h"
#include "memory.h"
#include "custom.h"
#include "blitter.h"
#include "blit.h"

#if 0
#include "events.h"
#include "uae.h"
#endif

#if 1
#include "hardware/custom.h"
struct Custom *custom;

#define get_cycles() 0
#define dmaen(item) TRUE

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

#define write_log(x,...)

// make compiler happy... don't care how....

#define SPCFLAG_BLTNASTY 512
#define CYCLE_UNIT 512
#define DMA_BLITTER   0x0040
#define DMA_BLITPRI   0x0400
#define INTREQ(x)
#define unset_special(x)
#define set_special(x)

// think this one executes the blitter, sorry its out of order.
#define events_schedule(x)

#endif



// will remove this line when... it compiles... (should be a argument for functions that needs it.)
// Library is shared, don't wont the data to be overwritten, by a different program... (program will think it has exclusive rights!)

//struct blitterContext *bC = NULL;			


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

static void blitter_dofast ( struct blitterContext *bC )
{
    int i,j;
    uaecptr bltadatptr = 0, bltbdatptr = 0, bltcdatptr = 0, bltddatptr = 0;
    uae_u8 mt = bC -> bltcon0 & 0xFF;

    blit_masktable[0] = bC -> blt_info.bltafwm;
    blit_masktable[bC -> blt_info.hblitsize - 1] &= bC -> blt_info.bltalwm;

    if (bC -> bltcon0 & 0x800) {
	bltadatptr = (uaecptr) bC->bltapt;
	bC -> bltapt += (bC -> blt_info.hblitsize*2 + bC -> blt_info.bltamod)*bC -> blt_info.vblitsize;
    }
    if (bC -> bltcon0 & 0x400) {
	bltbdatptr = (uaecptr) bC->bltbpt;
	bC -> bltbpt += (bC -> blt_info.hblitsize*2 + bC -> blt_info.bltbmod)*bC -> blt_info.vblitsize;
    }
    if (bC -> bltcon0 & 0x200) {
	bltcdatptr = (uaecptr) bC->bltcpt;
	bC -> bltcpt += (bC -> blt_info.hblitsize*2 + bC -> blt_info.bltcmod)*bC -> blt_info.vblitsize;
    }
    if (bC -> bltcon0 & 0x100) {
	bltddatptr = (uaecptr) bC->bltdpt;
	bC -> bltdpt += (bC -> blt_info.hblitsize*2 + bC -> blt_info.bltdmod)*bC -> blt_info.vblitsize;
    }

    if (blitfunc_dofast[mt] && ! bC -> blitfill)
	(*blitfunc_dofast[mt])(bC, bltadatptr, bltbdatptr, bltcdatptr, bltddatptr, &bC -> blt_info);
    else {
	uae_u32 blitbhold = bC -> blt_info.bltbhold;
	uae_u32 preva = 0, prevb = 0;
	uaecptr dstp = 0;
	int dodst = 0;

	/*if (!blitfill) write_log ("minterm %x not present\n",mt); */
	for (j = 0; j < bC -> blt_info.vblitsize; j++) {
	    bC -> blitfc = !!(bC -> bltcon1 & 0x4);
	    for (i = 0; i < bC -> blt_info.hblitsize; i++) {
		uae_u32 bltadat, blitahold;
		if (bltadatptr) {
		    bC -> blt_info.bltadat = bltadat = chipmem_agnus_wget (bltadatptr);
		    bltadatptr += 2;
		} else
		    bltadat = bC -> blt_info.bltadat;
		bltadat &= blit_masktable[i];
		blitahold = (((uae_u32)preva << 16) | bltadat) >> bC -> blt_info.blitashift;
		preva = bltadat;

		if (bltbdatptr) {
		    uae_u16 bltbdat;
		    bC -> blt_info.bltbdat = bltbdat = chipmem_agnus_wget (bltbdatptr);
		    bltbdatptr += 2;
		    blitbhold = (((uae_u32)prevb << 16) | bltbdat) >> bC -> blt_info.blitbshift;
		    prevb = bltbdat;
		}
		if (bltcdatptr) {
		    bC -> blt_info.bltcdat = chipmem_agnus_wget (bltcdatptr);
		    bltcdatptr += 2;
		}
		if (dodst)
		    chipmem_agnus_wput (dstp, bC -> blt_info.bltddat);
		bC -> blt_info.bltddat = blit_func (blitahold, blitbhold, bC -> blt_info.bltcdat, mt) & 0xFFFF;
		if (bC -> blitfill) {
		    uae_u16 d = bC -> blt_info.bltddat;
		    int ifemode = bC -> blitife ? 2 : 0;
		    int fc1 = blit_filltable[d & 255][ifemode + bC -> blitfc][1];
		    bC -> blt_info.bltddat = (blit_filltable[d & 255][ifemode + bC -> blitfc][0]
					+ (blit_filltable[d >> 8][ifemode + fc1][0] << 8));
		    bC -> blitfc = blit_filltable[d >> 8][ifemode + fc1][1];
		}
		if (bC -> blt_info.bltddat)
		    bC -> blt_info.blitzero = 0;
		if (bltddatptr) {
		    dodst = 1;
		    dstp = bltddatptr;
		    bltddatptr += 2;
		}
	    }
	    if (bltadatptr) bltadatptr += bC -> blt_info.bltamod;
	    if (bltbdatptr) bltbdatptr += bC -> blt_info.bltbmod;
	    if (bltcdatptr) bltcdatptr += bC -> blt_info.bltcmod;
	    if (bltddatptr) bltddatptr += bC -> blt_info.bltdmod;
	}
	if (dodst)
	    chipmem_agnus_wput (dstp, bC -> blt_info.bltddat);
	bC -> blt_info.bltbhold = blitbhold;
    }
    blit_masktable[0] = 0xFFFF;
    blit_masktable[bC -> blt_info.hblitsize - 1] = 0xFFFF;

    bC->bltstate = BLT_done;
}

static void blitter_dofast_desc( struct blitterContext *bC )
{
    int i,j;
    uaecptr bltadatptr = 0, bltbdatptr = 0, bltcdatptr = 0, bltddatptr = 0;
    uae_u8 mt = bC -> bltcon0 & 0xFF;

    blit_masktable[0] = bC->blt_info.bltafwm;
    blit_masktable[bC->blt_info.hblitsize - 1] &= bC->blt_info.bltalwm;

    if (bC -> bltcon0 & 0x800) {
	bltadatptr = (uaecptr) bC->bltapt;
	bC->bltapt -= (bC->blt_info.hblitsize*2 + bC->blt_info.bltamod)*bC->blt_info.vblitsize;
    }
    if (bC -> bltcon0 & 0x400) {
	bltbdatptr = (uaecptr) bC->bltbpt;
	bC->bltbpt -= (bC->blt_info.hblitsize*2 + bC->blt_info.bltbmod)*bC->blt_info.vblitsize;
    }
    if (bC -> bltcon0 & 0x200) {
	bltcdatptr = (uaecptr) bC->bltcpt;
	bC->bltcpt -= (bC->blt_info.hblitsize*2 + bC->blt_info.bltcmod)*bC->blt_info.vblitsize;
    }
    if (bC -> bltcon0 & 0x100) {
	bltddatptr = (uaecptr) bC->bltdpt;
	bC->bltdpt -= (bC->blt_info.hblitsize*2 + bC->blt_info.bltdmod)*bC->blt_info.vblitsize;
    }
    if (blitfunc_dofast_desc[mt] && !bC -> blitfill)
	(*blitfunc_dofast_desc[mt])( bC, bltadatptr, bltbdatptr, bltcdatptr, bltddatptr, &bC -> blt_info);
    else {
	uae_u32 blitbhold = bC -> blt_info.bltbhold;
	uae_u32 preva = 0, prevb = 0;
	uaecptr dstp = 0;
	int dodst = 0;

/*	if (!blitfill) write_log ("minterm %x not present\n",mt);*/
	for (j = 0; j < bC -> blt_info.vblitsize; j++) {
	    bC -> blitfc = !!( bC -> bltcon1 & 0x4);
	    for (i = 0; i < bC -> blt_info.hblitsize; i++) {
		uae_u32 bltadat, blitahold;
		if (bltadatptr) {
		    bC -> blt_info.bltadat = bltadat = chipmem_agnus_wget (bltadatptr);
		    bltadatptr -= 2;
		} else
		    bltadat = bC -> blt_info.bltadat;
		bltadat &= blit_masktable[i];
		blitahold = (((uae_u32)bltadat << 16) | preva) >> bC -> blt_info.blitdownashift;
		preva = bltadat;
		if (bltbdatptr) {
		    uae_u16 bltbdat;
		    bC -> blt_info.bltbdat = bltbdat = chipmem_agnus_wget (bltbdatptr);
		    bltbdatptr -= 2;
		    blitbhold = (((uae_u32)bltbdat << 16) | prevb) >> bC -> blt_info.blitdownbshift;
		    prevb = bltbdat;
		}
		if (bltcdatptr) {
		    bC -> blt_info.bltcdat = chipmem_agnus_wget (bltcdatptr);
		    bltcdatptr -= 2;
		}
		if (dodst)
		    chipmem_agnus_wput (dstp, bC -> blt_info.bltddat);
		bC -> blt_info.bltddat = blit_func (blitahold, blitbhold, bC -> blt_info.bltcdat, mt) & 0xFFFF;
		if (bC -> blitfill) {
		    uae_u16 d = bC->blt_info.bltddat;
		    int ifemode = bC -> blitife ? 2 : 0;
		    int fc1 = blit_filltable[d & 255][ifemode + bC -> blitfc][1];
		    bC -> blt_info.bltddat = (blit_filltable[d & 255][ifemode + bC -> blitfc][0]
					+ (blit_filltable[d >> 8][ifemode + fc1][0] << 8));
		    bC -> blitfc = blit_filltable[d >> 8][ifemode + fc1][1];
		}
		if (bC -> blt_info.bltddat)
		    bC -> blt_info.blitzero = 0;
		if (bltddatptr) {
		    dodst = 1;
		    dstp = bltddatptr;
		    bltddatptr -= 2;
		}
	    }
	    if (bltadatptr) bltadatptr -= bC -> blt_info.bltamod;
	    if (bltbdatptr) bltbdatptr -= bC -> blt_info.bltbmod;
	    if (bltcdatptr) bltcdatptr -= bC -> blt_info.bltcmod;
	    if (bltddatptr) bltddatptr -= bC -> blt_info.bltdmod;
	}
	if (dodst)
	    chipmem_agnus_wput (dstp, bC -> blt_info.bltddat);
	bC -> blt_info.bltbhold = blitbhold;
    }
    blit_masktable[0] = 0xFFFF;
    blit_masktable[bC -> blt_info.hblitsize - 1] = 0xFFFF;

    bC->bltstate = BLT_done;
}

STATIC_INLINE void blitter_read( struct blitterContext *bC )
{
    if (bC->bltcon0 & 0x200) {
	if (! dmaen (DMA_BLITTER))
	    return;
	bC -> blt_info.bltcdat = chipmem_bank.wget (bC -> bltcpt);
    }
    bC -> bltstate = BLT_work;
}

STATIC_INLINE void blitter_write( struct blitterContext *bC )
{
    if (bC -> blt_info.bltddat)
	bC -> blt_info.blitzero = 0;
    /* D-channel state has no effect on linedraw, but C must be enabled or nothing is drawn! */
    if (bC -> bltcon0 & 0x200) {
	if (!dmaen (DMA_BLITTER))
	    return;
	chipmem_agnus_wput (bC -> bltdpt, bC -> blt_info.bltddat);
    }
    bC -> bltstate = BLT_next;
}

STATIC_INLINE void blitter_line_incx( struct blitterContext *bC )
{
    if (++bC -> blinea_shift == 16) {
	bC -> blinea_shift = 0;
	bC -> bltcpt += 2;
    }
}

STATIC_INLINE void blitter_line_decx( struct blitterContext *bC )
{
    if (bC -> blinea_shift-- == 0) {
	bC -> blinea_shift = 15;
	bC -> bltcpt -= 2;
    }
}

STATIC_INLINE void blitter_line_decy( struct blitterContext *bC )
{
    bC -> bltcpt -= bC -> blt_info.bltcmod;
    bC -> blitonedot = 0;
}

STATIC_INLINE void blitter_line_incy( struct blitterContext *bC )
{
    bC -> bltcpt += bC -> blt_info.bltcmod;
    bC -> blitonedot = 0;
}

static void blitter_line( struct blitterContext *bC )
{
    uae_u16 blitahold = (bC -> blinea & bC -> blt_info.bltafwm) >> bC -> blinea_shift;
    uae_u16 blitbhold = bC -> blineb & 1 ? 0xFFFF : 0;
    uae_u16 blitchold = bC -> blt_info.bltcdat;

    if (bC -> blitsing && bC -> blitonedot)
	blitahold = 0;
    bC -> blitonedot = 1;
    bC -> blt_info.bltddat = blit_func (blitahold, blitbhold, blitchold, bC -> bltcon0 & 0xFF);
    if (!bC -> blitsign) {
	if (bC -> bltcon0 & 0x800)
	    bC -> bltapt += (uae_s16)bC -> blt_info.bltamod;
	if (bC -> bltcon1 & 0x10) {
	    if (bC -> bltcon1 & 0x8)
		blitter_line_decy( bC );
	    else
		blitter_line_incy( bC );
	} else {
	    if (bC -> bltcon1 & 0x8)
		blitter_line_decx( bC );
	    else
		blitter_line_incx( bC );
	}
    } else {
	if (bC -> bltcon0 & 0x800)
	    bC -> bltapt += (uae_s16) bC -> blt_info.bltbmod;
    }
    if (bC -> bltcon1 & 0x10) {
	if (bC -> bltcon1 & 0x4)
	    blitter_line_decx( bC );
	else
	    blitter_line_incx( bC );
    } else {
	if (bC -> bltcon1 & 0x4)
	    blitter_line_decy( bC );
	else
	    blitter_line_incy( bC );
    }
    bC->blitsign = 0 > (uae_s16) bC->bltapt;
    bC->bltstate = BLT_write;
}

STATIC_INLINE void blitter_nxline( struct blitterContext *bC )
{
    bC -> blineb = (bC -> blineb << 1) | (bC -> blineb >> 15);
    bC -> blt_info.vblitsize--;
    bC -> bltstate = BLT_read;
}

static void blit_init( struct blitterContext *bC )
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

static void actually_do_blit( struct blitterContext *bC )
{
    if (bC->blitline) {
	do {
	    blitter_read( bC );
	    blitter_line( bC );
	    blitter_write( bC );
	    bC -> bltdpt = bC -> bltcpt;
	    blitter_nxline( bC );
	    if (bC -> blt_info.vblitsize == 0)
		bC->bltstate = BLT_done;
	    
	} while (bC->bltstate != BLT_done);
    } else {
	if (bC->blitdesc)
	    blitter_dofast_desc( bC );
	else
	    blitter_dofast( bC );
    }
#if 0
    blitter_done_notify ();
#endif
}

void blitter_handler ( struct blitterContext *bC )
{
    if (!dmaen(DMA_BLITTER)) {
	event_blitter -> active = 1;
	event_blitter -> oldcycles = get_cycles();
	event_blitter -> evtime = 10 * CYCLE_UNIT + get_cycles (); /* wait a little */
	return; /* gotta come back later. */
    }
    actually_do_blit( bC );

    INTREQ(0x8040);
    event_blitter -> active = 0;
    unset_special (SPCFLAG_BLTNASTY);
}

#if 0



#endif

void do_blitter ( struct blitterContext *bC )
{
    int ch = (bC -> bltcon0 & 0x0f00) >> 8;
    bC -> blit_diag = blit_cycle_diagram_start[ch];

    bC -> blit_firstline_cycles = bC -> blit_first_cycle = get_cycles ();
    bC -> blit_last_cycle = 0;
    if (!currprefs.immediate_blits) {
	if (!bC->blitline) {
	    bC -> blit_cycles = bC -> blit_diag[1];
	    bC -> blit_firstline_cycles += bC -> blit_cycles * bC -> blt_info.hblitsize * CYCLE_UNIT;
	    bC -> blit_cycles *= bC -> blt_info.vblitsize * bC -> blt_info.hblitsize;
	} else
	     bC -> blit_cycles = 20; /* Desert Dream demo freezes if line draw is too fast */
    } else
	bC -> blit_cycles = 1;

    blit_init( bC );

    event_blitter -> active = 1;
    event_blitter -> oldcycles = get_cycles ();
    event_blitter -> evtime = bC -> blit_cycles * CYCLE_UNIT + get_cycles ();
    events_schedule();

    unset_special (SPCFLAG_BLTNASTY);
    if (dmaen(DMA_BLITPRI))
	set_special (SPCFLAG_BLTNASTY);

}

void maybe_blit (struct blitterContext *bC, int modulo)
{
    static int warned = 0;
    if (bC->bltstate == BLT_done)
	return;

    if (!warned) {
	warned = 1;
	write_log ("warning: Program does not wait for blitter\n");
    }
    if (!event_blitter -> active)
	write_log ("FOO!!?\n");

    if (modulo && get_cycles() < bC -> blit_firstline_cycles)
	return;
    blitter_handler( bC );
}

int blitnasty( struct blitterContext *bC )
{
    int cycles, ccnt;
    if (!(bC->regs.spcflags & SPCFLAG_BLTNASTY))
	return 0;
    if (bC -> bltstate == BLT_done)
	return 0;
    if (!dmaen(DMA_BLITTER))
	return 0;
    cycles = (get_cycles() - bC -> blit_first_cycle) / CYCLE_UNIT;
    ccnt = 0;
    while (bC -> blit_last_cycle < cycles) {
	int c;
	if (bC -> blit_last_cycle < bC -> blit_diag[0])
	    c = bC -> blit_diag[ bC -> blit_last_cycle + 2];
	else
	    c = bC -> blit_diag[((bC -> blit_last_cycle - bC -> blit_diag[0]) % bC -> blit_diag[1]) + 2 + bC -> blit_diag[0]];
	bC -> blit_last_cycle ++;
	if (!c)
	    return 0;
	ccnt++;
    }
    return ccnt;
}
