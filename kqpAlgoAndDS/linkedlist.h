#ifndef KQP_LINKEDLIST_H_
#define KQP_LINKEDLIST_H_

#include "basictypes.h"
#include "utilitymacs.h"

#define KQPLnLsDS(TYPE) struct { TYPE key, MemAddr head, MemAddr prev, MemAddr next; }
#define KQPLnLsName(NAME) PasteTokens(NAME, _dll)
#define KQPLnLsHead(NAME, NUM) KQPLnLsName(NAME, NUM).head
#define KQPLnLsKey(NAME, NUM) KQPLnLsName(NAME, NUM).key
#define KQPLnLsNext(NAME, NUM) KQPLnLsName(NAME, NUM).next
#define KQPLnLsPrev(NAME, NUM) KQPLnLsName(NAME, NUM).prev
#define KQPLnLsCreate(TYPE, NAME, KeyExpr, HeadExpr, NextExpr, PrevExpr) KQPLnLsDS(TYPE) KQPLnLsName(NAME) = { .key = (KeyExpr), .head = (HeadExpr), .next = (NextExpr), .prev = (PrevExpr) }

#define KQPLnLsFind(TYPE, NAME, KeyExpr)	\
	for (TYPE *head = KQPLnLsHead(NAME); head && head->key != (KeyExpr); head = head->next)

#define KQPLnLsPrepend(ITEM, NAME, KeyExpr)		\
	do {										\
		ITEM.next = KQPLnLsHead(NAME);			\
		if (KQPLnLsHead(NAME))					\
			KQPLnLsHead(NAME).prev = &ITEM;		\
		KQPLnLsHead(NAME) = &ITEM;				\
	} while (0)

#define KQPLnLsInsert(ITEM1, ITEM2)				\
	do {										\
		ITEM1.next = ITEM2.next;				\
		ITEM1.prev = &ITEM2;					\
		if (ITEM1.next)							\
			ITEM2.next.prev = &ITEM1;			\
		ITEM2.next = &ITEM1;					\
	} while (0)

#define KQPLnLsDelete(NAME, ITEM)				\
	do {										\
		if (ITEM.prev)							\
			ITEM.prev.next = ITEM.next;			\
		else KQPLnLsHead(NAME) = ITEM.next;		\
		if (ITEM.next)							\
			ITEM.next.prev = ITEM.prev;			\
	} while (0)

#endif