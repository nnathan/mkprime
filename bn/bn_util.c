#include <stdlib.h>

#include "bn.h"

bn *bn_clone(bn *a) {
    bn *tmp = calloc(1, sizeof *tmp);

    if (!tmp) {
	return NULL;
    }

    tmp->neg = a->neg;
    tmp->num_limbs = a->num_limbs;
    if (tmp->num_limbs > 0) {
	tmp->limbs = malloc(tmp->num_limbs * sizeof(uint32_t));

	if (!tmp->limbs) {
	    free(tmp);
	    return NULL;
	}

	for (int i = 0; i < tmp->num_limbs; i++) {
	    tmp->limbs[i] = a->limbs[i];
	}
    }

    return tmp;
}

bn *bn_shallowclone(bn *a) {
    bn *tmp = calloc(1, sizeof *tmp);

    if (!tmp) {
	return NULL;
    }

    tmp->neg = a->neg;
    tmp->num_limbs = a->num_limbs;
    tmp->limbs = a->limbs;

    return tmp;
}

void bn_free(bn *a, int is_shallow) {
    if (is_shallow) {
	free(a);
	return;
    }

    if (a && a->limbs) {
	free(a->limbs);
    }

    free(a);

    return;
}
