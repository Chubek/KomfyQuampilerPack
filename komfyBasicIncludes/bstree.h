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
#define BsTreeCreate(TYPE, NAME, KeyExpr, LeftExpr, RightExpr) BsTreeDS(TYPE) BsTreeName(NAME) = { .key = (KeyExpr), .root = (MemAddr)0, .parent = (MemAddr)0, .left = (LeftExpr), .right = (RightExpr), }, BsTreeRoot(NAME) = &BsTreeName(NAME)

#define BsTreeInsert(TREE, ITEM)									\
	do {															\
		MemAddr __tmp1 = TREE->root, MemAddr __tmp2 = (MemAddr)0;	\
		while (__tmp1) {											\
			__tmp2 = __tmp1;										\
			if (ITEM->key < __tmp1->key)							\
				__tmp1 = __tmp1->left;								\
			else													\
				__tmp1 = __tmp1->right;								\
		}															\
		ITEM->parent = __tmp2;										\
		if (!__tmp2)												\
			TREE->root = ITEM;										\
		else if (ITEM->key < __tmp2->key)							\
			__tmp2->left = ITEM;									\
		else														\
			__tmp2->right = ITEM;									\
	} while (0)


#define BsTreeImplementInOrderWalkFn(TYPE, NAME, ActionExpr)								\
	static inline void PasteTokens(bstree_walk_inorder_, NAME) (MemAddr node)				\
	{																						\
		if (node) {																			\
			PasteTokens(bstree_walk_inorder_, NAME)(*(node + BsTreeLeftOffset(TYPE)));		\
			do { ActionExpr(node); } while(0);												\
			PasteTokens(bstree_walk_inorder_, NAME)(*(node + BsTreeRightOffset(TYPE)));		\
		}																					\
	}


#define BsTreeIterSearch(TYPE, NAME, KeyExpr, DEST)		\
	do {												\
		BsTreeDS(TYPE) *__tmp = &BsTreeName(NAME);		\
		while (__tmp && __tmp->key != (KeyExpr)) {		\
			if (__tmp->key < (KeyExpr))					\
				__tmp = __tmp->left;					\
			else										\
				__tmp = __tmp->right;					\
		}												\
		DEST = __tmp;									\
	} while (0)


#define BsTreeMinimum(TREE, DEST)	\
	do {							\
		DEST = TREE;				\
		while (DEST->left)			\
			DEST = DEST->left;		\
	} while (0)

#define BsTreeMaximum(TREE, DEST)	\
	do {							\
		DEST = TREE;				\
		while (DEST->right)			\
			DEST = DEST->right;		\
	} while (0)

#define BsTreeTransplant(TREE, ITEM1, ITEM2)	\
	do {										\
		if (!ITEM1->parent)						\
			TREE->root = ITEM1;					\
		else if (ITEM1 == ITEM1->parent.left)	\
			ITEM1->parent.left = ITEM2;			\
		else									\
			ITEM1->parent.right = ITEM2;		\
		if (ITEM2)								\
			ITEM2->parent = ITEM1->parent;		\
	} while (0)


#define BsTreeDelete(TREE, ITEM)								\
	do {														\
		if (!ITEM->left) {										\
			BsTreeTreeTransplant(TREE, ITEM, ITEM->right);		\
		} else if (!ITEM->right) {								\
			BsTreeTreeTransplant(TREE, ITEM, ITEM->left);		\
		} else {												\
			MemAddr __min;										\
			BsTreeMinimum(ITEM->right);							\
			if (__min == ITEM->right) {							\
				BsTreeTransplant(TREE, __min, __min->right);	\
				__min->right = ITEM->right;						\
				__min->right->parent = __min;					\
			}													\
			BsTreeTransplant(TREE, ITEM, __min);				\
			__min->left = ITEM->left;							\
			__min->left.parent = __min;							\
		}														\
	} while (0)

#endif