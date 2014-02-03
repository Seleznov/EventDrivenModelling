#pragma once
#ifndef TRIANGULATION_H
#define TRIANGULATION_H

#include "Singleton.h"
#include <list>

using namespace std;

namespace EDM { namespace Model
{
	class Triangle;

	typedef list<Triangle*> TrianglesT;

	class Triangulation : public Singleton<Triangulation>
	{
	protected:
		Triangulation();
		~Triangulation();
		friend class Singleton<Triangulation>;
	public:
		TrianglesT m_triangles;
	};
}}

#endif