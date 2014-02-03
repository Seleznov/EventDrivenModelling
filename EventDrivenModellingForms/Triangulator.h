#pragma once
#ifndef TRIANGULATOR_H
#define TRIANGULATOR_H

namespace EDM { namespace Model
{
	class TriangEdge;
	typedef vector<TriangEdge> EdgesT;
}}

using namespace EDM::Model;

namespace EDM { namespace Logic 
{
	class Triangulator
	{
	public:
		static void Triangulate(size_t nodeCount);

	private:
		static EdgesT GetAllEdges(size_t nodeCount);
		static void BuildTriangEdges(EdgesT &allEdges);
		static void BuildBorderEdges();
		static void SortAdjEdgesOfNodes();
		static void FindOppositeEdgesForNodes();
	};
}}

#endif