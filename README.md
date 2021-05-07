# 3DEngine
A 3D game engine using OpenGL and SDL

## Game Theme
- WWI
## Level description
There will be a small village with some basic buildings in it, with some larger, open spaces and wide roads.
The player will be able to run around and shoot guns, as well as approach tanks and enter them to drive them around in 3rd person. 
## Project component implementation plan
### Stage One (Mandatory components)
- FPS camera
- Loading Objects from file (Can use external modules)
- 5 or more static models
- Simple terrain (like a plane)
- Movable player
- Textures
- Skybox
### Stage Two
- Height map based terrain
- Dynamic models
### Stage Three
- Load 3D models from file without external modules like Assimp
- HUD
### Stage Four
- Bump mapping
- Lighting/Shadows
- Reflections
- Particle systems

## Project start: 03/02/21
I have managed to get the project set up and a basic scene rendered without any objects. There is currently an issue with rendering a triangle (nothing is visible (Fixed: 08/02/21))

## Bug Fix: 08/02/21
The issue was caused by not having the GL context versions set correctly. The issue was fixed a few days ago but only just pushed.

## Update: 09/02/21 (early morning)
I have managed to get the engine to start rendering in 3D. Currently there is a little red triangle that spins arround on the Y axis.
<img src="Documentation_Assets/triangle_spin.gif?raw=true"/>

## Update: 09/02/21 (Late night)
Initial testing:

<img src="Documentation_Assets/initialFPS.png?raw=true"/>

Updated content:
I have managed to get the engine to load models from OBJ files (without using Assimp and instead using my own code) and there is a basic 3D game scene with a rotating monkey model from blender.
<img src="Documentation_Assets/monkey.gif?raw=true"/>

## Update: 10/02/21
I have managed to implement texture co-ordinate loading into my OBJ loader class and have implemented the textures into the model renderer. I tested everything was loading correctly by putting little up arrows on the texture where the eyes are and loaded that texture (wood.png).
<img src="Documentation_Assets/monkey_textured.gif?raw=true"/>

## Update: 17/02/21
I have made some updates to the model renderer and have gotten a skybox initially implemented, although there is currently a bug making it render black squares instead of textures

## Update: 23/02/21
I have gotten a basic scene put together and implemented into the game with a flat terrain and textured models. There is a skybox but a problem with rendering the textures still exists.
I have also created a scene manager system so that I can create and define multiple scenes for the game and switch between them during runtime (for future use).

## Update: 02/03/21
I have managed to fix the skybox and it is now rendering with texture.

### Current development state:
- All Stage one requirements met

## Update: 09/03/21
I have implemented some dynamic objects into the scene (a widnmill with a spinning fan and a bird that cirles the world)
So far this leaves just the height map terrain left for my stage two requirements
Here is a short gif of a stationary camera in the scene:
<img src="Documentation_Assets/dynamicObjects.gif?raw=true"/>

## Update: 23/03/21
I have started to work on creating a heightmap based terrain that will be built off of the model renderer and progress is slightly slow but hopefully will pick up

## Update: 08/04/21
I have implemented a heightmap based terrain and it seems to work nicely, I just need to create a heightmap that will fit the current map design and then move it into position.
Here is the current state of the height map terrain:
<img src="Documentation_Assets/heightTerrain.png?raw=true"/>

### Current development state:
- All Stage one requirements met
- All Stage two requirements met

## Update: 14/04/21
I have created a terrain heightmap specifically for the main level and textured it in blender with the results bellow:
<img src="Documentation_Assets/ImprovedTerrain.png?raw=true"/>

## Linux build testing: 27/04/21
I managed to build and run the game engine in lubuntu using a VM; however, there are two main issues with the current test:
- The camera movement does not work correctly in the VM because SDL_WarpMouseInWindow() is not working correctly
- The game is running at around 4 FPS (6 FPS if lucky)
I believe that these issues are being caused by the use of a VM as my current GPU (AMD RX5700) is not working with the VM itself, so I will try to run the build on a liveboot version of linux on two different machines (one with NVIDIA GPU and one with intel integrated graphics) to compare results.
<img src="Documentation_Assets/LinuxTestOne.png?raw=true"/>

## Update: 06/05/21
I have implemented a renderer class for sprites so that images can be orthographically rendered to the window on top of the game view
<img src="Documentation_Assets/HUDTest.png?raw=true"/>

- All Stage three requirements met

## Update 07/05/21
I have implemented a simple form of lighting in the scene and added some test code to make a nice looking sunset:
<img src="Documentation_Assets/Lighting.png?raw=true"/>
