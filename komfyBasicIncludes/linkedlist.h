#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include "basictypes.h"
#include "utilitymacs.h"

#define LnLsDS(TYPE) struct { TYPE key, MemAddr head, MemAddr prev, MemAddr next; }
#define LnLsName(NAME) PasteTokens(NAME, _dll)
#define LnLsHead(NAME, NUM) LnLsName(NAME, NUM).head
#define LnLsKey(NAME, NUM) LnLsName(NAME, NUM).key
#define LnLsNext(NAME, NUM) LnLsName(NAME, NUM).next
#define LnLsPrev(NAME, NUM) LnLsName(NAME, NUM).prev
#define LnLsCreate(TYPE, NAME, KeyExpr, HeadExpr, NextExpr, PrevExpr) LnLsDS(TYPE) LnLsName(NAME) = { .key = (KeyExpr), .head = (HeadExpr), .next = (NextExpr), .prev = (PrevExpr) }

#define LnLsFind(TYPE, NAME, KeyExpr)	\
	for (TYPE *head = LnLsHead(NAME); head && head->key != (KeyExpr); head = head->next)

#define LnLsPrepend(ITEM, NAME, KeyExpr)		\
	do {										\
		ITEM.next = LnLsHead(NAME);			\
		if (LnLsHead(NAME))					\
			LnLsHead(NAME).prev = &ITEM;		\
		LnLsHead(NAME) = &ITEM;				\
	} while (0)

#define LnLsInsert(ITEM1, ITEM2)				\
	do {										\
		ITEM1.next = ITEM2.next;				\
		ITEM1.prev = &ITEM2;					\
		if (ITEM1.next)							\
			ITEM2.next.prev = &ITEM1;			\
		ITEM2.next = &ITEM1;					\
	} while (0)

#define LnLsDelete(NAME, ITEM)				\
	do {										\
		if (ITEM.prev)							\
			ITEM.prev.next = ITEM.next;			\
		else LnLsHead(NAME) = ITEM.next;		\
		if (ITEM.next)							\
			ITEM.next.prev = ITEM.prev;			\
	} while (0)

#endif