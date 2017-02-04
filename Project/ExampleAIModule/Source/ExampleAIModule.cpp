#include "ExampleAIModule.h"
#include <iostream>


using namespace BWAPI;
using namespace Filter;
using namespace std;

bool analyzed;
bool analysis_just_finished;
vector <BWAPI::Unit> *workers;
vector <BWAPI::Unit> *resourceDepots;

DWORD WINAPI AnalyzeThread()
{
	BWTA::analyze();

	analyzed = true;
	analysis_just_finished = true;
	return 0;
}

void ExampleAIModule::drawTerrainData()
{
	//we will iterate through all the base locations, and draw their outlines.
	for (const auto& baseLocation : BWTA::getBaseLocations()) {
		TilePosition p = baseLocation->getTilePosition();

		//draw outline of center location
		Position leftTop(p.x * TILE_SIZE, p.y * TILE_SIZE);
		Position rightBottom(leftTop.x + 4 * TILE_SIZE, leftTop.y + 3 * TILE_SIZE);
		Broodwar->drawBoxMap(leftTop, rightBottom, Colors::Blue);

		//draw a circle at each mineral patch
		for (const auto& mineral : baseLocation->getStaticMinerals()) {
			Broodwar->drawCircleMap(mineral->getInitialPosition(), 30, Colors::Cyan);
		}

		//draw the outlines of Vespene geysers
		for (const auto& geyser : baseLocation->getGeysers()) {
			TilePosition p1 = geyser->getInitialTilePosition();
			Position leftTop1(p1.x * TILE_SIZE, p1.y * TILE_SIZE);
			Position rightBottom1(leftTop1.x + 4 * TILE_SIZE, leftTop1.y + 2 * TILE_SIZE);
			Broodwar->drawBoxMap(leftTop1, rightBottom1, Colors::Orange);
		}

		//if this is an island expansion, draw a yellow circle around the base location
		if (baseLocation->isIsland()) {
			Broodwar->drawCircleMap(baseLocation->getPosition(), 80, Colors::Yellow);
		}
	}

	//we will iterate through all the regions and ...
	for (const auto& region : BWTA::getRegions()) {
		// draw the polygon outline of it in green
		BWTA::Polygon p = region->getPolygon();
		for (size_t j = 0; j < p.size(); ++j) {
			Position point1 = p[j];
			Position point2 = p[(j + 1) % p.size()];
			Broodwar->drawLineMap(point1, point2, Colors::Green);
		}
		// visualize the chokepoints with red lines
		for (auto const& chokepoint : region->getChokepoints()) {
			Position point1 = chokepoint->getSides().first;
			Position point2 = chokepoint->getSides().second;
			Broodwar->drawLineMap(point1, point2, Colors::Red);
		}
	}
}

void ExampleAIModule::onStart()
{
	workers = new vector<BWAPI::Unit>();
	resourceDepots = new vector<BWAPI::Unit>();

	for (auto &unit : Broodwar->self()->getUnits())
	{
		//Start performing actions
		// If the unit is a worker unit
		if (unit->getType().isWorker())
		{
			workers->push_back(unit);
		}	

		//Store a pointer to refer to our resource dpots 
		//NOTE: This will only have 1 depot for the time being
		if (unit->getType().isResourceDepot())
		{
			resourceDepots->push_back(unit);
		}
			
	
	}

	//Start map analysis.
	BWTA::readMap();
	analyzed = false;
	analysis_just_finished = false;

}

void ExampleAIModule::onEnd(bool isWinner)
{
  // Called when the game ends
  if ( isWinner )
  {
    // Log your win here!
  }
}

void ExampleAIModule::onFrame()
{
	// Called once every game frame.
	// Display the game frame rate as text in the upper left area of the screen.
	Broodwar->drawTextScreen(200, 0,  "FPS: %d", Broodwar->getFPS() );
	Broodwar->drawTextScreen(200, 20, "Average FPS: %f", Broodwar->getAverageFPS() );

	// Return if the game is a replay or is paused.
	if ( Broodwar->isReplay() || Broodwar->isPaused() || !Broodwar->self() )
	//return;
	
	//BWTA draw
	if (analyzed)
		drawTerrainData();

	if (analysis_just_finished)
	{
		Broodwar << "Finished analyzing map." << std::endl;;
		analysis_just_finished = false;
	}

	// Prevent spamming by only running our onFrame once every number of latency frames.
	// Latency frames are the number of frames before commands are processed.
	if ( Broodwar->getFrameCount() % Broodwar->getLatencyFrames() != 0 )
		return;

	// Iterate through all the units that we own.
	for (auto &unit : Broodwar->self()->getUnits())
	{
		if (!UnitAction::checkUnitState(unit))
			continue;

		//Start performing actions with unit.
		// If the unit is a worker unit.
		if ( unit->getType().isWorker() )
		{
			ResourceGathering::workerGather(unit);
		}
		else if ( unit->getType().isResourceDepot() ) // A resource depot is a Command Center, Nexus, or Hatchery
		{
			ResourceGathering::buildWorker(unit);
		}
	}
}

