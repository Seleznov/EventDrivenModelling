#pragma once

#include "RefSingleton.h"

namespace EDM 
{
	using namespace System::ComponentModel;

	ref class Properties
	{
	private:
		static Properties^ m_self = nullptr;

		int m_actorsCount;
		float m_actorRadius;
		float m_speedKoef;

		int m_bordersCount;

		int m_xCellsCount;
		int m_yCellsCount;
		int m_actualXCellsCount;
		int m_actualYCellsCount;

		int m_actorsInCell;
		int m_bordersInCell;

		double m_actualTime;
		double m_localTime;
		int m_eventsCounter;
		int m_drawingPeriodInEvents;
		double m_drawingPeriodInSeconds;

		bool m_showCellsGrid;

		double m_eps;

	protected:
		Properties(void);

	public:			
		static property Properties^ Instance { Properties^ get(); };

#pragma region Actors params		

		[CategoryAttribute("Actors params")]
		[DescriptionAttribute("Actors count")]
		property int ActorsCount { int get(); void set(int value); }

		[CategoryAttribute("Actors params")]
		[DescriptionAttribute("Actors radius")]
		property float ActorsRadius { float get(); void set(float value); }

		[CategoryAttribute("Actors params")]
		[DescriptionAttribute("Speed koef")]
		property float SpeedKoef { float get(); void set(float value); }

		[CategoryAttribute("Actors params")]
		[DescriptionAttribute("Actors in cell")]
		property int ActorsInCell { int get(); void set(int value); }

#pragma endregion Actors params

#pragma  region Borders params

		[CategoryAttribute("Borders params")]
		property int BordersCount { int get(); void set(int value); }

		[CategoryAttribute("Borders params")]
		property int BordersInCell { int get(); void set(int value); }

#pragma  endregion Borders params

#pragma region Cells params

		[CategoryAttribute("Cells params")]
		property int xCellsCount { int get(); void set(int value); }

		[CategoryAttribute("Cells params")]
		property int yCellsCount { int get(); void set(int value); }

		[BrowsableAttribute(false)]
		property int ActualXCellsCount { int get(); }

		[BrowsableAttribute(false)]
		property int ActualYCellsCount { int get(); }

#pragma  endregion Cells params

#pragma region Time_n_events params

		[BrowsableAttribute(false)]
		property double ActualTime { double get(); void set(double value); }

		[BrowsableAttribute(false)]
		property double LocalTime {	double get(); void set(double value); }

		[BrowsableAttribute(false)]
		property int EventsCounter { int get(); void set(int value); }

		[CategoryAttribute("Time and events params")]
		property int DrawingPeriodInEvents{ int get(); void set(int value); }

		[CategoryAttribute("Time and events params")]
		property double DrawingPeriodInSeconds{ double get(); void set(double value); }

#pragma endregion Time_n_events params

#pragma region View params

		[BrowsableAttribute(false)]
		property bool ShowCellsGrid { bool get(); void set(bool value); }

#pragma endregion View params

		[BrowsableAttribute(true)]
		[CategoryAttribute("Others")]
		property double Eps { double get(); void set(double value); }

	};

	#define EDM_Prop Properties::Instance
}