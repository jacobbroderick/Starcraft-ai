#include "ExampleAIModule.h"

bool analyzed;
bool analysis_just_finished;
bool builtBarracks;
bool builtExpansion;
PlayerInfo* player;
BWTA::Region* home;
BWTA::Region* enemy_base;
std::vector <BWAPI::Unit> *workers;
std::vector <BWAPI::Unit> *resourceDepots;

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
		BWAPI::TilePosition p = baseLocation->getTilePosition();

		//draw outline of center location
		BWAPI::Position leftTop(p.x * TILE_SIZE, p.y * TILE_SIZE);
		BWAPI::Position rightBottom(leftTop.x + 4 * TILE_SIZE, leftTop.y + 3 * TILE_SIZE);
		BWAPI::Broodwar->drawBoxMap(leftTop, rightBottom, BWAPI::Colors::Blue);

		//draw a circle at each mineral patch
		for (const auto& mineral : baseLocation->getStaticMinerals()) {
			BWAPI::Broodwar->drawCircleMap(mineral->getInitialPosition(), 30, BWAPI::Colors::Cyan);
		}

		//draw the outlines of Vespene geysers
		for (const auto& geyser : baseLocation->getGeysers()) {
			BWAPI::TilePosition p1 = geyser->getInitialTilePosition();
			BWAPI::Position leftTop1(p1.x * TILE_SIZE, p1.y * TILE_SIZE);
			BWAPI::Position rightBottom1(leftTop1.x + 4 * TILE_SIZE, leftTop1.y + 2 * TILE_SIZE);
			BWAPI::Broodwar->drawBoxMap(leftTop1, rightBottom1, BWAPI::Colors::Orange);
		}

		//if this is an island expansion, draw a yellow circle around the base location
		if (baseLocation->isIsland()) {
			BWAPI::Broodwar->drawCircleMap(baseLocation->getPosition(), 80, BWAPI::Colors::Yellow);
		}
	}

	//we will iterate through all the regions and ...
	for (const auto& region : BWTA::getRegions()) {
		// draw the polygon outline of it in green
		BWTA::Polygon p = region->getPolygon();
		for (size_t j = 0; j < p.size(); ++j) {
			BWAPI::Position point1 = p[j];
			BWAPI::Position point2 = p[(j + 1) % p.size()];
			BWAPI::Broodwar->drawLineMap(point1, point2, BWAPI::Colors::Green);
		}
		// visualize the chokepoints with red lines
		for (auto const& chokepoint : region->getChokepoints()) {
			BWAPI::Position point1 = chokepoint->getSides().first;
			BWAPI::Position point2 = chokepoint->getSides().second;
			BWAPI::Broodwar->drawLineMap(point1, point2, BWAPI::Colors::Red);
		}
	}
}

void ExampleAIModule::onEnd(bool isWinner)
{
  // Called when the game ends
  if ( isWinner )
  {
    // Log your win here!
  }
}

void ExampleAIModule::onStart()
{
	player = new PlayerInfo();

	builtBarracks = false;
	builtExpansion = false;

	//Start map analysis.
	BWTA::readMap();
	analyzed = false;
	analysis_just_finished = false;
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)AnalyzeThread, NULL, 0, NULL);

	workers = new std::vector<BWAPI::Unit>();
	resourceDepots = new std::vector<BWAPI::Unit>();

	// Print the map name.
	// BWAPI returns std::string when retrieving a string, don't forget to add .c_str() when printing!
	BWAPI::Broodwar << "The map is " << BWAPI::Broodwar->mapName() << "!" << std::endl;

	// Enable the UserInput flag, which allows us to control the bot and type messages.
	BWAPI::Broodwar->enableFlag(BWAPI::Flag::UserInput);

	// Uncomment the following line and the bot will know about everything through the fog of war (cheat).
	//Broodwar->enableFlag(Flag::CompleteMapInformation);

	// Set the command optimization level so that common commands can be grouped
	// and reduce the bot's APM (Actions Per Minute).
	BWAPI::Broodwar->setCommandOptimizationLevel(2);

	// Check if this is a replay
	if (BWAPI::Broodwar->isReplay())
	{

		// Announce the players in the replay
		BWAPI::Broodwar << "The following players are in this replay:" << std::endl;

		// Iterate all the players in the game using a std:: iterator
		BWAPI::Playerset players = BWAPI::Broodwar->getPlayers();
		for (auto p : players)
		{
			// Only print the player if they are not an observer
			if (!p->isObserver())
				BWAPI::Broodwar << p->getName() << ", playing as " << p->getRace() << std::endl;
		}

	}
	else // if this is not a replay
	{
		// Retrieve you and your enemy's races. enemy() will just return the first enemy.
		// If you wish to deal with multiple enemies then you must use enemies().
		if (BWAPI::Broodwar->enemy()) // First make sure there is an enemy
			BWAPI::Broodwar << "The matchup is " << BWAPI::Broodwar->self()->getRace() << " vs " << BWAPI::Broodwar->enemy()->getRace() << std::endl;
	}

}

void ExampleAIModule::onFrame()
{
	// Called once every game frame

	// Display the game frame rate as text in the upper left area of the screen
	BWAPI::Broodwar->drawTextScreen(200, 0, "FPS: %d", BWAPI::Broodwar->getFPS());
	BWAPI::Broodwar->drawTextScreen(200, 20, "Average FPS: %f", BWAPI::Broodwar->getAverageFPS());

	// Return if the game is a replay or is paused
	if (BWAPI::Broodwar->isReplay() || BWAPI::Broodwar->isPaused() || !BWAPI::Broodwar->self())
		return;

	//BWTA draw
	if (analyzed)
	{
		drawTerrainData();
	}

	if (analysis_just_finished)
	{
		BWAPI::Broodwar << "Finished analyzing map." << std::endl;;
		analysis_just_finished = false;
	}
	// Prevent spamming by only running our onFrame once every number of latency frames.
	// Latency frames are the number of frames before commands are processed.
	if (BWAPI::Broodwar->getFrameCount() % BWAPI::Broodwar->getLatencyFrames() != 0)
		return;

	//Check for building flags
	BuildingConstruction::checkConstructionStarted(player);


	// Iterate through all the units that we own.
	for (auto &unit : BWAPI::Broodwar->self()->getUnits())
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
			if (BWAPI::Broodwar->self()->supplyUsed() < 20) // Build up to 10 workers for alpha and then stop building them
			{
				ResourceGathering::buildWorker(unit);
			}
		}

		/*
		//trains marines up to 20 supply
		else if (unit->getType() == BWAPI::UnitTypes::Terran_Barracks && BWAPI::Broodwar->self()->supplyUsed() < 40) {
			UnitAction::trainMarines(unit);
		}
		//builds barracks after 10 scvs are working
		if (!builtBarracks && BWAPI::Broodwar->self()->supplyUsed() >= 20)
		{
			BuildingConstruction::buildBarracks(unit, player);
			builtBarracks = true;
		}
		//builds expansion after 10 marines have been made
		if (!builtExpansion && BWAPI::Broodwar->self()->supplyUsed() >= 40)
		{
			//for some reason doesn't compile going to fix this tomorrow
			BWAPI::TilePosition newExpoTile = MapTools::getNextExpansion();
			BuildingConstruction::buildCenter(unit, newExpoTile, player);
			builtExpansion = true;
		}
		*/
	}
}

void ExampleAIModule::onSendText(std::string text)
{
	if (text == "/analyze") 
	{
		if (analyzed == false) 
		{
			BWAPI::Broodwar << "Analyzing map... this may take a minute" << std::endl;;
			//CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)AnalyzeThread, NULL, 0, NULL);
		}
	}
	else 
	{
		// Send the text to the game if it is not being processed.
		BWAPI::Broodwar->sendText("%s", text.c_str());
	}
}

void ExampleAIModule::onReceiveText(BWAPI::Player player, std::string text)
{
	// Parse the received text
	BWAPI::Broodwar << player->getName() << " said \"" << text << "\"" << std::endl;
}

void ExampleAIModule::onPlayerLeft(BWAPI::Player player)
{
	// Interact verbally with the other players in the game by
	// announcing that the other player has left.
	BWAPI::Broodwar->sendText("Goodbye %s!", player->getName().c_str());
}

void ExampleAIModule::onNukeDetect(BWAPI::Position target)
{

	// Check if the target is a valid position
	if (target)
	{
		// if so, print the location of the nuclear strike target
		BWAPI::Broodwar << "Nuclear Launch Detected at " << target << std::endl;
	}
	else
	{
		// Otherwise, ask other players where the nuke is!
		BWAPI::Broodwar->sendText("Where's the nuke?");
	}

	// You can also retrieve all the nuclear missile targets using Broodwar->getNukeDots()!
}

void ExampleAIModule::onUnitDiscover(BWAPI::Unit unit)
{
}

void ExampleAIModule::onUnitEvade(BWAPI::Unit unit)
{
}

void ExampleAIModule::onUnitShow(BWAPI::Unit unit)
{
}

void ExampleAIModule::onUnitHide(BWAPI::Unit unit)
{
}

void ExampleAIModule::onUnitCreate(BWAPI::Unit unit)
{
	if (BWAPI::Broodwar->isReplay())
	{
		// if we are in a replay, then we will print out the build order of the structures
		if (unit->getType().isBuilding() && !unit->getPlayer()->isNeutral())
		{
			int seconds = BWAPI::Broodwar->getFrameCount() / 24;
			int minutes = seconds / 60;
			seconds %= 60;
			BWAPI::Broodwar->sendText("%.2d:%.2d: %s creates a %s", minutes, seconds, unit->getPlayer()->getName().c_str(), unit->getType().c_str());
		}
	}
}

void ExampleAIModule::onUnitDestroy(BWAPI::Unit unit)
{
}

void ExampleAIModule::onUnitMorph(BWAPI::Unit unit)
{
	if (BWAPI::Broodwar->isReplay())
	{
		// if we are in a replay, then we will print out the build order of the structures
		if (unit->getType().isBuilding() && !unit->getPlayer()->isNeutral())
		{
			int seconds = BWAPI::Broodwar->getFrameCount() / 24;
			int minutes = seconds / 60;
			seconds %= 60;
			BWAPI::Broodwar->sendText("%.2d:%.2d: %s morphs a %s", minutes, seconds, unit->getPlayer()->getName().c_str(), unit->getType().c_str());
		}
	}
}

void ExampleAIModule::onUnitRenegade(BWAPI::Unit unit)
{
}

void ExampleAIModule::onSaveGame(std::string gameName)
{
	BWAPI::Broodwar << "The game was saved to \"" << gameName << "\"" << std::endl;
}

void ExampleAIModule::onUnitComplete(BWAPI::Unit unit)
{
}