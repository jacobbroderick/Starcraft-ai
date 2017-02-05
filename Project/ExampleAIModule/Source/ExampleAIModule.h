#pragma once
#include <BWAPI.h>
#include <BWTA.h>
#include <windows.h>
#include <vector>
#include "ResourceGathering.h"
#include "BuildingConstruction.h"
#include "UnitAction.h"


// Remember not to use "Broodwar" in any global class constructor!
class ExampleAIModule : public BWAPI::AIModule
{
public:
  // Virtual functions for callbacks, leave these as they are.
  virtual void onStart();
  virtual void onEnd(bool isWinner);
  virtual void onFrame();
  void ExampleAIModule::drawTerrainData();
  void ExampleAIModule::onSendText(std::string text);
};
