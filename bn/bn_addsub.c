#include <stdlib.h>
#include <assert.h>

#include "bn.h"

#define MAX(a,b) ((a) > (b) ? (a) : ( b))

bn *bn_add(bn *a, bn *b) {
    if (a->num_limbs == 0) {
	return bn_clone(b);
    }

    if (b->num_limbs == 0) {
	return bn_clone(a);
    }

    // -a + b == b - a
    if (a->neg && !b->neg) {
	bn *c = bn_shallowclone(a);

	if (!c) {
	    return NULL;
	}

	c->neg = 0;
	bn *d = bn_sub(b, c);
	bn_free(c, 1);
	return d;
    }

    // a + -b == a - b
    if (!a->neg && b->neg) {
	bn *c = bn_shallowclone(b);

	if (!c) {
	    return NULL;
	}

	c->neg = 0;
	bn *d = bn_sub(a, c);
	bn_free(c, 1);
	return d;
    }

    bn *c = calloc(1, sizeof(*c));

    if (!c) {
	return NULL;
    }

    c->neg = a->neg;
    c->num_limbs = MAX(a->num_limbs, b->num_limbs) + 1;
    c->limbs = calloc(c->num_limbs, sizeof(uint32_t));

    if (!c->limbs) {
	free(c);
	return NULL;
    }

    if (b->num_limbs > a->num_limbs) {
	BN_SWAP(a, b);
    }

    uint64_t aux;
    int carry = 0;

    for (int i = 0; i < b->num_limbs; i++) {
	aux = carry;
	aux += b->limbs[i];
	aux += a->limbs[i];
	c->limbs[i] = aux & 0xFFFFFFFFul;
	carry = aux >> 32;
	assert(carry <= 1);
    }

    for (int i = b->num_limbs; i < a->num_limbs; i++) {
	aux = carry;
	aux += a->limbs[i];
	c->limbs[i] = aux & 0xFFFFFFFFul;
	carry = aux >> 32;
	assert(carry <= 1);
    }

    if (carry) {
	c->limbs[c->num_limbs - 1] = 1;
    } else {
	uint32_t *tmp_limbs = realloc(c->limbs, (c->num_limbs - 1) * sizeof(uint32_t));

	if (!tmp_limbs) {
	    free(c->limbs);
	    free(c);
	    return NULL;
	}

	c->limbs = tmp_limbs;
	c->num_limbs--;
    }

    return c;
}


bn *bn_sub(bn *a, bn *b) {
    return NULL;
}
