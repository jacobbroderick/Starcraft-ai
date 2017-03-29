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
Input: N/A
Process: Checks the distance of all expansion locations that are known to not be in use.
Output: TilePosition of the closest expansion location.
*/
BWAPI::TilePosition MapTools::getNextExpansion()
{
	//Will hold the current closest base considered.
	BWTA::BaseLocation *closestBase = NULL;
	//Distance from the closest base considered thus far.
	double minDistance = 1000000;
	//Get the start location.
	BWAPI::TilePosition homeBase = BWAPI::Broodwar->self()->getStartLocation();

	//For each potential expansion location.
	for (BWTA::BaseLocation *currBase : BWTA::getBaseLocations())
	{
		//Check if the base has gas and is not the home base.
		if (!currBase->isMineralOnly() && !(currBase == BWTA::getStartLocation(BWAPI::Broodwar->self())))
		{

			//Get tile position of the current possible expansion.
			BWAPI::TilePosition currBaseTile = currBase->getTilePosition();

			bool buildingInTheWay = false;

            for (int x = 0; x < BWAPI::Broodwar->self()->getRace().getCenter().tileWidth(); ++x)
            {
                for (int y = 0; y < BWAPI::Broodwar->self()->getRace().getCenter().tileHeight(); ++y)
                {
                    BWAPI::TilePosition tp(currBaseTile.x + x, currBaseTile.y + y);

                    for (auto & unit : BWAPI::Broodwar->getUnitsOnTile(tp))
                    {
                        if (unit->getType().isBuilding() && !unit->isFlying())
                        {
                            buildingInTheWay = true;
                            break;
                        }
                    }
                }
            }
			if (buildingInTheWay)
			{
				//Skips the remainder of this iteration of the loop.
				continue;
			}

			//Calculate calculate distance and compare to closest expansion option.
			double distanceFromHomeBase = homeBase.getDistance(currBaseTile);

			//Base is not connected - continue looping.
			if (!BWTA::isConnected(homeBase, currBaseTile) || distanceFromHomeBase <= 0)
			{
				continue;
			}

			if (closestBase == NULL || distanceFromHomeBase < minDistance)
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
	return sqrt(pow(abs(origin.x / 32 - destination.x / 32), 2) + pow(abs(origin.y / 32 - destination.y / 32), 2));
}

/*
Input: Tiles at starting and ending locations.
Process: Calculates walking distance between the origin and destination.
Output: Distance.
*/
int MapTools::getGroundDistance(BWAPI::Position origin, BWAPI::Position destination)
{

}
