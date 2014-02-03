#pragma once
#ifndef TRIAGEDGE_H
#define TRIAGEDGE_H

#include <vector>
using namespace std;

namespace EDM { namespace Model
{
	class TriangNode;
	class Triangle;

	typedef TriangNode NodeT;
	//typedef TriangActor* NodesT;
	//typedef Triangle* AdjTrianglesT;

	class TriangEdge 
	{
	public:
		int m_begin; 
		int m_end;
		int m_first; 
		int m_second;

		TriangEdge();
		TriangEdge(int begin, int end);
		TriangEdge(int begin, int end,  int first, int second);
		~TriangEdge();

		void AddSideNode(int nodeNumber);
		int GetOtherSideNode(int sideNodeNumber);
		int GetOtherEdgeNode(int nodeNumber);
		void ChangeSideNode(int changedNumber, int newSideNodeNumber);
		void Change();

		static bool CompareByAbs(const TriangEdge &a, const TriangEdge &b);
	};
}}

#endif