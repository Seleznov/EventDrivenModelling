#pragma once
#ifndef TRIANGNODES_GENERATOR_H
#define TRIANGNODES_GENERATOR_H

#include <vector>

namespace EDM {
	namespace Model 
	{ 
		class TriangNode;
	}
	namespace EDM_Graphics { 
		class EDM_Rect;
	}
}

using namespace std;
using namespace EDM::EDM_Graphics;
using namespace EDM::Model;

namespace EDM { namespace Logic { namespace Generators {

	typedef vector<TriangNode> ActorsT;

	class TriangNodesGenerator
	{
	public:
		static ActorsT *GenerateNodes(int count, const EDM_Rect &coordBoundRect, 
			const EDM_Rect &velocityBoundEDM_Rect, double radius = -1.0);
	};
}}}

#endif