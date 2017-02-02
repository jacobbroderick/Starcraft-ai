#include <iostream>
#include "ResourceGathering.h"

using namespace BWAPI;
using namespace Filter;

/*
Input: Resource depot.
Process: If the resource depot is idle and fails to construct a worker more supply will be built. 
 Also, if supply is within 4 of the maximum supply, the AI has enough minerals, and it is more than 3 minutes into the game, then more supply will be built.
Output: None.
*/
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

/*
Input: Resource depot.
Process: Uses type of resource depot to determine race. Selects a worker to perform construction of supply structure.
Output: None.
*/
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
				else{
					ResourceGathering::currentMineralGatherers += 1;
				}
			}
		} // closure: has no powerup
	} // closure: if idle
}

/*
Input: Worker.
Process: Commands the worker to gather gas.
Output: None.
*/
bool ResourceGathering::gatherGas(BWAPI::Unit worker)
{
	if (!worker->gather(worker->getClosestUnit(IsRefinery)))
		return false;
	else
		return true;
}

/*
Input: Worker.
Process: Commands the worker to gather minerals.
Output: Returns true if the worker the worker is correctly directed to gather minerals and false otherwise.
*/
bool ResourceGathering::gatherMinerals(BWAPI::Unit worker)
{
	if (!worker->gather(worker->getClosestUnit(IsMineralField)))
		return false;
	else
		return true;
}

/*
Input: None.
Process: None.
Output: Current mineral count for the AI.
*/
int ResourceGathering::getMineralCount()
{
	return Broodwar->self()->minerals();
}

/*
Input: None.
Process: None.
Output: Current gas count for the AI.
*/
int ResourceGathering::getGasCount()
{
	return Broodwar->self()->gas();
}

