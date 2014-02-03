#include "EDM_Rect.h"
#include "EdgeIndexer.h"
#include "TriangNode.h"
#include "TriangNodesContainer.h"
#include "TriangNodesGenerator.h"
#include "Triangulator.h"
#include "Properties.h"

#include <algorithm>
using namespace std;

using namespace EDM::Logic::Generators;
using namespace EDM::Model;
using namespace EDM::Logic;

TriangNodesContainer::TriangNodesContainer()
{
	//////////////////////////////////////////////////////////////////////////
	// Generator is not works, need more debug

	/*EDM_Rect coordBoundRect = EDM_Rect(1.0f, 1.0f, EDM_Prop->xCellsCount - 1, EDM_Prop->yCellsCount - 1);
	EDM_Rect velocityBoundEDM_Rect = EDM_Rect(
	-EDM_Prop->SpeedKoef, -EDM_Prop->SpeedKoef, 
	EDM_Prop->SpeedKoef, EDM_Prop->SpeedKoef);
	m_nodes = *TriangNodesGenerator::GenerateNodes(
	EDM_Prop->ActorsCount - 4, coordBoundRect, 
	velocityBoundEDM_Rect, EDM_Prop->ActorsRadius);*/

	// Generator
	//////////////////////////////////////////////////////////////////////////

	TriangNode *a0 = new TriangNode(CoordT(1.0f, 1.0f), Vector2fT(0.0f, 0.0f), EDM_Prop->ActorsRadius, STATIC_POINT_MASSA);
	TriangNode *a1 = new TriangNode(CoordT(9.0f, 1.0f), Vector2fT(0.0f, 0.0f), EDM_Prop->ActorsRadius, STATIC_POINT_MASSA);
	TriangNode *a2 = new TriangNode(CoordT(9.0f, 9.0f), Vector2fT(0.0f, 0.0f), EDM_Prop->ActorsRadius, STATIC_POINT_MASSA);
	TriangNode *a3 = new TriangNode(CoordT(1.0f, 9.0f), Vector2fT(0.0f, 0.0f), EDM_Prop->ActorsRadius, STATIC_POINT_MASSA);
	TriangNode *a4 = new TriangNode(CoordT(4, 5), Vector2fT(0, -EDM_Prop->SpeedKoef), EDM_Prop->ActorsRadius);
	TriangNode *a5 = new TriangNode(CoordT(6, 5), Vector2fT(0, -EDM_Prop->SpeedKoef), EDM_Prop->ActorsRadius);
	
	m_nodes.push_back(*a0);
	m_nodes.push_back(*a1);
	m_nodes.push_back(*a2);
	m_nodes.push_back(*a3);
	m_nodes.push_back(*a4);
	m_nodes.push_back(*a5);
}

TriangNodesContainer::~TriangNodesContainer()
{
	m_nodes.clear();
}

void TriangNodesContainer::Sort()
{
	std::sort(m_nodes.begin(),m_nodes.end(), TriangNode::CompareByAscendingX);
}