/* bst - binary search tree
 * Copyright (C) 2022 ArcNyxx
 * see LICENCE file for licensing information */

#include <limits.h>
#include <stdlib.h>

#include "bst.h"

static bsn_t *bsn_init(int32_t val);
static void bsn_dest(bsn_t *curr, bsn_t *prev);

static bsn_t *
bsn_init(int32_t val)
{
	bsn_t *node;
	if ((node = malloc(sizeof(bsn_t))) == NULL)
		exit(1);
	node->val = val, node->lft = node->rgt = NULL;
}

static void
bsn_dest(bsn_t *curr, bsn_t *prev)
{
	if (curr->lft == NULL && curr->rgt == NULL) {
		if (prev->lft == curr)
			prev->lft = NULL;
		else
			prev->rgt = NULL;
	} else if (curr->lft != NULL && curr->rgt != NULL) {
		/* find max on lft side */
		bsn_t *scurr = curr->lft, *sprev = curr;
		for (; scurr->rgt != NULL; sprev = scurr, scurr = scurr->rgt);

		/* must only have one or zero children, delete other instead */
		curr->val = scurr->val;
		curr = scurr;

		/* reattach other branch */
		if (sprev->lft == scurr)
			sprev->lft = scurr->lft;
		else
			sprev->rgt = scurr->lft;
	} else {
		bsn_t *new;
		if (curr->lft != NULL)
			new = curr->lft;
		else
			new = curr->rgt;

		if (prev->lft == curr)
			prev->lft = new;
		else
			prev->rgt = new;
	}

	free(curr);
}

void
bst_init(bst_t *bst)
{
	bst->root = NULL, bst->size = 0;
}

void
bst_dest(bst_t *bst)
{
}

uint32_t
bst_size(bst_t *bst)
{
	return bst->size;
}

bool
bst_addn(bst_t *bst, int32_t val)
{
	bsn_t *curr = bst->root, *prev;

	if (curr == NULL) {
		bst->root = bsn_init(val), bst->size = 1;
		return true;
	}

	while (curr != NULL) {
		if (curr->val == val)
			return false;

		prev = curr;
		if (val > curr->val)
			curr = curr->rgt;
		else
			curr = curr->lft;
	}

	if (val > prev->val)
		prev->rgt = bsn_init(val);
	else
		prev->lft = bsn_init(val);

	bst->size += 1;
	return true;
}

bool
bst_remn(bst_t *bst, int32_t val)
{
	bsn_t *curr = bst->root, *prev = curr;

	while (curr != NULL) {
		if (curr->val == val) {
			if (prev == curr) {
				if (curr->lft != NULL && curr->rgt != NULL) {
					bsn_dest(curr, curr);
				} else {
					if (curr->lft == NULL &&
							curr->rgt == NULL)
						bst->root = NULL;
					else if (curr->lft == NULL)
						bst->root = curr->rgt;
					else
						bst->root = curr->lft;
					free(curr);
				}
			} else {
				bsn_dest(curr, prev);
			}

			bst->size -= 1;
			return true;
		}

		prev = curr;
		if (val > curr->val)
			curr = curr->rgt;
		else
			curr = curr->lft;
	}
	return false;
}

int32_t
bst_minn(bst_t *bst)
{
	if (bst->size == 0)
		return INT_MAX;

	bsn_t *node = bst->root;
	for (; node->lft != NULL; node = node->lft);
	return node->val;
}

int32_t
bst_maxn(bst_t *bst)
{
	if (bst->size == 0)
		return INT_MIN;

	bsn_t *node = bst->root;
	for (; node->rgt != NULL; node = node->rgt);
	return node->val;
}
