# EE267 Project - First Person Shooter
This is a repository for the final project of EE267 (Spring 2018, Stanford University)(https://stanford.edu/class/ee267/).

This game is a simple first-person shooter only complex enough for the final demonstration of our headsets.

## Opening the Project in Unity

Note: I've deleted the Library and Temp directories for portability; both are automatically generated when you open up a new project.

1. Clone or download/unzip the project
2. Open the project (FPS_Game) from Unity
3. If the scene is empty and untitled, open Scene_1.unity from Assets/Scenes
4. Wait for the scene to finish baking
   - There might be lighting issues if you don't wait for the baking to finish.

## Potential Errors

If you attempt to open the project and you're getting compiler errors:
> The type or namespace name 'Ports' does not exist in the namespace 'System.IO'.
or 
> The type or namespace name 'SerialPort' could not be found.
Go to 
> Edit > Project Settings > Player > Other Settings > Configuration
from the menu bar, and change the API Compatibility Level from .NET 2.0 Subset to .NET 2.0.

If you've attempted to play the game and experience double vision, select CardboardMain from the project Hierarchy window and change the screensize in the Inspector window. We used a Nexus 6 screen size.

If you receive an error
> InvalidOperationException: Specified port is not open.
this is because your VRduino is not connected. You can eliminate this issue by 
1. Feeding data from your VRduino into the appropriate port
   - On a Mac, open Terminal and enter ls /dev/ and you should see "/dev/cu.usbmodem" + some number. Assign this value to portName in the script Assets/Scripts/ReadUSB.cs script 
2. Open the Inspector window, select "Player", and disable the ReadUSB2 script


If you get a timeout error, you can play around with the delay in your project/vrduino/vrduino.ino file on line 125.

# Gameplay

The objective of the game is to destory all the target crates; these are white in color, have a pink particle effect attached, and can be seen floating and rotating above the ground. The particle effect makes them easy to identify across the map.

## Controls

- Camera orientation depends on orientation data passed in from a VRduino. 
  - If you don't have this connected, you can use your mouse or trackpad to move the camera around.

- Use left/down/right/up or a/s/d/w to move around the map

- Press the spacebar to jump

- Left-click or press the trackpad to fire

We connected a third party PS3 controller for our demonstration. I can provide directions attaching an external controller upon request.