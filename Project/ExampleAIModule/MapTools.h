#pragma once
#include <BWAPI.h>
#include <BWTA.h>
#include <Windows.h>
#include <algorithm>

class MapTools
{
public:
	MapTools::MapTools();
	int MapTools::getYExplored();
	int MapTools::getXExplored();
	BWAPI::TilePosition MapTools::getNextExpansion();
	double MapTools::getAbsoluteTileDistance(BWAPI::TilePosition origin, BWAPI::TilePosition destination);
	int MapTools::getGroundDistance(BWAPI::Position origin, BWAPI::Position destination);
};