# Project DevAI
---
## Index
+ [Installation Guide](#installation-guide)
+ [Classes and Functions](#classes-functions)
  - ResourceGathering
  - BuildingConstruction
  - UnitAction
  - PlayerInfo
  - MapTools
+ [Importing the AI into the game](#import-ai)











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

## Classes and Functions <a id="classes-functions"></a>
---
### ResourceGathering

### Building Construction

### UnitAction

### PlayerInfo

### MapTools

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
