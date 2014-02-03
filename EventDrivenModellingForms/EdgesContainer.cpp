#include "TriangEdge.h"
#include "EdgesContainer.h"
#include "TriangNode.h"
#include "TriangNodesContainer.h"
#include "Point2F.h"
#include "EDM_Math.h"

using namespace EDM::Model;
using namespace EDM::Logic;

EdgesContainer::EdgesContainer() { }

EdgesContainer::~EdgesContainer() { }

void EdgesContainer::AddIfNotExist(TriangEdge &edge)
{
	TriangNodesContainer *nodsInst = TriangNodesContainer::Instance();
	TriangNodesT *nodes = &nodsInst->m_nodes;

	bool isIntersected = false;
	for (size_t edgeIter = 0; edgeIter < m_edges.size(); edgeIter++)
	{
		Point2F p1 = (*nodes)[m_edges[edgeIter].m_begin].coord;
		Point2F p2 = (*nodes)[m_edges[edgeIter].m_end].coord;
		Point2F p3 = (*nodes)[edge.m_begin].coord;
		Point2F p4 = (*nodes)[edge.m_end].coord;

		if (EDM_Math::SegmentsIntersect(p1, p2, p3, p4))
		{
			isIntersected = true;
			break;
		}
	}

	if (!isIntersected)
	{
		m_edges.push_back(edge);
				
		Point2F beginCoord = (*nodes)[edge.m_begin].coord;
		Point2F endCoord = (*nodes)[edge.m_end].coord;

		float beginPolar = atan2(endCoord.y - beginCoord.y, endCoord.x - beginCoord.x);
		float endPolar = atan2(beginCoord.y - endCoord.y, beginCoord.x - endCoord.x);

		(*nodes)[edge.m_begin].m_adjEdges.push_back(EdgeIndexer(m_edges.size() - 1, beginPolar));
		(*nodes)[edge.m_end].m_adjEdges.push_back(EdgeIndexer(m_edges.size() - 1, endPolar));
	}

	nodsInst->FreeInst();
}

int EdgesContainer::FindEdgeBeetwenNodes(int n1, int n2)
{
	TriangNodesContainer *nodsInst = TriangNodesContainer::Instance();
	TriangNodesT *nodes = &nodsInst->m_nodes;

	int edgeIndx;
	for (size_t adjEdgeIter = 0; adjEdgeIter < (*nodes)[n1].m_adjEdges.size(); adjEdgeIter++)
	{
		edgeIndx = (*nodes)[n1].m_adjEdges[adjEdgeIter].number;
		if ((m_edges[edgeIndx].m_begin == n2)
			|| (m_edges[edgeIndx].m_end == n2))
		{
			nodsInst->FreeInst();
			return edgeIndx;
		}
	}

	edgeIndx = -1;
	nodsInst->FreeInst();
	return edgeIndx;
}