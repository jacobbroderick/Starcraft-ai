#include "UnitAction.h"

using namespace BWAPI;

/*
Input: Unit whose state is being validated.
Process: Checks the state of the input unit.
Output: True if unit is not dead, being constructed, disabled
*/
bool UnitAction::checkUnitState(BWAPI::Unit unit)
{
	// Ignore the unit if it no longer exists
	// Make sure to include this block when handling any Unit pointer!
	if (!unit->exists())
		return false;

	// Ignore the unit if it has one of the following status ailments
	if (unit->isLockedDown() || unit->isMaelstrommed() || unit->isStasised())
		return false;

	// Ignore the unit if it is in one of the following states
	if (unit->isLoaded() || !unit->isPowered() || unit->isStuck())
		return false;

	// Ignore the unit if it is incomplete or busy constructing
	if (!unit->isCompleted() || unit->isConstructing())
		return false;

	//Return true if no cases are found true.
	return true;
}
/*
Input: Barracks to train marines.
Process: Starts process to train marines.
Output: N/A
*/
void UnitAction::trainMarines(BWAPI::Unit unit, PlayerInfo* player)
{
	if (ResourceGathering::getMineralCount() + player->buildingMineralsOffset >= 50)
	{	//checks if there is sufficient minerals to train
		//checks if barracks is idle and cannot train marines or if more supply is needed
		if (BWAPI::Broodwar->self()->supplyUsed() <= 400)
		{
			if ((unit->isIdle() && !(unit->train(BWAPI::UnitTypes::Terran_Marine))) || ((BWAPI::Broodwar->self()->supplyUsed() + 4 >= BWAPI::Broodwar->self()->supplyTotal()) && ResourceGathering::getMineralCount() > 100))
			{
				BuildingConstruction::buildSupply(unit, player);
			}
		}
	}
}
/*
Input: N/A
Process: Selects all marines.
Output: N/A
*/
void UnitAction::selectArmy()
{
	for (auto &unit : BWAPI::Broodwar->self()->getUnits())
	{
		if (unit->getType() == BWAPI::UnitTypes::Terran_Marine)
		{
			//send to vector
		}
	}
}

/*
Input: Scout unit.
Process: Checks all possible base starting locations starting with furthest first.
Output: Reference to the scout.
*/
void UnitAction::scoutStartLocations(BWAPI::Unit unit)
{
	std::deque <BWAPI::TilePosition> sortedStartLocations;
	std::deque <long double> distances;

	for (BWTA::BaseLocation *currBase : BWTA::getBaseLocations())
	{
		//Check if the base has gas, if it doesn't, it cannot be a starting location.
		if (currBase->isMineralOnly() && !(currBase == BWTA::getStartLocation(BWAPI::Broodwar->self())) && Broodwar->isWalkable(currBase->getTilePosition().x, currBase->getTilePosition().y))
		{
			long double currDistanceFromScout = unit->getTilePosition().getDistance(currBase->getTilePosition());
			sortedStartLocations.push_front(currBase->getTilePosition());
			distances.push_front(currDistanceFromScout);

			for (unsigned int i = 0; i < distances.size() - 1; i++)
			{
				if (distances[i] < distances[i + 1])
				{
					//Reverse bubble sort distances (shortest in the back).
					long double tempDistance = distances[i];
					distances[i] = distances[i + 1];
					distances[i + 1] = tempDistance;
					//Move TilePositions vector to match the distances vector changes.
					BWAPI::TilePosition tempTilePosition = sortedStartLocations[i];
					sortedStartLocations[i] = sortedStartLocations[i + 1];
					sortedStartLocations[i + 1] = tempTilePosition;
				}
				else
					break;
			}
		}
	}

	//Broodwar->printf("deque size: %d", distances.size());
	//Broodwar->printf("Nearly finished scout function.");
	//Sends the unit to explore furthest possible enemy base location.
	//unit->move(BWAPI::Position(sortedStartLocations[0]).makeValid());

	//Sends the unit to explore the rest of the possible bases but adds them to a deque.
	//If statement catches stange instances when nothing is added to the sortedStartLocations deque. Will do more work to figure this out and clean it up.
	for (unsigned int i = 0; i < sortedStartLocations.size(); i++)
	{	
		if (i == 0)
			unit->move(BWAPI::Position(sortedStartLocations[i].makeValid()));
		else
			unit->move(BWAPI::Position(sortedStartLocations[i].makeValid()), true);
	}
}