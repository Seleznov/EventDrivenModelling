#pragma once
#ifndef POINT2F_H
#define POINT2F_H

#include <iostream>

using namespace std;

namespace EDM { namespace EDM_Graphics 
{
	class Point2F
	{
	public: 
		float x, y;		

		Point2F();
		Point2F(float x, float y);
		int eqf(const Point2F p);
		
		Point2F operator+(const Point2F p)
		{
			return Point2F(x + p.x, y + p.y);
		}

		friend Point2F operator-(const Point2F &p1, const Point2F &p2)
		{
			return Point2F(p1.x - p2.x, p1.y - p2.y);
		}

		Point2F operator*(float val)
		{
			return Point2F(val * x, val * y);
		}

		Point2F operator*(double val)
		{
			return Point2F(val * x, val * y);
		}

		bool operator<(Point2F p)
		{
			return (x + y) < (p.x + p.y);
		}

		int operator==(const Point2F p)
		{
			return (x == p.x) && (y == p.y);
		}
				
		int operator!=(const Point2F p)
		{
			return !(this->operator==(p));
		}

		friend ostream& operator<<(ostream& os, const Point2F &p)
		{
			return os << "(" << p.x << ";" << p.y << ")";
		}

		static struct CompFunctor
		{
			static bool CompareByX(const Point2F &a, const Point2F & b)
			{
				return a.x < b.x;
			}

			static bool CompareByY(const Point2F &a, const Point2F & b)
			{
				return a.y < b.y;
			}
		};
	};

	typedef Point2F CoordT;
	typedef Point2F Vector2fT;
	typedef Vector2fT NormalT;
}}

#endif