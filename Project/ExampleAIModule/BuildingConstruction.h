#pragma once
#include <BWAPI.h>
#include "PlayerInfo.h"

class BuildingConstruction
{
public:
	static void BuildingConstruction::buildCenter(BWAPI::Unit base, BWAPI::TilePosition buildLocation, PlayerInfo* player);
	static void BuildingConstruction::buildSupply(BWAPI::Unit base, PlayerInfo* player);
	static void BuildingConstruction::buildGas(BWAPI::Unit base, PlayerInfo* player);
	static void BuildingConstruction::buildBarracks(BWAPI::Unit base, PlayerInfo* player);
	static void BuildingConstruction::buildGateway(BWAPI::Unit base, PlayerInfo* player);
	static void BuildingConstruction::buildSpawningPool(BWAPI::Unit base, PlayerInfo* player);
	static bool BuildingConstruction::checkConstructionStarted(PlayerInfo* player);
};