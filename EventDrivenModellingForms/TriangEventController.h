#pragma once
#ifndef TRIANGEVENTCONTROLLER_H
#define TRIANGEVENTCONTROLLER_H

namespace EDM { namespace Logic {

	class TriangEventController
	{
	public:		
		static void FindStartTimesForNodes();
		static void FindNearestEventsForAdjNodesOfNode(int nodeInd, int prevCollisionEdgeInd );
		static void FindNearestEventForNode(int nodeInd, int prevCollisionEdgeInd );
		static double TimeToCollisionWithEdge(int nodeInd, int edgeInd, int prevCollisionEdgeInd );

	private:
		static EventArgs* ArgsInCollisionWithEdge(int nodeInd, int prevCollisionEdgeInd );
		static EventArgs* ArgsInCollisionWithNode(int nodeInd);
		static EventArgs* ArgsInCollisionWithOtherSideNode(int nodeInd, int otherSideNodeInd);

		static EventArgs* PartnerArgsInNodesCollisionEvent(int nodeInd);

		static double TimeToCollisionBwNodes(int firstInd, int secondInd);
		static void GetR1R2R3( TriangNode &p1, TriangNode &p2, TriangNode &p3, int &newNodeInd );

		// Check will point belong to segment after time. newNodeInd is the number of node.
		static bool OnSegment( CoordT &r1, CoordT &r2, CoordT &r3, 
			Vector2fT& r1_vel, Vector2fT& r2_vel, Vector2fT& r3_vel, double delta_time, int newNodeInd );
		static double GetDihotomiaTime(CoordT &r1, CoordT &r2, CoordT &r3, Vector2fT& r1_vel, 
			Vector2fT& r2_vel, Vector2fT& r3_vel, double maxTime, int newNodeInd, double radius);

		static void SetNewEvent(int nodeInd, EventArgs &args, DelegateT *del, bool changeQueue);
	};
}}

#endif