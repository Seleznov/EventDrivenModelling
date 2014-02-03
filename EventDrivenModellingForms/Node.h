#pragma once
#ifndef NODE_H
#define NODE_H

#include "Point2F.h"

//////////////////////////////////////////////////////////////////////////
// TODO: Rename to particle
//////////////////////////////////////////////////////////////////////////

namespace EDM { namespace Logic 
{
	struct EventArgs;

	template<class senderT, class argsT>
	class Event;
}}

using namespace EDM::EDM_Graphics;
using namespace EDM::Logic;

namespace EDM { namespace Model 
{
	class Node
	{
	protected:	
		typedef Event<int, EventArgs> EventT;

	public:
		CoordT		coord;
		CoordT		localCoord;
		Vector2fT	vel;
		double		radius, massa;
		EventT		*evnt;

		Node();
		~Node();
		Node(CoordT _coord, Vector2fT _vel, double _radius);
		Node(CoordT _coord, Vector2fT _vel, double _radius, double _massa);
		Node(CoordT _coord, Vector2fT _vel, double _radius, EventT *_event, double _massa = 1.0);
		void SetEvent(EventT *val);
		bool operator==(const Node obj);
		void Move();
		void Move(double time);
	private:
	};
}}

#endif