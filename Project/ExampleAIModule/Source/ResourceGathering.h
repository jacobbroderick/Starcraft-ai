#pragma once
#include <BWAPI.h>

class ResourceGathering
{
	public:
		static void ResourceGathering::buildWorker(BWAPI::Unit base);
		static void ResourceGathering::workerGather(BWAPI::Unit worker);
		static bool ResourceGathering::gatherGas(BWAPI::Unit worker);
		static bool ResourceGathering::gatherMinerals(BWAPI::Unit worker);
		static int ResourceGathering::getMineralCount();
		
};