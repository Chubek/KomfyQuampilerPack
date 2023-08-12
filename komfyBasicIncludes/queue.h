#ifndef QUEUE_H_
#define QUEUE_H_

#include "basictypes.h"
#include "utilitymacs.h"

#define QueueDS(TYPE, SIZE) struct { TYPE data[SIZE]; U64 head; U64 tail;  }
#define QueueName(NAME) PasteTokens(NAME, _queue)
#define QueueHead(NAME) QueueName(NAME).head
#define QueueTail(NAME) QueueName(NAME).tail
#define QueueCreate(TYPE, SIZE, NAME) QueueDS(TYPE, SIZE) QueueName(NAME) = {0}
#define QueueSize(NAME) sizeof(QueueName(NAME))
#define QueueLen(NAME, TYPE) (((QueueSize(NAME)) - (sizeof(U64) << 1)) / sizeof(TYPE))
#define QueueIsOverflown(NAME) (QueueTail(NAME) == QueueLen(NAME) - 1)
#define QueueIsUnderflown(NAME) (QueueHead(NAME) == QueueTail(NAME))
#define QueueIsEmpty(NAME) (QueueHead(NAME) == QueueTail(NAME))

#define QueueEnqueue(NAME, ValueExpr)									\
		do {															\
			if (QueueIsOverflown(NAME)) {							\
				ErrorFMT(ERR_QUEUE_OVERFLOW, NAME);						\
			} else {													\
				QueueName(NAME).data[QueueTail(NAME)] = (ValueExpr);	\
				if (QueueTail(NAME) == QueueLen(NAME)) 			\
					QueueTail(NAME) == 1;							\
				else QueueTail(NAME)++;								\
			}															\
		} while (0)

#define QueueDequeue(NAME, DestExpr)										\
		do {															\
			if (QueueIsUndeflown(NAME)) {							\
				ErrorFMT(ERR_QUEUE_UNDER, NAME);						\
			} else {													\
				DestExpr = QueueName(NAME).data[QueueTail(NAME)];		\
				if (QueueHead(NAME) == QueueLen(NAME)) 			\
					QueueHead(NAME) == 1;							\
				else QueueHead(NAME)++;								\
			}															\
		} while (0)

#endif