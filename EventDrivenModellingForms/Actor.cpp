//#include "Events.h"
#include "Actor.h"
//#include "ActorsContainer.h"
#include "Cell.h"
#include "CellsContainer.h"

using namespace EDM::Model;

Actor::Actor() : Node()
{
	/*this->coord = CoordT(0.0f, 0.0f);
	this->localCoord = this->coord;
	this->vel = Vector2fT(0.0f, 0.0f);
	this->radius = 0.0;
	this->evnt = new EventT();*/
	this->cell_x = FindXCellIndex(coord.x);
	this->cell_y = FindYCellIndex(coord.y);
	//this->massa = 1.0;
}

Actor::Actor(CoordT _coord, Vector2fT _vel, double _radius) 
	: Node(_coord, _vel, _radius)
{
	/*this->coord = _coord;
	this->localCoord = this->coord;
	this->vel = _vel;
	this->radius = _radius;
	this->evnt = new EventT();*/
	this->cell_x = FindXCellIndex(coord.x);
	this->cell_y = FindYCellIndex(coord.y);
	//this->massa = 1.0;
}

Actor::Actor(CoordT _coord, Vector2fT _vel, double _radius, double _massa)
	: Node(_coord, _vel, _radius, _massa)
{
	/*this->coord = _coord;
	this->localCoord = this->coord;
	this->vel = _vel;
	this->radius = _radius;
	this->evnt = _evnt;*/
	this->cell_x = FindXCellIndex(coord.x);
	this->cell_y = FindYCellIndex(coord.y);
	//this->massa = _massa;
}

Actor::Actor(CoordT _coord, Vector2fT _vel, double _radius, EventT *_evnt, double _massa)
	: Node(_coord, _vel, _radius, _evnt, _massa)
{
	/*this->coord = _coord;
	this->localCoord = this->coord;
	this->vel = _vel;
	this->radius = _radius;
	this->evnt = _evnt;*/
	this->cell_x = FindXCellIndex(coord.x);
	this->cell_y = FindYCellIndex(coord.y);
	//this->massa = _massa;
}

Actor::~Actor()
{ }

//void Actor::SetEvent(EventT *_evnt)
//{
//	delete this->evnt;
//	this->evnt = _evnt;
//}
//
//bool Actor::operator==(const Actor obj)
//{
//	return (coord == obj.coord) && (radius == obj.radius) && (vel == obj.vel) 
//		&& (evnt->args->time == obj.evnt->args->time);
//}

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
