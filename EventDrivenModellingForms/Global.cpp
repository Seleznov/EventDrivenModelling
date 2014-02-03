#include <math.h>

using namespace std;

#pragma region Global vars

int actorsCount = 40;
float actorRadius = 0.15f;
float speedKoef = 10.0f;

int xCellsCount = 10;
int yCellsCount = 10;
int actualXCellsCount = xCellsCount + 2;
int actualYCellsCount = yCellsCount + 2;
double xCellSize = 1;
double yCellSize = 1;

int bordersCount = 0;

int actorsInCell = 50;
int bordersInCell = 16;

double localTime = 0;
int eventsCounter = 0;
int drawingPeriodInEvents = 5;
int eventsCountSinceLastDrawing = 0;
#pragma endregion Global vars