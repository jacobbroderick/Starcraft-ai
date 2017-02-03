#include "MapTools.h"

/*



*/
MapTools::MapTools()
{

}

/*



*/
int MapTools::getYExplored()
{

}
/*



*/

int MapTools::getXExplored()
{

}

/*



*/
BWAPI::TilePosition MapTools::getNextExpansion()
{
	//Will hold the current closest base considered.
	BWTA::BaseLocation *closestBase = NULL;
	//Distance from the closest base considered thus far.
	double minDistance = 0;
	//Get the start location.
	BWAPI::TilePosition homeBase = BWAPI::Broodwar->self()->getStartLocation();

	//For each potential expansion location.
	for (BWTA::BaseLocation *currBase : BWTA::getBaseLocations())
	{
		//Check if the base has gas and is not the home base.
		if (!currBase->isMineralOnly() && !(currBase->getTilePosition() == homeBase))
		{
			//Get tile position of the current possible expansion.
			BWAPI::TilePosition currBaseTile = currBase->getTilePosition();

			int baseX1 = currBaseTile.x * 32;
			int baseY1 = currBaseTile.y * 32;
			int baseX2 = currBaseTile.x + BWAPI::UnitTypes::Terran_Command_Center.tileWidth() * 32;
			int baseY2 = currBaseTile.y + BWAPI::UnitTypes::Terran_Command_Center.tileHeight() * 32;

			bool buildingInTheWay = false;

			//For each unit within the building rectangle.
			for (BWAPI::Unit unit : BWAPI::Broodwar->getUnitsInRectangle(baseX1, baseY1, baseX2, baseY2))
			{
				//Check if it is a building.
				if (unit->getType().isBuilding())
				{
					//Set building flag.
					buildingInTheWay = true;
					break;
				}
			}

			if (buildingInTheWay)
			{
				//Skips the remainder of this iteration of the loop.
				continue;
			}

			//Calculate calculate distance and compare to closest expansion option.
			double distanceFromHomeBase = MapTools::getAbsoluteTileDistance(homeBase, currBaseTile);

			//currBase is currently pointing at the home base. 
			//NOTE:I don't think this is needed but keeping it for first round of unit testing.
			if (distanceFromHomeBase < 0)
				continue;

			if (!closestBase || distanceFromHomeBase < minDistance)
			{
				//Set new minDistance of the currBase being considered.
				minDistance = distanceFromHomeBase;
				closestBase = currBase;
			}
		}
	}

	//If a tile position was found, return it. If not, return none.
	if (closestBase)
		return closestBase->getTilePosition();
	else
		return BWAPI::TilePositions::None;
}

/*
Input: Tiles at starting and ending locations.
Process: Calculates absolute distance not considering terrain.
Output: Distance.
*/
double MapTools::getAbsoluteTileDistance(BWAPI::TilePosition origin, BWAPI::TilePosition destination)
{
	//Distance = pythatgorean Theorem abs(x1 - x2)^2 + abs(y1 - y2)^2 = c^2 --> c = distance. 
	return sqrt(pow(abs(origin.x - destination.x), 2) + pow(abs(origin.y - destination.y), 2));
}

/*
Input: Tiles at starting and ending locations.
Process: Calculates walking distance between the origin and destination.
Output: Distance.
*/
int MapTools::getGroundDistance(BWAPI::Position origin, BWAPI::Position destination)
{

}

