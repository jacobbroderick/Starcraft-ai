#pragma once
#include <BWAPI.h>

class BuildingConstruction
{
public:
	int expansionCount = 0;
	static void BuildingConstruction::buildSupply(BWAPI::Unit base);
	static void BuildingConstruction::buildGas(BWAPI::Unit base);
	static void BuildingConstruction::buildBarracks(BWAPI::Unit base);
	static void BuildingConstruction::buildGateway(BWAPI::Unit base);
	static void BuildingConstruction::buildHatchery(BWAPI::Unit base);
};