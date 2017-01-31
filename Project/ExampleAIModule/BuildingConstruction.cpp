#include <iostream>
#include "BuildingConstruction.h"

using namespace BWAPI;
using namespace Filter;


/*
Input: Resource depot.
Process: Uses type of resource depot to determine race. Selects a worker to perform construction of supply structure.
Output: None.
*/
void BuildingConstruction::buildSupply(BWAPI::Unit base)
{
	/*
	/ We can create an error handling function for this if we decide it is necessary
	/
	Position pos = base->getPosition();
	Error lastErr = Broodwar->getLastError();
	Broodwar->registerEvent([pos, lastErr](Game*) { Broodwar->drawTextMap(pos, "%c%s", Text::White, lastErr.c_str()); },   // action
		nullptr,    // condition
		Broodwar->getLatencyFrames());  // frames to run
	static int lastChecked = 0;

	// If we are supply blocked and haven't tried constructing more recently
	if (lastErr == Errors::Insufficient_Supply &&
		lastChecked + 100 < Broodwar->getFrameCount() &&
		Broodwar->self()->incompleteUnitCount(supplyProviderType) == 0)
	{
		lastChecked = Broodwar->getFrameCount();
		*/

	// Retrieve a unit that is capable of constructing the supply needed
	UnitType supplyProviderType = base->getType().getRace().getSupplyProvider();
	Unit supplyBuilder = base->getClosestUnit(GetType == supplyProviderType.whatBuilds().first && (IsIdle || IsGatheringMinerals) && IsOwned);

		// If a unit was found
	
	if (supplyBuilder)
	{
		if (supplyProviderType.isBuilding())
		{
			TilePosition targetBuildLocation = Broodwar->getBuildLocation(supplyProviderType, supplyBuilder->getTilePosition());
			if (targetBuildLocation)
			{
				// Register an event that draws the target build location
				Broodwar->registerEvent([targetBuildLocation, supplyProviderType](Game*)
				{
					Broodwar->drawBoxMap(Position(targetBuildLocation), Position(targetBuildLocation + supplyProviderType.tileSize()), Colors::Blue);
				},
				nullptr,  // condition
				supplyProviderType.buildTime() + 100);  // frames to run

			// Order the builder to construct the supply structure
			supplyBuilder->build(supplyProviderType, targetBuildLocation);
		}
		}
		else
		{
		// Train the supply provider (Overlord) if the provider is not a structure
		supplyBuilder->train(supplyProviderType);
		}
	}
}

/*
Input: Resource depot.
Process: Uses type of resource depot to determine race. Selects a worker to perform construction of gas structure.
Output: None.
*/
void BuildingConstruction::buildGas(BWAPI::Unit base)
{
	/*
	/ We can create an error handling function for this if we decide it is necessary
	/
	Position pos = base->getPosition();
	Error lastErr = Broodwar->getLastError();
	Broodwar->registerEvent([pos, lastErr](Game*) { Broodwar->drawTextMap(pos, "%c%s", Text::White, lastErr.c_str()); },   // action
	nullptr,    // condition
	Broodwar->getLatencyFrames());  // frames to run
	static int lastChecked = 0;

	// If we are supply blocked and haven't tried constructing more recently
	if (lastErr == Errors::Insufficient_Supply &&
	lastChecked + 100 < Broodwar->getFrameCount() &&
	Broodwar->self()->incompleteUnitCount(supplyProviderType) == 0)
	{
	lastChecked = Broodwar->getFrameCount();
	*/

	// Retrieve a unit that is capable of constructing the supply needed
	UnitType gasProviderType = base->getType().getRace().getRefinery();
	Unit gasBuilder = base->getClosestUnit(GetType == gasProviderType.whatBuilds().first && (IsIdle || IsGatheringMinerals) && IsOwned);

	// If a unit was found

	if (gasBuilder)
	{
		if (gasProviderType.isBuilding())
		{
			TilePosition targetBuildLocation = Broodwar->getBuildLocation(gasProviderType, gasBuilder->getTilePosition());
			if (targetBuildLocation)
			{
				// Register an event that draws the target build location
				Broodwar->registerEvent([targetBuildLocation, gasProviderType](Game*)
				{
					Broodwar->drawBoxMap(Position(targetBuildLocation), Position(targetBuildLocation + gasProviderType.tileSize()), Colors::Blue);
				},
					nullptr,  // condition
					gasProviderType.buildTime() + 100);  // frames to run

															// Order the builder to construct the supply structure
				gasBuilder->build(gasProviderType, targetBuildLocation);
			}
		}
		else
		{
			// Train the supply provider (Overlord) if the provider is not a structure
			gasBuilder->train(gasProviderType);
		}
	}
}

/*
Input: Resource depot.
Process: Build barracks based on the type of resource depot input.
Output: None.
*/
void BuildingConstruction::buildBarracks(BWAPI::Unit base)
{
	UnitType barracksType = UnitTypes::Terran_Barracks;
	Unit barracksBuilder = base->getClosestUnit(GetType == barracksType.whatBuilds().first && (IsIdle || IsGatheringMinerals) && IsOwned);

	if (barracksBuilder)
	{
		if (barracksType.isBuilding())
		{
			TilePosition targetBuildLocation = Broodwar->getBuildLocation(barracksType, barracksBuilder->getTilePosition());
			if (targetBuildLocation)
			{
				// Register an event that draws the target build location
				Broodwar->registerEvent([targetBuildLocation, barracksType](Game*)
				{
					Broodwar->drawBoxMap(Position(targetBuildLocation), Position(targetBuildLocation + barracksType.tileSize()), Colors::Blue);
				},
					nullptr,  // condition
					barracksType.buildTime() + 100);  // frames to run

														 // Order the builder to construct the supply structure
				barracksBuilder->build(barracksType, targetBuildLocation);
			}
		}
		else
		{
			// Train the supply provider (Overlord) if the provider is not a structure
			barracksBuilder->train(barracksType);
		}
	}
}