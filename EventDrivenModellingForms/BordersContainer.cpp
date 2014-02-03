#include "Global.h"
#include "Border.h"
#include "BordersContainer.h"

using namespace EDM::Model;

BordersContainer::BordersContainer()
{
	this->borders = BordersT(bordersCount);
}

BordersContainer::~BordersContainer()
{
	this->borders.clear();
}