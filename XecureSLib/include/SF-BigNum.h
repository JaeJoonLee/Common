/************************************
  REVISION LOG ENTRY
  Revision By: 차정호
  Revised on 98-11-25 오후 3:50:45
  Comments: ...
 ************************************/
#ifndef _SF_BIGNUM_H
#define _SF_BIGNUM_H

#include "SF-Error.h"
#include "SF-Rand.h"

#ifdef  __cplusplus
extern "C" {
#endif

#ifdef WIN32
#define BN_ULLONG	unsigned _int64
#else
#define BN_ULLONG	unsigned long long
#endif

#define BN_ULONG	unsigned long
#define BN_LONG		long
#define BN_BITS		64
#define BN_BYTES	4
#define BN_BITS2	32
#define BN_BITS4	16
#define BN_MASK2	(0xffffffffL)
#define BN_MASK2l	(0xffff)
#define BN_MASK2h1	(0xffff8000L)
#define BN_MASK2h	(0xffff0000L)
#define BN_CBIT		((BN_ULLONG)0x100000000LL)
#define BN_TBIT		(0x80000000L)
#define BN_NOT_MASK2	((BN_ULLONG)0xffffffff00000000LL)

#define BN_DEFAULT_BITS	1280

typedef struct {
	BN_ULONG *d;
	int top;
	int max;
	int neg;
} BIGNUM;

#define BN_CTX_NUM	12
typedef struct {
	int tos;
	BIGNUM *bn[BN_CTX_NUM];
} BN_CTX;

typedef struct {
        int ri;
        BIGNUM *RR;
        BIGNUM *N;
        BIGNUM *Ni;
	BN_ULONG n0;
} BN_MONT_CTX;


#define BN_num_bytes(a)	((BN_num_bits(a)+7)/8)
#define BN_is_word(a,w)	(((a)->top == 1) && ((a)->d[0] == (BN_ULONG)(w)))
#define BN_is_zero(a)	(((a)->top <= 1) && ((a)->d[0] == (BN_ULONG)0))
#define BN_is_one(a)	(BN_is_word((a),1))
#define BN_one(a)	(BN_set_word((a),1))
#define BN_zero(a)	(BN_set_word((a),0))

extern BIGNUM *BN_value_one;

BN_CTX *BN_CTX_new();
void	BN_CTX_free(BN_CTX *c);
int	BN_num_bits(BIGNUM *a);
int	BN_num_bits_word(BN_ULONG);
BIGNUM *BN_new(void);
void	BN_clear_free(BIGNUM *a);
BIGNUM *BN_copy(BIGNUM *a, BIGNUM *b);
BIGNUM *BN_bin2bn(unsigned char *s,int len,BIGNUM *ret);
int	BN_bn2bin(BIGNUM *a, unsigned char *to);
int	BN_sub(BIGNUM *r, BIGNUM *a, BIGNUM *b);
void	bn_qsub(BIGNUM *r, BIGNUM *a, BIGNUM *b);
int	BN_add(BIGNUM *r, BIGNUM *a, BIGNUM *b);
int	BN_mod(BIGNUM *rem, BIGNUM *m, BIGNUM *d, BN_CTX *ctx);
int	BN_div(BIGNUM *dv, BIGNUM *rem, BIGNUM *m, BIGNUM *d, BN_CTX *ctx);
int	BN_mul(BIGNUM *r, BIGNUM *a, BIGNUM *b);
int	BN_sqr(BIGNUM *r, BIGNUM *a,BN_CTX *ctx);
BN_ULONG BN_mod_word(BIGNUM *a, unsigned long w);
int     BN_add_word(BIGNUM *a, unsigned long w);
int	BN_set_word(BIGNUM *a, unsigned long w);
int	BN_cmp(BIGNUM *a, BIGNUM *b);
void	BN_free(BIGNUM *a);
int	BN_is_bit_set(BIGNUM *a, int n);
int	BN_lshift(BIGNUM *r, BIGNUM *a, int n);
int	BN_lshift1(BIGNUM *r, BIGNUM *a);
int	BN_mod_exp(BIGNUM *r, BIGNUM *a, BIGNUM *p, BIGNUM *m,BN_CTX *ctx);
int	BN_mod_exp_mont(BIGNUM *r, BIGNUM *a, BIGNUM *p, BIGNUM *m,BN_CTX *ctx);
int	BN_mod_exp_recp(BIGNUM *r, BIGNUM *a, BIGNUM *p, BIGNUM *m,BN_CTX *ctx);
int	BN_mask_bits(BIGNUM *a,int n);
int	BN_mod_mul_reciprocal(BIGNUM *r, BIGNUM *x, BIGNUM *y, BIGNUM *m, BIGNUM *i, int nb, BN_CTX *ctx);
int	BN_mod_mul(BIGNUM *ret, BIGNUM *a, BIGNUM *b, BIGNUM *m, BN_CTX *ctx);
int	BN_reciprocal(BIGNUM *r, BIGNUM *m, BN_CTX *ctx);
int	BN_rshift(BIGNUM *r, BIGNUM *a, int n);
int	BN_rshift1(BIGNUM *r, BIGNUM *a);
void	BN_clear(BIGNUM *a);
BIGNUM *bn_expand2(BIGNUM *b, int bits);
BIGNUM *BN_dup(BIGNUM *a);
int	BN_ucmp(BIGNUM *a, BIGNUM *b);
int	BN_set_bit(BIGNUM *a, int n);
int	BN_clear_bit(BIGNUM *a, int n);
int	BN_gcd(BIGNUM *r,BIGNUM *in_a,BIGNUM *in_b,BN_CTX *ctx);
BIGNUM *BN_mod_inverse(BIGNUM *a, BIGNUM *n,BN_CTX *ctx);
BIGNUM *BN_generate_prime(int bits, int strong, BIGNUM *add, BIGNUM *rem);
int	BN_is_prime(BIGNUM *p, int nchecks, BN_CTX *ctx);

BN_ULONG bn_mul_add_word(BN_ULONG *rp, BN_ULONG *ap, int num, BN_ULONG w);
BN_ULONG bn_mul_word(BN_ULONG *rp, BN_ULONG *ap, int num, BN_ULONG w);
void     bn_sqr_words(BN_ULONG *rp, BN_ULONG *ap, int num);
BN_ULONG bn_div64(BN_ULONG h, BN_ULONG l, BN_ULONG d);

int BN_mod_mul_montgomery(BIGNUM *r,BIGNUM *a,BIGNUM *b,BN_MONT_CTX *mont, BN_CTX *ctx);
int BN_from_montgomery(BIGNUM *r,BIGNUM *a,BN_MONT_CTX *mont,BN_CTX *ctx);
BN_MONT_CTX *BN_MONT_CTX_new();
void BN_MONT_CTX_free(BN_MONT_CTX *mont);
int BN_MONT_CTX_set(BN_MONT_CTX *mont,BIGNUM *modulus,BN_CTX *ctx);


#define ERR_R_MALLOC_FAILURE		10
#define BN_R_BAD_RECIPROCAL			100
#define BN_R_DIV_BY_ZERO			101
#define BN_R_NO_INVERSE				102

#ifdef  __cplusplus
}
#endif

#endif /* _SF_BIGNUM_H */







