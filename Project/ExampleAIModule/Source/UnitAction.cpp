#include "UnitAction.h"

/*
Called on every unit before being used.
Input: Unit being validated.
Process: 
Output: True if unit is not dead, being constructed, disabled
*/
bool UnitAction::checkUnitState(BWAPI::Unit unit)
{
	// Ignore the unit if it no longer exists
	// Make sure to include this block when handling any Unit pointer!
	if (!unit->exists())
		continue;

	// Ignore the unit if it has one of the following status ailments
	if (unit->isLockedDown() || unit->isMaelstrommed() || unit->isStasised())
		continue;

	// Ignore the unit if it is in one of the following states
	if (unit->isLoaded() || !unit->isPowered() || unit->isStuck())
		continue;

	// Ignore the unit if it is incomplete or busy constructing
	if (!unit->isCompleted() || unit->isConstructing())
		continue;
}