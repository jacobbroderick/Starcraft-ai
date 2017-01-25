#include "ResourceGathering.h"
#include <iostream>

using namespace BWAPI;
using namespace Filter;


	void ResourceGathering::buildWorker(BWAPI::Unit base)
	{
		//Get mineral count
		if (getMineralCount() > 50)
		{
			if (base->canTrain(BWAPI::UnitTypes::Terran_SCV))
				base->train(BWAPI::UnitTypes::Terran_SCV);
		}
	}

	void ResourceGathering::workerGather(BWAPI::Unit worker)
	{
		// if our worker is idle
		if (worker->isIdle())
		{
			// Order workers carrying a resource to return them to the center, otherwise find a mineral patch to harvest.
			if (worker->isCarryingGas() || worker->isCarryingMinerals())
			{
				worker->returnCargo();
			}
			else if (!worker->getPowerUp())  // The worker cannot harvest anything if it is carrying a powerup such as a flag Harvest from the nearest mineral patch or gas refinery
			{                              
				if (getMineralCount() < 400 && (Broodwar->elapsedTime() > 300))
				{
					if (gatherMinerals(worker))
					{
						// If the call fails, then print the last error message
						Broodwar << Broodwar->getLastError() << std::endl;
					}
				}

			} // closure: has no powerup
		} // closure: if idle
	}

	bool ResourceGathering::gatherGas(BWAPI::Unit worker)
	{
		if (!worker->gather(worker->getClosestUnit(IsRefinery)))
			return false;
		else
			return true;
	}

	bool ResourceGathering::gatherMinerals(BWAPI::Unit worker)
	{
		if (!worker->gather(worker->getClosestUnit(IsMineralField)))
			return false;
		else
			return true;
	}

	int ResourceGathering::getMineralCount()
	{
		return Broodwar->self()->minerals();
	}

