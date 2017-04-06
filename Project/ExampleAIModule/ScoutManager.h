#pragma once
#include <BWAPI.h>
#include <BWTA.h>

using namespace BWAPI;

class ScoutManager
{
public:
	bool unitScouting;
	BWAPI::Unit scoutingUnit;
	ScoutManager::ScoutManager();
	static void ScoutManager::scoutStartLocations(BWAPI::Unit unit);
	static void ScoutManager::attackTarget(BWAPI::Unit unit, BWAPI::Unit target);
};