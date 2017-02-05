#pragma once
#include <BWAPI.h>
#include "BuildingConstruction.h"

class ResourceGathering
{
	public:
		int optimumMineralGatherers;
		int optimumGasGatherers;
		int currentMineralGatherers;
		int currentGasGatherers;
		ResourceGathering::ResourceGathering();
		static void ResourceGathering::buildWorker(BWAPI::Unit base);
		static void ResourceGathering::workerGather(BWAPI::Unit worker);
		static bool ResourceGathering::gatherGas(BWAPI::Unit worker);
		static bool ResourceGathering::gatherMinerals(BWAPI::Unit worker);
		static int ResourceGathering::getMineralCount();
		static int ResourceGathering::getGasCount();
};