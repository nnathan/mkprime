#ifndef BN_H
#define BN_H

#include <stdint.h>

typedef struct bn {
	/* neg is set to 0 if non-negative, otherwise negative */
	int neg;

	/* Number of allocated limbs */
	int num_limbs;

	/* Instead of bikeshedding on optimal limb size,
	 * I chose a size that works well across 32 and 64-bit architectures.
	 */
	uint32_t *limbs;
} bn;

#define BN_SWAP(x,y)  do { bn *t = (x); (x) = (y); (y) = (t); } while (0)

bn *bn_add(bn *a, bn *b);
bn *bn_sub(bn *a, bn *b);
bn *bn_clone(bn *a);
bn *bn_shallowclone(bn *a);
void bn_free(bn *a, int is_shallow);

#endif /* BN_H */
