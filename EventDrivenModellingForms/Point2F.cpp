#include "Point2F.h"
#include "EDM_Math.h"

using namespace EDM::Logic;
using namespace EDM::EDM_Graphics;

Point2F::Point2F()
{
	x = 0;
	y = 0;
}

Point2F::Point2F(float x, float y)
{
	this->x = x;
	this->y = y;
}

int Point2F::eqf(const Point2F p)
{
	return EDM_Math::eqf(x, p.x) && EDM_Math::eqf(y, p.y);
}