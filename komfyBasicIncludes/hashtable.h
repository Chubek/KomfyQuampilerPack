#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include "basictypes.h"
#include "utilitymacs.h"

#define DJB2_MAGIC 33

#define HashTableRows 65536
#define HashTableCols 256

#define HashTableName(NAME) PasteTokens(NAME, _htable)
#define HashTableCreate(TYPE, NAME) TYPE HashTableName(NAME)[HashTableRows][HashTableCols]

#define HashTableHashOuter(MESSAGE, DEST)	\
	do {											\
		U8 chr;										\
		while ((chr = *MESSAGE++))					\
			DEST = (DEST * DJB2_MAGIC) + chr;		\
	} while (0)

#define HashTableHashInner(MESSAGE, DEST)		\
	do {										\
		DEST = (DJB2_MAGIC * MESSAGE) % 256;	\
	} while (0)

#define HashTableHashKeys(OUTER, INNER, KEY)	\
	do {																		\
		U16 hash_outer; U8 hash_inner;
		HashTableHashOuter(KEY, hash_outer);							\
		HashTableHashInner(hash_outer, hash_inner);		\
		INNER = (SizeU)inner_hash;
		OUTER = (SizeU)outer_hash;
	} while (0)

#define HashTableInsert(NAME, KEY, VALUE)	\
	do {																\
		SizeU inner, outer;							\
		HashTableHashKey(outer, inner, KEY);					\
		HashTableName(NAME)[outer][inner] = VALUE;			\
	} while (0)

#define HashTableRetrieve(TYPE_OUTER, TYPE_INNER, KEY, DEST)		\
	do {																\
		SizeU inner, outer;										\
		HashTableHashKey(outer, inner, KEY);					\
		VALUE = HashTableName(NAME)[outer][inner];			\
	} while (0)

#endif