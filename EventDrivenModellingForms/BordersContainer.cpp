#include "Properties.h"
#include "Border.h"
#include "BordersContainer.h"

using namespace EDM::Model;

BordersContainer::BordersContainer()
{
	this->borders = BordersT(EDM_Prop->BordersCount);
}

BordersContainer::~BordersContainer()
{
	this->borders.clear();
}