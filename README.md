# 3DEngine
A 3D game engine using OpenGL and SDL
Game theme: WWII

Level description:
There will be a small village with some basic buildings in it, with some larger, open spaces and wide roads.
The player will be able to run around and shoot guns, as well as approach tanks and enter them to drive them around in 3rd person. 

## Project start: 03/02/21
I have managed to get the project set up and a basic scene rendered without any objects. There is currently an issue with rendering a triangle (nothing is visible (Fixed: 08/02/21))

## Bug Fix: 08/02/21
The issue was caused by not having the GL context versions set correctly. The issue was fixed a few days ago but only just pushed.

## Update: 09/02/21 (early morning)
I have managed to get the engine to start rendering in 3D. Currently there is a little red triangle that spins arround on the Y axis.
<img src="Documentation_Assets/triangle_spin.gif?raw=true"/>

##Update: 09/02/21 (Late night)
Initial testing:

<img src="Documentation_Assets/initialFPS.png?raw=true"/>

Updated content:
I have managed to get the engine to load models from OBJ files (without using Assimp and instead using my own code) and there is a basic 3D game scene with a rotating monkey model from blender.
<img src="Documentation_Assets/monkey.gif?raw=true"/>