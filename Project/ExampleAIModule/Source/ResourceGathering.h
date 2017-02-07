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
		ResourceGathering();
		static void buildWorker(BWAPI::Unit base);
		static void workerGather(BWAPI::Unit worker);
		static bool gatherGas(BWAPI::Unit worker);
		static bool gatherMinerals(BWAPI::Unit worker);
		static int getMineralCount();
		static int getGasCount();
};