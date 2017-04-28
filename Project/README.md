# Project DevAI
---
## Index
+ [Installation Guide](#installation-guide)
+ [Classes and Functions](#classes-functions)
  - [ResourceGathering](#RG)
  - [BuildingConstruction](#BC)
  - [UnitAction](#UA)
  - [PlayerInfo](#PI)
  - [MapTools](#MT)
  - [ScoutManager](#SM)
+ [Importing the AI into the game](#import-ai)
+ [Download Scraper](#scraper)











## Installation Guide <a id="installation-guide"></a>
---
In order to install the project and correctly use it it is necessary to download other supporting software as well.
It is also preferable to be working on a device running at least Windows 7.
Below is a list of the required programs to be installed:

+ StarCraft Brood War
  - Must be updated to version 1.16.1
+ Visual Studio Community 2013
  - Can also be Visual Studio Community 2015 with 2013 compiler tools
+ BWAPI 4.1.2
+ BWTA 1.7.1

For supplementary information go to [this website](http://www.teamliquid.net/blogs/485544-intro-to-scbw-ai-development)

Important! Blizzard has taken down their installer for the original game without any patches and replaced it with version 1.18 included which does NOT support this API. As of late, there is no official installer that can be used to get version 1.16.1.

## Classes and Functions <a id="classes-functions"></a>
---
### ResourceGathering <a id="RG"></a>
#### Purpose:
The purpose of the ResourceGathering class is to start the game and have functions pertaining to the economy of the game.
The class contains basic functions and variables to keep the gathering of minerals and gasses efficient.

#### Functions:
#### buildWorker
##### Input
Command Center
##### Processes
If the Command Center is idle and fails to construct a worker more supply will be built. 
Also, if supply is within 4 of the maximum supply, the AI has enough minerals, and it is more than 3 minutes into the game, then more supply will be built.
##### Output
Either a worker is made, a supply depot is made, or nothing happens.

#### workerGather
##### Input
Command Center
##### Processes
Uses type of Command Center to determine race. Selects a worker to perform construction of supply structure.
##### Output
Worker is selected to be able to perform processes.

#### gatherGas
##### Input
Worker
##### Processes
Commands the worker to gather gas.
##### Output
Returns true if the worker is correctly directed to gather gas and false otherwise.

#### gatherMinerals
##### Input
Worker
##### Processes
Commands the worker to gather minerals.
##### Output
Returns true if the worker is correctly directed to gather minerals and false otherwise.

#### getMineralCount
##### Input
None
##### Processes
Gets in-game amount of minerals.
##### Output
Count of minerals.

#### getGasCount
##### Input
None
##### Processes
Get in-game amount of gas.
##### Output
Count of gas.

#### Variables:
The only variables for the class is optimum gatherers for both minerals and gas and the current gatherers for minerals and gas.

### Building Construction <a id="BC"></a>
#### Purpose:
The purpose of this class is to build any buildings necessary to play StarCraft. Any other buildings can be included in this class following this same pattern

#### Functions:
#### buildCenter
##### Input
Command Center, Building location(optional), player flag
##### Processes
Uses type of Command Center to determine race. Selects a worker to perform construction of an expansion.
##### Output
Command Center is built.

#### buildSupply
##### Input
Command Center, player flag
##### Processes
Uses type of Command Center to determine race. Selects a worker to perform construction of supply structure.
##### Output
Supply depot is built

#### buildGas
##### Input
Command Center, player flag
##### Processes
Uses type of Command Center to determine race. Selects a worker to perform construction of gas structure.
##### Output
Gas structure is built.

#### buildBarracks
##### Input
Command Center, player flag
##### Processes
Build Terran Barracks if the input is of Terran type.
##### Output
Barracks is built.

#### buildGateway
##### Input
Command Center, player flag
##### Processes
Build Protoss Gateway if the input is of Protoss type.
##### Output
Gateway is built.

#### buildSpawningPool
##### Input
Command Center, player flag
##### Processes
Build Zerg Spawning Pool if the input is of Zerg type.
##### Output
Spawning Pool is built.

#### checkConstructionStarted
##### Input
Player flag
##### Processes
Check construction flags and switch them off accordingly.
##### Output
Construction status is checked.

#### Variables:
None

### UnitAction <a id="UA"></a>
#### Purpose:
The purpose of this class is to be able to control units individually to perform actions. This includes buildings as well as other movable units.

#### Functions:
#### checkUnitState
##### Input
Unit whose state is being validated.
##### Processes
Checks the state of the input unit.
##### Output
True if unit is not dead, being constructed, disabled

#### trainMarines
##### Input
Barracks to train marines, player flag
##### Processes
Starts process to train marines.
##### Output
Marines are trained.

#### selectArmy
##### Input
None
##### Processes
Selects all marines.
##### Output
Marines are store in a queue.

#### Variables:
None

### PlayerInfo <a id="PI"></a>
#### Purpose:
The purpose of this class is to store variables to keep track of the game state that would otherwise be a global variable.

#### Functions:
#### adjustMineralOffset
##### Input
player flag
##### Processes
Adjusts the mineral offset to store the process of building until it is actually built.
##### Output
Minerals are adjusted.

#### adjustGasOffset
##### Input
player flag
##### Processes
Adjusts the gas offset to store the process of building until it is actually built.
##### Output
Gas is adjusted.

#### resetMinerals
##### Input
player flag
##### Processes
Reset the mineral offset to zero.
##### Output
Offset is reset.

#### resetGas
##### Input
player flag
##### Processes
Reset the mineral offset to zero.
##### Output
Offset is reset.

#### Variables:
Flags to store what buildings are being built, counts of our current barracks and expansions, and offsets in the resource counts for planned buildings.

### MapTools <a id="MT"></a>
#### Purpose:
The purpose of this class is to convert the map being played into data for the AI to interpret and use.

#### Functions:
#### getNextExpansion
##### Input
None
##### Processes
Finds next resource location to build an expansion.
##### Output
The tile position to build the base.

#### getAbsoluteTileDistance
##### Input
Tiles at starting and ending locations.
##### Processes
Calculates absolute distance not considering terrain.
##### Output
Distance

#### Variables:
None

### ScoutManager <a id="SM"></a>
#### Purpose:
The purpose of this class is to send out units to scout and be have units attack enemies that are seen.

#### Functions:
#### scoutStartLocations
##### Input
Unit that will be sent to scout.
##### Processes
Checks all possible base starting locations starting with the furthest away from your starting base.
##### Output
Reference to the scout.

#### attackTarget
##### Input
Unit that was sent to scout and the target to attack
##### Processes
Attacks the target with the scouting unit.
##### Output
Unit attacks target.

#### Variables:
Flag to see if the unit is scouting and the unit that is scouting.


## Importing the AI into the game <a id="import-ai"></a>
---
After everything is downloaded and code has been implemented it is required to compile and import the data into the game.
In order to compile the game you need to go into ExampleAIModule in the Project folder.
Then you need to run ExampleAIModule.vcxproj. When the project loads up change the solution configuration to Release not Debug
In the Solution Explorer window, right click ExampleAIModule and select Build and check to see it was built correctly.
Go back to the Project folder and go into the Release folder. Here you will find ExampleAIModule.dll, copy it.
Go to where StarCraft Brood War is installed and find or create a folder called bwapi-data and inside it find or create a folder called AI.
Inside the AI folder paste the copied file ExampleAIModule.dll and start up ChaosLauncher found in BWAPI. Make sure to run ChaosLauncher as administrator.
In ChaosLauncher make sure BWAPI Injector(1.16.1)RELEASE is checked and highlighted then select config.
In the config menu make sure the path for ai goes to the path where you pasted the .dll file.
Now go back to the ChaosLauncher and click Start then create a custom game and it should be set.

## Download Scraper <a id="scraper"></a>
---
The download scraper downloads the replays off of the gosugamers.net webpage. The usage is to send a command "DownloadScraper.py <StarcraftRace>" where <StarcraftRace> is the replay ID of the video.
