#pragma once
#ifndef NETEVENTCONTROLLER_H
#define NETEVENTCONTROLLER_H

namespace EDM { namespace Model {
	class Actor;
	struct Cell;
}}

using namespace EDM::Model;

namespace EDM { namespace Logic {

	class NetEventController
	{
	public:		
		static void FindStartTimesForActors();
		static void FindNearestEventForActor(int actorInd);

	private:
		static EventArgs* ArgsInCollisionWithCellBound(int actorInd);
		static EventArgs* ArgsInCollisionWithBoundInCell(int actorInd);
		static EventArgs* ArgsInCollisionWithActor(int actorInd);
		static EventArgs* PartnerArgsInActorsCollisionEvent(int actorInd);

		static void FindNeighbourCells(const Actor *actor, int &iMin, int &iMax, int &jMin, int &jMax);
		static void CheckNeighbourCells(int actorInd, int &iMin, int &iMax, int &jMin, 
			int &jMax, double & tMin, int &minNghbrActInd);
		static void CheckActorsInCell(const Cell &cell, int actorInd, double &tMin, int &minNghbrActInd);

		static double TimeToCollisionBwActors(int firstInd, int secondInd);

		static void SetNewEvent(int actorInd, EventArgs &args, DelegateT *del);
	};
}}

#endif