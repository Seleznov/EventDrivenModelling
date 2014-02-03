#pragma once
#ifndef BORDER_H
#define BORDER_H

#include "Point2F.h"
#include "EDM_Math.h"

namespace EDM { namespace EDM_Graphics {
	class Point2F;
}}

using namespace std;
using namespace EDM::EDM_Graphics;
using namespace EDM::Logic;

namespace EDM { namespace Model {

	struct Border {

		CoordT start, finish;
		NormalT normal;

		Border() {}

		Border(CoordT _start, CoordT _finish)
		{
			start = _start;
			finish = _finish;
			normal = EDM_Math::Normal(start, finish);
		}
	};
}}

#endif