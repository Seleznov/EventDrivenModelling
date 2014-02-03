#include "TriangNode.h"
#include "TriangNodesContainer.h"
#include "TriangEdge.h"
#include "EdgesContainer.h"
#include "Events.h"
#include "TriangEventController.h"
#include "PriorityQueue.h"
#include "EDM_Math.h"
#include "FloatGenerator.h"
#include "TriangEventHandler.h"

using namespace EDM::EDM_Graphics::Generators;

DelegateT *TriangEventHandler::delCollisionWithNode = new DelegateT(&CollisionWithNode);
DelegateT *TriangEventHandler::delCollisionWithOppositeEdge = new DelegateT(&CollisionWithOppositeEdge);


void TriangEventHandler::CollisionWithOppositeEdge(int sender, const EventArgs & args)
{	
	TriangNodesContainer *nodsInst = TriangNodesContainer::Instance();
	EdgesContainer *edgesInst = EdgesContainer::Instance();

	int oppEdgeInd = args.next;
	TriangEdge *oppEdge = &edgesInst->m_edges[oppEdgeInd];

	TriangNode *crntNode = &nodsInst->m_nodes[sender];
	int oppEdgeBeginNodeInd = oppEdge->m_begin;
	TriangNode *oppEdgeBeginNode = &nodsInst->m_nodes[oppEdgeBeginNodeInd];
	int oppEdgeEndNodeInd = oppEdge->m_end;
	TriangNode *oppEdgeEndNode = &nodsInst->m_nodes[oppEdgeEndNodeInd];

	crntNode->Move(args.time);
	oppEdgeBeginNode->Move(args.time);
	oppEdgeEndNode->Move(args.time);

	if (oppEdgeInd < 4) // collision with border edges
	{
		if (oppEdgeInd == 0 || oppEdgeInd == 2)
		{
			crntNode->vel.y = crntNode->vel.y * -1.0f;
		}
		else if (oppEdgeInd == 1 || oppEdgeInd == 3)
		{
			crntNode->vel.x = crntNode->vel.x * -1.0f;
		}

		TriangEventController::FindNearestEventForNode(sender, args.next);
		TriangEventController::FindNearestEventsForAdjNodesOfNode(sender, args.next);
	}
	else
	{
		int otherSideNodeInd = oppEdge->GetOtherSideNode(sender);
		TriangNode *otherSideNode = &nodsInst->m_nodes[otherSideNodeInd];
		
		crntNode->RemoveOppositeEdge(oppEdgeInd);
		otherSideNode->RemoveOppositeEdge(oppEdgeInd);
		oppEdgeBeginNode->RemoveAdjEdge(oppEdgeInd);
		oppEdgeEndNode->RemoveAdjEdge(oppEdgeInd);

		crntNode->AddAdjEdge(oppEdgeInd);
		otherSideNode->AddAdjEdge(oppEdgeInd);
		oppEdgeBeginNode->AddOppositeEdge(oppEdgeInd);
		oppEdgeEndNode->AddOppositeEdge(oppEdgeInd);

		int oppEdgeBeginNodeToOtherSideNodeInd = edgesInst->FindEdgeBeetwenNodes(oppEdge->m_begin, otherSideNodeInd);
		int oppEdgeBeginNodeToCrntNodeInd = edgesInst->FindEdgeBeetwenNodes(oppEdge->m_begin, sender);
		int oppEdgeEndNodeToOtherSideNodeInd = edgesInst->FindEdgeBeetwenNodes(oppEdge->m_end, otherSideNodeInd);
		int oppEdgeEndNodeToCrntNodeInd = edgesInst->FindEdgeBeetwenNodes(oppEdge->m_end, sender);

		oppEdgeEndNode->RemoveOppositeEdge(oppEdgeBeginNodeToOtherSideNodeInd);
		oppEdgeEndNode->RemoveOppositeEdge(oppEdgeBeginNodeToCrntNodeInd);
		oppEdgeBeginNode->RemoveOppositeEdge(oppEdgeEndNodeToOtherSideNodeInd);
		oppEdgeBeginNode->RemoveOppositeEdge(oppEdgeEndNodeToCrntNodeInd);

		edgesInst->m_edges[oppEdgeBeginNodeToOtherSideNodeInd].ChangeSideNode(oppEdge->m_end, sender);
		edgesInst->m_edges[oppEdgeBeginNodeToCrntNodeInd].ChangeSideNode(oppEdge->m_end, otherSideNodeInd);			
		edgesInst->m_edges[oppEdgeEndNodeToOtherSideNodeInd].ChangeSideNode(oppEdge->m_begin, sender);
		edgesInst->m_edges[oppEdgeEndNodeToCrntNodeInd].ChangeSideNode(oppEdge->m_begin, otherSideNodeInd);

		crntNode->AddOppositeEdge(oppEdgeBeginNodeToOtherSideNodeInd);
		crntNode->AddOppositeEdge(oppEdgeEndNodeToOtherSideNodeInd);
		otherSideNode->AddOppositeEdge(oppEdgeBeginNodeToCrntNodeInd);
		otherSideNode->AddOppositeEdge(oppEdgeEndNodeToCrntNodeInd);

		oppEdge->Change();

		TriangEventController::FindNearestEventForNode(sender, args.next);
		TriangEventController::FindNearestEventForNode(oppEdgeBeginNodeInd, args.next);
		TriangEventController::FindNearestEventForNode(oppEdgeEndNodeInd, args.next);
		TriangEventController::FindNearestEventForNode(otherSideNodeInd, args.next);
	}

	edgesInst->FreeInst();
	nodsInst->FreeInst();
}


void TriangEventHandler::CollisionWithNode(int sender, const EventArgs & args)
{
	TriangNodesContainer *nodsInst = TriangNodesContainer::Instance();
	int partnerInd = args.next;
	TriangNode *senderNode = &nodsInst->m_nodes[sender];
	TriangNode *partnerNode = &nodsInst->m_nodes[partnerInd];

	bool IsEventActual =	(partnerNode->evnt->args->next == sender) &&
							(args.time == partnerNode->evnt->args->time) &&
							(partnerNode->evnt->handler == senderNode->evnt->handler);
	if (IsEventActual)
	{
		senderNode->Move();
		partnerNode->Move();	

		Vector2fT dr = EDM_Math::GetVector2f(senderNode->localCoord, partnerNode->localCoord);
		Vector2fT dv = partnerNode->vel - senderNode->vel;

		if (!( (senderNode->massa == STATIC_POINT_MASSA) && (senderNode->vel == Point2F(0.0f, 0.0f)) ))
		{
			Point2F newSenderVel = senderNode->vel + dr * ((2 * partnerNode->massa * EDM_Math::ScalarProduct(dv, dr)) / 
				((senderNode->massa + partnerNode->massa) * EDM_Math::VectorSquare(dr)));
			senderNode->vel = newSenderVel;
			TriangEventController::FindNearestEventsForAdjNodesOfNode(sender, -1);
		}
		if (!( (partnerNode->massa == STATIC_POINT_MASSA) && (partnerNode->vel == Point2F(0.0f, 0.0f)) ))
		{
			Point2F newPartnerVel = partnerNode->vel - dr * ((2 * senderNode->massa * EDM_Math::ScalarProduct(dv, dr)) / 
				((senderNode->massa + partnerNode->massa) * EDM_Math::VectorSquare(dr)));
			partnerNode->vel = newPartnerVel;
			TriangEventController::FindNearestEventsForAdjNodesOfNode(partnerInd, -1);
		}

		TriangEventController::FindNearestEventForNode(partnerInd, -1);
	}
	
	TriangEventController::FindNearestEventForNode(sender, -1);
	
	nodsInst->FreeInst();
}

void TriangEventHandler::MoveAdjNodesOfNodeToTime(int nodeInd, double time)
{
	TriangNodesContainer *nodsInst = TriangNodesContainer::Instance();
	EdgesContainer *edgesInst = EdgesContainer::Instance();
	TriangNode *crntNode = &nodsInst->m_nodes[nodeInd];

	for (size_t adjEdgeCntr = 0; adjEdgeCntr < crntNode->m_adjEdges.size(); adjEdgeCntr++)
	{
		int adjEdgeInd = crntNode->m_adjEdges[adjEdgeCntr].number;
		int adjNodeInd = edgesInst->m_edges[adjEdgeInd].GetOtherEdgeNode(nodeInd);
		nodsInst->m_nodes[adjNodeInd].Move(time);
	}

	edgesInst->FreeInst();
	nodsInst->FreeInst();
}