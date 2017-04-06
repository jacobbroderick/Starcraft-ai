#include "ScoutManager.h"

/*
Input: N/A.
Process: Constructor.
Output: Reference to ScoutManager object.
*/
ScoutManager::ScoutManager()
{
	unitScouting = false;
	scoutingUnit = NULL;
}

/*
Input: Scout unit.
Process: Checks all possible base starting locations starting with furthest first.
Output: Reference to the scout.
*/
void ScoutManager::scoutStartLocations(BWAPI::Unit unit)
{
	std::deque <BWAPI::TilePosition> sortedStartLocations;
	std::deque <long double> distances;

	for (BWTA::BaseLocation *currBase : BWTA::getBaseLocations())
	{
		//Check if the base has gas, if it doesn't, it cannot be a starting location.
		if (!currBase->isMineralOnly() && currBase != BWTA::getStartLocation(BWAPI::Broodwar->self()) /*&& (Broodwar->isWalkable(currBase->getTilePosition().x, currBase->getTilePosition().y)*/)
		{
			long double currDistanceFromScout = unit->getTilePosition().getDistance(currBase->getTilePosition());
			sortedStartLocations.push_front(currBase->getTilePosition());
			distances.push_front(currDistanceFromScout);


			//Eventually change this to go to the bases closes to the corners of the map. Usually maps are designed to have start locations there.
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

	//Sends the unit to explore the possible bases but adds them to a queue of locations to visit.
	for (unsigned int i = 0; i < sortedStartLocations.size(); i++)
	{
		Broodwar->printf("i: %d.", i);
		if (i == 0)
			unit->move(BWAPI::Position(sortedStartLocations[i]));
		else
			unit->move(BWAPI::Position(sortedStartLocations[i]), true);
	}
}

/*
Input: Scout unit and target to attack.
Process: Attacks the target with scouting unit.
OutputN/A.
*/
void ScoutManager::attackTarget(BWAPI::Unit unit, BWAPI::Unit target) 
{

}