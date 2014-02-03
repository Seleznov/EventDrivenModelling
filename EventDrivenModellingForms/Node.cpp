#include "Events.h"
#include "Node.h"
//#include "ActorsContainer.h"
#include "Cell.h"
//#include "CellsContainer.h"
#include "Properties.h"

using namespace EDM::Model;

Node::Node()
{
	this->coord = CoordT(0.0f, 0.0f);
	this->localCoord = this->coord;
	this->vel = Vector2fT(0.0f, 0.0f);
	this->radius = 0.0;
	this->evnt = new EventT();
	//this->cell_x = FindXCellIndex(coord.x);
	//this->cell_y = FindYCellIndex(coord.y);
	this->massa = 1.0;
}

Node::Node(CoordT _coord, Vector2fT _vel, double _radius)
{
	this->coord = _coord;
	this->localCoord = this->coord;
	this->vel = _vel;
	this->radius = _radius;
	this->evnt = new EventT();
	//this->cell_x = FindXCellIndex(coord.x);
	//this->cell_y = FindYCellIndex(coord.y);
	this->massa = 1.0;
}

Node::Node(CoordT _coord, Vector2fT _vel, double _radius, double _massa)
{
	this->coord = _coord;
	this->localCoord = this->coord;
	this->vel = _vel;
	this->radius = _radius;
	this->evnt = new EventT();
	this->massa = _massa;
}

Node::Node(CoordT _coord, Vector2fT _vel, double _radius, EventT *_evnt, double _massa)
{
	this->coord = _coord;
	this->localCoord = this->coord;
	this->vel = _vel;
	this->radius = _radius;
	this->evnt = _evnt;
	//this->cell_x = FindXCellIndex(coord.x);
	//this->cell_y = FindYCellIndex(coord.y);
	this->massa = _massa;
}

Node::~Node()
{
	//delete evnt;
}

void Node::SetEvent(EventT *_evnt)
{
	delete this->evnt;
	this->evnt = _evnt;
}

bool Node::operator==(const Node obj)
{
	return (coord == obj.coord) && (radius == obj.radius) && (vel == obj.vel) 
		&& (evnt->args->time == obj.evnt->args->time);
}

void Node::Move()
{
	localCoord = localCoord + vel * (evnt->args->time - evnt->args->localTime);		
	evnt->args->localTime = evnt->args->time;
}

void Node::Move(double time)
{
	localCoord = localCoord + vel * (time - evnt->args->localTime);		
	evnt->args->localTime = time;
}
