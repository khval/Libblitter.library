 /*
  * UAE - The Un*x Amiga Emulator
  *
  * MC68000 emulation
  *
  * Copyright 1995 Bernd Schmidt
  */

#if 0

#include "readcpu.h"
#include "machdep/m68k.h"

#endif

#ifndef SET_CFLG

#define SET_CFLG(x) (CFLG = (x))
#define SET_NFLG(x) (NFLG = (x))
#define SET_VFLG(x) (VFLG = (x))
#define SET_ZFLG(x) (ZFLG = (x))
#define SET_XFLG(x) (XFLG = (x))

#define GET_CFLG CFLG
#define GET_NFLG NFLG
#define GET_VFLG VFLG
#define GET_ZFLG ZFLG
#define GET_XFLG XFLG

#define CLEAR_CZNV do { \
 SET_CFLG (0); \
 SET_ZFLG (0); \
 SET_NFLG (0); \
 SET_VFLG (0); \
} while (0)

#define COPY_CARRY (SET_XFLG (GET_CFLG))
#endif

extern const int areg_byteinc[];
extern const int imm8_table[];

extern int movem_index1[256];
extern int movem_index2[256];
extern int movem_next[256];

extern int fpp_movem_index1[256];
extern int fpp_movem_index2[256];
extern int fpp_movem_next[256];

extern int broken_in;

#if 0
typedef unsigned long cpuop_func (uae_u32) REGPARAM;

struct cputbl {
    cpuop_func *handler;
    int specific;
    uae_u16 opcode;
};

extern unsigned long op_illg (uae_u32) REGPARAM;

#endif

typedef char flagtype;

/* You can set this to long double to be more accurate. However, the
   resulting alignment issues will cost a lot of performance in some
   apps */
#define USE_LONG_DOUBLE 0

#if USE_LONG_DOUBLE
typedef long double fptype;
#else
typedef double fptype;
#endif

struct regstruct
{
    uae_u32 regs[16];

    uae_u32 pc;
    uae_u8 *pc_p;
    uae_u8 *pc_oldp;

    uae_u16 irc, ir;
    uae_u32 spcflags;

    uaecptr usp,isp,msp;
    uae_u16 sr;
    flagtype t1;
    flagtype t0;
    flagtype s;
    flagtype m;
    flagtype x;
    flagtype stopped;
    int intmask;

    uae_u32 vbr,sfc,dfc;

    fptype fp[8];
    fptype fp_result;

    uae_u32 fpcr,fpsr,fpiar;
    uae_u32 fpsr_highbyte;

    uae_u32 caar, cacr;
    uae_u32 itt0, itt1, dtt0, dtt1;
    uae_u32 tcr, mmusr, urp, srp, buscr;

    uae_u32 mmu_fslw, mmu_fault_addr;
    uae_u16 mmu_ssw;
    uae_u32 wb3_data;
    uae_u16 wb3_status;

    uae_u64 srp_030, crp_030;
    uae_u32 tt0_030, tt1_030, tc_030;
    uae_u16 mmusr_030;

    uae_u32 pcr;
    
    uae_u32 kick_mask;
    uae_u32 address_space_mask;

    uae_u8 panic;
    uae_u32 panic_pc, panic_addr;
};

// regs, lastint_regs;

#if 0

STATIC_INLINE uae_u32 munge24(uae_u32 x)
{
    return x & regs.address_space_mask;
}

STATIC_INLINE void set_special (uae_u32 x)
{
    regs.spcflags |= x;
}

STATIC_INLINE void unset_special (uae_u32 x)
{
    regs.spcflags &= ~x;
}

#define m68k_dreg(r,num) ((r).regs[(num)])
#define m68k_areg(r,num) (((r).regs + 8)[(num)])

STATIC_INLINE void m68k_setpc (uaecptr newpc)
{
    regs.pc_p = regs.pc_oldp = get_real_address (newpc);
    regs.pc = newpc;
}

STATIC_INLINE uaecptr m68k_getpc (void)
{
    return regs.pc + ((char *)regs.pc_p - (char *)regs.pc_oldp);
}

STATIC_INLINE uaecptr m68k_getpc_p (uae_u8 *p)
{
    return regs.pc + ((char *)p - (char *)regs.pc_oldp);
}

#define get_ibyte(o) do_get_mem_byte((uae_u8 *)(regs.pc_p + (o) + 1))
#define get_iword(o) do_get_mem_word((uae_u16 *)(regs.pc_p + (o)))
#define get_ilong(o) do_get_mem_long((uae_u32 *)(regs.pc_p + (o)))

#define m68k_incpc(o) (regs.pc_p += (o))

/* These are only used by the 68020/68881 code, and therefore don't
 * need to handle prefetch.  */
STATIC_INLINE uae_u32 next_ibyte (void)
{
    uae_u32 r = get_ibyte (0);
    m68k_incpc (2);
    return r;
}

STATIC_INLINE uae_u32 next_iword (void)
{
    uae_u32 r = get_iword (0);
    m68k_incpc (2);
    return r;
}

STATIC_INLINE uae_u32 next_ilong (void)
{
    uae_u32 r = get_ilong (0);
    m68k_incpc (4);
    return r;
}

STATIC_INLINE void m68k_do_rts(void)
{
    m68k_setpc(get_long(m68k_areg (regs, 7)));
    m68k_areg (regs, 7) += 4;
}

STATIC_INLINE void m68k_do_bsr(uaecptr oldpc, uae_s32 offset)
{
    m68k_areg (regs, 7) -= 4;
    put_long(m68k_areg (regs, 7), oldpc);
    m68k_incpc(offset);
}

STATIC_INLINE void m68k_do_jsr(uaecptr oldpc, uaecptr dest)
{
    m68k_areg (regs, 7) -= 4;
    put_long(m68k_areg (regs, 7), oldpc);
    m68k_setpc(dest);
}

#endif

#if 0

STATIC_INLINE void m68k_setstopped (int stop)
{
    regs.stopped = stop;
    /* A traced STOP instruction drops through immediately without
       actually stopping.  */
    if (stop && (regs.spcflags & SPCFLAG_DOTRACE) == 0)
	regs.spcflags |= SPCFLAG_STOP;
}

#endif

extern uae_u32 get_disp_ea_020 (uae_u32 base, uae_u32 dp);
extern uae_u32 get_disp_ea_000 (uae_u32 base, uae_u32 dp);

#if 0
extern uae_s32 ShowEA (FILE *, int reg, amodes mode, wordsizes size, char *buf);
#endif

extern void MakeSR (void);
extern void MakeFromSR (void);
extern void Exception (int, uaecptr);
extern void dump_counts (void);
extern int m68k_move2c (int, uae_u32 *);
extern int m68k_movec2 (int, uae_u32 *);
extern void m68k_divl (uae_u32, uae_u32, uae_u16, uaecptr);
extern void m68k_mull (uae_u32, uae_u32, uae_u16);
extern void init_m68k (void);
extern void m68k_go (int);

#if 0
extern void m68k_dumpstate (FILE *, uaecptr *);
extern void m68k_disasm (FILE *, uaecptr, uaecptr *, int);
#endif

extern void m68k_reset (void);

extern void mmu_op (uae_u32, uae_u16);
extern void mmu_op30 (uaecptr, uae_u32, int, uaecptr);

extern void fpp_opp (uae_u32, uae_u16);
extern void fdbcc_opp (uae_u32, uae_u16);
extern void fscc_opp (uae_u32, uae_u16);
extern void ftrapcc_opp (uae_u32,uaecptr);
extern void fbcc_opp (uae_u32, uaecptr, uae_u32);
extern void fsave_opp (uae_u32);
extern void frestore_opp (uae_u32);

extern void exception3 (uae_u32 opcode, uaecptr addr, uaecptr fault);
extern void exception3i (uae_u32 opcode, uaecptr addr, uaecptr fault);
extern void exception2 (uaecptr addr, uaecptr fault);
extern void cpureset (void);

extern void fill_prefetch_slow (void);

#define CPU_OP_NAME(a) op ## a

#if 0

/* 68060 */
extern const struct cputbl op_smalltbl_0_ff[];
/* 68040 */
extern const struct cputbl op_smalltbl_1_ff[];
/* 68030 */
extern const struct cputbl op_smalltbl_2_ff[];
/* 68020 */
extern const struct cputbl op_smalltbl_3_ff[];
/* 68010 */
extern const struct cputbl op_smalltbl_4_ff[];
/* 68000 - unused */
#if 0
extern const struct cputbl op_smalltbl_5_ff[];
#endif
/* 68000 slow but compatible.  */
extern const struct cputbl op_smalltbl_6_ff[];

extern cpuop_func *cpufunctbl[65536] ASM_SYM_FOR_FUNC ("cpufunctbl");

#endif

#ifdef JIT
#else
#define flush_icache(X) do {} while (0)
#endif
