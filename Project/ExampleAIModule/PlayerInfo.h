#pragma once
//#include "Base.h"

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

	//Offset flags and values for costs incurred by building events.
	bool mineralsOffset;
	bool gasOffset;
	int buildingMineralsOffset;
	int buildingGasOffset; 
	void adjustMineralOffset(int cost);
	void adjustGasOffset(int cost);
	void PlayerInfo::resetMinerals();
	void PlayerInfo::resetGas();
};