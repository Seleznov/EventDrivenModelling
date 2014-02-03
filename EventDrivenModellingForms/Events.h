#pragma once
#ifndef EVENTS_H
#define EVENTS_H

#include <float.h>

namespace EDM { namespace Model {
	//class Actor;
}}

using namespace EDM::Model;

namespace EDM { namespace Logic 
{
	template<class SenderT, class ArgsT>
	struct Delegate
	{		
		typedef void (*delegateFunc)(SenderT, const ArgsT&);

		Delegate(delegateFunc _funcPtr)
		{
			funcPtr = _funcPtr; 
		}

		~Delegate() {}

		bool operator==(Delegate<SenderT, ArgsT> other)
		{
			return funcPtr == other.funcPtr;
		}

		delegateFunc funcPtr;
	};

	struct EventArgs
	{
		double time;
		double localTime;
		int next;

		EventArgs()
		{
			this->time = DBL_MAX;
			this->localTime = 0;
			this->next = -1;
		}

		EventArgs(double inTime, double inLocalTime, int next)
		{
			this->time = inTime;
			this->localTime = inLocalTime;
			this->next = next;
		}
	};

	template<class SenderT, class ArgsT>
	class Event
	{
		typedef Delegate<SenderT, ArgsT> DelegateT;

	public:
		SenderT sender;
		ArgsT *args;
		DelegateT *handler;

		Event();
		Event(SenderT inSender, ArgsT &inArgs, DelegateT *handler);
		void OnHandler();
		~Event();
	};

	typedef Event<int, EventArgs> EventT;
	typedef Delegate<int, EventArgs> DelegateT;
}}

#endif