#ifndef KQP_QUEUE_H_
#define KQP_QUEUE_H_

#include "basictypes.h"
#include "utilitymacs.h"

#define KQPQueueDS(TYPE, SIZE) struct { TYPE data[SIZE]; U64 head; U64 tail;  }
#define KQPQueueName(NAME) PasteTokens(NAME, _queue)
#define KQPQueueHead(NAME) KQPQueueName(NAME).head
#define KQPQueueTail(NAME) KQPQueueName(NAME).tail
#define KQPQueueCreate(TYPE, SIZE, NAME) KQPQueueDS(TYPE, SIZE) KQPQueueName(NAME) = {0}
#define KQPQueueSize(NAME) sizeof(KQPQueueName(NAME))
#define KQPQueueLen(NAME, TYPE) (((KQPQueueSize(NAME)) - (sizeof(U64) << 1)) / sizeof(TYPE))
#define KQPQueueIsOverflown(NAME) (KQPQueueTail(NAME) == KQPQueueLen(NAME) - 1)
#define KQPQueueIsUnderflown(NAME) (KQPQueueHead(NAME) == KQPQueueTail(NAME))

#define KQPQueueEnqueue(NAME, VALUE)									\
		do {															\
			if (KQPQueueIsOverflown(NAME)) {							\
				ErrorFMT(ERR_QUEUE_OVERFLOW, NAME);						\
			} else {													\
				KQPQueueName(NAME).data[KQPQueueTail(NAME)] = VALUE;	\
				if (KQPQueueTail(NAME) == KQPQueueLen(NAME)) 			\
					KQPQueueTail(NAME) == 1;							\
				else KQPQueueTail(NAME)++;								\
			}															\
		} while (0)

#define KQPQueueDequeue(NAME, DEST)										\
		do {															\
			if (KQPQueueIsUndeflown(NAME)) {							\
				ErrorFMT(ERR_QUEUE_UNDER, NAME);						\
			} else {													\
				DEST = KQPQueueName(NAME).data[KQPQueueTail(NAME)];		\
				if (KQPQueueHead(NAME) == KQPQueueLen(NAME)) 			\
					KQPQueueHead(NAME) == 1;							\
				else KQPQueueHead(NAME)++;								\
			}															\
		} while (0)

#endif