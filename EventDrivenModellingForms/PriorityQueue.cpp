#include <vector>
#include <list>
#include <math.h>

#include "TriangNode.h"
#include "Actor.h"
#include "Events.h"
#include "NetEventController.h"
#include "TriangEventController.h"
#include "ActorsContainer.h"
#include "TriangNodesContainer.h"
#include "PriorityQueue.h"
#include "Properties.h"

using namespace std;
using namespace EDM;
using namespace EDM::Logic;
using namespace EDM::Model;

PriorityQueue::PriorityQueue()
{
	int actualActorsCount = PriorityQueue::CalcActualActorsCount(EDM_Prop->ActorsCount);	
	AddMissingActors(actualActorsCount);

	NetEventController::FindStartTimesForActors();		

	m_startInd = CalcStartInd(actualActorsCount);
	int heapTreeSize = CalcHeapTreeSize(m_startInd, actualActorsCount);
	InitHeapTree(heapTreeSize);	
	FillHeapTree();	
}

PriorityQueue::~PriorityQueue()
{
	delete m_heapTree;
}

int PriorityQueue::CalcActualActorsCount(int actorsCount) const
{
	int actualCount = 2;
	while (actualCount < actorsCount)
	{
		actualCount *= 2;
	}
	return actualCount;
}

void PriorityQueue::AddMissingActors(int actualActorsCount) const
{
	ActorsContainer *acInst = ActorsContainer::Instance();

	unsigned int fakeActCount = actualActorsCount - EDM_Prop->ActorsCount;
	for (unsigned int i = 0; i < fakeActCount; i++)
	{
		EventArgs *fakeArgs = new EventArgs(DBL_MAX, DBL_MAX, -1);
		EventT *fakeEvnt = new EventT(-1, *fakeArgs, nullptr);
		Actor fakeActor = Actor(CoordT(FLT_MAX, FLT_MAX), Vector2fT(), 0, fakeEvnt);
		acInst->actors.push_back(fakeActor);
	}

	acInst->FreeInst();
}

void PriorityQueue::AddMissingNodes(int actualActorsCount) const
{
	TriangNodesContainer *nodsInst = TriangNodesContainer::Instance();

	unsigned int fakeActCount = actualActorsCount - EDM_Prop->ActorsCount;
	for (unsigned int i = 0; i < fakeActCount; i++)
	{
		EventArgs *fakeArgs = new EventArgs(DBL_MAX, DBL_MAX, -1);
		EventT *fakeEvnt = new EventT(-1, *fakeArgs, nullptr);
		TriangNode fakeNode = TriangNode(CoordT(FLT_MAX, FLT_MAX), Vector2fT(), 0, fakeEvnt);
		nodsInst->m_nodes.push_back(fakeNode);
	}

	nodsInst->FreeInst();
}

int PriorityQueue::CalcStartInd(int actualActorsCount) const
{
	return actualActorsCount - 1;
}

int PriorityQueue::CalcHeapTreeSize(int startInd, int actualActorsCount) const
{
	return startInd + actualActorsCount;
}

void PriorityQueue::InitHeapTree(int heapTreeSize)
{
	m_heapTree = new HeapTreeT(heapTreeSize);
}

void PriorityQueue::FillHeapTree()
{
	FillBottomHeapTreeTier();

	int rChInd = (*m_heapTree).size() - 1;
	int lChInd = rChInd - 1;

	while (rChInd != 0)
	{
		ChangeHeap(lChInd, rChInd);
		rChInd = rChInd - 2;
		lChInd = lChInd - 2;
	}
}

void PriorityQueue::FillBottomHeapTreeTier()
{
	for (unsigned int i = m_startInd, val = 0; i < m_heapTree->size(); i++, val++)
	{
		(*m_heapTree)[i] = val;
	}
}

void PriorityQueue::ChangeHeap(int lChInd, int rChInd)
{
	ActorsContainer *acInst = ActorsContainer::Instance();

	int parentInd = lChInd / 2;
	int actLeftInd = (*m_heapTree)[lChInd];
	int actRightInd = (*m_heapTree)[rChInd];
	if (acInst->actors[actLeftInd].evnt->args->time <=
		acInst->actors[actRightInd].evnt->args->time)
	{
		(*m_heapTree)[parentInd] = (*m_heapTree)[lChInd];
	}
	else
	{
		(*m_heapTree)[parentInd] = (*m_heapTree)[rChInd];
	}

	acInst->FreeInst();
}

void PriorityQueue::ChangeHeapTree(int changedActorInd)
{
	int crntInd = m_startInd + changedActorInd;
	int lChInd, rChInd, parentInd = -1;

	while (parentInd != 0)
	{
		if (crntInd % 2 == 0)
		{
			lChInd = crntInd - 1;
			rChInd = crntInd;
		}
		else
		{
			lChInd = crntInd;
			rChInd = crntInd + 1;
		}
		parentInd = lChInd / 2;
		ChangeHeap(lChInd, rChInd);
		crntInd = parentInd;
	}
}

void PriorityQueue::PlayNetEventsForTime()
{
	Properties ^prop = EDM_Prop;
	prop->ActualTime += prop->DrawingPeriodInSeconds;

	ActorsContainer *acInst = ActorsContainer::Instance();	
	int crntActInd, nextActInd;
	double elapsedTime, crntEvntTime, nextEvntTime, crntActTime, nextActTime;
	elapsedTime = 0.0;
	
	crntActInd = GetFirst();
	nextEvntTime = acInst->actors[crntActInd].evnt->args->time;		
	while ((prop->ActualTime >= nextEvntTime) && (elapsedTime <= prop->DrawingPeriodInSeconds))
	{
		acInst->actors[crntActInd].evnt->OnHandler();
		crntActInd = GetFirst();
		nextEvntTime = acInst->actors[crntActInd].evnt->args->time;
		prop->EventsCounter++;

#ifdef DEBUG
		if (prop->EventsCounter == 2754)
		{		 int q = 0;			 }
#endif
		
	}

	acInst->FreeInst();
}