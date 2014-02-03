#pragma once
#ifndef EDGESCONTAINER_H
#define EDGESCONTAINER_H

#include "Singleton.h"
#include <vector>

using namespace std;

namespace EDM { namespace Model
{
	class TriangEdge;
	typedef vector<TriangEdge> EdgesT;

	class EdgesContainer : public Singleton<EdgesContainer>
	{
	protected:
		EdgesContainer();
		~EdgesContainer();
		friend class Singleton<EdgesContainer>;
	public:
		EdgesT m_edges;

		void AddIfNotExist(TriangEdge &edge);
		int FindEdgeBeetwenNodes(int n1, int n2);
	};
}}

#endif