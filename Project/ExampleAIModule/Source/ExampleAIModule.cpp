#include "ExampleAIModule.h"
#include <iostream>

using namespace BWAPI;
using namespace Filter;

void ExampleAIModule::onStart()
{/*
	// Hello World!
  Broodwar->sendText("Hello world!");

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
  if ( Broodwar->isReplay() )
  {

    // Announce the players in the replay
    Broodwar << "The following players are in this replay:" << std::endl;
    
    // Iterate all the players in the game using a std:: iterator
    Playerset players = Broodwar->getPlayers();
    for(auto p : players)
    {
      // Only print the player if they are not an observer
      if ( !p->isObserver() )
        Broodwar << p->getName() << ", playing as " << p->getRace() << std::endl;
    }

  }
  else // if this is not a replay
  {
    // Retrieve you and your enemy's races. enemy() will just return the first enemy.
    // If you wish to deal with multiple enemies then you must use enemies().
    if ( Broodwar->enemy() ) // First make sure there is an enemy
      Broodwar << "The matchup is " << Broodwar->self()->getRace() << " vs " << Broodwar->enemy()->getRace() << std::endl;
  }
  */
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
  // Called once every game frame
  // Display the game frame rate as text in the upper left area of the screen
  Broodwar->drawTextScreen(200, 0,  "FPS: %d", Broodwar->getFPS() );
  Broodwar->drawTextScreen(200, 20, "Average FPS: %f", Broodwar->getAverageFPS() );

  // Return if the game is a replay or is paused
  if ( Broodwar->isReplay() || Broodwar->isPaused() || !Broodwar->self() )
    //return;

  // Prevent spamming by only running our onFrame once every number of latency frames.
  // Latency frames are the number of frames before commands are processed.
  if ( Broodwar->getFrameCount() % Broodwar->getLatencyFrames() != 0 )
    return;

  // Iterate through all the units that we own
  for (auto &unit : Broodwar->self()->getUnits())
  {
    // Ignore the unit if it no longer exists
    // Make sure to include this block when handling any Unit pointer!
    if ( !unit->exists() )
      continue;

    // Ignore the unit if it has one of the following status ailments
    if ( unit->isLockedDown() || unit->isMaelstrommed() || unit->isStasised() )
      continue;

    // Ignore the unit if it is in one of the following states
    if ( unit->isLoaded() || !unit->isPowered() || unit->isStuck() )
      continue;

    // Ignore the unit if it is incomplete or busy constructing
    if ( !unit->isCompleted() || unit->isConstructing() )
      continue;

	//Start performing actions
    // If the unit is a worker unit
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

