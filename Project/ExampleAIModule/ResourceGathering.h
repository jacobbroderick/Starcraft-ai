#pragma once
#include <BWAPI.h>
#include "BuildingConstruction.h"

class ResourceGathering
{
	public:
		//these values are placeholders
		int optimumMineralGatherers = 13;
		int optimumGasGatherers = 3;
		int currentMineralGatherers = 0;
		int currentGasGatherers = 0;
		static void ResourceGathering::buildWorker(BWAPI::Unit base);
		static void ResourceGathering::workerGather(BWAPI::Unit worker);
		static bool ResourceGathering::gatherGas(BWAPI::Unit worker);
		static bool ResourceGathering::gatherMinerals(BWAPI::Unit worker);
		static int ResourceGathering::getMineralCount();
		static int ResourceGathering::getGasCount();
};