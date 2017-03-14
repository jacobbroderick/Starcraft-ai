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

	//Offset values.
	mineralsOffset = false;
	gasOffset = false;
	buildingMineralsOffset = 0;
	buildingGasOffset = 0;
}

void PlayerInfo::adjustMineralOffset(int offset)
{
	buildingMineralsOffset += offset;
	if (buildingMineralsOffset != 0)
		mineralsOffset = true;
	else
		mineralsOffset = false;
}

void PlayerInfo::adjustGasOffset(int offset)
{
	buildingGasOffset += offset;
	if (buildingGasOffset != 0)
		gasOffset = true;
	else
		gasOffset = false;
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