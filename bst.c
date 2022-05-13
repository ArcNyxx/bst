/* bst - binary search tree
 * Copyright (C) 2022 ArcNyxx
 * see LICENCE file for licensing information */

#include <limits.h>
#include <stdlib.h>

#include "bst.h"

static void bsn_dest(bsn_t *curr, bsn_t *prev);

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

bsn_t *
bsn_init(bst_find_t val)
{
	bsn_t *node;
	if ((node = malloc(sizeof(bsn_t))) == NULL)
		exit(1);
	node->val = val, node->lft = node->rgt = NULL;
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

bool
bst_addn(bst_t *bst, bsn_t *bsn)
{
	bsn_t *curr = bst->root, *prev;

	if (curr == NULL) {
		bst->root = bsn, bst->size = 1;
		return true;
	}

	while (curr != NULL) {
		if (curr->val == bsn->val)
			return false;

		prev = curr;
		if (bsn->val > curr->val)
			curr = curr->rgt;
		else
			curr = curr->lft;
	}

	if (bsn->val > prev->val)
		prev->rgt = bsn;
	else
		prev->lft = bsn;

	bst->size += 1;
	return true;
}

bool
bst_remn(bst_t *bst, bst_find_t val)
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

bsn_t *
bst_find(bst_t *bst, bst_find_t val)
{
	bsn_t *curr = bst->root;

	while (curr != NULL) {
		if (curr->val == val)
			return curr;

		if (val > curr->val)
			curr = curr->rgt;
		else
			curr = curr->lft;
	}

	return NULL;
}

bst_find_t
bst_minn(bst_t *bst)
{
	if (bst->size == 0)
		return INT_MAX;

	bsn_t *node = bst->root;
	for (; node->lft != NULL; node = node->lft);
	return node->val;
}

bst_find_t
bst_maxn(bst_t *bst)
{
	if (bst->size == 0)
		return INT_MIN;

	bsn_t *node = bst->root;
	for (; node->rgt != NULL; node = node->rgt);
	return node->val;
}
