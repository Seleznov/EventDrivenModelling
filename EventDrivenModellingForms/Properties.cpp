#include "Properties.h"

using namespace EDM;

Properties::Properties(void)
{
	m_actorsCount = 6;
	m_actorRadius = 0.4f;
	m_speedKoef = 3.0f;
	m_actorsInCell = 50;

	m_xCellsCount = 10;
	m_yCellsCount = 10;
	m_actualXCellsCount = m_xCellsCount + 2;
	m_actualYCellsCount = m_yCellsCount + 2;
	//m_xCellSize = 1.0;
	//m_yCellSize = 1.0;

	m_bordersCount = 0;
	m_bordersInCell = 16;

	m_actualTime = 0.0;
	m_localTime = 0.0;
	m_eventsCounter = 0;
	m_drawingPeriodInEvents = 5;
	m_drawingPeriodInSeconds = 0.032;
	//m_eventsCountSinceLastDrawing = 0;

	m_showCellsGrid = true;

// 	m_isNetMethod = false;
// 	m_isTriangMethod = true;

	m_eps = 1e-5;
}

Properties^ Properties::Instance::get()
{
	if (m_self == nullptr)
	{
		m_self = gcnew Properties();
	}
	return m_self;
}

#pragma region Actors params

int Properties::ActorsCount::get() { return m_actorsCount; }
void Properties::ActorsCount::set(int value) { m_actorsCount = value; }

float Properties::ActorsRadius::get() {return m_actorRadius; }
void Properties::ActorsRadius::set(float value) { m_actorRadius = value; }

float Properties::SpeedKoef::get() {return m_speedKoef; }
void Properties::SpeedKoef::set(float value) { m_speedKoef = value; }

int Properties::ActorsInCell::get() { return m_actorsInCell; }
void Properties::ActorsInCell::set(int value) { m_actorsInCell = value; }

#pragma endregion Actors params

#pragma  region Borders params

int Properties::BordersCount::get() { return m_bordersCount; }
void Properties::BordersCount::set(int value) { m_bordersCount = value; }

int Properties::BordersInCell::get() { return m_bordersInCell; }
void Properties::BordersInCell::set(int value) { m_bordersInCell = value; }

#pragma  endregion Borders params

#pragma region Cells params

int Properties::xCellsCount::get() { return m_xCellsCount; }
void Properties::xCellsCount::set(int value) 
{ m_xCellsCount = value; m_actualXCellsCount = value + 2; }

int Properties::yCellsCount::get() { return m_yCellsCount; }
void Properties::yCellsCount::set(int value) 
{ m_yCellsCount = value; m_actualYCellsCount = value + 2; }

int Properties::ActualXCellsCount::get() { return m_actualXCellsCount; }
int Properties::ActualYCellsCount::get() { return m_actualYCellsCount; }

//double Properties::xCellSize::get() { return m_xCellSize; }
//double Properties::yCellSize::get() { return m_yCellSize; }

#pragma endregion Cells params

#pragma region Time'n'events params

double Properties::ActualTime::get() { return m_actualTime; }
void Properties::ActualTime::set(double value) { m_actualTime = value; }

double Properties::LocalTime::get() { return m_localTime; }
void Properties::LocalTime::set(double value) { m_localTime = value; }

int Properties::EventsCounter::get() { return m_eventsCounter; }
void Properties::EventsCounter::set(int value) { m_eventsCounter = value; }

int Properties::DrawingPeriodInEvents::get() { return m_drawingPeriodInEvents; }
void Properties::DrawingPeriodInEvents::set(int value) { m_drawingPeriodInEvents = value; }

double Properties::DrawingPeriodInSeconds::get() { return m_drawingPeriodInSeconds; }
void Properties::DrawingPeriodInSeconds::set(double value) { m_drawingPeriodInSeconds = value; }

//int Properties::EventsCountSinceLastDrawing::get() { return m_eventsCountSinceLastDrawing; }
//void Properties::EventsCountSinceLastDrawing::set(int value) { m_eventsCountSinceLastDrawing = value; }

#pragma endregion Time'n'events params

#pragma region View params

bool Properties::ShowCellsGrid::get() { return m_showCellsGrid; }
void Properties::ShowCellsGrid::set(bool value) { m_showCellsGrid = value; }

#pragma endregion View params

//////////////////////////////////////////////////////////////////////////

double Properties::Eps::get() { return m_eps; }
void Properties::Eps::set(double value) { m_eps = value; }

//bool Properties::IsNetMethod::get() { return m_isNetMethod; }
//void Properties::IsNetMethod::set(bool value) { m_isNetMethod = value; }
//
//bool Properties::IsTriangMethod::get() { return m_isTriangMethod; }
//void Properties::IsTriangMethod::set(bool value) { m_isTriangMethod = value; }