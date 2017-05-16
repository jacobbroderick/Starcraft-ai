#include <iostream>
#include "BuildingConstruction.h"

using namespace BWAPI;
using namespace Filter;

/*
Input: Resource depot.
Process: Uses type of resource depot to determine race. Selects a worker to perform construction of an expansion.
Output: None.
*/
void BuildingConstruction::buildCenter(BWAPI::Unit base, BWAPI::TilePosition buildLocation, PlayerInfo* player)
{
	// Retrieve a unit that is capable of constructing the supply needed.
	UnitType centerProviderType = UnitTypes::Terran_Barracks;
	Unit centerBuilder = base->getClosestUnit(GetType == centerProviderType.whatBuilds().first && (IsIdle || IsGatheringMinerals) && IsOwned);
	Broodwar << "Building" << std::endl;
	// If a unit was found.
	if (centerBuilder && !player->buildingCommandCenter)
	{
		if (centerProviderType.isBuilding())
		{
			
			//TilePosition targetBuildLocation = Broodwar->getBuildLocation(centerProviderType, buildLocation);
			if (buildLocation)
			{
				
				//centerBuilder->move(BWAPI::Position(65, 15));
				Broodwar << "Building" << std::endl;
				// Order the builder to construct the center structure.
				TilePosition shift(-20, -20); 
				centerBuilder->build(UnitTypes::Terran_Command_Center, buildLocation + shift);
				//player->buildingCommandCenter = true;
				//player->expansionCount++;
				player->adjustMineralOffset(-400);
			}
		}
	}
}

/*
Input: Resource depot.
Process: Uses type of resource depot to determine race. Selects a worker to perform construction of supply structure.
Output: None.
*/
void BuildingConstruction::buildSupply(BWAPI::Unit base, PlayerInfo* player)
{
	/*
	/ We can create an error handling function for this if we decide it is necessary.
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

	// Retrieve a unit that is capable of constructing the supply needed.
	UnitType supplyProviderType = base->getType().getRace().getSupplyProvider();
	Unit supplyBuilder = base->getClosestUnit(GetType == supplyProviderType.whatBuilds().first && (IsIdle || IsGatheringMinerals) && IsOwned);

	// If a unit was found.
	if (supplyBuilder && !player->buildingSupplyDepot)
	{
		if (supplyProviderType.isBuilding())
		{
			TilePosition targetBuildLocation = Broodwar->getBuildLocation(supplyProviderType, supplyBuilder->getTilePosition());
			if (targetBuildLocation)
			{
				// Register an event that draws the target build location.
				Broodwar->registerEvent([targetBuildLocation, supplyProviderType](Game*)
				{
					Broodwar->drawBoxMap(Position(targetBuildLocation), Position(targetBuildLocation + supplyProviderType.tileSize()), Colors::Blue);
				},
				nullptr, 
				supplyProviderType.buildTime() + 100);  // frames to run.

			// Order the builder to construct the supply structure.
			supplyBuilder->build(supplyProviderType, targetBuildLocation);
			player->adjustMineralOffset(-100);
			player->buildingSupplyDepot = true;
			}
		}
		else
		{
		// Train the supply provider (Overlord) if the provider is not a structure.
		supplyBuilder->train(supplyProviderType);
		}
	}
}

/*
Input: Resource depot.
Process: Uses type of resource depot to determine race. Selects a worker to perform construction of gas structure.
Output: None.
*/
void BuildingConstruction::buildGas(BWAPI::Unit base, PlayerInfo* player)
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
	}
}

/*
Input: Resource depot.
Process: Build Terran Barracks if the input is of Terran type.
Output: None.
*/
void BuildingConstruction::buildBarracks(BWAPI::Unit base, PlayerInfo* player)
{
	UnitType terranType = UnitTypes::Terran_Barracks;
	Unit barracksBuilder = base->getClosestUnit(GetType == terranType.whatBuilds().first && (IsIdle || IsGatheringMinerals) && IsOwned);

	if (barracksBuilder && ResourceGathering::getMineralCount() + player->buildingMineralsOffset >= 150)
	{
		if (terranType.isBuilding() && !player->buildingBarracks)
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

				// Order the builder to construct the barracks structure
				Broodwar << targetBuildLocation << terranType << std::endl;
				barracksBuilder->build(terranType, targetBuildLocation);
				player->barracksCount++;
				player->adjustMineralOffset(-150);
				player->buildingBarracks = true;
			}
		}
	}
}

/*
Input: Resource depot.
Process: Build Protoss Gateway if the input is of Protoss type.
Output: None.
*/
void BuildingConstruction::buildGateway(BWAPI::Unit base, PlayerInfo* player)
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

				// Order the builder to construct the gateway structure
				gatewayBuilder->build(protossType, targetBuildLocation);
			}
		}
	}
}

/*
Input: Resource depot.
Process: Build Zerg Spawning Pool if the input is of Zerg type.
Output: None.
*/
void BuildingConstruction::buildSpawningPool(BWAPI::Unit base, PlayerInfo* player)
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

				// Order the builder to construct the spawning pool structure
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

/*
Input: Player info object.
Process: Check construction flags and switch them off accordingly.
Output: None.
*/
void BuildingConstruction::checkConstructionStarted(PlayerInfo* player)
{
	//Check if there exists a structure that matches the input structure and check if isConstructing()
	//If it is, we know to reset the offset
	for (auto &unit : Broodwar->self()->getUnits())
	{
		if (unit->getType() == UnitTypes::Terran_Academy && unit->isConstructing() && player->buildingAcademy)
		{
			//player->buildingAcademy = false;
			player->adjustMineralOffset(150);
		}
		else if (unit->getType() == UnitTypes::Terran_Armory && unit->isConstructing() && player->buildingArmory)
		{
			//player->buildingArmory = false;
			player->adjustMineralOffset(100);
			player->adjustGasOffset(50);
		}
		else if (unit->getType() == UnitTypes::Terran_Barracks && unit->isConstructing() && player->buildingBarracks)
		{
			//player->buildingBarracks = false;
			player->adjustMineralOffset(150);
		}
		else if (unit->getType() == UnitTypes::Terran_Bunker && unit->isConstructing() && player->buildingBunker)
		{
			//player->buildingBunker = false;
			player->adjustMineralOffset(150);
		}
		else if (unit->getType() == UnitTypes::Terran_Command_Center && unit->isConstructing() && player->buildingCommandCenter)
		{
			//player->buildingCommandCenter = false;
			player->adjustMineralOffset(400);
		}
		else if (unit->getType() == UnitTypes::Terran_Engineering_Bay && unit->isConstructing() && player->buildingEngineeringBay)
		{
			//player->buildingEngineeringBay = false;
			player->adjustMineralOffset(125);
		}
		else if (unit->getType() == UnitTypes::Terran_Factory && unit->isConstructing() && player->buildingFactory)
		{
			//player->buildingFactory = false;
			player->adjustMineralOffset(200);
			player->adjustGasOffset(100);
		}
		else if (unit->getType() == UnitTypes::Terran_Missile_Turret && unit->isConstructing() && player->buildingMissileTurret)
		{
			//player->buildingMissileTurret = false;
			player->adjustMineralOffset(75);
		}
		else if (unit->getType() == UnitTypes::Terran_Refinery && unit->isConstructing() && player->buildingRefinery)
		{
			//player->buildingRefinery = false;
			player->adjustMineralOffset(100);
		}
		else if (unit->getType() == UnitTypes::Terran_Science_Facility && unit->isConstructing() && player->buildingScienceFacility)
		{
			//player->buildingScienceFacility = false;
			player->adjustMineralOffset(100);
			player->adjustGasOffset(150);
		}
		else if (unit->getType() == UnitTypes::Terran_Starport && unit->isConstructing() && player->buildingStarport)
		{
			//player->buildingStarport = false;
			player->adjustMineralOffset(150);
			player->adjustGasOffset(100);
		}
		else if (unit->getType() == UnitTypes::Terran_Supply_Depot && unit->isConstructing() && player->buildingSupplyDepot)
		{
			//player->buildingSupplyDepot = false;
			player->adjustMineralOffset(100);
		}
	}

}
