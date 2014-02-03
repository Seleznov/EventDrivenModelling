#include "TriangNode.h"
#include "TriangNodesContainer.h"
#include "TriangEdge.h"
#include "EdgesContainer.h"
#include "Events.h"
#include "PriorityQueue.h"
#include "TriangEventHandler.h"
#include "EDM_Math.h"
#include "TriangEventController.h"
#include "Properties.h"

using namespace EDM;
using namespace EDM::Logic;
using namespace EDM::Model;

void TriangEventController::FindStartTimesForNodes()
{
	// first four nodes are static with infinity massa
	for (int nodeCntr = 0; nodeCntr < EDM_Prop->ActorsCount; nodeCntr++)
	{
		FindNearestEventForNode(nodeCntr, -1);
	}
}

void TriangEventController::FindNearestEventsForAdjNodesOfNode(int nodeInd, int prevCollisionEdgeInd)
{
	TriangNodesContainer *nodsInst = TriangNodesContainer::Instance();
	EdgesContainer *edgesInst = EdgesContainer::Instance();
	TriangNode *crntNode = &nodsInst->m_nodes[nodeInd];

	for (size_t adjEdgeCntr = 0; adjEdgeCntr < crntNode->m_adjEdges.size(); adjEdgeCntr++)
	{
		int adjEdgeInd = crntNode->m_adjEdges[adjEdgeCntr].number;
		int adjNodeInd = edgesInst->m_edges[adjEdgeInd].GetOtherEdgeNode(nodeInd);
		FindNearestEventForNode(adjNodeInd, prevCollisionEdgeInd);
	}

	edgesInst->FreeInst();
	nodsInst->FreeInst();
}

void TriangEventController::FindNearestEventForNode(int nodeInd, int prevCollisionEdgeInd)
{
	TriangNodesContainer *nodsInst = TriangNodesContainer::Instance();	

	EdgesContainer *edgeInst = EdgesContainer::Instance();
	EventArgs *edgeArgs = ArgsInCollisionWithEdge(nodeInd, prevCollisionEdgeInd);
	EventArgs *nodeArgs = ArgsInCollisionWithNode(nodeInd);

	double tMin = min(edgeArgs->time, nodeArgs->time);
	if (tMin == edgeArgs->time)
	{
		int otherSideNodeInd = -1;
		EventArgs *otherSideNodeArgs = new EventArgs();
		if (edgeArgs->next > 3)
		{
			otherSideNodeInd = edgeInst->m_edges[edgeArgs->next].GetOtherSideNode(nodeInd);
			otherSideNodeArgs = ArgsInCollisionWithOtherSideNode(nodeInd, otherSideNodeInd);
		}
		
		if (tMin > otherSideNodeArgs->time)
		{
			SetNewEvent(nodeInd, *otherSideNodeArgs, TriangEventHandler::delCollisionWithNode, true);
		}
		else
		{		
			//actual event must be set in the last place
			SetNewEvent(nodeInd, *edgeArgs, TriangEventHandler::delCollisionWithOppositeEdge, true);
		}
	}
	else if ((tMin == nodeArgs->time) && (tMin <= nodsInst->m_nodes[nodeArgs->next].evnt->args->time))
	{
		SetNewEvent(nodeInd, *nodeArgs, TriangEventHandler::delCollisionWithNode, true);
		int partnerInd = nodeArgs->next;
		EventArgs *partnerArgs = PartnerArgsInNodesCollisionEvent(nodeInd);
		SetNewEvent(partnerInd, *partnerArgs, TriangEventHandler::delCollisionWithNode, true);
	}
	else
	{
		EventArgs *emptyArgs = new EventArgs(DBL_MAX, nodsInst->m_nodes[nodeInd].evnt->args->localTime, -1);
		SetNewEvent(nodeInd, *emptyArgs, nullptr, true);
	}
	

	edgeInst->FreeInst();
	nodsInst->FreeInst();
}

void TriangEventController::SetNewEvent(int nodeInd, EventArgs &args, DelegateT *del, bool changeQueue)
{
	TriangNodesContainer *nodsInst = TriangNodesContainer::Instance();
	EventT *evnt = new EventT(nodeInd, args, del);
	nodsInst->m_nodes[nodeInd].SetEvent(evnt);

	if (PriorityQueue::IsExist() && changeQueue)
	{
		PriorityQueue *queueInst = PriorityQueue::Instance();
		queueInst->ChangeHeapTree(nodeInd);
		queueInst->FreeInst();
	}

	nodsInst->FreeInst();
}

EventArgs* TriangEventController::PartnerArgsInNodesCollisionEvent(int nodeInd)
{
	TriangNodesContainer *nodsInst = TriangNodesContainer::Instance();
	TriangNode *crntNode = &nodsInst->m_nodes[nodeInd]; 
	TriangNode *partnerNode = &nodsInst->m_nodes[crntNode->evnt->args->next];

	EventArgs *partnerArgs = new EventArgs(
		crntNode->evnt->args->time, 
		partnerNode->evnt->args->localTime,
		crntNode->evnt->sender);

	nodsInst->FreeInst();
	return partnerArgs;
}


EventArgs* TriangEventController::ArgsInCollisionWithEdge(int nodeInd, int prevCollisionEdgeInd)
{
	TriangNodesContainer *nodsInst = TriangNodesContainer::Instance();
	TriangNode *crntNode = &nodsInst->m_nodes[nodeInd];

	double tMin = DBL_MAX;
	int minEdgeInd = -1;

	for (size_t edgeCntr = 0; edgeCntr < crntNode->m_oppositeEdges.size(); edgeCntr++)
	{
		int oppEdgeInd = crntNode->m_oppositeEdges[edgeCntr];
		double timeToCollision = TimeToCollisionWithEdge(nodeInd, oppEdgeInd, prevCollisionEdgeInd);
		if (timeToCollision < tMin)
		{
			tMin = timeToCollision;
			minEdgeInd = oppEdgeInd;
		}
	}

	EventArgs *args = new EventArgs(tMin, crntNode->evnt->args->localTime, minEdgeInd);
	nodsInst->FreeInst();
	return args;	
}

double TriangEventController::TimeToCollisionWithEdge( int nodeInd, int edgeInd, int prevCollisionEdgeInd )
{
	double time = DBL_MAX;
	int newNodeInd = -1;
	TriangNodesContainer *nodsInst = TriangNodesContainer::Instance();
	EdgesContainer *edgInst = EdgesContainer::Instance();

	if ( (nodsInst->m_nodes[nodeInd].evnt->args->next == edgeInd)
		&& (edgeInd == prevCollisionEdgeInd) )
	{
		nodsInst->FreeInst();
		return time;
	}
	
	TriangNode r1 = nodsInst->m_nodes[nodeInd];
	TriangNode r2 = nodsInst->m_nodes[edgInst->m_edges[edgeInd].m_begin];
	TriangNode r3 = nodsInst->m_nodes[edgInst->m_edges[edgeInd].m_end];
	GetR1R2R3( r1, r2, r3, newNodeInd );

	CoordT new_r2 = EDM_Math::ri0_(r2.localCoord, r1.evnt->args->localTime, r2.evnt->args->localTime, r2.vel);
	CoordT r3_ = EDM_Math::ri0_(r3.localCoord, r2.evnt->args->localTime, r3.evnt->args->localTime, r3.vel);
	CoordT new_r3 = EDM_Math::ri0_(r3_, r1.evnt->args->localTime, r2.evnt->args->localTime, r3.vel);

	double A = (r1.vel.x - r3.vel.x) * (r2.vel.y - r3.vel.y) - (r2.vel.x - r3.vel.x) * (r1.vel.y - r3.vel.y);

	double B = (
		(r1.localCoord.x - new_r3.x) * (r2.vel.y - r3.vel.y) + 
		(new_r2.y - new_r3.y) * (r1.vel.x - r3.vel.x) -
		(new_r2.x - new_r3.x) * (r1.vel.y - r3.vel.y) - 
		(r1.localCoord.y - new_r3.y) * (r2.vel.x - r3.vel.x));

	double C = (r1.localCoord.x - new_r3.x) * (new_r2.y - new_r3.y) - (new_r2.x - new_r3.x) * (r1.localCoord.y - new_r3.y);

	if (A == 0)
	{
		if (C * B <= 0 )
		{
			// it is a time, when node center intersect the edge.
			double dt = -C / B;		
			if (OnSegment(r1.localCoord, new_r2, new_r3, r1.vel, r2.vel, r3.vel, dt, newNodeInd))
			{
				// it is a time, when node circle intersect the edge.
				double dihTime = GetDihotomiaTime(r1.localCoord, new_r2, new_r3, 
					r1.vel, r2.vel, r3.vel, dt, newNodeInd, r1.radius);
				{
					time = r1.evnt->args->localTime + dihTime; 
				}
			}
		}
	}
	else
	{
		double discrim = B * B - 4 * A * C;
		if (discrim > 0)
		{
			double dt_1 = (-B - sqrt(discrim)) / (2 * A);
			double dt_2 = (-B + sqrt(discrim)) / (2 * A);
			
			// it is a time, when node center intersect the edge.
			double dt;
			dt_1 > 0 ? dt = dt_1 : dt = dt_2;
			if (dt > 0 && OnSegment(r1.localCoord, new_r2, new_r3, r1.vel, r2.vel, r3.vel, dt, newNodeInd))
			{
				// it is a time, when node circle intersect the edge.
				double dihTime = GetDihotomiaTime(r1.localCoord, new_r2, new_r3, 
					r1.vel, r2.vel, r3.vel, dt, newNodeInd, r1.radius);
				time = r1.evnt->args->localTime + dihTime; 
			}
		}
	}

	edgInst->FreeInst();
	nodsInst->FreeInst();
	return time;
}

EventArgs* TriangEventController::ArgsInCollisionWithNode(int nodeInd)
{
	TriangNodesContainer *nodsInst = TriangNodesContainer::Instance();
	EdgesContainer *edgInst = EdgesContainer::Instance();
	TriangNode *crntNode = &nodsInst->m_nodes[nodeInd]; 

	double tMin = DBL_MAX;
	int minNghbrNodeInd = -1;

	for (size_t adjEdgeCntr = 0; adjEdgeCntr < crntNode->m_adjEdges.size(); adjEdgeCntr++)
	{
		int adjEdgeInd = crntNode->m_adjEdges[adjEdgeCntr].number;
		int nghbrNodeInd = edgInst->m_edges[adjEdgeInd].GetOtherEdgeNode(nodeInd);
		double timeToCollision = TimeToCollisionBwNodes(nodeInd, nghbrNodeInd);
		if (timeToCollision < tMin)
		{
			tMin = timeToCollision;
			minNghbrNodeInd = nghbrNodeInd;
		}
	}

	EventArgs *args = new EventArgs(tMin, crntNode->evnt->args->localTime, minNghbrNodeInd);
	edgInst->FreeInst();
	nodsInst->FreeInst();
	return args;
}

EventArgs* TriangEventController::ArgsInCollisionWithOtherSideNode(int nodeInd, int otherSideNodeInd)
{
	TriangNodesContainer *nodsInst = TriangNodesContainer::Instance();

	double timeToCollision = TimeToCollisionBwNodes(nodeInd, otherSideNodeInd);
	EventArgs *args = new EventArgs(timeToCollision, nodsInst->m_nodes[nodeInd].evnt->args->localTime, otherSideNodeInd);

	nodsInst->FreeInst();
	return args;
}

double TriangEventController::TimeToCollisionBwNodes(int firstInd, int secondInd)
{
	TriangNodesContainer *nodsInst = TriangNodesContainer::Instance();
	TriangNode *first, *second;
	if (nodsInst->m_nodes[firstInd].evnt->args->localTime >= nodsInst->m_nodes[secondInd].evnt->args->localTime)
	{
		first = &nodsInst->m_nodes[firstInd];
		second = &nodsInst->m_nodes[secondInd];
	}
	else
	{
		first = &nodsInst->m_nodes[secondInd];
		second = &nodsInst->m_nodes[firstInd];
	}

	// normalization to equal local time
	Point2F dv = first->vel - second->vel;
	CoordT r20_ = EDM_Math::ri0_(
		second->localCoord, first->evnt->args->localTime, 
		second->evnt->args->localTime, second->vel);
	Point2F dr = first->localCoord - r20_;

	double L = first->radius + second->radius;
	double A = EDM_Math::ScalarProduct(dv, dv);
	double B = -EDM_Math::ScalarProduct(dr, dv);
	double C = EDM_Math::ScalarProduct(dr, dr) - L * L;
	
	// sometimes C is negative, in this case we use small positive value
	if (C < 0)
		C = 0.00001;
	double discrim = EDM_Math::Discrim(B, A, C);

	if ((discrim > 0) && (B > sqrt(discrim)))
	{
		double dt = EDM_Math::dt(B, discrim, A);
		double time = first->evnt->args->localTime + dt;		
		if ((time <= second->evnt->args->time))
		{
			nodsInst->FreeInst();
			return time;
		}
	}

	nodsInst->FreeInst();
	return DBL_MAX;
}

void TriangEventController::GetR1R2R3( TriangNode &p1, TriangNode &p2, TriangNode &p3, int &newNodeInd )
{	
	TriangNode r1, r2, r3;
	double t_loc_3 = min( p1.evnt->args->localTime, min( p2.evnt->args->localTime, p3.evnt->args->localTime ) );
	if ( t_loc_3 == p1.evnt->args->localTime )
	{
		r3 = p1;
		newNodeInd = 3;

		double t_loc_2 = min( p2.evnt->args->localTime, p3.evnt->args->localTime );
		if ( t_loc_2 == p2.evnt->args->localTime )
		{
			r2 = p2;
			r1 = p3;
		}
		else
		{
			r2 = p3;
			r1 = p2;
		}
	}
	else if ( t_loc_3 == p2.evnt->args->localTime )
	{
		r3 = p2;

		double t_loc_2 = min( p1.evnt->args->localTime, p3.evnt->args->localTime );
		if ( t_loc_2 == p1.evnt->args->localTime )
		{
			r2 = p1;
			newNodeInd = 2;
			r1 = p3;
		}
		else
		{
			r2 = p3;
			r1 = p1;
			newNodeInd = 1;
		}
	}
	else
	{
		r3 = p3;

		double t_loc_2 = min( p1.evnt->args->localTime, p2.evnt->args->localTime );
		if ( t_loc_2 == p1.evnt->args->localTime )
		{
			r2 = p1;
			newNodeInd = 2;
			r1 = p2;
		}
		else
		{
			r2 = p2;
			r1 = p1;
			newNodeInd = 1;
		}
	}

	p1 = r1;
	p2 = r2;
	p3 = r3;
}

bool TriangEventController::OnSegment( CoordT &r1, CoordT &r2, CoordT &r3, 
	Vector2fT& r1_vel, Vector2fT& r2_vel, Vector2fT& r3_vel, double delta_time, int newNodeInd) 
{
	CoordT new_r1 = r1_vel * delta_time + r1;
	CoordT new_r2 = r2_vel * delta_time + r2;
	CoordT new_r3 = r3_vel * delta_time + r3;

	if (newNodeInd == 1)
	{
		return EDM_Math::OnSegmentEq(new_r2, new_r3, new_r1);
	}
	else if (newNodeInd == 2)
	{
		return EDM_Math::OnSegmentEq(new_r1, new_r3, new_r2);
	}
	else if (newNodeInd == 3)
	{
		return EDM_Math::OnSegmentEq(new_r1, new_r2, new_r3);
	}
	return false;
}

double TriangEventController::GetDihotomiaTime(CoordT &r1, CoordT &r2, CoordT &r3, 
	Vector2fT& r1_vel, Vector2fT& r2_vel, Vector2fT& r3_vel, double maxTime, int newNodeInd, double radius)
{
	double halfTime = maxTime / 2;
	double minTime = 0;

	CoordT new_r1 = r1_vel * halfTime + r1;
	CoordT new_r2 = r2_vel * halfTime + r2;
	CoordT new_r3 = r3_vel * halfTime + r3;
	
	float dist;
	if (newNodeInd == 1)
		dist = EDM_Math::DistanceBetweenPointAndLine(new_r2, new_r3, new_r1);
	else if (newNodeInd == 2)
		dist = EDM_Math::DistanceBetweenPointAndLine(new_r1, new_r3, new_r2);
	else if (newNodeInd == 3)
		dist = EDM_Math::DistanceBetweenPointAndLine(new_r1, new_r2, new_r3);

	while(abs(dist - radius) > EDM_Prop->Eps)
	{
		if (dist > radius)
			minTime = halfTime;
		else
			maxTime = halfTime;
		halfTime = (minTime + maxTime) / 2;

		new_r1 = r1_vel * halfTime + r1;
		new_r2 = r2_vel * halfTime + r2;
		new_r3 = r3_vel * halfTime + r3;

		if (newNodeInd == 1)
			dist = EDM_Math::DistanceBetweenPointAndLine(new_r2, new_r3, new_r1);
		else if (newNodeInd == 2)
			dist = EDM_Math::DistanceBetweenPointAndLine(new_r1, new_r3, new_r2);
		else if (newNodeInd == 3)
			dist = EDM_Math::DistanceBetweenPointAndLine(new_r1, new_r2, new_r3);
	}

	return halfTime;
}