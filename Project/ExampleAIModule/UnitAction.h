#pragma once
#include <BWAPI.h>
#include "ResourceGathering.h"

class UnitAction
{
public:
	static bool checkUnitState(BWAPI::Unit unit);
	static void trainMarines(BWAPI::Unit unit);
	static void selectArmy();
};