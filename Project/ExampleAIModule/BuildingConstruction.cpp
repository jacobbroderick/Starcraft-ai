#include <iostream>
#include "BuildingConstruction.h"

using namespace BWAPI;
using namespace Filter;

/*
Input: Resource depot.
Process: Uses type of resource depot to determine race. Selects a worker to perform construction of an expansion.
Output: None.
*/
void BuildingConstruction::buildCenter(BWAPI::Unit base){

	// Retrieve a unit that is capable of constructing the supply needed
	UnitType centerProviderType = center->getType().getRace().getCenter();
	Unit centerBuilder = center->getClosestUnit(GetType == centerProviderType.whatBuilds().first && (IsIdle || IsGatheringMinerals) && IsOwned);

	// If a unit was found
	if (centerBuilder)
	{
		if (centerProviderType.isBuilding())
		{
			TilePosition targetBuildLocation = Broodwar->getBuildLocation(centerProviderType, centerBuilder->getTilePosition());
			if (targetBuildLocation)
			{
				// Register an event that draws the target build location
				Broodwar->registerEvent([targetBuildLocation, centerProviderType](Game*)
				{
					Broodwar->drawBoxMap(Position(targetBuildLocation), Position(targetBuildLocation + centerProviderType.tileSize()), Colors::Blue);
				},
				nullptr,  // condition
				centerProviderType.buildTime() + 100);  // frames to run

			// Order the builder to construct the supply structure
			centerBuilder->build(centerProviderType, targetBuildLocation);
			BuildingConstruction::expansionCount++;
		}
		}
		else
		{
		// Train the supply provider (Overlord) if the provider is not a structure
		centerBuilder->train(centerProviderType);
		}
	}
}

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
Process: Build Terran Barracks if the input is of Terran type.
Output: None.
*/
void BuildingConstruction::buildBarracks(BWAPI::Unit base)
{
	UnitType terranType = UnitTypes::Terran_Barracks;
	Unit barracksBuilder = base->getClosestUnit(GetType == terranType.whatBuilds().first && (IsIdle || IsGatheringMinerals) && IsOwned);

	if (barracksBuilder)
	{
		if (terranType.isBuilding())
		{
			TilePosition targetBuildLocation = Broodwar->getBuildLocation(terranType, barracksBuilder->getTilePosition());
			if (targetBuildLocation)
			{
				// Register an event that draws the target build location
				Broodwar->registerEvent([targetBuildLocation, terranType](Game*)
				{
					Broodwar->drawBoxMap(Position(targetBuildLocation), Position(targetBuildLocation + terranType.tileSize()), Colors::Blue);
				},
					nullptr,  // condition
					terranType.buildTime() + 100);  // frames to run

														 // Order the builder to construct the supply structure
				barracksBuilder->build(terranType, targetBuildLocation);
			}
		}
		else
		{
			// Train the supply provider (Overlord) if the provider is not a structure
			barracksBuilder->train(terranType);
		}
	}
}

/*
Input: Resource depot.
Process: Build Protoss Gateway if the input is of Protoss type.
Output: None.
*/
void BuildingConstruction::buildGateway(BWAPI::Unit base)
{
	UnitType protossType = UnitTypes::Protoss_Gateway;
	Unit gatewayBuilder = base->getClosestUnit(GetType == protossType.whatBuilds().first && (IsIdle || IsGatheringMinerals) && IsOwned);

	if (gatewayBuilder)
	{
		if (protossType.isBuilding())
		{
			TilePosition targetBuildLocation = Broodwar->getBuildLocation(protossType, gatewayBuilder->getTilePosition());
			if (targetBuildLocation)
			{
				// Register an event that draws the target build location
				Broodwar->registerEvent([targetBuildLocation, protossType](Game*)
				{
					Broodwar->drawBoxMap(Position(targetBuildLocation), Position(targetBuildLocation + protossType.tileSize()), Colors::Blue);
				},
					nullptr,  // condition
					protossType.buildTime() + 100);  // frames to run

													  // Order the builder to construct the supply structure
				gatewayBuilder->build(protossType, targetBuildLocation);
			}
		}
		else
		{
			// Train the supply provider (Overlord) if the provider is not a structure
			gatewayBuilder->train(protossType);
		}
	}
}

/*
Input: Resource depot.
Process: Build Zerg Spawning Pool if the input is of Zerg type.
Output: None.
*/
void BuildingConstruction::buildSpawningPool(BWAPI::Unit base)
{
	UnitType zergType = UnitTypes::Zerg_Spawning_Pool;
	Unit spawningPoolBuilder = base->getClosestUnit(GetType == zergType.whatBuilds().first && (IsIdle || IsGatheringMinerals) && IsOwned);

	if (spawningPoolBuilder)
	{
		if (zergType.isBuilding())
		{
			TilePosition targetBuildLocation = Broodwar->getBuildLocation(zergType, spawningPoolBuilder->getTilePosition());
			if (targetBuildLocation)
			{
				// Register an event that draws the target build location
				Broodwar->registerEvent([targetBuildLocation, zergType](Game*)
				{
					Broodwar->drawBoxMap(Position(targetBuildLocation), Position(targetBuildLocation + zergType.tileSize()), Colors::Blue);
				},
					nullptr,  // condition
					zergType.buildTime() + 100);  // frames to run

													 // Order the builder to construct the supply structure
				spawningPoolBuilder->build(zergType, targetBuildLocation);
			}
		}
		else
		{
			// Train the supply provider (Overlord) if the provider is not a structure
			spawningPoolBuilder->train(zergType);
		}
	}
}
