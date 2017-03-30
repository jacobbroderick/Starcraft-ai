#pragma once
#include <BWAPI.h>
#include <BWTA.h>
#include <deque>
#include "ResourceGathering.h"
#include "PlayerInfo.h"

class UnitAction
{
public:
	static bool checkUnitState(BWAPI::Unit unit);
	static void trainMarines(BWAPI::Unit unit, PlayerInfo* player);
	static void selectArmy();
	static void scoutStartLocations(BWAPI::Unit unit);
};