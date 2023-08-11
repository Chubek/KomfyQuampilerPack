#ifndef BSTREE_H_
#define BSTREE_H_

#include "basictypes.h"
#include "utilitymacs.h"

#define BsTreeDS(TYPE) struct { TYPE key; const MemAddr root; MemAddr parent; MemAddr left; MemAddr right;  }
#define BsTreeName(NAME) PasteTokens(NAME, _bstree)
#define BsTreeKey(NAME) BsTreeName(NAME).key
#define BsTreeRoot(NAME) BsTreeName(NAME).root
#define BsTreeParent(NAME) BsTreeName(NAME).parent
#define BsTreeLeft(NAME) BsTreeName(NAME).left
#define BsTreeRight(NAME) BsTreeName(NAME).right
#define BsTreeKeyOffset(TYPE) 0
#define BsTreeRootOffset(TYPE) (sizeof(TYPE))
#define BsTreeParentOffset(TYPE) (sizeof(TYPE) + sizeof(MemAddr))
#define BsTreeLeftOffset(TYPE) (sizeof(TYPE) + (sizeof(MemAddr) * 2))
#define BsTreeRightOffset(TYPE) (sizeof(TYPE) + (sizeof(MemAddr) * 3))
#define BsTreeCreate(TYPE, NAME, KeyExpr) BsTreeDS(TYPE) BsTreeName(NAME) = { .key = (KeyExpr), .root = (MemAddr)0, .parent = (MemAddr)0, .left = (MemAddr)0, .right = (MemAddr)0, }, BsTreeRoot(NAME) = &BsTreeName(NAME)

#define BsTreeInsert(TYPE, NAME, ITEM)
	do {
		MemAddr __root = BsTreeRoot(NAME), MemAddr __tmp;
		while (__root) {
			__tmp = __root;
			if (ITEM->key < *(__root + BsTreeKeyOffset(TYPE)))
				__root = *(__root + BsTreeLeftOffset(TYPE));
			else
				__root = *(__root + BsTreeRightOffset(TYPE));
		}
		ITEM.parent = __tmp;
		if (!__tmp)
			BsTreeRoot(NAME) = &ITEM;
		else if (ITEM->key < *(__tmp + BsTreeKeyOffset(TYPE)))
			*(__tmp + BsTreeLeftOffset(TYPE)) = &ITEM;
		else 
			*(__tmp + BsTreeRightOffset(TYPE)) = &ITEM;
	} while (0)


#define BsTreeImplementInOrderWalkFn(TYPE, NAME, ActionExpr)
	static inline void PasteTokens(bstree_walk_inorder_, NAME) (MemAddr node)
	{
		if (node) {
			PasteTokens(bstree_walk_inorder_, NAME)(*(node + BsTreeLeftOffset(TYPE)));
			do { ActionExpr(node); } while(0);
			PasteTokens(bstree_walk_inorder_, NAME)(*(node + BsTreeRightOffset(TYPE)));
		}
	}

#define BsTreeImplementSearchFn(TYPE, NAME, ActionExpr)
	static inline TYPE PasteTokens(bstree_search_, NAME) (MemAddr node, TYPE key)
	{
		TYPE nodekey = (TYPE)(*(node + BsTreeKeyOffset(TYPE)));
		if (!node || nodekey == key)
			do { ActionExpr(node); } while (0);
		else if (nodeky < key)
			PasteTokens(bstree_search_, NAME) (*(node + BsTreeLeftOffset(TYPE)), key);
	}

#define BsTreeMinimum(TYPE, NAME, DEST)
	do {
		DEST = &BsTreeName(NAME);
		while (DEST->left)
			DEST = DEST->left;
	} while (0)

#define BsTreeMaximum(TYPE, NAME, DEST)
	do {
		DEST = &BsTreeName(NAME);
		while (DEST->right)
			DEST = DEST->right;
	} while (0)




#endif