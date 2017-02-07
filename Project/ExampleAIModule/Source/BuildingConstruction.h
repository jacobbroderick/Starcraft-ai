#pragma once
#include <BWAPI.h>

class BuildingConstruction
{
public:
	static void buildCenter(BWAPI::Unit base, BWAPI::TilePosition buildLocation);
	static void buildSupply(BWAPI::Unit base);
	static void buildGas(BWAPI::Unit base);
	static void buildBarracks(BWAPI::Unit base);
	static void buildGateway(BWAPI::Unit base);
	static void buildSpawningPool(BWAPI::Unit base);
};