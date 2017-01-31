#include "UnitAction.h"

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