#ifndef GRAPH_H_
#define GRAPH_H_

#include "basictypes.h"
#include "utilitymacs.h"
#include "queue.h"


#define GraphColorWhite 0xff
#define GraphColorGray 0x80
#define GraphColorBlack 0x10
#define GraphDistanceSentinel 0xf24
#define GraphPredecessorSentinel (MemAddr)0xf1442

#define GraphJoint 1
#define GraphDisjoint 0
#define GraphEnds 2

#define GraphNodeDS(VOID) struct { SizeU adjinfo; SizeU weight;  MemAddr nextedge;  }
#define GraphMainDS(SIZE) struct { GraphNodeDS(0) *edges[SIZE + 1]; SizeU outdegrees[SIZE + 1]; SizeU numvertices; SizeU numedges; Bool directed }
#define GraphName(NAME) PasteTokens(NAME, _graph)
#define GraphCreate(NAME, SIZE, NumVertsExpr, NumEdgesExpr, DirectedExpr) GraphMainDS(SIZE) GraphName(NAME) = { .edges = {0}, .outdegrees = {0}, .numedges = (NumEdgesExpr), .numvertices = (NumVertsExpr), .directed = (DirectedExpr) }

#define GraphImplementInsertEdge(NAME, SIZE)
	typedef GraphNodeMainDS(SIZE) PasteTokens(NAME, _gnode_t);
	typedef GraphMainDS(0) PasteTokens(NAME, _gmain_t);
	static inline void PasteTokens(NAME, _insert_edge) (PasteTokens(NAME, _gmain_t) *graph, SizeU idx; U8 adjinfo, Bool directed)
	{
		PasteTokens(NAME, _gnode_t) *edgeptr;
		edgeptr = (PasteTokens(NAME, _gnode_t)*)MemoryAllocate(sizeof(PasteTokens(NAME, _gnode_t)));
		edgeptr->weight = 0;
		edgetpr->adjinfo = adjinfo;
		edgeptr->next = graph->edges[idx];
		graph->edges[idx] = edgeptr;
		graph->degree[idx]++;
	}


#endif