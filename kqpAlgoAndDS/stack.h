#ifndef KQP_STACK_H_
#define KQP_STACK_H_

#include "basictypes.h"
#include "utilitymacs.h"

#define KQPStackDS(TYPE, SIZE) struct { TYPE data[SIZE]; U64 top;  }
#define KQPStackName(NAME) PASTE(NAME, _stack)
#define KQPStackCreate(TYPE, SIZE, NAME) KQPStackDS(TYPE, SIZE) KQPStackName(NAME) = {0}
#define KQPStackSize(NAME, TYPE) ((sizeof(KQPStackName(NAME)) - sizeof(U64)) / sizeof(TYPE))
#define KQPStackTop(NAME) KQPStackName(NAME).top
#define KQPStackAtBottom(NAME) (KQPStackTop(NAME) == KQPStackSize(NAME))
#define KQPStackAtTop(NAME) (KQPStackTop(NAME) == 0)

#define KQPStackPush(NAME, VALUE)								\
	do {														\
		if (KQPStackAtBottom(NAME)) {							\
			ErrorFMT(ERR_STACK_OVERFLOW, ToString(NAME));		\
		}														\
		KQPStackName(NAME).data[KQPStackTop(NAME)++] = VALUE;	\
	} while (0)

#define KQPStackPop(NAME, DEST)									\
	do {														\
		if (KQPStackAtTo(NAME)) {								\
			ErrorFMT(ERR_STACK_UNDERFLOW, ToString(NAME));		\
		}														\
		DEST = KQPStackName(NAME).data[--KQPStackTop(NAME)];	\
	} while (0)


#endif