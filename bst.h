/* bst - binary search tree
 * Copyright (C) 2022 ArcNyxx
 * see LICENCE file for licensing information */

#ifndef BST_H
#define BST_H

#include <stdbool.h>
#include <stdint.h>

typedef struct bsn {
	int32_t val;
	struct bsn *lft, *rgt;
} bsn_t;

typedef struct bst {
	bsn_t *root;
	uint32_t size;
} bst_t;

void     bst_init(bst_t *bst);
void     bst_dest(bst_t *bst);

uint32_t bst_size(bst_t *bst);

bool     bst_addn(bst_t *bst, int32_t val);
bool     bst_remn(bst_t *bst, int32_t val);

int32_t  bst_minn(bst_t *bst);
int32_t  bst_maxn(bst_t *bst);

#endif /* BST_H */
