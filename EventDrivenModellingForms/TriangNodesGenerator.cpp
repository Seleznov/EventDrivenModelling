#include "TriangNode.h"
#include "EDM_Rect.h"
#include "Events.h"
#include "NetEventHandler.h"
#include "PointsGenerator.h"
#include "TriangEdge.h"
#include "TriangNodesGenerator.h"
#include "TriangNodesContainer.h"

using namespace EDM::Logic::Generators;
using namespace EDM::EDM_Graphics::Generators;
using namespace EDM::EDM_Graphics;

TriangNodesT *TriangNodesGenerator::GenerateNodes(int count, const EDM_Rect &coordBoundRect, 
	const EDM_Rect &velocityBoundEDM_Rect, double radius)
{
	count += 4;
	TriangNodesT *nodes = new TriangNodesT(count);
	(*nodes)[0] = TriangNode(
		coordBoundRect.leftBottom, 
		Vector2fT(0.0f, 0.0f), radius, DBL_MAX);
	(*nodes)[1] = TriangNode(
		CoordT(coordBoundRect.leftBottom.x, coordBoundRect.rightTop.y), 
		Vector2fT(0.0f, 0.0f), radius, DBL_MAX);
	(*nodes)[2] = TriangNode(
		coordBoundRect.rightTop, 
		Vector2fT(0.0f, 0.0f), radius, DBL_MAX);
	(*nodes)[3] = TriangNode(
		CoordT(coordBoundRect.rightTop.x, coordBoundRect.leftBottom.y),
		Vector2fT(0.0f, 0.0f), radius, DBL_MAX);

	for (int i = 4; i < count; i++)
	{
		CoordT coord = PointGenerator::GeneratePoint2F(coordBoundRect);
		Vector2fT vel = PointGenerator::GeneratePoint2F(velocityBoundEDM_Rect);

		if (radius == -1.0)
		{
			double radius = FloatGenerator::Generate(0.1, 0.9);
			(*nodes)[i] = TriangNode(coord, vel, radius);
		}
		else
		{
			(*nodes)[i] = TriangNode(coord, vel, radius);
		}
	}
	return nodes;
}