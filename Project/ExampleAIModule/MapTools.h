#pragma once
#include <BWAPI.h>
#include <BWTA.h>
#include <Windows.h>

class MapTools
{
public:
	MapTools::MapTools();
	int MapTools::getYExplored();
	int MapTools::getXExplored();
	BWAPI::TilePosition MapTools::getNextExpansion();
	int MapTools::getGroundDistance(BWAPI::Position origin, BWAPI::Position destination);
};