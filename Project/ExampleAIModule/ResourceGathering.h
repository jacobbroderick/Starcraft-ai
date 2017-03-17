#pragma once
#include <BWAPI.h>
#include "BuildingConstruction.h"
#include "PlayerInfo.h"

using namespace BWAPI;

class ResourceGathering
{
	public:
		int optimumMineralGatherers;
		int optimumGasGatherers;
		int currentMineralGatherers;
		int currentGasGatherers;
		ResourceGathering();
		static void buildWorker(Unit base, PlayerInfo* player);
		static void workerGather(Unit worker);
		static bool gatherGas(Unit worker);
		static bool gatherMinerals(Unit worker);
		static int getMineralCount();
		static int getGasCount();
};