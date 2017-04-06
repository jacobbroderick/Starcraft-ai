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

