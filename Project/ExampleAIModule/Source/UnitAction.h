#pragma once
#include <BWAPI.h>
#include "ResourceGathering.h"

class UnitAction
{
public:
	static bool UnitAction::checkUnitState(BWAPI::Unit unit);
	static void UnitAction::trainMarines(BWAPI::Unit unit);
	static void UnitAction::selectArmy();
};