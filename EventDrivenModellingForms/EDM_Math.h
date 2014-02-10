#pragma once
#ifndef EDM_MATH_H
#define EDM_MATH_H

#include "Events.h"
#include "Properties.h"

#include <iostream>
#include <sstream>
#include <iomanip>
#include <float.h>
#include <math.h>
#include <limits>

using namespace std;
using namespace EDM;
using namespace EDM::Model;

namespace EDM { namespace EDM_Graphics {
	class Point2F;
}}

using namespace EDM::EDM_Graphics;

//////////////////////////////////////////////////////////////////////////
// TODO: Change double to float
//////////////////////////////////////////////////////////////////////////

namespace EDM { namespace Logic {

	static const float INF = numeric_limits<float>::infinity();
	static const float NaNf = numeric_limits<float>::quiet_NaN();
	
	enum RelativePosition { Parallel, Perpendicular, Collinear, Intersect };
	enum SegmentBorder { Segment, Interval };

	class EDM_Math
	{
	public:
		inline static bool eqf(float val1, float val2);
		inline static bool eqd(double val1, double val2);
		inline static float Round (float x, int precision);
		inline static double angleCos(Point2F a, Point2F b);
		inline static double VectorAbs(Point2F vect);
		inline static double VectorSquare(Point2F vect);
		inline static double ScalarProduct(Point2F v1, Point2F v2);
		inline static Point2F GetVector2f(Point2F p1, Point2F p2);
		inline static double Discrim(double B, double A, double C);
		inline static Point2F ri0_(Point2F ri0, double t10, double ti0, Point2F vi);
		inline static double dt(double B, double Disctim, double A);
		inline static NormalT Normal(Point2F a, Point2F b);

		inline static RelativePosition RelativePositionBetweenTwoLines(Point2F &a1, Point2F &b1, Point2F &a2, Point2F &b2);
		inline static Point2F IntersectPointBetweenTwoLine(Point2F &a1, Point2F &a2, Point2F &b1, Point2F &b2);
		inline static Point2F CenterPointBetweenTwoPoints(Point2F &a, Point2F &b);
		inline static bool IsLeftPoint(Point2F &a, Point2F &b, Point2F &p);
		inline static bool IsPointLowerThenLine(Point2F &l1, Point2F &l2, Point2F &p);
		inline static bool IsPointBelongToSegment(Point2F &a, Point2F &b, Point2F &p, SegmentBorder borderType);
		inline static bool IntersectPointBwTwoSegments(Point2F &a1, Point2F &b1, Point2F &a2, Point2F &b2, Point2F &intersect);
		inline static Point2F IntersectPointBwPerpendicFromPointAndLine(Point2F &a, Point2F &b, Point2F &point);
		inline static float DistanceBetweenPointAndLine(Point2F a, Point2F b, Point2F point);

		inline static int det(int a, int b, int c, int d);
		inline static bool SegmentsIntersect(Point2F &p1, Point2F &p2, Point2F &p3, Point2F &p4);
		inline static float Direct(Point2F &pi, Point2F &pj, Point2F &pk);

		// Is point pk belongs to segment pipj, when pk is not equal to pi or pj.
		inline static bool OnSegment(Point2F &pi, Point2F &pj, Point2F &pk);

		// Is point pk belongs to segment pipj, when pk is equal to pi or pj.
		inline static bool OnSegmentEq(Point2F &pi, Point2F &pj, Point2F &pk);
	};

#pragma region Implements

	bool EDM_Math::eqf(float val1, float val2)
	{
		float res = abs(val1 - val2);
		if (res < EDM_Prop->Eps)
		{
			return true;
		}
		return false;
	}

	bool EDM_Math::eqd(double val1, double val2)
	{
		double res = abs(val1 - val2);
		if (res < EDM_Prop->Eps)
		{
			return true;
		}
		return false;
	}

	 int EDM_Math::det(int a, int b, int c, int d) {
		return a * d - b * c;
	}

	float EDM_Math::Round(float x, int precision)
	{
		stringstream s;
		s << setprecision(precision) <<  x;
		s >> x;
		return x;
	}

	double EDM_Math::angleCos(Point2F a, Point2F b)
	{
		return EDM_Math::ScalarProduct(a, b) / (EDM_Math::VectorAbs(a) * EDM_Math::VectorAbs(b));
	}

	double EDM_Math::VectorAbs(Point2F vect)
	{
		return sqrt(vect.x * vect.x + vect.y * vect.y);
	}

	double EDM_Math::VectorSquare(Point2F vect)
	{
		return VectorAbs(vect) * VectorAbs(vect);
	}

	double EDM_Math::ScalarProduct(Point2F dr, Point2F dv)
	{
		return dr.x * dv.x + dr.y * dv.y;
	}

	Point2F EDM_Math::GetVector2f(Point2F p1, Point2F p2)
	{
		return Point2F(p2.x - p1.x, p2.y - p1.y);
	}

	double EDM_Math::Discrim(double B, double A, double C)
	{
		double b_2 = B*B;
		double ac = A*C;
		return b_2 - ac;
	}

	Point2F EDM_Math::ri0_(Point2F ri0, double t10, double ti0, Point2F vi)
	{
		return ri0 + vi * (t10 - ti0);
	}

	double EDM_Math::dt(double B, double Disctim, double A)
	{
		return (B - sqrt(Disctim)) / A;
	}

	NormalT EDM_Math::Normal(Point2F a, Point2F b)
	{
		return Point2F(a.y - b.y, b.x - a.x);
	}

	RelativePosition EDM_Math::RelativePositionBetweenTwoLines(Point2F &a1, Point2F &b1, Point2F &a2, Point2F &b2)
	{
		float k1 = (b1.y - a1.y) / (b1.x - a1.x);
		float free1 = (a1.x * (a1.y - b1.y) / (b1.x - a1.x)) + a1.y;

		float k2 = (b2.y - a2.y) / (b2.x - a2.x);
		float free2 = (a2.x * (a2.y - b2.y) / (b2.x - a2.x)) + a2.y;


		if (((k1 == INF) && (k2 == -INF))
			|| ((k1 == -INF) && (k2 == INF))
			|| ((k1 == INF) && (k2 == INF))
			|| ((k1 == -INF) && (k2 == -INF)))
		{
			if (a1.x == a2.x)
			{
				return RelativePosition::Collinear;
			}
			else
			{
				return RelativePosition::Parallel;
			}
		}
		else
		{
			if (k1 == k2)
			{
				if (free1 == free2)
				{
					return RelativePosition::Collinear;
				}
				return RelativePosition::Parallel;
			}
			return RelativePosition::Intersect;
		}
	}

	Point2F EDM_Math::IntersectPointBetweenTwoLine(Point2F &a1, Point2F &b1, Point2F &a2, Point2F &b2)
	{
		float A1 = a1.y - b1.y;
		float B1 = b1.x - a1.x;
		float C1 = a1.x * b1.y - b1.x * a1.y;

		float A2 = a2.y - b2.y;
		float B2 = b2.x - a2.x;
		float C2 = a2.x * b2.y - b2.x * a2.y;

		// Kramer rule
		float x = -(C1 * B2 - C2 * B1) / (A1 * B2 - A2 * B1);
		float y =  -(A1 * C2 - A2 * C1) / (A1 * B2 - A2 * B1);

		return Point2F(x, y);
	}

	Point2F EDM_Math::CenterPointBetweenTwoPoints(Point2F &a, Point2F &b)
	{
		float x = (a.x + b.x) / 2;
		float y = (a.y + b.y) / 2;
		return Point2F(x,y);
	}

	bool EDM_Math::IsLeftPoint(Point2F &a, Point2F &b, Point2F &p)
	{
		Point2F vect1 = GetVector2f(a, b);
		Point2F vect2 = GetVector2f(a, p);
		if((vect1.x * vect2.y - vect1.y * vect2.x) > 0)
			return true;
		return false;
	}

	bool EDM_Math::IsPointLowerThenLine(Point2F &l1, Point2F &l2, Point2F &p)
	{
		float k = (l2.y - l1.y) / (l2.x - l1.x);
		float b = l1.y - k * l1.x;
		float fx = k * p.x + b ;
		if (fx > p.y)
		{
			return true;
		}
		return false;
	}

	bool EDM_Math::IsPointBelongToSegment(Point2F &a, Point2F &b, Point2F &p, SegmentBorder borderType)
	{
		Point2F apVect(p.x - a.x, p.y - a.y);
		Point2F abVect(b.x - a.x, b.y - a.y);

		/*if ((p == a) || (p == b))
		{
		return false;
		}*/

		bool isCollinear = false;

		if (((a.y == b.y) && (b.y == p.y))
			|| ((a.x == b.x) && (b.x == p.x)))
		{
			isCollinear = true;
		}

		float round1 = apVect.x / abVect.x;// 5;
		float round2 = apVect.y / abVect.y;// 5;
		if (EDM_Math::eqf(round1, round2))
		{
			isCollinear = true;
		}

		if (isCollinear) // if apVect is collinear to abVect			
		{			
			if (borderType == SegmentBorder::Interval)
			{
				if ((p.eqf(a)) || (p.eqf(b)))
				{
					return false;
				}
				float roundPX = p.x;//Round(p.x, 6);
				float roundPY = p.y;//Round(p.y, 6);
				if (((a.x < roundPX && roundPX < b.x) // point.x belong to (a.x ; b.x) or
					|| (b.x < roundPX && roundPX < a.x)) // point.x belong to (b.x ; a.x)
					&& ((a.y < roundPY && roundPY < b.y) // point.x belong to (a.x ; b.x) or
					|| (b.y < roundPY && roundPY < a.y))) // point.x belong to (b.x ; a.x)
					return true;
			}
			if (borderType == SegmentBorder::Segment)
			{
				if (((a.x <= p.x && p.x <= b.x) // point.x belong to [a.x ; b.x] or
						|| (b.x <= p.x && p.x <= a.x)) // point.x belong to [b.x ; a.x]
					&& ((a.y <= p.y && p.y <= b.y) // point.y belong to [a.y ; b.y] or
						|| (b.y <= p.y && p.y <= a.y))) // point.y belong to [b.y ; a.y]
					return true;
			}
		}

		return false;
	}

	bool EDM_Math::IntersectPointBwTwoSegments(Point2F &a1, Point2F &b1, Point2F &a2, Point2F &b2, Point2F &intersect)
	{
		RelativePosition rp = RelativePositionBetweenTwoLines(a1, b1, a2, b2);

		if (rp == RelativePosition::Intersect)
		{
			intersect = EDM_Math::IntersectPointBetweenTwoLine(a1, b1, a2, b2);

			if (IsPointBelongToSegment(a1, b1, intersect, SegmentBorder::Interval) &&
				IsPointBelongToSegment(a2, b2, intersect, SegmentBorder::Interval))
			{
				return true;
			}
		}

		if (rp == RelativePosition::Collinear)
		{
			if ((IsPointBelongToSegment(a1, b1, a2, SegmentBorder::Segment) // if one segment locate in another
					&& IsPointBelongToSegment(a1, b1, b2, SegmentBorder::Segment))
				|| (IsPointBelongToSegment(a2, b2, a1, SegmentBorder::Segment) 
					&& 	IsPointBelongToSegment(a2, b2, b1, SegmentBorder::Segment)))
			{
				return true;
			}
		}

		return false;
	}

	bool EDM_Math::SegmentsIntersect(Point2F &p1, Point2F &p2, Point2F &p3, Point2F &p4)
	{
		if ((p1 == p3) && (p2 == p4)
			|| (p1 == p4) && (p2 == p3))
		{
			return true;
		}

		float d1 = Direct(p3, p4, p1);
		float d2 = Direct(p3, p4, p2);
		float d3 = Direct(p1, p2, p3);
		float d4 = Direct(p1, p2, p4);

		if ( (((d1 > 0) && (d2 < 0)) || ((d1 < 0) && (d2 > 0))) 
			&& (((d3 > 0) && (d4 < 0)) || ((d3 < 0) && (d4 > 0))) )
		{
			return true;
		}
		else if ((d1 == 0) && OnSegment(p3, p4, p1))
		{
			return true;
		}
		else if ((d2 == 0) && OnSegment(p3, p4, p2))
		{
			return true;
		}
		else if ((d3 == 0) && OnSegment(p1, p2, p3))
		{
			return true;
		}
		else if ((d4 == 0) && OnSegment(p1, p2, p4))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

#pragma endregion

	float EDM_Math::Direct(Point2F &pi, Point2F &pj, Point2F &pk)
	{
		return (pk.x - pi.x) * (pj.y - pi.y) - (pj.x - pi.x) * (pk.y - pi.y);
	}

	bool EDM_Math::OnSegment(Point2F &pi, Point2F &pj, Point2F &pk)
	{
		if ( ((min(pi.x, pj.x) < pk.x) && (pk.x < max(pi.x, pj.x)) )
			&& ((min(pi.y, pj.y) < pk.y) && (pk.y < max(pi.y, pj.y))) )
		{
			return true;
		}
		return false;
	}

	bool EDM_Math::OnSegmentEq(Point2F &pi, Point2F &pj, Point2F &pk)
	{
		if ( ((min(pi.x, pj.x) <= pk.x) && (pk.x <= max(pi.x, pj.x)) )
			&& ((min(pi.y, pj.y) <= pk.y) && (pk.y <= max(pi.y, pj.y))) )
		{
			return true;
		}
		return false;
	}

 	Point2F EDM_Math::IntersectPointBwPerpendicFromPointAndLine(Point2F& a, Point2F& b, Point2F& point)
 	{
 		Point2F normal = EDM_Math::Normal(a, b);
 		Point2F secondPoint(point.x + normal.x, point.y + normal.y);
 		Point2F intersectPoint = EDM_Math::IntersectPointBetweenTwoLine(a, b, point, secondPoint);
 		return intersectPoint;
 	}

	float EDM_Math::DistanceBetweenPointAndLine(Point2F a, Point2F b, Point2F point)
	{
		Point2F intersectPoint = EDM_Math::IntersectPointBwPerpendicFromPointAndLine(a, b, point);
		float dist = EDM_Math::VectorAbs(EDM_Math::GetVector2f(point, intersectPoint));
		return dist;
	}
}}

#endif