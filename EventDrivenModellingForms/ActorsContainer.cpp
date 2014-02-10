#include "Actor.h"
#include "ActorsGenerator.h"
#include "EDM_Rect.h"
#include "ActorsContainer.h"
#include "Properties.h"

using namespace EDM::Logic::Generators;

ActorsContainer::ActorsContainer()
{
	EDM_Rect coordBoundRect = EDM_Rect(1.0f, 1.0f, EDM_Prop->xCellsCount + 1, EDM_Prop->yCellsCount + 1);
	EDM_Rect velocityBoundEDM_Rect = EDM_Rect(-EDM_Prop->SpeedKoef, -EDM_Prop->SpeedKoef, EDM_Prop->SpeedKoef, EDM_Prop->SpeedKoef);
	actors = *ActorsGenerator::GenerateActors(EDM_Prop->ActorsCount, coordBoundRect, velocityBoundEDM_Rect, EDM_Prop->ActorsRadius);

	/*Actor *a1 = new Actor(CoordT(2.0f, 2.0f), Vector2fT(EDM_Prop->SpeedKoef, -EDM_Prop->SpeedKoef), EDM_Prop->ActorsRadius);
	Actor *a2 = new Actor(CoordT(3.0f, 2.0f), Vector2fT(-EDM_Prop->SpeedKoef, -EDM_Prop->SpeedKoef), EDM_Prop->ActorsRadius);
	actors.push_back(*a1);
	actors.push_back(*a2);*/

	/*Actor *a0 = new Actor(CoordT(1.0f, 1.0f), Vector2fT(0.0f, 0.0f), EDM_Prop->ActorsRadius, 1e10);
	Actor *a1 = new Actor(CoordT(10.0f, 1.0f), Vector2fT(0.0f, 0.0f), EDM_Prop->ActorsRadius, 1e10);
	Actor *a2 = new Actor(CoordT(10.0f, 10.0f), Vector2fT(0.0f, 0.0f), EDM_Prop->ActorsRadius, 1e10);
	Actor *a3 = new Actor(CoordT(1.0f, 10.0f), Vector2fT(0.0f, 0.0f), EDM_Prop->ActorsRadius, 1e10);
	Actor *a4 = new Actor(CoordT(3, 3), Vector2fT(EDM_Prop->SpeedKoef, -EDM_Prop->SpeedKoef), EDM_Prop->ActorsRadius);
	Actor *a5 = new Actor(CoordT(4, 3), Vector2fT(-EDM_Prop->SpeedKoef, -EDM_Prop->SpeedKoef), EDM_Prop->ActorsRadius);

	actors.push_back(*a0);
	actors.push_back(*a1);
	actors.push_back(*a2);
	actors.push_back(*a3);
	actors.push_back(*a4);
	actors.push_back(*a5);*/

	AddActorsInCells();
}

ActorsContainer::~ActorsContainer()
{ 
	this->actors.clear(); 
}

void ActorsContainer::AddActorsInCells()
{
	for (int actCnrt = 0; actCnrt < EDM_Prop->ActorsCount; actCnrt++)
	{
		this->actors[actCnrt].AddActorInCell(actCnrt);
	}
}