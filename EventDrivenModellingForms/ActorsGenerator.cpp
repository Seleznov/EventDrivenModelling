//#include "Global.h"
#include "Actor.h"
#include "EDM_Rect.h"
#include "Events.h"
#include "NetEventHandler.h"
#include "PointsGenerator.h"
#include "ActorsGenerator.h"

using namespace EDM::Logic::Generators;
using namespace EDM::EDM_Graphics::Generators;

ActorsT *ActorsGenerator::GenerateActors(int count, const EDM_Rect &coordBoundRect, 
	const EDM_Rect &velocityBoundEDM_Rect, double radius)
{
	ActorsT *actors = new ActorsT(count);
	for (int i = 0; i < count; i++)
	{
		CoordT coord = PointGenerator::GeneratePoint2F(coordBoundRect);
		Vector2fT vel = PointGenerator::GeneratePoint2F(velocityBoundEDM_Rect);

		if (radius == -1.0)
		{
			double radius = FloatGenerator::Generate(0.1, 0.9);
			(*actors)[i] = Actor(coord, vel, radius);
		}
		else
		{
			(*actors)[i] = Actor(coord, vel, radius);
		}
	}
	return actors;
}