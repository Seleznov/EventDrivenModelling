#pragma once
#ifndef CELL_H
#define CELL_H

#include <vector>
#include "Properties.h"

using namespace std;
using namespace EDM;

namespace EDM { namespace Model {

	struct Cell {
		vector<int> actors;
		vector<int> borders;

		Cell()
		{
			actors.reserve(EDM_Prop->ActorsInCell);
			borders.reserve(EDM_Prop->BordersInCell);
		}
	};

}}

#endif