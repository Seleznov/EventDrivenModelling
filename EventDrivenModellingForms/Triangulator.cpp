#include "EdgeIndexer.h"
#include "TriangNode.h"
#include "TriangNodesContainer.h"
#include "TriangEdge.h"
#include "EdgesContainer.h"
#include "Triangle.h"
#include "Triangulation.h"
#include "Triangulator.h"
#include "Point2F.h"
#include "EDM_Math.h"

#include <algorithm>
using namespace std;

using namespace EDM::Model;
using namespace EDM::Logic;

void Triangulator::Triangulate(size_t nodeCount)
{
	EdgesT allEdges = GetAllEdges(nodeCount);
	BuildTriangEdges(allEdges);
	SortAdjEdgesOfNodes();
	FindOppositeEdgesForNodes();
}

EdgesT Triangulator::GetAllEdges(size_t nodeCount)
{
	vector<TriangEdge> *allEdges = new vector<TriangEdge>();
	allEdges->reserve(nodeCount * nodeCount - nodeCount);
	for (size_t frstNodeIter = 0; frstNodeIter <nodeCount; frstNodeIter++)
	{
		for (size_t scndNodeIter = 0; scndNodeIter < nodeCount; scndNodeIter++)
		{
			if (frstNodeIter != scndNodeIter)
			{
				allEdges->push_back(TriangEdge(frstNodeIter, scndNodeIter));
			}			
		}
	}
	sort(allEdges->begin(), allEdges->end(), TriangEdge::CompareByAbs);
	return *allEdges;
}

void Triangulator::BuildTriangEdges(EdgesT &allEdges)
{
	EdgesContainer *edgsInst = EdgesContainer::Instance();

	BuildBorderEdges();
	for (size_t allEdgeIter = 0; allEdgeIter < allEdges.size(); allEdgeIter++)
	{
		edgsInst->AddIfNotExist(allEdges[allEdgeIter]);
	}

	edgsInst->FreeInst();
}

void Triangulator::BuildBorderEdges()
{
	EdgesContainer *edgsInst = EdgesContainer::Instance();

	TriangEdge *e0 = new TriangEdge(0, 1);
	TriangEdge *e1 = new TriangEdge(1, 2);
	TriangEdge *e2 = new TriangEdge(2, 3);
	TriangEdge *e3 = new TriangEdge(3, 0);
	edgsInst->AddIfNotExist(*e0);
	edgsInst->AddIfNotExist(*e1);
	edgsInst->AddIfNotExist(*e2);
	edgsInst->AddIfNotExist(*e3);

	edgsInst->FreeInst();
}

void Triangulator::SortAdjEdgesOfNodes()
{
	TriangNodesContainer *nodsInst = TriangNodesContainer::Instance();
	TriangNodesT *nodes = &nodsInst->m_nodes;

	for (size_t nodeIter = 0; nodeIter < nodes->size(); nodeIter++)
	{
		(*nodes)[nodeIter].SortAdjEdges();
	}

	nodsInst->FreeInst();
}

void Triangulator::FindOppositeEdgesForNodes()
{
	TriangNodesContainer *nodsInst = TriangNodesContainer::Instance();
	TriangNodesT *nodes = &nodsInst->m_nodes;

	for (size_t nodeIter = 0; nodeIter < nodes->size(); nodeIter++)
	{
		(*nodes)[nodeIter].FindOppositeEdges(nodeIter);
	}

	nodsInst->FreeInst();
}