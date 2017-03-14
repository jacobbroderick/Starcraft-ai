#include "PlayerInfo.h"

PlayerInfo::PlayerInfo()
{
	//Building flags.
	academyBuilding = false;
	armoryBuilding = false;
	buildingBarracks = false;
	buildingBunker = false;
	buildingCommandCenter = false;
	buildingEngeineeringBay = false;
	buildingTerranFactory = false;
	buildingMissileTurret = false;
	buildingRefinery = false;
	buildingScienceFacility = false;
	buildingStarport = false;
	buildingSupplyDepot = false;

	//Offset values.
	mineralsOffset = false;
	gasOffset = false;
	buildingMineralsOffset = 0;
	buildingGasOffset = 0;
}

void PlayerInfo::setMineralOffset(int offset)
{
	buildingMineralsOffset = offset;
	mineralsOffset = true;
}

void PlayerInfo::setGasOffset(int offset)
{
	buildingGasOffset = offset;
	gasOffset = true;
}

void PlayerInfo::resetMinerals()
{
	mineralsOffset = false;
	buildingMineralsOffset = 0;
}

void PlayerInfo::resetGas()
{
	gasOffset = false;
	buildingGasOffset = 0;
}