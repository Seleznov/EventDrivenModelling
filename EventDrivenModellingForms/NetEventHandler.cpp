#include "Actor.h"
#include "ActorsContainer.h"
#include "Border.h"
#include "BordersContainer.h"
#include "Cell.h"
#include "CellsContainer.h"
#include "Events.h"
#include "NetEventController.h"
#include "PriorityQueue.h"
#include "EDM_Math.h"
#include "NetEventHandler.h"
#include "FloatGenerator.h"

//////////////////////////////////////////////////////////////////////////
//TODO: ADD ENUM TYPE FOR BORDERS
//////////////////////////////////////////////////////////////////////////

using namespace EDM::EDM_Graphics::Generators;

DelegateT *NetEventHandler::delCollisionWithCellBorder = new DelegateT(&CollisionWithCellBorder);
DelegateT *NetEventHandler::delCollisionWithBorderInCell = new DelegateT(&CollisionWithBorderInCell);
DelegateT *NetEventHandler::delCollisionWithActor = new DelegateT(&CollisionWithActor);

void NetEventHandler::CollisionWithCellBorder(int sender, const EventArgs & args)
{	
	ActorsContainer *acInst = ActorsContainer::Instance();
	//PriorityQueue *queueInst = PriorityQueue::Instance();
	CellContainer *ccInst= CellContainer::Instance();
	Actor *crntAcrt = &acInst->actors[sender];

	crntAcrt->Move();

	int newCell_x = crntAcrt->cell_x;
	int newCell_y = crntAcrt->cell_y;

	int lBordInputCellsCount = 0;

	switch (args.next)
	{
	case 1: // left border
		if (--newCell_x < 1)
		{
			newCell_x = 1;
			crntAcrt->vel.x = crntAcrt->vel.x * -1.0f;
		}
		break;
	case 2: // right border
		if (++newCell_x > EDM_Prop->xCellsCount)
		{
			newCell_x = EDM_Prop->xCellsCount;
			crntAcrt->vel.x = crntAcrt->vel.x * -1.0f;
		}
		break;
	case 3: // bottom border
		if (--newCell_y < 1)
		{
			newCell_y = 1;
			crntAcrt->vel.y = crntAcrt->vel.y * -1.0f;
		}
		break;
	case 4: // top border
		if (++newCell_y > EDM_Prop->yCellsCount)
		{
			newCell_y = EDM_Prop->yCellsCount;
			crntAcrt->vel.y = crntAcrt->vel.y * -1.0f;
		}

#pragma region Maxvells Daemons
		/*{
			float ver = FloatGenerator::Generate(0,1);
			if (ver < 0.1)
			{
				crntAcrt->vel.y = crntAcrt->vel.y * -1.0f;
			}
			else
			{
				if (++newCell_y > EDM_Prop->yCellsCount)
					newCell_y = EDM_Prop->yCellsCount;
			}
		}*/
#pragma endregion

		break;
	
	default:
		throw exception("Method: CollisionWithCellBorder >> Incorrect border index.");
		break;
	}

	ccInst->UpdateIndices(sender, newCell_x, newCell_y);

	NetEventController::FindNearestEventForActor(sender);

	ccInst->FreeInst();
	//queueInst->FreeInst();
	acInst->FreeInst();
}

void NetEventHandler::CollisionWithBorderInCell(int sender, const EventArgs & args)
{
	ActorsContainer *acInst = ActorsContainer::Instance();
	BordersContainer *bcInst = BordersContainer::Instance();
	PriorityQueue *queueInst = PriorityQueue::Instance();
	int borderInd = args.next;
	Actor *crntAcrt = &acInst->actors[sender];
	Border *crntBord = &bcInst->borders[borderInd];

	crntAcrt->Move();

	Vector2fT newVel = crntAcrt->vel - crntBord->normal * 2.0 * 
		EDM_Math::ScalarProduct(crntAcrt->vel, crntBord->normal);
	crntAcrt->vel = newVel;

	NetEventController::FindNearestEventForActor(sender);

	queueInst->FreeInst();
	bcInst->FreeInst();
	acInst->FreeInst();
	cout << "CollisionWithBorderInCell" << endl;
}

void NetEventHandler::CollisionWithActor(int sender, const EventArgs & args)
{
	ActorsContainer *acInst = ActorsContainer::Instance();
	//PriorityQueue *queueInst = PriorityQueue::Instance();
	int partnerInd = args.next;
	Actor *first = &acInst->actors[sender];
	Actor *second = &acInst->actors[partnerInd];

	bool IsEventActual =	(second->evnt->args->next == sender) &&
							(args.time == second->evnt->args->time) &&
							(second->evnt->handler == first->evnt->handler);
	if (IsEventActual)
	{
		first->Move();
		second->Move();	

		Vector2fT dr = EDM_Math::GetVector2f(first->localCoord, second->localCoord);
		Vector2fT dv = second->vel - first->vel;

		Point2F newFirstVel = first->vel + dr * ((2 * second->massa * EDM_Math::ScalarProduct(dv, dr)) / 
			((first->massa + second->massa) * EDM_Math::VectorSquare(dr)));
		Point2F newSecondVel = second->vel - dr * ((2 * first->massa * EDM_Math::ScalarProduct(dv, dr)) / 
			((first->massa + second->massa) * EDM_Math::VectorSquare(dr)));

		first->vel = newFirstVel;
		second->vel = newSecondVel;

		
		//queueInst->ChangeHeapTree(partnerInd);
		NetEventController::FindNearestEventForActor(partnerInd);
	}

	NetEventController::FindNearestEventForActor(sender);
	
	//queueInst->ChangeHeapTree(sender);
	

	//queueInst->FreeInst();
	acInst->FreeInst();
}

//
//switch (args.next)
//{
//case 1:
//	if (--newCell_j < 0)
//	{
//		newCell_j = gridSqrtCount - 1;
//		crntAcrt->coord.y = wordHeight - 0.01f;
//	}
//	break;
//case 2:
//	if (++newCell_i > gridSqrtCount - 1)
//	{
//		newCell_i = 0;
//		crntAcrt->coord.x = lBordInputCellsCount + 0.01f;
//	}
//	break;
//case 3:
//	if (++newCell_j > gridSqrtCount - 1)
//	{
//		newCell_j = 0;
//		crntAcrt->coord.y = 0.01f;
//	}
//	break;
//case 4:
//	if (--newCell_i < lBordInputCellsCount)
//	{
//		newCell_i = crntAcrt->cell_x;
//		crntAcrt->vel.x = crntAcrt->vel.x * -1.0f;
//	}
//	break;