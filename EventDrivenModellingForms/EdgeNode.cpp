#include "Point2F.h"
#include "TriangNode.h"
#include "EdgeNode.h"
#include "DCEL.h"
#include "EDM_Math.h"

using namespace EDM::Logic;

EdgeNode::EdgeNode()
{
	vBegin = nullptr;
	vEnd = nullptr;
	fLeft = nullptr;
	fRight = nullptr;
	p1 = nullptr;
	p2 = nullptr;
	checkingFlag = false;
}

EdgeNode::EdgeNode(Point2F &_vBegin, Point2F &_vEnd, TriangNode &_fLeft, TriangNode &_fRight)
{	
	vBegin = &_vBegin;
	vEnd = &_vEnd;
	fLeft = &_fLeft;
	fRight = &_fRight;
	p1 = nullptr;
	p2 = nullptr;
	checkingFlag = false;
}

EdgeNode::EdgeNode(Point2F &_vBegin, Point2F &_vEnd, TriangNode &_fLeft, TriangNode &_fRight, EdgeNode &_p1, EdgeNode &_p2)
{	
	vBegin = &_vBegin;
	vEnd = &_vEnd;
	fLeft = &_fLeft;
	fRight = &_fRight;
	p1 = &_p1;
	p2 = &_p2;
	checkingFlag = false;
}

EdgeNode::~EdgeNode()
{
	//delete p1, p2;
	//delete vBegin, vEnd, fLeft, fRight;
}

bool EdgeNode::operator==(const EdgeNode &edge)
{
	return *vBegin == *(edge.vBegin) && *vEnd == *(edge.vEnd) && *fLeft == *(edge.fLeft) && *fRight == *(edge.fRight);
}

bool EdgeNode::operator!=(const EdgeNode &edge)
{
	return !(*this == edge);
}

TriangNode *EdgeNode::GetOtherSideFace(TriangNode &face)
{
	if (face == *fLeft)
	{
		return fRight;
	}
	return fLeft;
}

EdgeNode *EdgeNode::Next(TriangNode &face, Direction direct)
{
	if (face == *fLeft)
	{
		if (direct == Direction::CW)
		{
			return p1;
		}
		if (p2 == nullptr)
		{
			return nullptr;
		}
		if (*vEnd == *(p2->vBegin))
		{
			return p2->p1;
		}
		return p2->p2;
	}
	else
	{
		if (direct == Direction::CW)
		{
			return p2;
		}
		if (p2 == nullptr)
		{
			return nullptr;
		}
		if (p1 == nullptr)
		{
			return p2;
		}
		if (*vBegin == *(p1->vEnd))
		{
			return p1->p2;
		}
		return p1->p1;
	}
}

bool EdgeNode::IsLeftFromSplitLine(DCEL &splitLine)
{
	DCEL_EdgesT::iterator splitEdgeIter = splitLine.edges.begin();
	while(splitEdgeIter != splitLine.edges.end())
	{
		if (!EDM_Math::IsLeftPoint(*(*splitEdgeIter)->vBegin, *(*splitEdgeIter)->vEnd, *vBegin)
			&& !EDM_Math::IsLeftPoint(*(*splitEdgeIter)->vBegin, *(*splitEdgeIter)->vEnd, *vEnd))
		{
			return false;
		}
		splitEdgeIter++;
	}
	return true;
}