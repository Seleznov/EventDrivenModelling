#pragma once
#ifndef TRIANGACTORSCONTAINER_H
#define TRIANGACTORSCONTAINER_H

#include "Singleton.h"
#include <vector>

namespace EDM { namespace Model
{
	class TriangNode;
}}

namespace EDM { namespace Model
{
	typedef vector<TriangNode> TriangNodesT;
	const double STATIC_POINT_MASSA = 1e10;

	class TriangNodesContainer : public Singleton<TriangNodesContainer>
	{
	protected:
		TriangNodesContainer();
		~TriangNodesContainer();
		friend class Singleton<TriangNodesContainer>;
	public:
		TriangNodesT m_nodes;

		void Sort();
	};
}}

#endif