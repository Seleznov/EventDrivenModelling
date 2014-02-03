#pragma once
#ifndef GLOBAL_H
#define GLOBAL_H

#pragma region Global vars

extern int actorsCount;
extern float actorRadius;
extern float speedKoef;

extern int bordersCount;

extern int xCellsCount;
extern int yCellsCount;
extern int actualXCellsCount;
extern int actualYCellsCount;
extern double xCellSize;
extern double yCellSize;

extern int actorsInCell;
extern int bordersInCell;

extern double localTime;
extern int eventsCounter;
extern int drawingPeriodInEvents;
extern int eventsCountSinceLastDrawing;
#pragma endregion Global vars

#endif