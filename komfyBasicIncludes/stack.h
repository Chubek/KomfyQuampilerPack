#ifndef STACK_H_
#define STACK_H_

#include "basictypes.h"
#include "utilitymacs.h"

#define StackDS(TYPE, SIZE) struct { TYPE data[SIZE]; U64 top;  }
#define StackName(NAME) PasteTokens(NAME, _stack)
#define StackCreate(TYPE, SIZE, NAME) StackDS(TYPE, SIZE) StackName(NAME) = {0}
#define StackSize(NAME) sizeof(StackName(NAME))
#define StackLen(NAME, TYPE) (((StackSize(NAME)) - sizeof(U64)) / sizeof(TYPE))
#define StackTop(NAME) StackName(NAME).top
#define StackAtBottom(NAME) (StackTop(NAME) == StackLen(NAME) - 1)
#define StackAtTop(NAME) (StackTop(NAME) == 0)

#define StackPush(NAME, VALUE)								\
	do {														\
		if (StackAtBottom(NAME)) {							\
			ErrorFMT(ERR_STACK_OVERFLOW, ToString(NAME));		\
		}														\
		StackName(NAME).data[StackTop(NAME)++] = VALUE;	\
	} while (0)

#define StackPop(NAME, DEST)									\
	do {														\
		if (StackAtTop(NAME)) {								\
			ErrorFMT(ERR_STACK_UNDERFLOW, ToString(NAME));		\
		}														\
		DEST = StackName(NAME).data[--StackTop(NAME)];	\
	} while (0)


#endif