#pragma once
#include <BWAPI.h>
#include <BWTA.h>
#include <windows.h>
#include <algorithm>

class MapTools
{
public:
	MapTools::MapTools();
	static int MapTools::getYExplored();
	static int MapTools::getXExplored();
	static BWAPI::TilePosition MapTools::getNextExpansion();
	static long double MapTools::getAbsoluteTileDistance(BWAPI::TilePosition origin, BWAPI::TilePosition destination);
	static int MapTools::getGroundDistance(BWAPI::Position origin, BWAPI::Position destination);
};