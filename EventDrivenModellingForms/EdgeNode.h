//The structure of node of double connected edge list

#pragma  once
#ifndef EDGENODE_H
#define EDGENODE_H

#include <vector>
using namespace std;

namespace EDM { 
	namespace EDM_Graphics
	{
		class Point2F;
	}
	namespace Model 
	{ 
		class TriangNode;
	}
}

using namespace EDM::EDM_Graphics;
using namespace EDM::Model;

namespace EDM { namespace Logic
{
	class DCEL;
	enum Direction { CW, CCW }; // clockwise, counterclockwise 

	class EdgeNode
	{
	public:
		Point2F *vBegin;
		Point2F *vEnd;
		TriangNode *fLeft;
		TriangNode *fRight;
		EdgeNode *p1;
		EdgeNode *p2;
		bool checkingFlag;

		EdgeNode();
		EdgeNode(Point2F &_vBegin, Point2F &_vEnd, TriangNode &_fLeft, TriangNode &_fRight);
		EdgeNode(Point2F &_vBegin, Point2F &_vEnd, TriangNode &_fLeft, TriangNode &_fRight, EdgeNode &_p1, EdgeNode &_p2);
		~EdgeNode();

		bool operator==(const EdgeNode& edge);
		bool operator!=(const EdgeNode& edge);

		TriangNode *GetOtherSideFace(TriangNode &face);
		EdgeNode *Next(TriangNode &face, Direction direct);
		bool IsLeftFromSplitLine(DCEL &splitLine);
	};
}}

#endif

