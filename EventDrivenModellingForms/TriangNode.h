#pragma once
#ifndef TRIANGACTOR_H
#define TRIANGACTOR_H

#include <list>
#include <vector>
#include "Node.h"
#include "EdgeIndexer.h"

namespace EDM { namespace Model
{
	class EdgeIndexer;
	class TriangEdge;
	typedef vector<TriangEdge> EdgesT;

	class TriangNode: public Node
	{
	public:
		vector<EdgeIndexer> m_adjEdges;
		vector<int> m_oppositeEdges;

		TriangNode();
		TriangNode(CoordT _coordT, Vector2fT _vel, double _radius);
		TriangNode(CoordT _coordT, Vector2fT _vel, double _radius, double _massa);
		TriangNode(CoordT _coordT, Vector2fT _vel, double _radius, EventT *_evnt, double _massa = 1.0);
		~TriangNode();

		void SortAdjEdges();
		void FindOppositeEdges(size_t nodeIndx);
		void FindAdjNodesIndxs(int nodeIndx, int crntEdgeIndx, int nextEdgeIndx, 
			int &crntAdjNodeIndx, int &nextAdjNodeIndx, EdgesT &edges);
		

		void AddOppositeEdge(int edgeInd);
		void AddAdjEdge(int edgeInd);
		void RemoveOppositeEdge(int edgeInd);
		void RemoveAdjEdge(int edgeInd);

		bool operator==(const TriangNode obj);
		bool operator!=(const TriangNode obj);

		static bool CompareByAscendingX(const TriangNode &a, const TriangNode & b)
		{
			return a.coord.x < b.coord.x;
		}
	};
}}

#endif