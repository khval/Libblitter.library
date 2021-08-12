

#define STATIC_INLINE inline

#define REGPARAM2
#define REGPARAM

#warning small subset

typedef void  * uaecptr;
typedef unsigned char uae_u8;
typedef unsigned short uae_u16;
typedef unsigned int uae_u32;
typedef unsigned long long int uae_u64;

typedef signed char uae_s8;
typedef signed short uae_s16;
typedef signed int uae_s32;
typedef signed long long int uae_s64;


#define chipmem_agnus_wget(addr) *((uae_u16 *) (addr))
#define chipmem_agnus_wput(addr,v) *((uae_u16 *) (addr))=(v)
#define get_real_address(addr) *((uae_u8 *) (addr))

