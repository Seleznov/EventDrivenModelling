#pragma once
#ifndef FLOAT_GENERATOR_H
#define FLOAT_GENERATOR_H

#include <stdlib.h>
#include <time.h>

namespace EDM { namespace EDM_Graphics { 	namespace Generators {

	class FloatGenerator
	{
	public:
		static float Generate(float min, float max)
		{
			float randFloat = (float)rand()/RAND_MAX;
			float randFloatInInterval = (max - min) * (randFloat) + min;
			return randFloatInInterval;
		}
	};
}}}

#endif
