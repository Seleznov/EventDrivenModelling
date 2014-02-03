#pragma once
#ifndef EDGE_H
#define EDGE_H

#include <vector>
using namespace std;

namespace EDM { namespace Model
{
	class TriangEdge;

	//typedef Edge* EdgesT;

	class Triangle
	{

	public:
		vector<TriangEdge*> m_edges;

		Triangle();
		Triangle(TriangEdge *first, TriangEdge *second, TriangEdge *third);
		~Triangle();
	};
}}

#endif