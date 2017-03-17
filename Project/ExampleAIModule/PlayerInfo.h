#pragma once
//#include "Base.h"
#include <BWAPI.h>


class PlayerInfo
{
public:
	
	//Constructor.
	PlayerInfo::PlayerInfo();

	//Flags to indicate what is currently being built and keep offsets current.
	bool buildingAcademy;
	bool buildingArmory;
	bool buildingBarracks;
	bool buildingBunker;
	bool buildingCommandCenter;
	bool buildingEngineeringBay;
	bool buildingFactory;
	bool buildingMissileTurret;
	bool buildingRefinery;
	bool buildingScienceFacility;
	bool buildingStarport;
	bool buildingSupplyDepot;

	//Structure Counts
	int barracksCount;
	int expansionCount;

	//Offset flags and values for costs incurred by building events.
	bool mineralsOffsetFlag;
	bool gasOffsetFlag;
	int buildingMineralsOffset;
	int buildingGasOffset; 
	void adjustMineralOffset(int cost);
	void adjustGasOffset(int cost);
	void PlayerInfo::resetMinerals();
	void PlayerInfo::resetGas();
};