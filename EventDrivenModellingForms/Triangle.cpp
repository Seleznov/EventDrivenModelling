#include "Triangle.h"

using namespace EDM::Model;

Triangle::Triangle()
{
	m_edges.resize(3, nullptr);
}

Triangle::Triangle(TriangEdge *first, TriangEdge *second, TriangEdge *third)
{
	m_edges.reserve(3);
	m_edges.push_back(first);
	m_edges.push_back(second);
	m_edges.push_back(third);
}

Triangle::~Triangle()
{
	m_edges.clear();
}
