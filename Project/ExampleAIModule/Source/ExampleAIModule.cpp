#include "ExampleAIModule.h"

using namespace BWAPI;

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

	workers = new std::vector<Unit>();
	resourceDepots = new std::vector<Unit>();

	// Print the map name.
	// BWAPI returns std::string when retrieving a string, don't forget to add .c_str() when printing!
	Broodwar << "The map is " << Broodwar->mapName() << "!" << std::endl;

	// Enable the UserInput flag, which allows us to control the bot and type messages.
	Broodwar->enableFlag(Flag::UserInput);

	// Uncomment the following line and the bot will know about everything through the fog of war (cheat).
	//Broodwar->enableFlag(Flag::CompleteMapInformation);

	// Set the command optimization level so that common commands can be grouped
	// and reduce the bot's APM (Actions Per Minute).
	Broodwar->setCommandOptimizationLevel(2);

	// Check if this is a replay
	if (Broodwar->isReplay())
	{

		// Announce the players in the replay
		Broodwar << "The following players are in this replay:" << std::endl;

		// Iterate all the players in the game using a std:: iterator
		Playerset players = Broodwar->getPlayers();
		for (auto p : players)
		{
			// Only print the player if they are not an observer
			if (!p->isObserver())
				Broodwar << p->getName() << ", playing as " << p->getRace() << std::endl;
		}

	}
	else // if this is not a replay
	{
		// Retrieve you and your enemy's races. enemy() will just return the first enemy.
		// If you wish to deal with multiple enemies then you must use enemies().
		if (Broodwar->enemy()) // First make sure there is an enemy
			Broodwar << "The matchup is " << Broodwar->self()->getRace() << " vs " << Broodwar->enemy()->getRace() << std::endl;
	}

}

void ExampleAIModule::onFrame()
{
	// Called once every game frame

	// Display the game frame rate as text in the upper left area of the screen
	Broodwar->drawTextScreen(200, 0, "FPS: %d", Broodwar->getFPS());
	Broodwar->drawTextScreen(200, 20, "Average FPS: %f", Broodwar->getAverageFPS());

	// Return if the game is a replay or is paused
	if (Broodwar->isReplay() || Broodwar->isPaused() || !Broodwar->self())
		return;

	//BWTA draw
	if (analyzed)
	{
		drawTerrainData();
	}

	if (analysis_just_finished)
	{
		Broodwar << "Finished analyzing map." << std::endl;;
		analysis_just_finished = false;
	}
	// Prevent spamming by only running our onFrame once every number of latency frames.
	// Latency frames are the number of frames before commands are processed.
	if (Broodwar->getFrameCount() % Broodwar->getLatencyFrames() != 0)
		return;

	//Check for building flags if minerals/gas offset flag(s) are set and we need to check if the offset needs to be reversed.
	if(player->mineralsOffsetFlag || player->gasOffsetFlag)
		BuildingConstruction::checkConstructionStarted(player);

	// Iterate through all the units that we own.
	for (auto &unit : Broodwar->self()->getUnits())
	{
		if (!UnitAction::checkUnitState(unit))
			continue;

		if (unit->getType().isWorker() && unit != player->scoutManager->scoutingUnit)
		{
			if (!player->scoutManager->unitScouting && player->enemyBase == BWAPI::TilePositions::None && analyzed)
			{
				ScoutManager::scoutStartLocations(unit);
				player->scoutManager->unitScouting = true;
				player->scoutManager->scoutingUnit = unit;
			}
			else
				ResourceGathering::workerGather(unit);
		}

		/*
		if (unit->getType().isResourceDepot() && ResourceGathering::getMineralCount() > 400)
		{
			TilePosition newExpoTile = MapTools::getNextExpansion();
			BuildingConstruction::buildCenter(unit, newExpoTile, player);
		}
		*/
		/*
		//Start performing actions with unit.
		// If the unit is a worker unit.
		if (unit->getType().isWorker())
		{
			ResourceGathering::workerGather(unit);
		}
		else if (unit->getType().isResourceDepot() && Broodwar->self()->supplyUsed() / 2 < 10) // A resource depot is a Command Center, Nexus, or Hatchery
		{
			ResourceGathering::buildWorker(unit, player);
		}
		else if (unit->getType().isResourceDepot() && !player->barracksCount && Broodwar->self()->supplyUsed() / 2 == 10)
		{
			BuildingConstruction::buildBarracks(unit, player);
		}
		else if (unit->getType() == UnitTypes::Terran_Barracks && Broodwar->self()->supplyUsed() / 2 < 15)
		{
			UnitAction::trainMarines(unit, player);
		}
		else if (unit->getType().isResourceDepot() && !player->expansionCount && Broodwar->self()->supplyUsed()/2 == 15 && ResourceGathering::getMineralCount() + player->buildingMineralsOffset >= 400)
		{
			player->expansionCount++;
			player->adjustMineralOffset(-400);
			TilePosition newExpoTile = MapTools::getNextExpansion();
			BuildingConstruction::buildCenter(unit, newExpoTile, player);
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
			Broodwar << "Analyzing map... this may take a minute" << std::endl;;
			//CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)AnalyzeThread, NULL, 0, NULL);
		}
	}
	else 
	{
		// Send the text to the game if it is not being processed.
		Broodwar->sendText("%s", text.c_str());
	}
}

void ExampleAIModule::onReceiveText(BWAPI::Player player, std::string text)
{
	// Parse the received text
	Broodwar << player->getName() << " said \"" << text << "\"" << std::endl;
}

void ExampleAIModule::onPlayerLeft(BWAPI::Player player)
{
	// Interact verbally with the other players in the game by
	// announcing that the other player has left.
	Broodwar->sendText("Goodbye %s!", player->getName().c_str());
}

void ExampleAIModule::onNukeDetect(BWAPI::Position target)
{

	// Check if the target is a valid position
	if (target)
	{
		// if so, print the location of the nuclear strike target
		Broodwar << "Nuclear Launch Detected at " << target << std::endl;
	}
	else
	{
		// Otherwise, ask other players where the nuke is!
		Broodwar->sendText("Where's the nuke?");
	}

	// You can also retrieve all the nuclear missile targets using Broodwar->getNukeDots()!
}

void ExampleAIModule::onUnitDiscover(BWAPI::Unit unit)
{
	if (unit->getType().isResourceDepot() && Broodwar->self()->isEnemy(unit->getPlayer()))
	{
		player->scoutManager->unitScouting = false;
		player->scoutManager->scoutingUnit->move(Position(Broodwar->self()->getStartLocation()));
		player->enemyBase = unit->getTilePosition();
		player->scoutManager->scoutingUnit = NULL;
	}
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
			int seconds = Broodwar->getFrameCount() / 24;
			int minutes = seconds / 60;
			seconds %= 60;
			Broodwar->sendText("%.2d:%.2d: %s creates a %s", minutes, seconds, unit->getPlayer()->getName().c_str(), unit->getType().c_str());
		}
	}
}

void ExampleAIModule::onUnitDestroy(BWAPI::Unit unit)
{
}

void ExampleAIModule::onUnitMorph(BWAPI::Unit unit)
{
	if (Broodwar->isReplay())
	{
		// if we are in a replay, then we will print out the build order of the structures
		if (unit->getType().isBuilding() && !unit->getPlayer()->isNeutral())
		{
			int seconds = Broodwar->getFrameCount() / 24;
			int minutes = seconds / 60;
			seconds %= 60;
			Broodwar->sendText("%.2d:%.2d: %s morphs a %s", minutes, seconds, unit->getPlayer()->getName().c_str(), unit->getType().c_str());
		}
	}
}

void ExampleAIModule::onUnitRenegade(BWAPI::Unit unit)
{
}

void ExampleAIModule::onSaveGame(std::string gameName)
{
	Broodwar << "The game was saved to \"" << gameName << "\"" << std::endl;
}

void ExampleAIModule::onUnitComplete(BWAPI::Unit unit)
{
	//Building flag adjustments.
	if (unit->getType() == UnitTypes::Terran_Academy)
		player->buildingAcademy = false;
	else if (unit->getType() == UnitTypes::Terran_Armory)
		player->buildingArmory = false;
	else if (unit->getType() == UnitTypes::Terran_Barracks)
		player->buildingBarracks = false;
	else if (unit->getType() == UnitTypes::Terran_Bunker)
		player->buildingBunker = false;
	else if (unit->getType() == UnitTypes::Terran_Command_Center)
		player->buildingCommandCenter = false;
	else if (unit->getType() == UnitTypes::Terran_Factory)
		player->buildingFactory = false;
	else if (unit->getType() == UnitTypes::Terran_Missile_Turret)
		player->buildingMissileTurret = false;
	else if (unit->getType() == UnitTypes::Terran_Refinery)
		player->buildingRefinery = false;
	else if (unit->getType() == UnitTypes::Terran_Science_Facility)
		player->buildingScienceFacility = false;
	else if (unit->getType() == UnitTypes::Terran_Starport)
		player->buildingStarport = false;
	else if (unit->getType() == UnitTypes::Terran_Supply_Depot)
		player->buildingSupplyDepot = false;

}