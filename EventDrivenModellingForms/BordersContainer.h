#pragma once
#ifndef BORDERSCONTAINER_H
#define BORDERSCONTAINER_H

#include "Singleton.h"
#include <vector>

using namespace std;

namespace EDM { namespace Model 
{
	struct Border;

	typedef vector<Border> BordersT;

	class BordersContainer : public Singleton<BordersContainer>
	{
	protected:
		BordersContainer();
		~BordersContainer();
		friend class Singleton<BordersContainer>;
	public:
		BordersT borders;
	};
}}

#endif