 /*
  * UAE - The Un*x Amiga Emulator
  *
  * Blitter emulation
  *
  * (c) 1995 Bernd Schmidt
  */

#if 0
struct bltinfo {
    int blitzero;
    int blitashift,blitbshift,blitdownashift,blitdownbshift;
    uae_u32 bltadat, bltbdat, bltcdat,bltddat,bltahold,bltbhold,bltafwm,bltalwm;
    int vblitsize,hblitsize;
    int bltamod,bltbmod,bltcmod,bltdmod;
};
#else
struct bltinfo {
    int blitzero;
    int blitashift,blitbshift,blitdownashift,blitdownbshift;
    uae_u16 bltadat, bltbdat, bltcdat,bltddat,bltahold,bltbhold,bltafwm,bltalwm;
    int vblitsize,hblitsize;
    int bltamod,bltbmod,bltcmod,bltdmod;
};
#endif
extern enum blitter_states {
    BLT_done, BLT_init, BLT_read, BLT_work, BLT_write, BLT_next
} ;


// we setup the context when we call the blitter... hate to change too many things...

struct blitterContext
{
	uae_u16 bltsize;
	uae_u16 oldvblts;
	uae_u16 bltcon0, bltcon1;
	uae_u32 bltapt, bltbpt, bltcpt, bltdpt;
	int blinea_shift;
	uae_u16 blinea, blineb;
	int blitline, blitfc, blitfill, blitife, blitsing, blitdesc;
	int blitonedot, blitsign;
	long int bltwait;
	struct bltinfo blt_info;
	enum blitter_states bltstate;
	struct regstruct regs;

	// more 

	long int blit_cycles;
	long blit_firstline_cycles;
	long blit_first_cycle;
	int blit_last_cycle;
	uae_u8 *blit_diag;
};

#if 0
extern struct bltinfo blt_info;
extern uae_u16 bltsize, oldvblts;
extern uae_u16 bltcon0,bltcon1;
extern int blinea_shift;
extern uae_u32 bltapt,bltbpt,bltcpt,bltdpt;
#endif

extern void maybe_blit( struct blitterContext *bC ,int);
extern int blitnasty( struct blitterContext *bC );
extern void blitter_handler( struct blitterContext *bC  );
extern void build_blitfilltable();
extern void do_blitter( struct blitterContext *bC );

#if 0
extern void blitter_done_notify (void);
#endif

typedef void blitter_func( struct blitterContext *bC,uaecptr, uaecptr, uaecptr, uaecptr, struct bltinfo *);

#define BLITTER_MAX_WORDS 2048

extern blitter_func *const blitfunc_dofast[256];
extern blitter_func *const blitfunc_dofast_desc[256];
extern uae_u32 blit_masktable[BLITTER_MAX_WORDS];
