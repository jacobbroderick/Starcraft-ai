#include "PlayerInfo.h"

PlayerInfo::PlayerInfo()
{

	//Building flags.
	bool buildingAcademy = false;
	bool buildingArmory = false;
	buildingBarracks = false;
	buildingBunker = false;
	buildingCommandCenter = false;
	buildingEngineeringBay = false;
	buildingFactory = false;
	buildingMissileTurret = false;
	buildingRefinery = false;
	buildingScienceFacility = false;
	buildingStarport = false;
	buildingSupplyDepot = false;

	//Scouting info
	scoutManager = new ScoutManager();
	unitScouting = false;
	scoutingUnit = NULL;

	//Offset values.
	mineralsOffsetFlag = false;
	gasOffsetFlag = false;
	buildingMineralsOffset = 0;
	buildingGasOffset = 0;

	//Structure counts.
	barracksCount = 0;
	expansionCount = 0;

	//Enemy info.
	enemyBase = BWAPI::TilePositions::None;
}

void PlayerInfo::adjustMineralOffset(int offset)
{
	buildingMineralsOffset += offset;
	if (buildingMineralsOffset != 0)
		mineralsOffsetFlag = true;
	else
		mineralsOffsetFlag = false;
}

void PlayerInfo::adjustGasOffset(int offset)
{
	buildingGasOffset += offset;
	if (buildingGasOffset != 0)
		gasOffsetFlag = true;
	else
		gasOffsetFlag = false;
}

void PlayerInfo::resetMinerals()
{
	mineralsOffsetFlag = false;
	buildingMineralsOffset = 0;
}

void PlayerInfo::resetGas()
{
	gasOffsetFlag = false;
	buildingGasOffset = 0;
}
