#pragma once
#include <BWAPI.h>

class BuildingConstruction
{
public:
	static int BuildingConstruction::barrackCount;
	static int BuildingConstruction::expansionCount;
	static void BuildingConstruction::buildCenter(BWAPI::Unit base);
	static void BuildingConstruction::buildSupply(BWAPI::Unit base);
	static void BuildingConstruction::buildGas(BWAPI::Unit base);
	static void BuildingConstruction::buildBarracks(BWAPI::Unit base);
	static void BuildingConstruction::buildGateway(BWAPI::Unit base);
	static void BuildingConstruction::buildSpawningPool(BWAPI::Unit base);
};