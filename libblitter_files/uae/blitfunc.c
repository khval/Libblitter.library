#include "sysconfig.h"
#include "sysdeps.h"
#include "newcpu.h"
#include "options.h"
#include "custom.h"
#include "memory.h"
#include "blitter.h"
#include "blitfunc.h"

void blitdofast_0 (struct blitterContext *bC,uaecptr pta, uaecptr ptb, uaecptr ptc, uaecptr ptd, struct bltinfo *b)
{
int i,j;
uae_u32 totald = 0;
uae_u32 dstd=0;
uaecptr dstp = 0;
int dodst = 0;
for (j = 0; j < b->vblitsize; j++) {
	for (i = 0; i < b->hblitsize; i++) {
		uae_u32 bltadat, srca;

		if (dodst) chipmem_agnus_wput (dstp, dstd);
		dstd = (0) & 0xFFFF;
		totald |= dstd;
		if (ptd) { dodst = 1; dstp = ptd; ptd += 2; }
	}
	if (ptd) ptd += b->bltdmod;
}
		if (dstp) chipmem_agnus_wput (dstp, dstd);
if (totald != 0) b->blitzero = 0;
}
void blitdofast_desc_0 (struct blitterContext *bC,uaecptr pta, uaecptr ptb, uaecptr ptc, uaecptr ptd, struct bltinfo *b)
{
uae_u32 totald = 0;
int i,j;
uae_u32 dstd=0;
uaecptr dstp = 0;
int dodst = 0;
for (j = 0; j < b->vblitsize; j++) {
	for (i = 0; i < b->hblitsize; i++) {
		uae_u32 bltadat, srca;
		if (dodst) chipmem_agnus_wput (dstp, dstd);
		dstd = (0) & 0xFFFF;
		totald |= dstd;
		if (ptd) { dodst = 1; dstp = ptd; ptd -= 2; }
	}
	if (ptd) ptd -= b->bltdmod;
}
		if (dodst) chipmem_agnus_wput (dstp, dstd);
if (totald != 0) b->blitzero = 0;
}
void blitdofast_a (struct blitterContext *bC,uaecptr pta, uaecptr ptb, uaecptr ptc, uaecptr ptd, struct bltinfo *b)
{
int i,j;
uae_u32 totald = 0;
uae_u32 preva = 0;
uae_u32 srcc = b->bltcdat;
uae_u32 dstd=0;
uaecptr dstp = 0;
int dodst = 0;
for (j = 0; j < b->vblitsize; j++) {
	for (i = 0; i < b->hblitsize; i++) {
		uae_u32 bltadat, srca;

		if (ptc) { srcc = chipmem_agnus_wget (ptc); ptc += 2; }
		if (pta) { bC -> blt_info.bltadat = bltadat = chipmem_agnus_wget (pta); pta += 2; } else { bltadat = bC -> blt_info.bltadat; }
		bltadat &= blit_masktable[i];
		srca = (((uae_u32)preva << 16) | bltadat) >> b->blitashift;
		preva = bltadat;
		if (dodst) chipmem_agnus_wput (dstp, dstd);
		dstd = ((~srca & srcc)) & 0xFFFF;
		totald |= dstd;
		if (ptd) { dodst = 1; dstp = ptd; ptd += 2; }
	}
	if (pta) pta += b->bltamod;
	if (ptc) ptc += b->bltcmod;
	if (ptd) ptd += b->bltdmod;
}
b->bltcdat = srcc;
		if (dstp) chipmem_agnus_wput (dstp, dstd);
if (totald != 0) b->blitzero = 0;
}
void blitdofast_desc_a (struct blitterContext *bC,uaecptr pta, uaecptr ptb, uaecptr ptc, uaecptr ptd, struct bltinfo *b)
{
uae_u32 totald = 0;
int i,j;
uae_u32 preva = 0;
uae_u32 srcc = b->bltcdat;
uae_u32 dstd=0;
uaecptr dstp = 0;
int dodst = 0;
for (j = 0; j < b->vblitsize; j++) {
	for (i = 0; i < b->hblitsize; i++) {
		uae_u32 bltadat, srca;
		if (ptc) { srcc = chipmem_agnus_wget (ptc); ptc -= 2; }
		if (pta) { bC ->  blt_info.bltadat = bltadat = chipmem_agnus_wget (pta); pta -= 2; } else { bltadat = bC -> blt_info.bltadat; }
		bltadat &= blit_masktable[i];
		srca = (((uae_u32)bltadat << 16) | preva) >> b->blitdownashift;
		preva = bltadat;
		if (dodst) chipmem_agnus_wput (dstp, dstd);
		dstd = ((~srca & srcc)) & 0xFFFF;
		totald |= dstd;
		if (ptd) { dodst = 1; dstp = ptd; ptd -= 2; }
	}
	if (pta) pta -= b->bltamod;
	if (ptc) ptc -= b->bltcmod;
	if (ptd) ptd -= b->bltdmod;
}
b->bltcdat = srcc;
		if (dodst) chipmem_agnus_wput (dstp, dstd);
if (totald != 0) b->blitzero = 0;
}
void blitdofast_2a (struct blitterContext *bC,uaecptr pta, uaecptr ptb, uaecptr ptc, uaecptr ptd, struct bltinfo *b)
{
int i,j;
uae_u32 totald = 0;
uae_u32 preva = 0;
uae_u32 prevb = 0, srcb = b->bltbhold;
uae_u32 srcc = b->bltcdat;
uae_u32 dstd=0;
uaecptr dstp = 0;
int dodst = 0;
for (j = 0; j < b->vblitsize; j++) {
	for (i = 0; i < b->hblitsize; i++) {
		uae_u32 bltadat, srca;

		if (ptc) { srcc = chipmem_agnus_wget (ptc); ptc += 2; }
		if (ptb) {
			uae_u32 bltbdat; bC -> blt_info.bltbdat = bltbdat = chipmem_agnus_wget (ptb); ptb += 2;
			srcb = (((uae_u32)prevb << 16) | bltbdat) >> b->blitbshift;
			prevb = bltbdat;
		}
		if (pta) { bC -> blt_info.bltadat = bltadat = chipmem_agnus_wget (pta); pta += 2; } else { bltadat = bC -> blt_info.bltadat; }
		bltadat &= blit_masktable[i];
		srca = (((uae_u32)preva << 16) | bltadat) >> b->blitashift;
		preva = bltadat;
		if (dodst) chipmem_agnus_wput (dstp, dstd);
		dstd = ((srcc & ~(srca & srcb))) & 0xFFFF;
		totald |= dstd;
		if (ptd) { dodst = 1; dstp = ptd; ptd += 2; }
	}
	if (pta) pta += b->bltamod;
	if (ptb) ptb += b->bltbmod;
	if (ptc) ptc += b->bltcmod;
	if (ptd) ptd += b->bltdmod;
}
b->bltbhold = srcb;
b->bltcdat = srcc;
		if (dstp) chipmem_agnus_wput (dstp, dstd);
if (totald != 0) b->blitzero = 0;
}
void blitdofast_desc_2a (struct blitterContext *bC,uaecptr pta, uaecptr ptb, uaecptr ptc, uaecptr ptd, struct bltinfo *b)
{
uae_u32 totald = 0;
int i,j;
uae_u32 preva = 0;
uae_u32 prevb = 0, srcb = b->bltbhold;
uae_u32 srcc = b->bltcdat;
uae_u32 dstd=0;
uaecptr dstp = 0;
int dodst = 0;
for (j = 0; j < b->vblitsize; j++) {
	for (i = 0; i < b->hblitsize; i++) {
		uae_u32 bltadat, srca;
		if (ptc) { srcc = chipmem_agnus_wget (ptc); ptc -= 2; }
		if (ptb) {
			uae_u32 bltbdat; bC -> blt_info.bltbdat = bltbdat = chipmem_agnus_wget (ptb); ptb -= 2;
			srcb = ((bltbdat << 16) | prevb) >> b->blitdownbshift;
			prevb = bltbdat;
		}
		if (pta) { bC ->  blt_info.bltadat = bltadat = chipmem_agnus_wget (pta); pta -= 2; } else { bltadat = bC -> blt_info.bltadat; }
		bltadat &= blit_masktable[i];
		srca = (((uae_u32)bltadat << 16) | preva) >> b->blitdownashift;
		preva = bltadat;
		if (dodst) chipmem_agnus_wput (dstp, dstd);
		dstd = ((srcc & ~(srca & srcb))) & 0xFFFF;
		totald |= dstd;
		if (ptd) { dodst = 1; dstp = ptd; ptd -= 2; }
	}
	if (pta) pta -= b->bltamod;
	if (ptb) ptb -= b->bltbmod;
	if (ptc) ptc -= b->bltcmod;
	if (ptd) ptd -= b->bltdmod;
}
b->bltbhold = srcb;
b->bltcdat = srcc;
		if (dodst) chipmem_agnus_wput (dstp, dstd);
if (totald != 0) b->blitzero = 0;
}
void blitdofast_30 (struct blitterContext *bC,uaecptr pta, uaecptr ptb, uaecptr ptc, uaecptr ptd, struct bltinfo *b)
{
int i,j;
uae_u32 totald = 0;
uae_u32 preva = 0;
uae_u32 prevb = 0, srcb = b->bltbhold;
uae_u32 dstd=0;
uaecptr dstp = 0;
int dodst = 0;
for (j = 0; j < b->vblitsize; j++) {
	for (i = 0; i < b->hblitsize; i++) {
		uae_u32 bltadat, srca;

		if (ptb) {
			uae_u32 bltbdat; bC -> blt_info.bltbdat = bltbdat = chipmem_agnus_wget (ptb); ptb += 2;
			srcb = (((uae_u32)prevb << 16) | bltbdat) >> b->blitbshift;
			prevb = bltbdat;
		}
		if (pta) { bC -> blt_info.bltadat = bltadat = chipmem_agnus_wget (pta); pta += 2; } else { bltadat = bC -> blt_info.bltadat; }
		bltadat &= blit_masktable[i];
		srca = (((uae_u32)preva << 16) | bltadat) >> b->blitashift;
		preva = bltadat;
		if (dodst) chipmem_agnus_wput (dstp, dstd);
		dstd = ((srca & ~srcb)) & 0xFFFF;
		totald |= dstd;
		if (ptd) { dodst = 1; dstp = ptd; ptd += 2; }
	}
	if (pta) pta += b->bltamod;
	if (ptb) ptb += b->bltbmod;
	if (ptd) ptd += b->bltdmod;
}
b->bltbhold = srcb;
		if (dstp) chipmem_agnus_wput (dstp, dstd);
if (totald != 0) b->blitzero = 0;
}
void blitdofast_desc_30 (struct blitterContext *bC,uaecptr pta, uaecptr ptb, uaecptr ptc, uaecptr ptd, struct bltinfo *b)
{
uae_u32 totald = 0;
int i,j;
uae_u32 preva = 0;
uae_u32 prevb = 0, srcb = b->bltbhold;
uae_u32 dstd=0;
uaecptr dstp = 0;
int dodst = 0;
for (j = 0; j < b->vblitsize; j++) {
	for (i = 0; i < b->hblitsize; i++) {
		uae_u32 bltadat, srca;
		if (ptb) {
			uae_u32 bltbdat; bC -> blt_info.bltbdat = bltbdat = chipmem_agnus_wget (ptb); ptb -= 2;
			srcb = ((bltbdat << 16) | prevb) >> b->blitdownbshift;
			prevb = bltbdat;
		}
		if (pta) { bC ->  blt_info.bltadat = bltadat = chipmem_agnus_wget (pta); pta -= 2; } else { bltadat = bC -> blt_info.bltadat; }
		bltadat &= blit_masktable[i];
		srca = (((uae_u32)bltadat << 16) | preva) >> b->blitdownashift;
		preva = bltadat;
		if (dodst) chipmem_agnus_wput (dstp, dstd);
		dstd = ((srca & ~srcb)) & 0xFFFF;
		totald |= dstd;
		if (ptd) { dodst = 1; dstp = ptd; ptd -= 2; }
	}
	if (pta) pta -= b->bltamod;
	if (ptb) ptb -= b->bltbmod;
	if (ptd) ptd -= b->bltdmod;
}
b->bltbhold = srcb;
		if (dodst) chipmem_agnus_wput (dstp, dstd);
if (totald != 0) b->blitzero = 0;
}
void blitdofast_3a (struct blitterContext *bC,uaecptr pta, uaecptr ptb, uaecptr ptc, uaecptr ptd, struct bltinfo *b)
{
int i,j;
uae_u32 totald = 0;
uae_u32 preva = 0;
uae_u32 prevb = 0, srcb = b->bltbhold;
uae_u32 srcc = b->bltcdat;
uae_u32 dstd=0;
uaecptr dstp = 0;
int dodst = 0;
for (j = 0; j < b->vblitsize; j++) {
	for (i = 0; i < b->hblitsize; i++) {
		uae_u32 bltadat, srca;

		if (ptc) { srcc = chipmem_agnus_wget (ptc); ptc += 2; }
		if (ptb) {
			uae_u32 bltbdat; bC -> blt_info.bltbdat = bltbdat = chipmem_agnus_wget (ptb); ptb += 2;
			srcb = (((uae_u32)prevb << 16) | bltbdat) >> b->blitbshift;
			prevb = bltbdat;
		}
		if (pta) { bC -> blt_info.bltadat = bltadat = chipmem_agnus_wget (pta); pta += 2; } else { bltadat = bC -> blt_info.bltadat; }
		bltadat &= blit_masktable[i];
		srca = (((uae_u32)preva << 16) | bltadat) >> b->blitashift;
		preva = bltadat;
		if (dodst) chipmem_agnus_wput (dstp, dstd);
		dstd = ((srcb ^ (srca | (srcb ^ srcc)))) & 0xFFFF;
		totald |= dstd;
		if (ptd) { dodst = 1; dstp = ptd; ptd += 2; }
	}
	if (pta) pta += b->bltamod;
	if (ptb) ptb += b->bltbmod;
	if (ptc) ptc += b->bltcmod;
	if (ptd) ptd += b->bltdmod;
}
b->bltbhold = srcb;
b->bltcdat = srcc;
		if (dstp) chipmem_agnus_wput (dstp, dstd);
if (totald != 0) b->blitzero = 0;
}
void blitdofast_desc_3a (struct blitterContext *bC,uaecptr pta, uaecptr ptb, uaecptr ptc, uaecptr ptd, struct bltinfo *b)
{
uae_u32 totald = 0;
int i,j;
uae_u32 preva = 0;
uae_u32 prevb = 0, srcb = b->bltbhold;
uae_u32 srcc = b->bltcdat;
uae_u32 dstd=0;
uaecptr dstp = 0;
int dodst = 0;
for (j = 0; j < b->vblitsize; j++) {
	for (i = 0; i < b->hblitsize; i++) {
		uae_u32 bltadat, srca;
		if (ptc) { srcc = chipmem_agnus_wget (ptc); ptc -= 2; }
		if (ptb) {
			uae_u32 bltbdat; bC -> blt_info.bltbdat = bltbdat = chipmem_agnus_wget (ptb); ptb -= 2;
			srcb = ((bltbdat << 16) | prevb) >> b->blitdownbshift;
			prevb = bltbdat;
		}
		if (pta) { bC ->  blt_info.bltadat = bltadat = chipmem_agnus_wget (pta); pta -= 2; } else { bltadat = bC -> blt_info.bltadat; }
		bltadat &= blit_masktable[i];
		srca = (((uae_u32)bltadat << 16) | preva) >> b->blitdownashift;
		preva = bltadat;
		if (dodst) chipmem_agnus_wput (dstp, dstd);
		dstd = ((srcb ^ (srca | (srcb ^ srcc)))) & 0xFFFF;
		totald |= dstd;
		if (ptd) { dodst = 1; dstp = ptd; ptd -= 2; }
	}
	if (pta) pta -= b->bltamod;
	if (ptb) ptb -= b->bltbmod;
	if (ptc) ptc -= b->bltcmod;
	if (ptd) ptd -= b->bltdmod;
}
b->bltbhold = srcb;
b->bltcdat = srcc;
		if (dodst) chipmem_agnus_wput (dstp, dstd);
if (totald != 0) b->blitzero = 0;
}
void blitdofast_3c (struct blitterContext *bC,uaecptr pta, uaecptr ptb, uaecptr ptc, uaecptr ptd, struct bltinfo *b)
{
int i,j;
uae_u32 totald = 0;
uae_u32 preva = 0;
uae_u32 prevb = 0, srcb = b->bltbhold;
uae_u32 dstd=0;
uaecptr dstp = 0;
int dodst = 0;
for (j = 0; j < b->vblitsize; j++) {
	for (i = 0; i < b->hblitsize; i++) {
		uae_u32 bltadat, srca;

		if (ptb) {
			uae_u32 bltbdat; bC -> blt_info.bltbdat = bltbdat = chipmem_agnus_wget (ptb); ptb += 2;
			srcb = (((uae_u32)prevb << 16) | bltbdat) >> b->blitbshift;
			prevb = bltbdat;
		}
		if (pta) { bC -> blt_info.bltadat = bltadat = chipmem_agnus_wget (pta); pta += 2; } else { bltadat = bC -> blt_info.bltadat; }
		bltadat &= blit_masktable[i];
		srca = (((uae_u32)preva << 16) | bltadat) >> b->blitashift;
		preva = bltadat;
		if (dodst) chipmem_agnus_wput (dstp, dstd);
		dstd = ((srca ^ srcb)) & 0xFFFF;
		totald |= dstd;
		if (ptd) { dodst = 1; dstp = ptd; ptd += 2; }
	}
	if (pta) pta += b->bltamod;
	if (ptb) ptb += b->bltbmod;
	if (ptd) ptd += b->bltdmod;
}
b->bltbhold = srcb;
		if (dstp) chipmem_agnus_wput (dstp, dstd);
if (totald != 0) b->blitzero = 0;
}
void blitdofast_desc_3c (struct blitterContext *bC,uaecptr pta, uaecptr ptb, uaecptr ptc, uaecptr ptd, struct bltinfo *b)
{
uae_u32 totald = 0;
int i,j;
uae_u32 preva = 0;
uae_u32 prevb = 0, srcb = b->bltbhold;
uae_u32 dstd=0;
uaecptr dstp = 0;
int dodst = 0;
for (j = 0; j < b->vblitsize; j++) {
	for (i = 0; i < b->hblitsize; i++) {
		uae_u32 bltadat, srca;
		if (ptb) {
			uae_u32 bltbdat; bC -> blt_info.bltbdat = bltbdat = chipmem_agnus_wget (ptb); ptb -= 2;
			srcb = ((bltbdat << 16) | prevb) >> b->blitdownbshift;
			prevb = bltbdat;
		}
		if (pta) { bC ->  blt_info.bltadat = bltadat = chipmem_agnus_wget (pta); pta -= 2; } else { bltadat = bC -> blt_info.bltadat; }
		bltadat &= blit_masktable[i];
		srca = (((uae_u32)bltadat << 16) | preva) >> b->blitdownashift;
		preva = bltadat;
		if (dodst) chipmem_agnus_wput (dstp, dstd);
		dstd = ((srca ^ srcb)) & 0xFFFF;
		totald |= dstd;
		if (ptd) { dodst = 1; dstp = ptd; ptd -= 2; }
	}
	if (pta) pta -= b->bltamod;
	if (ptb) ptb -= b->bltbmod;
	if (ptd) ptd -= b->bltdmod;
}
b->bltbhold = srcb;
		if (dodst) chipmem_agnus_wput (dstp, dstd);
if (totald != 0) b->blitzero = 0;
}
void blitdofast_4a (struct blitterContext *bC,uaecptr pta, uaecptr ptb, uaecptr ptc, uaecptr ptd, struct bltinfo *b)
{
int i,j;
uae_u32 totald = 0;
uae_u32 preva = 0;
uae_u32 prevb = 0, srcb = b->bltbhold;
uae_u32 srcc = b->bltcdat;
uae_u32 dstd=0;
uaecptr dstp = 0;
int dodst = 0;
for (j = 0; j < b->vblitsize; j++) {
	for (i = 0; i < b->hblitsize; i++) {
		uae_u32 bltadat, srca;

		if (ptc) { srcc = chipmem_agnus_wget (ptc); ptc += 2; }
		if (ptb) {
			uae_u32 bltbdat; bC -> blt_info.bltbdat = bltbdat = chipmem_agnus_wget (ptb); ptb += 2;
			srcb = (((uae_u32)prevb << 16) | bltbdat) >> b->blitbshift;
			prevb = bltbdat;
		}
		if (pta) { bC -> blt_info.bltadat = bltadat = chipmem_agnus_wget (pta); pta += 2; } else { bltadat = bC -> blt_info.bltadat; }
		bltadat &= blit_masktable[i];
		srca = (((uae_u32)preva << 16) | bltadat) >> b->blitashift;
		preva = bltadat;
		if (dodst) chipmem_agnus_wput (dstp, dstd);
		dstd = ((srcc ^ (srca & (srcb | srcc)))) & 0xFFFF;
		totald |= dstd;
		if (ptd) { dodst = 1; dstp = ptd; ptd += 2; }
	}
	if (pta) pta += b->bltamod;
	if (ptb) ptb += b->bltbmod;
	if (ptc) ptc += b->bltcmod;
	if (ptd) ptd += b->bltdmod;
}
b->bltbhold = srcb;
b->bltcdat = srcc;
		if (dstp) chipmem_agnus_wput (dstp, dstd);
if (totald != 0) b->blitzero = 0;
}
void blitdofast_desc_4a (struct blitterContext *bC,uaecptr pta, uaecptr ptb, uaecptr ptc, uaecptr ptd, struct bltinfo *b)
{
uae_u32 totald = 0;
int i,j;
uae_u32 preva = 0;
uae_u32 prevb = 0, srcb = b->bltbhold;
uae_u32 srcc = b->bltcdat;
uae_u32 dstd=0;
uaecptr dstp = 0;
int dodst = 0;
for (j = 0; j < b->vblitsize; j++) {
	for (i = 0; i < b->hblitsize; i++) {
		uae_u32 bltadat, srca;
		if (ptc) { srcc = chipmem_agnus_wget (ptc); ptc -= 2; }
		if (ptb) {
			uae_u32 bltbdat; bC -> blt_info.bltbdat = bltbdat = chipmem_agnus_wget (ptb); ptb -= 2;
			srcb = ((bltbdat << 16) | prevb) >> b->blitdownbshift;
			prevb = bltbdat;
		}
		if (pta) { bC ->  blt_info.bltadat = bltadat = chipmem_agnus_wget (pta); pta -= 2; } else { bltadat = bC -> blt_info.bltadat; }
		bltadat &= blit_masktable[i];
		srca = (((uae_u32)bltadat << 16) | preva) >> b->blitdownashift;
		preva = bltadat;
		if (dodst) chipmem_agnus_wput (dstp, dstd);
		dstd = ((srcc ^ (srca & (srcb | srcc)))) & 0xFFFF;
		totald |= dstd;
		if (ptd) { dodst = 1; dstp = ptd; ptd -= 2; }
	}
	if (pta) pta -= b->bltamod;
	if (ptb) ptb -= b->bltbmod;
	if (ptc) ptc -= b->bltcmod;
	if (ptd) ptd -= b->bltdmod;
}
b->bltbhold = srcb;
b->bltcdat = srcc;
		if (dodst) chipmem_agnus_wput (dstp, dstd);
if (totald != 0) b->blitzero = 0;
}
void blitdofast_6a (struct blitterContext *bC,uaecptr pta, uaecptr ptb, uaecptr ptc, uaecptr ptd, struct bltinfo *b)
{
int i,j;
uae_u32 totald = 0;
uae_u32 preva = 0;
uae_u32 prevb = 0, srcb = b->bltbhold;
uae_u32 srcc = b->bltcdat;
uae_u32 dstd=0;
uaecptr dstp = 0;
int dodst = 0;
for (j = 0; j < b->vblitsize; j++) {
	for (i = 0; i < b->hblitsize; i++) {
		uae_u32 bltadat, srca;

		if (ptc) { srcc = chipmem_agnus_wget (ptc); ptc += 2; }
		if (ptb) {
			uae_u32 bltbdat; bC -> blt_info.bltbdat = bltbdat = chipmem_agnus_wget (ptb); ptb += 2;
			srcb = (((uae_u32)prevb << 16) | bltbdat) >> b->blitbshift;
			prevb = bltbdat;
		}
		if (pta) { bC -> blt_info.bltadat = bltadat = chipmem_agnus_wget (pta); pta += 2; } else { bltadat = bC -> blt_info.bltadat; }
		bltadat &= blit_masktable[i];
		srca = (((uae_u32)preva << 16) | bltadat) >> b->blitashift;
		preva = bltadat;
		if (dodst) chipmem_agnus_wput (dstp, dstd);
		dstd = ((srcc ^ (srca & srcb))) & 0xFFFF;
		totald |= dstd;
		if (ptd) { dodst = 1; dstp = ptd; ptd += 2; }
	}
	if (pta) pta += b->bltamod;
	if (ptb) ptb += b->bltbmod;
	if (ptc) ptc += b->bltcmod;
	if (ptd) ptd += b->bltdmod;
}
b->bltbhold = srcb;
b->bltcdat = srcc;
		if (dstp) chipmem_agnus_wput (dstp, dstd);
if (totald != 0) b->blitzero = 0;
}
void blitdofast_desc_6a (struct blitterContext *bC,uaecptr pta, uaecptr ptb, uaecptr ptc, uaecptr ptd, struct bltinfo *b)
{
uae_u32 totald = 0;
int i,j;
uae_u32 preva = 0;
uae_u32 prevb = 0, srcb = b->bltbhold;
uae_u32 srcc = b->bltcdat;
uae_u32 dstd=0;
uaecptr dstp = 0;
int dodst = 0;
for (j = 0; j < b->vblitsize; j++) {
	for (i = 0; i < b->hblitsize; i++) {
		uae_u32 bltadat, srca;
		if (ptc) { srcc = chipmem_agnus_wget (ptc); ptc -= 2; }
		if (ptb) {
			uae_u32 bltbdat; bC -> blt_info.bltbdat = bltbdat = chipmem_agnus_wget (ptb); ptb -= 2;
			srcb = ((bltbdat << 16) | prevb) >> b->blitdownbshift;
			prevb = bltbdat;
		}
		if (pta) { bC ->  blt_info.bltadat = bltadat = chipmem_agnus_wget (pta); pta -= 2; } else { bltadat = bC -> blt_info.bltadat; }
		bltadat &= blit_masktable[i];
		srca = (((uae_u32)bltadat << 16) | preva) >> b->blitdownashift;
		preva = bltadat;
		if (dodst) chipmem_agnus_wput (dstp, dstd);
		dstd = ((srcc ^ (srca & srcb))) & 0xFFFF;
		totald |= dstd;
		if (ptd) { dodst = 1; dstp = ptd; ptd -= 2; }
	}
	if (pta) pta -= b->bltamod;
	if (ptb) ptb -= b->bltbmod;
	if (ptc) ptc -= b->bltcmod;
	if (ptd) ptd -= b->bltdmod;
}
b->bltbhold = srcb;
b->bltcdat = srcc;
		if (dodst) chipmem_agnus_wput (dstp, dstd);
if (totald != 0) b->blitzero = 0;
}
void blitdofast_8a (struct blitterContext *bC,uaecptr pta, uaecptr ptb, uaecptr ptc, uaecptr ptd, struct bltinfo *b)
{
int i,j;
uae_u32 totald = 0;
uae_u32 preva = 0;
uae_u32 prevb = 0, srcb = b->bltbhold;
uae_u32 srcc = b->bltcdat;
uae_u32 dstd=0;
uaecptr dstp = 0;
int dodst = 0;
for (j = 0; j < b->vblitsize; j++) {
	for (i = 0; i < b->hblitsize; i++) {
		uae_u32 bltadat, srca;

		if (ptc) { srcc = chipmem_agnus_wget (ptc); ptc += 2; }
		if (ptb) {
			uae_u32 bltbdat; bC -> blt_info.bltbdat = bltbdat = chipmem_agnus_wget (ptb); ptb += 2;
			srcb = (((uae_u32)prevb << 16) | bltbdat) >> b->blitbshift;
			prevb = bltbdat;
		}
		if (pta) { bC -> blt_info.bltadat = bltadat = chipmem_agnus_wget (pta); pta += 2; } else { bltadat = bC -> blt_info.bltadat; }
		bltadat &= blit_masktable[i];
		srca = (((uae_u32)preva << 16) | bltadat) >> b->blitashift;
		preva = bltadat;
		if (dodst) chipmem_agnus_wput (dstp, dstd);
		dstd = ((srcc & (~srca | srcb))) & 0xFFFF;
		totald |= dstd;
		if (ptd) { dodst = 1; dstp = ptd; ptd += 2; }
	}
	if (pta) pta += b->bltamod;
	if (ptb) ptb += b->bltbmod;
	if (ptc) ptc += b->bltcmod;
	if (ptd) ptd += b->bltdmod;
}
b->bltbhold = srcb;
b->bltcdat = srcc;
		if (dstp) chipmem_agnus_wput (dstp, dstd);
if (totald != 0) b->blitzero = 0;
}
void blitdofast_desc_8a (struct blitterContext *bC,uaecptr pta, uaecptr ptb, uaecptr ptc, uaecptr ptd, struct bltinfo *b)
{
uae_u32 totald = 0;
int i,j;
uae_u32 preva = 0;
uae_u32 prevb = 0, srcb = b->bltbhold;
uae_u32 srcc = b->bltcdat;
uae_u32 dstd=0;
uaecptr dstp = 0;
int dodst = 0;
for (j = 0; j < b->vblitsize; j++) {
	for (i = 0; i < b->hblitsize; i++) {
		uae_u32 bltadat, srca;
		if (ptc) { srcc = chipmem_agnus_wget (ptc); ptc -= 2; }
		if (ptb) {
			uae_u32 bltbdat; bC -> blt_info.bltbdat = bltbdat = chipmem_agnus_wget (ptb); ptb -= 2;
			srcb = ((bltbdat << 16) | prevb) >> b->blitdownbshift;
			prevb = bltbdat;
		}
		if (pta) { bC ->  blt_info.bltadat = bltadat = chipmem_agnus_wget (pta); pta -= 2; } else { bltadat = bC -> blt_info.bltadat; }
		bltadat &= blit_masktable[i];
		srca = (((uae_u32)bltadat << 16) | preva) >> b->blitdownashift;
		preva = bltadat;
		if (dodst) chipmem_agnus_wput (dstp, dstd);
		dstd = ((srcc & (~srca | srcb))) & 0xFFFF;
		totald |= dstd;
		if (ptd) { dodst = 1; dstp = ptd; ptd -= 2; }
	}
	if (pta) pta -= b->bltamod;
	if (ptb) ptb -= b->bltbmod;
	if (ptc) ptc -= b->bltcmod;
	if (ptd) ptd -= b->bltdmod;
}
b->bltbhold = srcb;
b->bltcdat = srcc;
		if (dodst) chipmem_agnus_wput (dstp, dstd);
if (totald != 0) b->blitzero = 0;
}
void blitdofast_8c (struct blitterContext *bC,uaecptr pta, uaecptr ptb, uaecptr ptc, uaecptr ptd, struct bltinfo *b)
{
int i,j;
uae_u32 totald = 0;
uae_u32 preva = 0;
uae_u32 prevb = 0, srcb = b->bltbhold;
uae_u32 srcc = b->bltcdat;
uae_u32 dstd=0;
uaecptr dstp = 0;
int dodst = 0;
for (j = 0; j < b->vblitsize; j++) {
	for (i = 0; i < b->hblitsize; i++) {
		uae_u32 bltadat, srca;

		if (ptc) { srcc = chipmem_agnus_wget (ptc); ptc += 2; }
		if (ptb) {
			uae_u32 bltbdat; bC -> blt_info.bltbdat = bltbdat = chipmem_agnus_wget (ptb); ptb += 2;
			srcb = (((uae_u32)prevb << 16) | bltbdat) >> b->blitbshift;
			prevb = bltbdat;
		}
		if (pta) { bC -> blt_info.bltadat = bltadat = chipmem_agnus_wget (pta); pta += 2; } else { bltadat = bC -> blt_info.bltadat; }
		bltadat &= blit_masktable[i];
		srca = (((uae_u32)preva << 16) | bltadat) >> b->blitashift;
		preva = bltadat;
		if (dodst) chipmem_agnus_wput (dstp, dstd);
		dstd = ((srcb & (~srca | srcc))) & 0xFFFF;
		totald |= dstd;
		if (ptd) { dodst = 1; dstp = ptd; ptd += 2; }
	}
	if (pta) pta += b->bltamod;
	if (ptb) ptb += b->bltbmod;
	if (ptc) ptc += b->bltcmod;
	if (ptd) ptd += b->bltdmod;
}
b->bltbhold = srcb;
b->bltcdat = srcc;
		if (dstp) chipmem_agnus_wput (dstp, dstd);
if (totald != 0) b->blitzero = 0;
}
void blitdofast_desc_8c (struct blitterContext *bC,uaecptr pta, uaecptr ptb, uaecptr ptc, uaecptr ptd, struct bltinfo *b)
{
uae_u32 totald = 0;
int i,j;
uae_u32 preva = 0;
uae_u32 prevb = 0, srcb = b->bltbhold;
uae_u32 srcc = b->bltcdat;
uae_u32 dstd=0;
uaecptr dstp = 0;
int dodst = 0;
for (j = 0; j < b->vblitsize; j++) {
	for (i = 0; i < b->hblitsize; i++) {
		uae_u32 bltadat, srca;
		if (ptc) { srcc = chipmem_agnus_wget (ptc); ptc -= 2; }
		if (ptb) {
			uae_u32 bltbdat; bC -> blt_info.bltbdat = bltbdat = chipmem_agnus_wget (ptb); ptb -= 2;
			srcb = ((bltbdat << 16) | prevb) >> b->blitdownbshift;
			prevb = bltbdat;
		}
		if (pta) { bC ->  blt_info.bltadat = bltadat = chipmem_agnus_wget (pta); pta -= 2; } else { bltadat = bC -> blt_info.bltadat; }
		bltadat &= blit_masktable[i];
		srca = (((uae_u32)bltadat << 16) | preva) >> b->blitdownashift;
		preva = bltadat;
		if (dodst) chipmem_agnus_wput (dstp, dstd);
		dstd = ((srcb & (~srca | srcc))) & 0xFFFF;
		totald |= dstd;
		if (ptd) { dodst = 1; dstp = ptd; ptd -= 2; }
	}
	if (pta) pta -= b->bltamod;
	if (ptb) ptb -= b->bltbmod;
	if (ptc) ptc -= b->bltcmod;
	if (ptd) ptd -= b->bltdmod;
}
b->bltbhold = srcb;
b->bltcdat = srcc;
		if (dodst) chipmem_agnus_wput (dstp, dstd);
if (totald != 0) b->blitzero = 0;
}
void blitdofast_9a (struct blitterContext *bC,uaecptr pta, uaecptr ptb, uaecptr ptc, uaecptr ptd, struct bltinfo *b)
{
int i,j;
uae_u32 totald = 0;
uae_u32 preva = 0;
uae_u32 prevb = 0, srcb = b->bltbhold;
uae_u32 srcc = b->bltcdat;
uae_u32 dstd=0;
uaecptr dstp = 0;
int dodst = 0;
for (j = 0; j < b->vblitsize; j++) {
	for (i = 0; i < b->hblitsize; i++) {
		uae_u32 bltadat, srca;

		if (ptc) { srcc = chipmem_agnus_wget (ptc); ptc += 2; }
		if (ptb) {
			uae_u32 bltbdat; bC -> blt_info.bltbdat = bltbdat = chipmem_agnus_wget (ptb); ptb += 2;
			srcb = (((uae_u32)prevb << 16) | bltbdat) >> b->blitbshift;
			prevb = bltbdat;
		}
		if (pta) { bC -> blt_info.bltadat = bltadat = chipmem_agnus_wget (pta); pta += 2; } else { bltadat = bC -> blt_info.bltadat; }
		bltadat &= blit_masktable[i];
		srca = (((uae_u32)preva << 16) | bltadat) >> b->blitashift;
		preva = bltadat;
		if (dodst) chipmem_agnus_wput (dstp, dstd);
		dstd = ((srcc ^ (srca & ~srcb))) & 0xFFFF;
		totald |= dstd;
		if (ptd) { dodst = 1; dstp = ptd; ptd += 2; }
	}
	if (pta) pta += b->bltamod;
	if (ptb) ptb += b->bltbmod;
	if (ptc) ptc += b->bltcmod;
	if (ptd) ptd += b->bltdmod;
}
b->bltbhold = srcb;
b->bltcdat = srcc;
		if (dstp) chipmem_agnus_wput (dstp, dstd);
if (totald != 0) b->blitzero = 0;
}
void blitdofast_desc_9a (struct blitterContext *bC,uaecptr pta, uaecptr ptb, uaecptr ptc, uaecptr ptd, struct bltinfo *b)
{
uae_u32 totald = 0;
int i,j;
uae_u32 preva = 0;
uae_u32 prevb = 0, srcb = b->bltbhold;
uae_u32 srcc = b->bltcdat;
uae_u32 dstd=0;
uaecptr dstp = 0;
int dodst = 0;
for (j = 0; j < b->vblitsize; j++) {
	for (i = 0; i < b->hblitsize; i++) {
		uae_u32 bltadat, srca;
		if (ptc) { srcc = chipmem_agnus_wget (ptc); ptc -= 2; }
		if (ptb) {
			uae_u32 bltbdat; bC -> blt_info.bltbdat = bltbdat = chipmem_agnus_wget (ptb); ptb -= 2;
			srcb = ((bltbdat << 16) | prevb) >> b->blitdownbshift;
			prevb = bltbdat;
		}
		if (pta) { bC ->  blt_info.bltadat = bltadat = chipmem_agnus_wget (pta); pta -= 2; } else { bltadat = bC -> blt_info.bltadat; }
		bltadat &= blit_masktable[i];
		srca = (((uae_u32)bltadat << 16) | preva) >> b->blitdownashift;
		preva = bltadat;
		if (dodst) chipmem_agnus_wput (dstp, dstd);
		dstd = ((srcc ^ (srca & ~srcb))) & 0xFFFF;
		totald |= dstd;
		if (ptd) { dodst = 1; dstp = ptd; ptd -= 2; }
	}
	if (pta) pta -= b->bltamod;
	if (ptb) ptb -= b->bltbmod;
	if (ptc) ptc -= b->bltcmod;
	if (ptd) ptd -= b->bltdmod;
}
b->bltbhold = srcb;
b->bltcdat = srcc;
		if (dodst) chipmem_agnus_wput (dstp, dstd);
if (totald != 0) b->blitzero = 0;
}
void blitdofast_a8 (struct blitterContext *bC,uaecptr pta, uaecptr ptb, uaecptr ptc, uaecptr ptd, struct bltinfo *b)
{
int i,j;
uae_u32 totald = 0;
uae_u32 preva = 0;
uae_u32 prevb = 0, srcb = b->bltbhold;
uae_u32 srcc = b->bltcdat;
uae_u32 dstd=0;
uaecptr dstp = 0;
int dodst = 0;
for (j = 0; j < b->vblitsize; j++) {
	for (i = 0; i < b->hblitsize; i++) {
		uae_u32 bltadat, srca;

		if (ptc) { srcc = chipmem_agnus_wget (ptc); ptc += 2; }
		if (ptb) {
			uae_u32 bltbdat; bC -> blt_info.bltbdat = bltbdat = chipmem_agnus_wget (ptb); ptb += 2;
			srcb = (((uae_u32)prevb << 16) | bltbdat) >> b->blitbshift;
			prevb = bltbdat;
		}
		if (pta) { bC -> blt_info.bltadat = bltadat = chipmem_agnus_wget (pta); pta += 2; } else { bltadat = bC -> blt_info.bltadat; }
		bltadat &= blit_masktable[i];
		srca = (((uae_u32)preva << 16) | bltadat) >> b->blitashift;
		preva = bltadat;
		if (dodst) chipmem_agnus_wput (dstp, dstd);
		dstd = ((srcc & (srca | srcb))) & 0xFFFF;
		totald |= dstd;
		if (ptd) { dodst = 1; dstp = ptd; ptd += 2; }
	}
	if (pta) pta += b->bltamod;
	if (ptb) ptb += b->bltbmod;
	if (ptc) ptc += b->bltcmod;
	if (ptd) ptd += b->bltdmod;
}
b->bltbhold = srcb;
b->bltcdat = srcc;
		if (dstp) chipmem_agnus_wput (dstp, dstd);
if (totald != 0) b->blitzero = 0;
}
void blitdofast_desc_a8 (struct blitterContext *bC,uaecptr pta, uaecptr ptb, uaecptr ptc, uaecptr ptd, struct bltinfo *b)
{
uae_u32 totald = 0;
int i,j;
uae_u32 preva = 0;
uae_u32 prevb = 0, srcb = b->bltbhold;
uae_u32 srcc = b->bltcdat;
uae_u32 dstd=0;
uaecptr dstp = 0;
int dodst = 0;
for (j = 0; j < b->vblitsize; j++) {
	for (i = 0; i < b->hblitsize; i++) {
		uae_u32 bltadat, srca;
		if (ptc) { srcc = chipmem_agnus_wget (ptc); ptc -= 2; }
		if (ptb) {
			uae_u32 bltbdat; bC -> blt_info.bltbdat = bltbdat = chipmem_agnus_wget (ptb); ptb -= 2;
			srcb = ((bltbdat << 16) | prevb) >> b->blitdownbshift;
			prevb = bltbdat;
		}
		if (pta) { bC ->  blt_info.bltadat = bltadat = chipmem_agnus_wget (pta); pta -= 2; } else { bltadat = bC -> blt_info.bltadat; }
		bltadat &= blit_masktable[i];
		srca = (((uae_u32)bltadat << 16) | preva) >> b->blitdownashift;
		preva = bltadat;
		if (dodst) chipmem_agnus_wput (dstp, dstd);
		dstd = ((srcc & (srca | srcb))) & 0xFFFF;
		totald |= dstd;
		if (ptd) { dodst = 1; dstp = ptd; ptd -= 2; }
	}
	if (pta) pta -= b->bltamod;
	if (ptb) ptb -= b->bltbmod;
	if (ptc) ptc -= b->bltcmod;
	if (ptd) ptd -= b->bltdmod;
}
b->bltbhold = srcb;
b->bltcdat = srcc;
		if (dodst) chipmem_agnus_wput (dstp, dstd);
if (totald != 0) b->blitzero = 0;
}
void blitdofast_aa (struct blitterContext *bC,uaecptr pta, uaecptr ptb, uaecptr ptc, uaecptr ptd, struct bltinfo *b)
{
int i,j;
uae_u32 totald = 0;
uae_u32 srcc = b->bltcdat;
uae_u32 dstd=0;
uaecptr dstp = 0;
int dodst = 0;
for (j = 0; j < b->vblitsize; j++) {
	for (i = 0; i < b->hblitsize; i++) {
		uae_u32 bltadat, srca;

		if (ptc) { srcc = chipmem_agnus_wget (ptc); ptc += 2; }
		if (dodst) chipmem_agnus_wput (dstp, dstd);
		dstd = (srcc) & 0xFFFF;
		totald |= dstd;
		if (ptd) { dodst = 1; dstp = ptd; ptd += 2; }
	}
	if (ptc) ptc += b->bltcmod;
	if (ptd) ptd += b->bltdmod;
}
b->bltcdat = srcc;
		if (dstp) chipmem_agnus_wput (dstp, dstd);
if (totald != 0) b->blitzero = 0;
}
void blitdofast_desc_aa (struct blitterContext *bC,uaecptr pta, uaecptr ptb, uaecptr ptc, uaecptr ptd, struct bltinfo *b)
{
uae_u32 totald = 0;
int i,j;
uae_u32 srcc = b->bltcdat;
uae_u32 dstd=0;
uaecptr dstp = 0;
int dodst = 0;
for (j = 0; j < b->vblitsize; j++) {
	for (i = 0; i < b->hblitsize; i++) {
		uae_u32 bltadat, srca;
		if (ptc) { srcc = chipmem_agnus_wget (ptc); ptc -= 2; }
		if (dodst) chipmem_agnus_wput (dstp, dstd);
		dstd = (srcc) & 0xFFFF;
		totald |= dstd;
		if (ptd) { dodst = 1; dstp = ptd; ptd -= 2; }
	}
	if (ptc) ptc -= b->bltcmod;
	if (ptd) ptd -= b->bltdmod;
}
b->bltcdat = srcc;
		if (dodst) chipmem_agnus_wput (dstp, dstd);
if (totald != 0) b->blitzero = 0;
}
void blitdofast_b1 (struct blitterContext *bC,uaecptr pta, uaecptr ptb, uaecptr ptc, uaecptr ptd, struct bltinfo *b)
{
int i,j;
uae_u32 totald = 0;
uae_u32 preva = 0;
uae_u32 prevb = 0, srcb = b->bltbhold;
uae_u32 srcc = b->bltcdat;
uae_u32 dstd=0;
uaecptr dstp = 0;
int dodst = 0;
for (j = 0; j < b->vblitsize; j++) {
	for (i = 0; i < b->hblitsize; i++) {
		uae_u32 bltadat, srca;

		if (ptc) { srcc = chipmem_agnus_wget (ptc); ptc += 2; }
		if (ptb) {
			uae_u32 bltbdat; bC -> blt_info.bltbdat = bltbdat = chipmem_agnus_wget (ptb); ptb += 2;
			srcb = (((uae_u32)prevb << 16) | bltbdat) >> b->blitbshift;
			prevb = bltbdat;
		}
		if (pta) { bC -> blt_info.bltadat = bltadat = chipmem_agnus_wget (pta); pta += 2; } else { bltadat = bC -> blt_info.bltadat; }
		bltadat &= blit_masktable[i];
		srca = (((uae_u32)preva << 16) | bltadat) >> b->blitashift;
		preva = bltadat;
		if (dodst) chipmem_agnus_wput (dstp, dstd);
		dstd = (~(srca ^ (srcc | (srca ^ srcb)))) & 0xFFFF;
		totald |= dstd;
		if (ptd) { dodst = 1; dstp = ptd; ptd += 2; }
	}
	if (pta) pta += b->bltamod;
	if (ptb) ptb += b->bltbmod;
	if (ptc) ptc += b->bltcmod;
	if (ptd) ptd += b->bltdmod;
}
b->bltbhold = srcb;
b->bltcdat = srcc;
		if (dstp) chipmem_agnus_wput (dstp, dstd);
if (totald != 0) b->blitzero = 0;
}
void blitdofast_desc_b1 (struct blitterContext *bC,uaecptr pta, uaecptr ptb, uaecptr ptc, uaecptr ptd, struct bltinfo *b)
{
uae_u32 totald = 0;
int i,j;
uae_u32 preva = 0;
uae_u32 prevb = 0, srcb = b->bltbhold;
uae_u32 srcc = b->bltcdat;
uae_u32 dstd=0;
uaecptr dstp = 0;
int dodst = 0;
for (j = 0; j < b->vblitsize; j++) {
	for (i = 0; i < b->hblitsize; i++) {
		uae_u32 bltadat, srca;
		if (ptc) { srcc = chipmem_agnus_wget (ptc); ptc -= 2; }
		if (ptb) {
			uae_u32 bltbdat; bC -> blt_info.bltbdat = bltbdat = chipmem_agnus_wget (ptb); ptb -= 2;
			srcb = ((bltbdat << 16) | prevb) >> b->blitdownbshift;
			prevb = bltbdat;
		}
		if (pta) { bC ->  blt_info.bltadat = bltadat = chipmem_agnus_wget (pta); pta -= 2; } else { bltadat = bC -> blt_info.bltadat; }
		bltadat &= blit_masktable[i];
		srca = (((uae_u32)bltadat << 16) | preva) >> b->blitdownashift;
		preva = bltadat;
		if (dodst) chipmem_agnus_wput (dstp, dstd);
		dstd = (~(srca ^ (srcc | (srca ^ srcb)))) & 0xFFFF;
		totald |= dstd;
		if (ptd) { dodst = 1; dstp = ptd; ptd -= 2; }
	}
	if (pta) pta -= b->bltamod;
	if (ptb) ptb -= b->bltbmod;
	if (ptc) ptc -= b->bltcmod;
	if (ptd) ptd -= b->bltdmod;
}
b->bltbhold = srcb;
b->bltcdat = srcc;
		if (dodst) chipmem_agnus_wput (dstp, dstd);
if (totald != 0) b->blitzero = 0;
}
void blitdofast_ca (struct blitterContext *bC,uaecptr pta, uaecptr ptb, uaecptr ptc, uaecptr ptd, struct bltinfo *b)
{
int i,j;
uae_u32 totald = 0;
uae_u32 preva = 0;
uae_u32 prevb = 0, srcb = b->bltbhold;
uae_u32 srcc = b->bltcdat;
uae_u32 dstd=0;
uaecptr dstp = 0;
int dodst = 0;
for (j = 0; j < b->vblitsize; j++) {
	for (i = 0; i < b->hblitsize; i++) {
		uae_u32 bltadat, srca;

		if (ptc) { srcc = chipmem_agnus_wget (ptc); ptc += 2; }
		if (ptb) {
			uae_u32 bltbdat; bC -> blt_info.bltbdat = bltbdat = chipmem_agnus_wget (ptb); ptb += 2;
			srcb = (((uae_u32)prevb << 16) | bltbdat) >> b->blitbshift;
			prevb = bltbdat;
		}
		if (pta) { bC -> blt_info.bltadat = bltadat = chipmem_agnus_wget (pta); pta += 2; } else { bltadat = bC -> blt_info.bltadat; }
		bltadat &= blit_masktable[i];
		srca = (((uae_u32)preva << 16) | bltadat) >> b->blitashift;
		preva = bltadat;
		if (dodst) chipmem_agnus_wput (dstp, dstd);
		dstd = ((srcc ^ (srca & (srcb ^ srcc)))) & 0xFFFF;
		totald |= dstd;
		if (ptd) { dodst = 1; dstp = ptd; ptd += 2; }
	}
	if (pta) pta += b->bltamod;
	if (ptb) ptb += b->bltbmod;
	if (ptc) ptc += b->bltcmod;
	if (ptd) ptd += b->bltdmod;
}
b->bltbhold = srcb;
b->bltcdat = srcc;
		if (dstp) chipmem_agnus_wput (dstp, dstd);
if (totald != 0) b->blitzero = 0;
}
void blitdofast_desc_ca (struct blitterContext *bC,uaecptr pta, uaecptr ptb, uaecptr ptc, uaecptr ptd, struct bltinfo *b)
{
uae_u32 totald = 0;
int i,j;
uae_u32 preva = 0;
uae_u32 prevb = 0, srcb = b->bltbhold;
uae_u32 srcc = b->bltcdat;
uae_u32 dstd=0;
uaecptr dstp = 0;
int dodst = 0;
for (j = 0; j < b->vblitsize; j++) {
	for (i = 0; i < b->hblitsize; i++) {
		uae_u32 bltadat, srca;
		if (ptc) { srcc = chipmem_agnus_wget (ptc); ptc -= 2; }
		if (ptb) {
			uae_u32 bltbdat; bC -> blt_info.bltbdat = bltbdat = chipmem_agnus_wget (ptb); ptb -= 2;
			srcb = ((bltbdat << 16) | prevb) >> b->blitdownbshift;
			prevb = bltbdat;
		}
		if (pta) { bC ->  blt_info.bltadat = bltadat = chipmem_agnus_wget (pta); pta -= 2; } else { bltadat = bC -> blt_info.bltadat; }
		bltadat &= blit_masktable[i];
		srca = (((uae_u32)bltadat << 16) | preva) >> b->blitdownashift;
		preva = bltadat;
		if (dodst) chipmem_agnus_wput (dstp, dstd);
		dstd = ((srcc ^ (srca & (srcb ^ srcc)))) & 0xFFFF;
		totald |= dstd;
		if (ptd) { dodst = 1; dstp = ptd; ptd -= 2; }
	}
	if (pta) pta -= b->bltamod;
	if (ptb) ptb -= b->bltbmod;
	if (ptc) ptc -= b->bltcmod;
	if (ptd) ptd -= b->bltdmod;
}
b->bltbhold = srcb;
b->bltcdat = srcc;
		if (dodst) chipmem_agnus_wput (dstp, dstd);
if (totald != 0) b->blitzero = 0;
}
void blitdofast_cc (struct blitterContext *bC,uaecptr pta, uaecptr ptb, uaecptr ptc, uaecptr ptd, struct bltinfo *b)
{
int i,j;
uae_u32 totald = 0;
uae_u32 prevb = 0, srcb = b->bltbhold;
uae_u32 dstd=0;
uaecptr dstp = 0;
int dodst = 0;
for (j = 0; j < b->vblitsize; j++) {
	for (i = 0; i < b->hblitsize; i++) {
		uae_u32 bltadat, srca;

		if (ptb) {
			uae_u32 bltbdat; bC -> blt_info.bltbdat = bltbdat = chipmem_agnus_wget (ptb); ptb += 2;
			srcb = (((uae_u32)prevb << 16) | bltbdat) >> b->blitbshift;
			prevb = bltbdat;
		}
		if (dodst) chipmem_agnus_wput (dstp, dstd);
		dstd = (srcb) & 0xFFFF;
		totald |= dstd;
		if (ptd) { dodst = 1; dstp = ptd; ptd += 2; }
	}
	if (ptb) ptb += b->bltbmod;
	if (ptd) ptd += b->bltdmod;
}
b->bltbhold = srcb;
		if (dstp) chipmem_agnus_wput (dstp, dstd);
if (totald != 0) b->blitzero = 0;
}
void blitdofast_desc_cc (struct blitterContext *bC,uaecptr pta, uaecptr ptb, uaecptr ptc, uaecptr ptd, struct bltinfo *b)
{
uae_u32 totald = 0;
int i,j;
uae_u32 prevb = 0, srcb = b->bltbhold;
uae_u32 dstd=0;
uaecptr dstp = 0;
int dodst = 0;
for (j = 0; j < b->vblitsize; j++) {
	for (i = 0; i < b->hblitsize; i++) {
		uae_u32 bltadat, srca;
		if (ptb) {
			uae_u32 bltbdat; bC -> blt_info.bltbdat = bltbdat = chipmem_agnus_wget (ptb); ptb -= 2;
			srcb = ((bltbdat << 16) | prevb) >> b->blitdownbshift;
			prevb = bltbdat;
		}
		if (dodst) chipmem_agnus_wput (dstp, dstd);
		dstd = (srcb) & 0xFFFF;
		totald |= dstd;
		if (ptd) { dodst = 1; dstp = ptd; ptd -= 2; }
	}
	if (ptb) ptb -= b->bltbmod;
	if (ptd) ptd -= b->bltdmod;
}
b->bltbhold = srcb;
		if (dodst) chipmem_agnus_wput (dstp, dstd);
if (totald != 0) b->blitzero = 0;
}
void blitdofast_d8 (struct blitterContext *bC,uaecptr pta, uaecptr ptb, uaecptr ptc, uaecptr ptd, struct bltinfo *b)
{
int i,j;
uae_u32 totald = 0;
uae_u32 preva = 0;
uae_u32 prevb = 0, srcb = b->bltbhold;
uae_u32 srcc = b->bltcdat;
uae_u32 dstd=0;
uaecptr dstp = 0;
int dodst = 0;
for (j = 0; j < b->vblitsize; j++) {
	for (i = 0; i < b->hblitsize; i++) {
		uae_u32 bltadat, srca;

		if (ptc) { srcc = chipmem_agnus_wget (ptc); ptc += 2; }
		if (ptb) {
			uae_u32 bltbdat; bC -> blt_info.bltbdat = bltbdat = chipmem_agnus_wget (ptb); ptb += 2;
			srcb = (((uae_u32)prevb << 16) | bltbdat) >> b->blitbshift;
			prevb = bltbdat;
		}
		if (pta) { bC -> blt_info.bltadat = bltadat = chipmem_agnus_wget (pta); pta += 2; } else { bltadat = bC -> blt_info.bltadat; }
		bltadat &= blit_masktable[i];
		srca = (((uae_u32)preva << 16) | bltadat) >> b->blitashift;
		preva = bltadat;
		if (dodst) chipmem_agnus_wput (dstp, dstd);
		dstd = ((srca ^ (srcc & (srca ^ srcb)))) & 0xFFFF;
		totald |= dstd;
		if (ptd) { dodst = 1; dstp = ptd; ptd += 2; }
	}
	if (pta) pta += b->bltamod;
	if (ptb) ptb += b->bltbmod;
	if (ptc) ptc += b->bltcmod;
	if (ptd) ptd += b->bltdmod;
}
b->bltbhold = srcb;
b->bltcdat = srcc;
		if (dstp) chipmem_agnus_wput (dstp, dstd);
if (totald != 0) b->blitzero = 0;
}
void blitdofast_desc_d8 (struct blitterContext *bC,uaecptr pta, uaecptr ptb, uaecptr ptc, uaecptr ptd, struct bltinfo *b)
{
uae_u32 totald = 0;
int i,j;
uae_u32 preva = 0;
uae_u32 prevb = 0, srcb = b->bltbhold;
uae_u32 srcc = b->bltcdat;
uae_u32 dstd=0;
uaecptr dstp = 0;
int dodst = 0;
for (j = 0; j < b->vblitsize; j++) {
	for (i = 0; i < b->hblitsize; i++) {
		uae_u32 bltadat, srca;
		if (ptc) { srcc = chipmem_agnus_wget (ptc); ptc -= 2; }
		if (ptb) {
			uae_u32 bltbdat; bC -> blt_info.bltbdat = bltbdat = chipmem_agnus_wget (ptb); ptb -= 2;
			srcb = ((bltbdat << 16) | prevb) >> b->blitdownbshift;
			prevb = bltbdat;
		}
		if (pta) { bC ->  blt_info.bltadat = bltadat = chipmem_agnus_wget (pta); pta -= 2; } else { bltadat = bC -> blt_info.bltadat; }
		bltadat &= blit_masktable[i];
		srca = (((uae_u32)bltadat << 16) | preva) >> b->blitdownashift;
		preva = bltadat;
		if (dodst) chipmem_agnus_wput (dstp, dstd);
		dstd = ((srca ^ (srcc & (srca ^ srcb)))) & 0xFFFF;
		totald |= dstd;
		if (ptd) { dodst = 1; dstp = ptd; ptd -= 2; }
	}
	if (pta) pta -= b->bltamod;
	if (ptb) ptb -= b->bltbmod;
	if (ptc) ptc -= b->bltcmod;
	if (ptd) ptd -= b->bltdmod;
}
b->bltbhold = srcb;
b->bltcdat = srcc;
		if (dodst) chipmem_agnus_wput (dstp, dstd);
if (totald != 0) b->blitzero = 0;
}
void blitdofast_e2 (struct blitterContext *bC,uaecptr pta, uaecptr ptb, uaecptr ptc, uaecptr ptd, struct bltinfo *b)
{
int i,j;
uae_u32 totald = 0;
uae_u32 preva = 0;
uae_u32 prevb = 0, srcb = b->bltbhold;
uae_u32 srcc = b->bltcdat;
uae_u32 dstd=0;
uaecptr dstp = 0;
int dodst = 0;
for (j = 0; j < b->vblitsize; j++) {
	for (i = 0; i < b->hblitsize; i++) {
		uae_u32 bltadat, srca;

		if (ptc) { srcc = chipmem_agnus_wget (ptc); ptc += 2; }
		if (ptb) {
			uae_u32 bltbdat; bC -> blt_info.bltbdat = bltbdat = chipmem_agnus_wget (ptb); ptb += 2;
			srcb = (((uae_u32)prevb << 16) | bltbdat) >> b->blitbshift;
			prevb = bltbdat;
		}
		if (pta) { bC -> blt_info.bltadat = bltadat = chipmem_agnus_wget (pta); pta += 2; } else { bltadat = bC -> blt_info.bltadat; }
		bltadat &= blit_masktable[i];
		srca = (((uae_u32)preva << 16) | bltadat) >> b->blitashift;
		preva = bltadat;
		if (dodst) chipmem_agnus_wput (dstp, dstd);
		dstd = ((srcc ^ (srcb & (srca ^ srcc)))) & 0xFFFF;
		totald |= dstd;
		if (ptd) { dodst = 1; dstp = ptd; ptd += 2; }
	}
	if (pta) pta += b->bltamod;
	if (ptb) ptb += b->bltbmod;
	if (ptc) ptc += b->bltcmod;
	if (ptd) ptd += b->bltdmod;
}
b->bltbhold = srcb;
b->bltcdat = srcc;
		if (dstp) chipmem_agnus_wput (dstp, dstd);
if (totald != 0) b->blitzero = 0;
}
void blitdofast_desc_e2 (struct blitterContext *bC,uaecptr pta, uaecptr ptb, uaecptr ptc, uaecptr ptd, struct bltinfo *b)
{
uae_u32 totald = 0;
int i,j;
uae_u32 preva = 0;
uae_u32 prevb = 0, srcb = b->bltbhold;
uae_u32 srcc = b->bltcdat;
uae_u32 dstd=0;
uaecptr dstp = 0;
int dodst = 0;
for (j = 0; j < b->vblitsize; j++) {
	for (i = 0; i < b->hblitsize; i++) {
		uae_u32 bltadat, srca;
		if (ptc) { srcc = chipmem_agnus_wget (ptc); ptc -= 2; }
		if (ptb) {
			uae_u32 bltbdat; bC -> blt_info.bltbdat = bltbdat = chipmem_agnus_wget (ptb); ptb -= 2;
			srcb = ((bltbdat << 16) | prevb) >> b->blitdownbshift;
			prevb = bltbdat;
		}
		if (pta) { bC ->  blt_info.bltadat = bltadat = chipmem_agnus_wget (pta); pta -= 2; } else { bltadat = bC -> blt_info.bltadat; }
		bltadat &= blit_masktable[i];
		srca = (((uae_u32)bltadat << 16) | preva) >> b->blitdownashift;
		preva = bltadat;
		if (dodst) chipmem_agnus_wput (dstp, dstd);
		dstd = ((srcc ^ (srcb & (srca ^ srcc)))) & 0xFFFF;
		totald |= dstd;
		if (ptd) { dodst = 1; dstp = ptd; ptd -= 2; }
	}
	if (pta) pta -= b->bltamod;
	if (ptb) ptb -= b->bltbmod;
	if (ptc) ptc -= b->bltcmod;
	if (ptd) ptd -= b->bltdmod;
}
b->bltbhold = srcb;
b->bltcdat = srcc;
		if (dodst) chipmem_agnus_wput (dstp, dstd);
if (totald != 0) b->blitzero = 0;
}
void blitdofast_ea (struct blitterContext *bC,uaecptr pta, uaecptr ptb, uaecptr ptc, uaecptr ptd, struct bltinfo *b)
{
int i,j;
uae_u32 totald = 0;
uae_u32 preva = 0;
uae_u32 prevb = 0, srcb = b->bltbhold;
uae_u32 srcc = b->bltcdat;
uae_u32 dstd=0;
uaecptr dstp = 0;
int dodst = 0;
for (j = 0; j < b->vblitsize; j++) {
	for (i = 0; i < b->hblitsize; i++) {
		uae_u32 bltadat, srca;

		if (ptc) { srcc = chipmem_agnus_wget (ptc); ptc += 2; }
		if (ptb) {
			uae_u32 bltbdat; bC -> blt_info.bltbdat = bltbdat = chipmem_agnus_wget (ptb); ptb += 2;
			srcb = (((uae_u32)prevb << 16) | bltbdat) >> b->blitbshift;
			prevb = bltbdat;
		}
		if (pta) { bC -> blt_info.bltadat = bltadat = chipmem_agnus_wget (pta); pta += 2; } else { bltadat = bC -> blt_info.bltadat; }
		bltadat &= blit_masktable[i];
		srca = (((uae_u32)preva << 16) | bltadat) >> b->blitashift;
		preva = bltadat;
		if (dodst) chipmem_agnus_wput (dstp, dstd);
		dstd = ((srcc | (srca & srcb))) & 0xFFFF;
		totald |= dstd;
		if (ptd) { dodst = 1; dstp = ptd; ptd += 2; }
	}
	if (pta) pta += b->bltamod;
	if (ptb) ptb += b->bltbmod;
	if (ptc) ptc += b->bltcmod;
	if (ptd) ptd += b->bltdmod;
}
b->bltbhold = srcb;
b->bltcdat = srcc;
		if (dstp) chipmem_agnus_wput (dstp, dstd);
if (totald != 0) b->blitzero = 0;
}
void blitdofast_desc_ea (struct blitterContext *bC,uaecptr pta, uaecptr ptb, uaecptr ptc, uaecptr ptd, struct bltinfo *b)
{
uae_u32 totald = 0;
int i,j;
uae_u32 preva = 0;
uae_u32 prevb = 0, srcb = b->bltbhold;
uae_u32 srcc = b->bltcdat;
uae_u32 dstd=0;
uaecptr dstp = 0;
int dodst = 0;
for (j = 0; j < b->vblitsize; j++) {
	for (i = 0; i < b->hblitsize; i++) {
		uae_u32 bltadat, srca;
		if (ptc) { srcc = chipmem_agnus_wget (ptc); ptc -= 2; }
		if (ptb) {
			uae_u32 bltbdat; bC -> blt_info.bltbdat = bltbdat = chipmem_agnus_wget (ptb); ptb -= 2;
			srcb = ((bltbdat << 16) | prevb) >> b->blitdownbshift;
			prevb = bltbdat;
		}
		if (pta) { bC ->  blt_info.bltadat = bltadat = chipmem_agnus_wget (pta); pta -= 2; } else { bltadat = bC -> blt_info.bltadat; }
		bltadat &= blit_masktable[i];
		srca = (((uae_u32)bltadat << 16) | preva) >> b->blitdownashift;
		preva = bltadat;
		if (dodst) chipmem_agnus_wput (dstp, dstd);
		dstd = ((srcc | (srca & srcb))) & 0xFFFF;
		totald |= dstd;
		if (ptd) { dodst = 1; dstp = ptd; ptd -= 2; }
	}
	if (pta) pta -= b->bltamod;
	if (ptb) ptb -= b->bltbmod;
	if (ptc) ptc -= b->bltcmod;
	if (ptd) ptd -= b->bltdmod;
}
b->bltbhold = srcb;
b->bltcdat = srcc;
		if (dodst) chipmem_agnus_wput (dstp, dstd);
if (totald != 0) b->blitzero = 0;
}
void blitdofast_f0 (struct blitterContext *bC,uaecptr pta, uaecptr ptb, uaecptr ptc, uaecptr ptd, struct bltinfo *b)
{
int i,j;
uae_u32 totald = 0;
uae_u32 preva = 0;
uae_u32 dstd=0;
uaecptr dstp = 0;
int dodst = 0;
for (j = 0; j < b->vblitsize; j++) {
	for (i = 0; i < b->hblitsize; i++) {
		uae_u32 bltadat, srca;

		if (pta) { bC -> blt_info.bltadat = bltadat = chipmem_agnus_wget (pta); pta += 2; } else { bltadat = bC -> blt_info.bltadat; }
		bltadat &= blit_masktable[i];
		srca = (((uae_u32)preva << 16) | bltadat) >> b->blitashift;
		preva = bltadat;
		if (dodst) chipmem_agnus_wput (dstp, dstd);
		dstd = (srca) & 0xFFFF;
		totald |= dstd;
		if (ptd) { dodst = 1; dstp = ptd; ptd += 2; }
	}
	if (pta) pta += b->bltamod;
	if (ptd) ptd += b->bltdmod;
}
		if (dstp) chipmem_agnus_wput (dstp, dstd);
if (totald != 0) b->blitzero = 0;
}
void blitdofast_desc_f0 (struct blitterContext *bC,uaecptr pta, uaecptr ptb, uaecptr ptc, uaecptr ptd, struct bltinfo *b)
{
uae_u32 totald = 0;
int i,j;
uae_u32 preva = 0;
uae_u32 dstd=0;
uaecptr dstp = 0;
int dodst = 0;
for (j = 0; j < b->vblitsize; j++) {
	for (i = 0; i < b->hblitsize; i++) {
		uae_u32 bltadat, srca;
		if (pta) { bC ->  blt_info.bltadat = bltadat = chipmem_agnus_wget (pta); pta -= 2; } else { bltadat = bC -> blt_info.bltadat; }
		bltadat &= blit_masktable[i];
		srca = (((uae_u32)bltadat << 16) | preva) >> b->blitdownashift;
		preva = bltadat;
		if (dodst) chipmem_agnus_wput (dstp, dstd);
		dstd = (srca) & 0xFFFF;
		totald |= dstd;
		if (ptd) { dodst = 1; dstp = ptd; ptd -= 2; }
	}
	if (pta) pta -= b->bltamod;
	if (ptd) ptd -= b->bltdmod;
}
		if (dodst) chipmem_agnus_wput (dstp, dstd);
if (totald != 0) b->blitzero = 0;
}
void blitdofast_fa (struct blitterContext *bC,uaecptr pta, uaecptr ptb, uaecptr ptc, uaecptr ptd, struct bltinfo *b)
{
int i,j;
uae_u32 totald = 0;
uae_u32 preva = 0;
uae_u32 srcc = b->bltcdat;
uae_u32 dstd=0;
uaecptr dstp = 0;
int dodst = 0;
for (j = 0; j < b->vblitsize; j++) {
	for (i = 0; i < b->hblitsize; i++) {
		uae_u32 bltadat, srca;

		if (ptc) { srcc = chipmem_agnus_wget (ptc); ptc += 2; }
		if (pta) { bC -> blt_info.bltadat = bltadat = chipmem_agnus_wget (pta); pta += 2; } else { bltadat = bC -> blt_info.bltadat; }
		bltadat &= blit_masktable[i];
		srca = (((uae_u32)preva << 16) | bltadat) >> b->blitashift;
		preva = bltadat;
		if (dodst) chipmem_agnus_wput (dstp, dstd);
		dstd = ((srca | srcc)) & 0xFFFF;
		totald |= dstd;
		if (ptd) { dodst = 1; dstp = ptd; ptd += 2; }
	}
	if (pta) pta += b->bltamod;
	if (ptc) ptc += b->bltcmod;
	if (ptd) ptd += b->bltdmod;
}
b->bltcdat = srcc;
		if (dstp) chipmem_agnus_wput (dstp, dstd);
if (totald != 0) b->blitzero = 0;
}
void blitdofast_desc_fa (struct blitterContext *bC,uaecptr pta, uaecptr ptb, uaecptr ptc, uaecptr ptd, struct bltinfo *b)
{
uae_u32 totald = 0;
int i,j;
uae_u32 preva = 0;
uae_u32 srcc = b->bltcdat;
uae_u32 dstd=0;
uaecptr dstp = 0;
int dodst = 0;
for (j = 0; j < b->vblitsize; j++) {
	for (i = 0; i < b->hblitsize; i++) {
		uae_u32 bltadat, srca;
		if (ptc) { srcc = chipmem_agnus_wget (ptc); ptc -= 2; }
		if (pta) { bC ->  blt_info.bltadat = bltadat = chipmem_agnus_wget (pta); pta -= 2; } else { bltadat = bC -> blt_info.bltadat; }
		bltadat &= blit_masktable[i];
		srca = (((uae_u32)bltadat << 16) | preva) >> b->blitdownashift;
		preva = bltadat;
		if (dodst) chipmem_agnus_wput (dstp, dstd);
		dstd = ((srca | srcc)) & 0xFFFF;
		totald |= dstd;
		if (ptd) { dodst = 1; dstp = ptd; ptd -= 2; }
	}
	if (pta) pta -= b->bltamod;
	if (ptc) ptc -= b->bltcmod;
	if (ptd) ptd -= b->bltdmod;
}
b->bltcdat = srcc;
		if (dodst) chipmem_agnus_wput (dstp, dstd);
if (totald != 0) b->blitzero = 0;
}
void blitdofast_fc (struct blitterContext *bC,uaecptr pta, uaecptr ptb, uaecptr ptc, uaecptr ptd, struct bltinfo *b)
{
int i,j;
uae_u32 totald = 0;
uae_u32 preva = 0;
uae_u32 prevb = 0, srcb = b->bltbhold;
uae_u32 dstd=0;
uaecptr dstp = 0;
int dodst = 0;
for (j = 0; j < b->vblitsize; j++) {
	for (i = 0; i < b->hblitsize; i++) {
		uae_u32 bltadat, srca;

		if (ptb) {
			uae_u32 bltbdat; bC -> blt_info.bltbdat = bltbdat = chipmem_agnus_wget (ptb); ptb += 2;
			srcb = (((uae_u32)prevb << 16) | bltbdat) >> b->blitbshift;
			prevb = bltbdat;
		}
		if (pta) { bC -> blt_info.bltadat = bltadat = chipmem_agnus_wget (pta); pta += 2; } else { bltadat = bC -> blt_info.bltadat; }
		bltadat &= blit_masktable[i];
		srca = (((uae_u32)preva << 16) | bltadat) >> b->blitashift;
		preva = bltadat;
		if (dodst) chipmem_agnus_wput (dstp, dstd);
		dstd = ((srca | srcb)) & 0xFFFF;
		totald |= dstd;
		if (ptd) { dodst = 1; dstp = ptd; ptd += 2; }
	}
	if (pta) pta += b->bltamod;
	if (ptb) ptb += b->bltbmod;
	if (ptd) ptd += b->bltdmod;
}
b->bltbhold = srcb;
		if (dstp) chipmem_agnus_wput (dstp, dstd);
if (totald != 0) b->blitzero = 0;
}
void blitdofast_desc_fc (struct blitterContext *bC,uaecptr pta, uaecptr ptb, uaecptr ptc, uaecptr ptd, struct bltinfo *b)
{
uae_u32 totald = 0;
int i,j;
uae_u32 preva = 0;
uae_u32 prevb = 0, srcb = b->bltbhold;
uae_u32 dstd=0;
uaecptr dstp = 0;
int dodst = 0;
for (j = 0; j < b->vblitsize; j++) {
	for (i = 0; i < b->hblitsize; i++) {
		uae_u32 bltadat, srca;
		if (ptb) {
			uae_u32 bltbdat; bC -> blt_info.bltbdat = bltbdat = chipmem_agnus_wget (ptb); ptb -= 2;
			srcb = ((bltbdat << 16) | prevb) >> b->blitdownbshift;
			prevb = bltbdat;
		}
		if (pta) { bC ->  blt_info.bltadat = bltadat = chipmem_agnus_wget (pta); pta -= 2; } else { bltadat = bC -> blt_info.bltadat; }
		bltadat &= blit_masktable[i];
		srca = (((uae_u32)bltadat << 16) | preva) >> b->blitdownashift;
		preva = bltadat;
		if (dodst) chipmem_agnus_wput (dstp, dstd);
		dstd = ((srca | srcb)) & 0xFFFF;
		totald |= dstd;
		if (ptd) { dodst = 1; dstp = ptd; ptd -= 2; }
	}
	if (pta) pta -= b->bltamod;
	if (ptb) ptb -= b->bltbmod;
	if (ptd) ptd -= b->bltdmod;
}
b->bltbhold = srcb;
		if (dodst) chipmem_agnus_wput (dstp, dstd);
if (totald != 0) b->blitzero = 0;
}
