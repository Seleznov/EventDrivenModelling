#pragma once
#ifndef ACTORSCONTAINER_H
#define ACTORSCONTAINER_H

#include "Singleton.h"
#include <vector>

namespace EDM { namespace Model 
{
	class Actor;

	typedef vector<Actor> ActorsT;

	class ActorsContainer : public Singleton<ActorsContainer>
	{
	protected:
		ActorsContainer();
		~ActorsContainer();
		friend class Singleton<ActorsContainer>;
	public:
		void AddActorsInCells();
		ActorsT actors;
	};
}}

#endif