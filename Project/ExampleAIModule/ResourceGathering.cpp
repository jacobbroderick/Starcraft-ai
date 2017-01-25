#include <iostream>
#include "ResourceGathering.h"

using namespace BWAPI;
using namespace Filter;

	void ResourceGathering::buildWorker(BWAPI::Unit base)
	{
		
		//Get mineral count
		if (getMineralCount() >= 50)
		{
			//If the base is not building anything AND the attempt to build a worker fails 
			//OR
			//the supply used is marginally close to the supply total AND can afford to increase supply AND 3 minutes into game
			if (base->isIdle() && !base->train(base->getType().getRace().getWorker() || ((Broodwar->self()->supplyUsed() + 4 >= Broodwar->self()->supplyTotal()) && getMineralCount() > 100) && (Broodwar->elapsedTime() < 180)))
			{
				// If that fails, draw the error at the location so that you can visibly see what went wrong!
				// However, drawing the error once will only appear for a single frame
				// so create an event that keeps it on the screen for some frames
				BuildingConstruction::buildSupply(base);
			}
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
				if (getMineralCount() < 400 && (Broodwar->elapsedTime() < 300))
				{
					if (gatherMinerals(worker))
					{
						//Eventually create a class to handle these errors
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

	int ResourceGathering::getGasCount()
	{
		return Broodwar->self()->gas();
	}

