#include "Actor.h"
#include "Cell.h"
#include "CellsContainer.h"

///werfhekjsdhgfklusdhlkgljkfdlgj

using namespace EDM::Model;

Actor::Actor() : Node()
{
	this->cell_x = FindXCellIndex(coord.x);
	this->cell_y = FindYCellIndex(coord.y);
}

Actor::Actor(CoordT _coord, Vector2fT _vel, double _radius) 
	: Node(_coord, _vel, _radius)
{
	this->cell_x = FindXCellIndex(coord.x);
	this->cell_y = FindYCellIndex(coord.y);
}

Actor::Actor(CoordT _coord, Vector2fT _vel, double _radius, double _massa)
	: Node(_coord, _vel, _radius, _massa)
{
	this->cell_x = FindXCellIndex(coord.x);
	this->cell_y = FindYCellIndex(coord.y);
}

Actor::Actor(CoordT _coord, Vector2fT _vel, double _radius, EventT *_evnt, double _massa)
	: Node(_coord, _vel, _radius, _evnt, _massa)
{
	this->cell_x = FindXCellIndex(coord.x);
	this->cell_y = FindYCellIndex(coord.y);
}

Actor::~Actor()
{ }

void Actor::AddActorInCell(int actorInd)
{
	CellContainer *ccInst = CellContainer::Instance();
	
	ccInst->grid[cell_y][cell_x].actors.push_back(actorInd);

	ccInst->FreeInst();
}

//void Actor::Move()
//{
//	localCoord = localCoord + vel * (evnt->args->time - evnt->args->localTime);		
//	//localCoord = coord;
//	evnt->args->localTime = evnt->args->time;
//}
