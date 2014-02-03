#pragma once
#ifndef POINT_GENERATOR_H
#define POINT_GENERATOR_H

#include <list>
#include "Point2F.h"
#include "EDM_Rect.h"
#include "FloatGenerator.h"

namespace EDM { namespace EDM_Graphics { namespace Generators {

	class PointGenerator
	{
	public:
		static list<Point2F> *GeneratePoint2FList(int count, const EDM_Rect &boundEDM_Rect, float border = 0)
		{
			list<Point2F> *points = new list<Point2F>();				

			for (int i = 0; i < count; i++)
			{
				points->push_back(GeneratePoint2F(boundEDM_Rect, border));
			}

			return points;
		}

		static Point2F GeneratePoint2F(const EDM_Rect &boundEDM_Rect, float border = 0)
		{
			float x = FloatGenerator::Generate(boundEDM_Rect.leftBottom.x + border, boundEDM_Rect.rightTop.x - border);
			float y = FloatGenerator::Generate(boundEDM_Rect.leftBottom.y + border, boundEDM_Rect.rightTop.y - border);
			return Point2F(x, y);
		}
	};
	
}}}

#endif