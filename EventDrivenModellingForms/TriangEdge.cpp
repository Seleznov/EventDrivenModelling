#include "EdgeIndexer.h"
#include "TriangNode.h"
#include "TriangEdge.h"
#include "TriangNodesContainer.h"
#include "Point2F.h"
#include "EDM_Math.h"

using namespace EDM::Logic;
using namespace EDM::Model;

TriangEdge::TriangEdge()
{
	m_begin = -1;
	m_end = -1;
	m_first = -1;
	m_second = -1;
}

TriangEdge::TriangEdge(int begin, int end)
{
	m_begin = begin;
	m_end = end;
	m_first = -1;
	m_second = -1;
}

TriangEdge::TriangEdge(int begin, int end,  int first, int second)
{
	m_begin = begin;
	m_end = end;
	m_first = first;
	m_second = second;
}

TriangEdge::~TriangEdge() { }

bool TriangEdge::CompareByAbs(const TriangEdge &a, const TriangEdge &b)
{
	TriangNodesContainer *nodsInst = TriangNodesContainer::Instance();

	Point2F aBegin = nodsInst->m_nodes[a.m_begin].coord;
	Point2F aEnd = nodsInst->m_nodes[a.m_end].coord;
	Point2F bBegin = nodsInst->m_nodes[b.m_begin].coord;
	Point2F bEnd = nodsInst->m_nodes[b.m_end].coord;

	double absA = EDM_Math::VectorAbs(EDM_Math::GetVector2f(aBegin, aEnd));
	double absB = EDM_Math::VectorAbs(EDM_Math::GetVector2f(bBegin, bEnd));

	nodsInst->FreeInst();
	return absA < absB;
}

void TriangEdge::AddSideNode(int nodeNumber)
{
	if (m_first == -1)
	{
		m_first = nodeNumber;
	}
	else if (m_second == -1)
	{
		m_second = nodeNumber;
	}
	else
	{
		throw std::exception("The edge has had all side numbers.");
	}

}

int TriangEdge::GetOtherSideNode(int sideNodeNumber)
{
	if (sideNodeNumber == m_first)
	{
		return m_second;
	}
	if (sideNodeNumber == m_second)
	{
		return m_first;
	}

	throw std::exception("The edge does not has this side number.");
}

int TriangEdge::GetOtherEdgeNode(int nodeNumber)
{
	if (nodeNumber == m_begin)
	{
		return m_end;
	}
	if (nodeNumber == m_end)
	{
		return m_begin;
	}
	
	throw std::exception("Incorrect node for this edge.");
}

void TriangEdge::ChangeSideNode(int changedNumber, int newSideNodeNumber)
{
	if (changedNumber == m_first)
	{
		m_first = newSideNodeNumber;
		return;
	}
	if (changedNumber == m_second)
	{
		m_second = newSideNodeNumber;
		return;
	}
	throw std::exception("The edge does not has this side number.");
}

void TriangEdge::Change()
{
	int tempBegin = m_begin;
	int tempEnd = m_end;
	m_begin = m_first;
	m_end = m_second;
	m_first = tempBegin;
	m_second = tempEnd;
}