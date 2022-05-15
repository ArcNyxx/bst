/* bst - binary search tree
 * Copyright (C) 2022 ArcNyxx
 * see LICENCE file for licensing information */

#include <limits.h>
#include <stdlib.h>

#include "bst.h"

static bsn_t *bsn_dest(bsn_t *curr, bsn_t *prev);

static bsn_t *
bsn_dest(bsn_t *curr, bsn_t *prev)
{
	if (curr->lft == NULL && curr->rgt == NULL) {
		if (prev->lft == curr)
			prev->lft = NULL;
		else
			prev->rgt = NULL;
	} else if (curr->lft != NULL && curr->rgt != NULL) {
		/* find max on left side */
		bsn_t *scurr = curr->lft, *sprev = curr;
		for (; scurr->rgt != NULL; sprev = scurr, scurr = scurr->rgt);

		/* must only have one or zero children, delete other instead */
		curr->val = scurr->val, curr->data = scurr->data;
		curr = scurr;

		/* reattach other branch */
		if (sprev->lft == scurr)
			sprev->lft = scurr->lft;
		else
			sprev->rgt = scurr->lft;
	} else {
		if (prev->lft == curr)
			prev->lft = curr->lft != NULL ? curr->lft : curr->rgt;
		else
			prev->rgt = curr->lft != NULL ? curr->lft : curr->rgt;
	}

	return curr;
}

bsn_t *
bsn_init(bst_find_t val)
{
	bsn_t *node;
	if ((node = malloc(sizeof(bsn_t))) == NULL)
		exit(1);
	node->val = val, node->lft = node->rgt = NULL;
	return node;
}

bst_t *
bst_init(bst_t *bst)
{
	bst->root = NULL, bst->size = 0;
}

bst_t *
bst_dest(bst_t *bst)
{
	if (bst->root != NULL) {
		for (; bst->root->lft != NULL;
				bsn_dest(bst->root->lft, bst->root));
		for (; bst->root->rgt != NULL;
				bsn_dest(bst->root->rgt, bst->root));
		free(bst->root);
	}

	return bst_init(bst);
}

bool
bst_addn(bst_t *bst, bsn_t *node)
{
	bsn_t *curr = bst->root, *prev;

	if (curr == NULL) {
		bst->root = node, bst->size = 1;
		return true;
	}

	while (curr != NULL) {
		if (curr->val == node->val)
			return false;

		prev = curr;
		curr = node->val > curr->val ? curr->rgt : curr->lft;
	}

	if (node->val > prev->val)
		prev->rgt = node;
	else
		prev->lft = node;

	bst->size += 1;
	return true;
}

bsn_t *
bst_remn(bst_t *bst, bst_find_t val)
{
	bsn_t *curr = bst->root, *prev;

	while (curr != NULL) {
		if (curr->val == val) {
			if (curr == bst->root && (curr->lft == NULL ||
					curr->rgt == NULL)) {
				/* root, unable to swap from left */
				if (curr->lft == NULL &&
						curr->rgt == NULL)
					bst->root = NULL;
				else if (curr->lft == NULL)
					bst->root = curr->rgt;
				else
					bst->root = curr->lft;
			} else {
				curr = bsn_dest(curr, prev);
			}

			bst->size -= 1;
			return curr;
		}

		prev = curr;
		curr = val > curr->val ? curr->rgt : curr->lft;
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

		curr = val > curr->val ? curr->rgt : curr->lft;
	}

	return NULL;
}

bst_find_t
bst_minn(bst_t *bst)
{
	if (bst->size == 0)
		return LLONG_MAX;

	bsn_t *node = bst->root;
	for (; node->lft != NULL; node = node->lft);
	return node->val;
}

bst_find_t
bst_maxn(bst_t *bst)
{
	if (bst->size == 0)
		return LLONG_MIN;

	bsn_t *node = bst->root;
	for (; node->rgt != NULL; node = node->rgt);
	return node->val;
}
