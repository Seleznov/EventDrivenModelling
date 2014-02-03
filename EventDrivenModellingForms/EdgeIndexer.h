#pragma once
#ifndef EDGEINDEXER_H
#define EDGEINDEXER_H

namespace EDM { namespace Model 
{
	class EdgeIndexer
	{
	public:
		int number;
		double polar;

		EdgeIndexer(int _number, double _polar)
			: number(_number), polar(_polar) 
		{ }

		static bool CompareByPolar(const EdgeIndexer &a, const EdgeIndexer &b)
		{
			return a.polar < b.polar;
		}

		bool operator==(const int _number)
		{
			return number == _number;
		}
	};
}}

#endif