#pragma once
//#include "Base.h"

class PlayerInfo
{
public:
	
	//Constructor.
	PlayerInfo::PlayerInfo();

	//Flags to indicate what is currently being built and keep offsets current.
	bool academyBuilding;
	bool armoryBuilding;
	bool buildingBarracks;
	bool buildingBunker;
	bool buildingCommandCenter;
	bool buildingEngeineeringBay;
	bool buildingTerranFactory;
	bool buildingMissileTurret;
	bool buildingRefinery;
	bool buildingScienceFacility;
	bool buildingStarport;
	bool buildingSupplyDepot;

	//Offset flags and values for costs incurred by building events.
	bool mineralsOffset;
	bool gasOffset;
	int buildingMineralsOffset;
	int buildingGasOffset; //Not sure any buildings cost gas.
	void setMineralOffset(int cost);
	void setGasOffset(int cost);
	void PlayerInfo::resetMinerals();
	void PlayerInfo::resetGas();
};