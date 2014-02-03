#pragma once
#ifndef EDM_RECT_H
#define EDM_RECT_H

#include "Point2F.h"

namespace EDM { namespace EDM_Graphics { 

	class EDM_Rect
	{		
	public:
		Point2F leftBottom;
		Point2F rightTop;

		EDM_Rect() {}

		EDM_Rect(Point2F inLeftBottom, Point2F inRightTop)
		{
			leftBottom = inLeftBottom;
			rightTop = inRightTop;
		}

		EDM_Rect(float inLeft, float inBottom, float inRight, float inTop)
			:	leftBottom(inLeft, inBottom),
				rightTop(inRight, inTop)
		{}
	};
}}

#endif