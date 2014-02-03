#pragma once
#ifndef ACTOR_H
#define ACTOR_H

#include "Point2F.h"
#include "Node.h"

namespace EDM { 
	namespace Logic 
	{
		struct EventArgs;

		template<class senderT, class argsT>
		class Event;
	}
}

using namespace EDM::EDM_Graphics;
using namespace EDM::Logic;

namespace EDM { namespace Model 
{
	class Actor : public Node
	{
		//typedef Event<int, EventArgs> EventT;

	public:
		//CoordT		coord;
		//CoordT		localCoord;
		//Vector2fT	vel;
		//double		radius, massa;
		int			cell_x, cell_y;
		//EventT		*evnt;

		Actor();
		Actor(CoordT _coord, Vector2fT _vel, double _radius);
		Actor(CoordT _coord, Vector2fT _vel, double _radius, double _massa);
		Actor(CoordT _coord, Vector2fT _vel, double _radius, EventT *_evnt, double _massa = 1.0);
		~Actor();
		//void SetEvent(EventT *val);					
		//bool operator==(const Actor obj);
		void AddActorInCell(int actorInd);		
		//void Move();
	private:
		inline int FindXCellIndex(float xCoord);
		inline int FindYCellIndex(float yCoord);		
	};

	int Actor::FindXCellIndex(float xCoord)
	{
		return (int)xCoord;
	}

	int Actor::FindYCellIndex(float yCoord)
	{
		return (int)yCoord;
	}
}}

#endif