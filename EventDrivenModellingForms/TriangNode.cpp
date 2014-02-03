#include "EdgeIndexer.h"
#include "TriangEdge.h"
#include "TriangNode.h"
#include "TriangNodesContainer.h"
#include "EdgesContainer.h"
#include <algorithm>

using namespace std;
using namespace EDM::Model;

TriangNode::TriangNode() : Node()
{
	//m_neighbours = new list<Node*>();
}

TriangNode::TriangNode(CoordT _coord, Vector2fT _vel, double _radius)
	: Node(_coord, _vel, _radius)
{
	//m_neighbours = new list<Node*>();
}

TriangNode::TriangNode(CoordT _coord, Vector2fT _vel, double _radius, double _massa)
	: Node(_coord, _vel, _radius, _massa)
{
	//m_neighbours = new list<Node*>();
}

TriangNode::TriangNode(CoordT _coord, Vector2fT _vel, double _radius, EventT *_evnt, double _massa)
	: Node(_coord, _vel, _radius, _evnt, _massa)
{
	//m_neighbours = new list<Node*>();
}

TriangNode::~TriangNode()
{
	//delete m_neighbours;
}

void TriangNode::SortAdjEdges()
{
	sort(m_adjEdges.begin(), m_adjEdges.end(), EdgeIndexer::CompareByPolar);
}

void TriangNode::FindOppositeEdges(size_t nodeIndx)
{

	EdgesContainer *edgsInst = EdgesContainer::Instance();

	int crntEdgeIndx, nextEdgeIndx, crntAdjNodeIndx, nextAdjNodeIndx; 
	for (size_t adjEdgeIter = 0; adjEdgeIter < m_adjEdges.size() - 1; adjEdgeIter++)
	{
		crntEdgeIndx = m_adjEdges[adjEdgeIter].number;
		nextEdgeIndx = m_adjEdges[adjEdgeIter + 1].number;
		
		FindAdjNodesIndxs(nodeIndx, crntEdgeIndx, nextEdgeIndx, crntAdjNodeIndx, nextAdjNodeIndx, edgsInst->m_edges);

		int oppEdgeIndx = edgsInst->FindEdgeBeetwenNodes(crntAdjNodeIndx, nextAdjNodeIndx);
		if (oppEdgeIndx != -1)
		{
			m_oppositeEdges.push_back(oppEdgeIndx);
			edgsInst->m_edges[oppEdgeIndx].AddSideNode(nodeIndx);
		}
	}
	
	if (m_adjEdges.size() > 2)
	{
		crntEdgeIndx = m_adjEdges[m_adjEdges.size() - 1].number;
		nextEdgeIndx = m_adjEdges[0].number;
		FindAdjNodesIndxs(nodeIndx, crntEdgeIndx, nextEdgeIndx, crntAdjNodeIndx, nextAdjNodeIndx, edgsInst->m_edges);
		int oppEdgeIndx = edgsInst->FindEdgeBeetwenNodes(crntAdjNodeIndx, nextAdjNodeIndx);
		if (oppEdgeIndx != -1)
		{
			m_oppositeEdges.push_back(oppEdgeIndx);
			edgsInst->m_edges[oppEdgeIndx].AddSideNode(nodeIndx);
		}
	}
	edgsInst->FreeInst();
}

void TriangNode::FindAdjNodesIndxs(int nodeIndx, int crntEdgeIndx, int nextEdgeIndx, 
	int &crntAdjNodeIndx, int &nextAdjNodeIndx, EdgesT &edges)
{
	if (edges[crntEdgeIndx].m_begin == nodeIndx)
	{
		crntAdjNodeIndx = edges[crntEdgeIndx].m_end;
	}
	else
	{
		crntAdjNodeIndx = edges[crntEdgeIndx].m_begin;
	}

	if (edges[nextEdgeIndx].m_begin == nodeIndx)
	{
		nextAdjNodeIndx = edges[nextEdgeIndx].m_end;
	}
	else
	{
		nextAdjNodeIndx = edges[nextEdgeIndx].m_begin;
	}
}

void TriangNode::AddAdjEdge(int edgeInd)
{
	m_adjEdges.push_back(EdgeIndexer(edgeInd, DBL_MAX));
}

void TriangNode::AddOppositeEdge(int edgeInd)
{
	m_oppositeEdges.push_back(edgeInd);
}

void TriangNode::RemoveOppositeEdge(int edgeInd)
{
	vector<int>::iterator oppEdgeIt = find(m_oppositeEdges.begin(), m_oppositeEdges.end(), edgeInd);
	swap((*oppEdgeIt), (m_oppositeEdges)[m_oppositeEdges.size() - 1]);
	m_oppositeEdges.pop_back();
}

void TriangNode::RemoveAdjEdge(int edgeInd)
{
	vector<EdgeIndexer>::iterator adjEdgeIt = find(m_adjEdges.begin(), m_adjEdges.end(), edgeInd);
	swap((*adjEdgeIt), (m_adjEdges)[m_adjEdges.size() - 1]);
	m_adjEdges.pop_back();
}

bool TriangNode::operator==(const TriangNode obj)
{
	return Node::operator==(obj);
}

bool TriangNode::operator!=(const TriangNode obj)
{
	return !(this->operator==(obj));
}