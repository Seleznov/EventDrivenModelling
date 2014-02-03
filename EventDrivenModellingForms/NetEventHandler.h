#pragma once
#ifndef NETEVENTHANDLER_H
#define NETEVENTHANDLER_H

namespace EDM { namespace Logic 
{
	struct EventArgs;

	class NetEventHandler
	{
	public: 
		static DelegateT *delCollisionWithCellBorder;
		static DelegateT *delCollisionWithBorderInCell;
		static DelegateT *delCollisionWithActor;

	private:
		static void CollisionWithCellBorder(int sender, const EventArgs & args);
		static void CollisionWithBorderInCell(int sender, const EventArgs & args);
		static void CollisionWithActor(int sender, const EventArgs & args);
	};
}}

#endif