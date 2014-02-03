#pragma once
#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <vector>
#include "Singleton.h"
//#include "Global.h"

namespace EDM { namespace Model 
{
class Actor;
}}

using namespace EDM::Model;

namespace EDM { namespace Logic {
	
	typedef vector<int> HeapTreeT;

	class PriorityQueue : public Singleton<PriorityQueue>
	{

#pragma region Constructors

	protected:
		PriorityQueue();
		~PriorityQueue();
		friend class Singleton<PriorityQueue>;

#pragma endregion Constructors

#pragma region Fields

	private:
		HeapTreeT *m_heapTree;
		int m_startInd;

#pragma endregion Fields

#pragma region Methods

	private:
		int CalcActualActorsCount(int actorsCount) const;
		void AddMissingActors(int actualActorsCount) const;
		void AddMissingNodes(int actualActorsCount) const;
		inline int CalcHeapTreeSize(int startInd, int actualActorsCount) const;
		inline int CalcStartInd(int actualActorsCount) const;
		void InitHeapTree(int actualHeapSize);

		void FillHeapTree();
		void FillBottomHeapTreeTier();
		void ChangeHeap(int lChInd, int rChInd);
				
	public:
		void ChangeHeapTree(int changedActorInd);
		inline int GetFirst() const;
		//void PlayEventsForEventsCount();
		void PlayNetEventsForTime();
		void PlayTriangEventsForTime();
		
#pragma endregion Methods
	};

	int PriorityQueue::GetFirst() const
	{
		return (*m_heapTree)[0];
	}
}}

#endif