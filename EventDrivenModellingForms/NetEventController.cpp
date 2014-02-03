#include "Actor.h"
#include "ActorsContainer.h"
#include "Cell.h"
#include "CellsContainer.h"
#include "Border.h"
#include "BordersContainer.h"
#include "Events.h"
#include "PriorityQueue.h"
#include "NetEventHandler.h"
#include "EDM_Math.h"
#include "NetEventController.h"
#include "Global.h"
#include "Properties.h"

using namespace EDM;
using namespace EDM::Logic;

void NetEventController::FindStartTimesForActors()
{
	for (int actCntr = 0; actCntr < EDM_Prop->ActorsCount; actCntr++)
	{
		FindNearestEventForActor(actCntr);
	}
}

void NetEventController::FindNearestEventForActor(int actorInd)
{
	ActorsContainer *acInst = ActorsContainer::Instance();	
	EventArgs *cellBoundArgs = ArgsInCollisionWithCellBound(actorInd);
	EventArgs *borderInCellArgs = ArgsInCollisionWithBoundInCell(actorInd);
	EventArgs *actorArgs = ArgsInCollisionWithActor(actorInd);

	double tMin = min(cellBoundArgs->time, min(borderInCellArgs->time, actorArgs->time));	
	if (tMin == cellBoundArgs->time)
		// next event is collision with cell bound
	{
		SetNewEvent(actorInd, *cellBoundArgs, NetEventHandler::delCollisionWithCellBorder);
	}
	else if (tMin == borderInCellArgs->time)
		// next event is collision with border in cell
	{
		SetNewEvent(actorInd, *borderInCellArgs, NetEventHandler::delCollisionWithBorderInCell);
	}
	else 
		// next event is collision with actor
	{
		SetNewEvent(actorInd, *actorArgs, NetEventHandler::delCollisionWithActor);
		EventArgs *partnerArgs = PartnerArgsInActorsCollisionEvent(actorInd);
		int partnerInd = acInst->actors[actorInd].evnt->args->next;
		SetNewEvent(partnerInd, *partnerArgs, NetEventHandler::delCollisionWithActor);
	}
	
	acInst->FreeInst();
}

void NetEventController::SetNewEvent(int actorInd, EventArgs &args, DelegateT *del)
{
	ActorsContainer *acInst = ActorsContainer::Instance();
	EventT *evnt = new EventT(actorInd, args, del);
	acInst->actors[actorInd].SetEvent(evnt);

	if (PriorityQueue::IsExist())
	{
		PriorityQueue *queueInst = PriorityQueue::Instance();
		queueInst->ChangeHeapTree(actorInd);
		queueInst->FreeInst();
	}

	acInst->FreeInst();
}

EventArgs* NetEventController::PartnerArgsInActorsCollisionEvent(int actorInd)
{
	ActorsContainer *acInst = ActorsContainer::Instance();
	Actor *crntAct = &acInst->actors[actorInd]; 
	Actor *partnerAct = &acInst->actors[crntAct->evnt->args->next];

	EventArgs *partnerArgs = new EventArgs(
		crntAct->evnt->args->time, 
		partnerAct->evnt->args->localTime,
		crntAct->evnt->sender);

	acInst->FreeInst();
	return partnerArgs;
}

EventArgs* NetEventController::ArgsInCollisionWithCellBound(int actorInd)
{
	ActorsContainer *acInst = ActorsContainer::Instance();
	Actor *crntAct = &acInst->actors[actorInd];

	double tRight = DBL_MAX; double tLeft = DBL_MAX; double tTop = DBL_MAX; double tBottom = DBL_MAX;
	//////////////////////////////////////////////////////////////////////////
	//ÎØÈÁÊÀ Ñ ÎÒÐÈÖÀÒÅËÜÍÛÌ ÂÐÅÌÅÍÅÌ!!!
	//////////////////////////////////////////////////////////////////////////
	if (crntAct->vel.x > 0)
	{
		double xBoundCoord = (crntAct->cell_x + 1);
		tRight = crntAct->evnt->args->localTime + (xBoundCoord - crntAct->localCoord.x) / crntAct->vel.x;
	}
	else if (crntAct->vel.x < 0)
	{
		double xBoundCoord = crntAct->cell_x;
		tLeft = crntAct->evnt->args->localTime + (xBoundCoord - crntAct->localCoord.x) / crntAct->vel.x;
	}
	if (crntAct->vel.y > 0)
	{
		double yBoundCoord = (crntAct->cell_y + 1) ;
		tTop = crntAct->evnt->args->localTime + (yBoundCoord - crntAct->localCoord.y) / crntAct->vel.y;
	}
	else if (crntAct->vel.y < 0)
	{
		double yBoundCoord = (crntAct->cell_y);
		tBottom = crntAct->evnt->args->localTime + (yBoundCoord - crntAct->localCoord.y) / crntAct->vel.y;
	}

	double tMin = min(min(tLeft, tRight), min(tBottom, tTop));
	int minBordInd = -1;

	if (tMin == tLeft)
		minBordInd = 1;
	else if (tMin == tRight)
		minBordInd = 2;
	else if (tMin == tBottom)
		minBordInd = 3;
	else
		minBordInd = 4;

	EventArgs *args = new EventArgs(tMin, crntAct->evnt->args->localTime, minBordInd);
	acInst->FreeInst();
	return args;	
}

EventArgs* NetEventController::ArgsInCollisionWithBoundInCell(int actorInd)
{
	ActorsContainer *acInst = ActorsContainer::Instance();
	CellContainer *ccInst = CellContainer::Instance();
	BordersContainer *bcInst = BordersContainer::Instance();

	Actor *crntAct = &acInst->actors[actorInd];
	Cell *crntCell = &ccInst->grid[crntAct->cell_y][crntAct->cell_x];

	double tMin = DBL_MAX;
	int minBordInd = -1;

	for (unsigned int bordCntr = 0; bordCntr < crntCell->borders.size(); bordCntr++)
	{
		int bordInd = crntCell->borders[bordCntr];
		Border *crntBord = &bcInst->borders[bordInd];
		double P = EDM_Math::ScalarProduct(crntAct->vel, crntBord->normal);
		if (P < 0)
		{
			double B = (crntAct->localCoord.x - crntBord->start.x) * crntBord->normal.x + 
				(crntAct->localCoord.y - crntBord->start.y) * crntBord->normal.y;
			//////////////////////////////////////////////////////////////////////////
			//ÓÒÎ×ÍÈÒÜ
			double timeToCollision = crntAct->evnt->args->localTime - B / P;

			Point2F intrsctPnt = crntAct->localCoord + crntAct->vel * timeToCollision;

			double scalarProduct = (intrsctPnt.x - crntBord->start.x) * (intrsctPnt.x - crntBord->finish.x) + 
				(intrsctPnt.y - crntBord->start.y) * (intrsctPnt.y - crntBord->finish.y);

			if ((scalarProduct < 0) && (timeToCollision < tMin))
			{
				tMin = timeToCollision;
				minBordInd = bordCntr;
			}
		}
	}

	EventArgs *args = new EventArgs(tMin, crntAct->evnt->args->time, minBordInd);

	bcInst->FreeInst();
	ccInst->FreeInst();
	acInst->FreeInst();	
	return args;
}

EventArgs* NetEventController::ArgsInCollisionWithActor(int actorInd)
{
	ActorsContainer *acInst = ActorsContainer::Instance();
	Actor *crntAct = &acInst->actors[actorInd]; 

	int xMin = -1; 
	int xMax = -1; 
	int yMin = -1; 
	int yMax = -1; 
	FindNeighbourCells(crntAct, xMin, xMax, yMin, yMax);
	
	double tMin = DBL_MAX;
	int minNghbrActInd = -1;

	CheckNeighbourCells(actorInd, xMin, xMax, yMin, yMax, tMin, minNghbrActInd);

	EventArgs *args = new EventArgs(tMin, crntAct->evnt->args->localTime, minNghbrActInd);

	acInst->FreeInst();
	return args;
}

void NetEventController::FindNeighbourCells(const Actor *actor, int &xMin, int &xMax, int &yMin, int &yMax)
{
	xMin = actor->cell_x - 1; 
	xMax = actor->cell_x + 1;
	if (xMin < 1)
		xMin = 1;
	if (xMax > EDM_Prop->xCellsCount)
		xMax = EDM_Prop->xCellsCount;

	yMin = actor->cell_y - 1; 
	yMax = actor->cell_y + 1;
	if (yMin < 1)
		yMin = 1;
	if (yMax > EDM_Prop->yCellsCount)
		yMax = EDM_Prop->yCellsCount;
}

void NetEventController::CheckNeighbourCells(int actorInd, int &iMin, int &iMax, int &jMin, 
											int &jMax, double & tMin, int &minNghbrActInd)
{
	CellContainer *ccInst = CellContainer::Instance();

	for (unsigned short jCntr = jMin; jCntr <= jMax; jCntr++)
	{
		for (unsigned short iCntr = iMin; iCntr <= iMax; iCntr++)
		{
			int actorsInNghbrCellCount = ccInst->grid[jCntr][iCntr].actors.size();
			if (actorsInNghbrCellCount > 0)
			{
				CheckActorsInCell(ccInst->grid[jCntr][iCntr], actorInd, tMin, minNghbrActInd);
			}
		}
	}

	ccInst->FreeInst();
}

void NetEventController::CheckActorsInCell(const Cell &cell, int actorInd, double &tMin, int &minNghbrActInd)
{
	for (unsigned short actCntr = 0; actCntr < cell.actors.size(); actCntr++)
	{
		int nghbrActInd = cell.actors[actCntr];
		if (actorInd != nghbrActInd)
		{
			double timeToCollision = TimeToCollisionBwActors(actorInd, nghbrActInd);
			if (timeToCollision < tMin)
			{
				tMin = timeToCollision;
				minNghbrActInd = nghbrActInd;
			}
		}
	}
}

double NetEventController::TimeToCollisionBwActors(int firstInd, int secondInd)
{
	ActorsContainer *acInst = ActorsContainer::Instance();
	Actor *first, *second;
	if (acInst->actors[firstInd].evnt->args->localTime >= acInst->actors[secondInd].evnt->args->localTime)
	{
		first = &acInst->actors[firstInd];
		second = &acInst->actors[secondInd];
	}
	else
	{
		first = &acInst->actors[secondInd];
		second = &acInst->actors[firstInd];
	}

	//////////////////////////////////////////////////////////////////////////
	//íîðìàëèçîâàòü ê åäèíîìó ëîêàëüíîìó âðåìåíè
	Point2F dv = first->vel - second->vel;
	CoordT r20_ = EDM_Math::ri0_(
		second->localCoord, first->evnt->args->localTime, 
		second->evnt->args->localTime, second->vel);
	Point2F dr = first->localCoord - r20_;

	double L = first->radius + second->radius;
	double A = EDM_Math::ScalarProduct(dv, dv);
	double B = -EDM_Math::ScalarProduct(dr, dv);
	double C = EDM_Math::ScalarProduct(dr, dr) - L * L;
	//////////////////////////////////////////////////////////////////////////
	if (C < 0)
		C = 0.00001;
	double discrim = EDM_Math::Discrim(B, A, C);

	if ((discrim > 0) && (B > sqrt(discrim)))
	{
		double dt = EDM_Math::dt(B, discrim, A);
		double time = first->evnt->args->localTime + dt;
		if (time <= second->evnt->args->time)
		{
			acInst->FreeInst();
			return time;
		}
	}

	acInst->FreeInst();
	return DBL_MAX;
}