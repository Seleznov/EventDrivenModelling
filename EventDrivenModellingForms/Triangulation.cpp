#include "Triangulation.h"

using namespace EDM::Model;

Triangulation::Triangulation()
{
}

Triangulation::~Triangulation()
{
	TrianglesT::iterator triangIter;
	for (triangIter = m_triangles.begin(); triangIter != m_triangles.end(); triangIter++)
	{
		delete *triangIter;
	}
	m_triangles.clear();
}