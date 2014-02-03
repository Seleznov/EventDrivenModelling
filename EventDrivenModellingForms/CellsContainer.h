#pragma once
#ifndef CELLCONTAINER_H
#define CELLCONTAINER_H

#include "Singleton.h"

namespace EDM { namespace Model 
{
	struct Cell;

	typedef vector< vector<Cell> > GridT;

	class CellContainer : public Singleton<CellContainer>
	{
	protected:
		CellContainer();
		~CellContainer();
		friend class Singleton<CellContainer>;
	public:
		void UpdateIndices(int actorInd, int newCell_i, int newCell_j);
		GridT grid;
	};
}}

#endif