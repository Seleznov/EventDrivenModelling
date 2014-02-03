#include "Actor.h"
#include "ActorsContainer.h"
#include "Cell.h"
#include "CellsContainer.h"

#include <algorithm>

using namespace EDM::Model;

CellContainer::CellContainer()
{
	Properties ^prop = Properties::Instance;
	this->grid = GridT(prop->ActualYCellsCount);
	GridT::iterator cIter = grid.begin();
	while (cIter != grid.end())
	{
		*cIter = vector<Cell>(EDM_Prop->ActualXCellsCount);
		cIter++;
	}
}

CellContainer::~CellContainer()
{
	this->grid.clear();
}

void CellContainer::UpdateIndices(int actorInd, int newCell_i, int newCell_j)
{
	ActorsContainer *acInst = ActorsContainer::Instance();
	Actor *crntAct = &acInst->actors[actorInd];
	vector<int> *actVect = &this->grid[crntAct->cell_y][crntAct->cell_x].actors;

	vector<int>::iterator it = find((*actVect).begin(), (*actVect).end(), actorInd);
	swap((*it), (*actVect)[actVect->size() - 1]);
	actVect->pop_back();

	this->grid[newCell_j][newCell_i].actors.push_back(actorInd);
	crntAct->cell_x = newCell_i;
	crntAct->cell_y = newCell_j;

	acInst->FreeInst();
}