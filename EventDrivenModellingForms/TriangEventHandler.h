#pragma once
#ifndef TRIANGEVENTHANDLER_H
#define TRIANGEVENTHANDLER_H

namespace EDM { namespace Logic 
{
	struct EventArgs;

	class TriangEventHandler
	{
	public: 
		static DelegateT *delCollisionWithNode;
		static DelegateT *delCollisionWithOppositeEdge;

	private:
		static void CollisionWithNode(int sender, const EventArgs & args);
		static void CollisionWithOppositeEdge(int sender, const EventArgs & args);		
		static void MoveAdjNodesOfNodeToTime(int nodeInd, double time);
	};
}}

#endif