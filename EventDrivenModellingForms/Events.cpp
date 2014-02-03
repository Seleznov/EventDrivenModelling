#include "Actor.h"
#include "Events.h"

using namespace EDM::Model;
using namespace EDM::Logic;

template Event<int, EventArgs>::Event();
template<class SenderT, class ArgsT>
Event<SenderT, ArgsT>::Event()
{
	this->sender = -1;
	this->args = new EventArgs();
	this->handler = nullptr;
}

template Event<int, EventArgs>::Event(int inSender, EventArgs &inArgs, DelegateT *handler);
template<class SenderT, class ArgsT>
Event<SenderT, ArgsT>::Event(SenderT inSender, ArgsT &inArgs, DelegateT *handler)
{
	this->sender = inSender;
	this->args = &inArgs;
	this->handler = handler;
}

template void Event<int, EventArgs>::OnHandler();
template<class SenderT, class ArgsT>
void Event<SenderT, ArgsT>::OnHandler()
{
	if (this->handler != nullptr)
	{
		this->handler->funcPtr(this->sender, *this->args);
	}
}

template Event<int, EventArgs>::~Event();
template<class SenderT, class ArgsT>
Event<SenderT, ArgsT>::~Event()
{
	//delete this->args;
	//delete this->handler;
}