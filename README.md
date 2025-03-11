# Projects
Repository for Unreal and Unity Projects.

## Contents:

- [Unreal](#unreal-projects)

- [Unity](#unity-projects)

## Unreal Projects
- [Marching Squares](#marching-squares)

- [Bloxorz](#bloxorz)
  
- [Cosmic Horror](#untitled-cosmic-horror-game)

- [Boids](#boids)

- [Battleship](#battleships)


# Marching Squares
Implementation of the marching squares algorithm using Unreal's procedural mesh component. The programming is done entirely in Unreal's flavour of C++.
The implementation is based on the following wikipedia article:
https://en.wikipedia.org/wiki/Marching_squares

### Grid, Case Numbers, and Outline
![GridAndLines](https://github.com/Pablo-Arevalo-Escobar/Unreal-Unity/assets/63361048/4aebece3-47d9-4d92-95bf-5c0c0f3f542f)
### Zoomed In
![GridZoom](https://github.com/Pablo-Arevalo-Escobar/Unreal-Unity/assets/63361048/d4760f67-7db7-416e-80b1-f2842aa0dd48)
### Rendering the squares with height and grid
![SquaresWithGrid](https://github.com/Pablo-Arevalo-Escobar/Unreal-Unity/assets/63361048/4925b9d1-fcdd-4dc5-8ef0-539912b6dbc3)
#### Rendering the squares with height and no grid
![NoGrid](https://github.com/Pablo-Arevalo-Escobar/Unreal-Unity/assets/63361048/35bfa98b-b9b0-4cca-8b2d-36fb3a6d9a65)



# Bloxorz
A modern reimagining of the web classic Bloxorz. 
The game is made using Unreal Engine, the programming is done almost entirely in Unreal's flavour of C++ apart from certain UI related functionality.

## Contents:
- [Videos](#videos)

- [Images](#images)

- [Controls](#controls)

- [Rules](#rules)

## Videos

### Game Footage

#### Snow Effects 

https://github.com/user-attachments/assets/a7e45e8b-30cc-44f2-b51b-4bfae915a49f



https://github.com/user-attachments/assets/c14efa24-0d0a-4df6-ae18-8e91db46c0e6

#### Base Game

https://github.com/user-attachments/assets/3c99aa8a-fd3e-471a-b495-94c91cda2486


https://github.com/Pablo-Arevalo-Escobar/Bloxorz/assets/63361048/30a90905-79e0-418d-bc82-54e21d781167


https://github.com/user-attachments/assets/7201f9f7-24b4-4714-b50d-1a1d08d79b85



https://github.com/Pablo-Arevalo-Escobar/Bloxorz/assets/63361048/bb1679ac-1ba1-4b85-b69b-e55a759f361e

### Level Editor Footage
#### Tile viewer


https://github.com/user-attachments/assets/8d5f750d-7444-4d5f-90f7-8d61016a290a


#### Linking buttons to bridges/tiles

https://github.com/user-attachments/assets/fde1d361-5323-48c8-920c-29b1d175bb80


## Controls
Movement:

W/UP_ARROW    = Move up

S/DOWN_ARROW  = Move down

A/LEFT_ARROW  = Move left

D/RIGHT_ARROW = Move right

Special:

SPACE = Toggle between the split cubes 

## Rules


### Tile Types

Black Tile:

  - The black tile is the end point of the level. It is the player's goal to make it here.

Bridge Tile:

  - The bridge tile can open new paths but must be activated by a switch!

Fall/Red Tile:

  - These tiles will fall whenever the player character is standing on top of them.

Torus Tile:
  - The torus tile splits your character into two at puts them at different points of the map.

Circle switches:

  - Circle switches are activated whenever the character is over them regardless if the character is flat or standing.

Cross switches:

  - Cross switches are activated whenever the character is standing over them. If the character is flat, the switch does 
    not react.

### Movement Counter

The amount of moves the player makes in each level is stored and used to calculate their overall score at the end (score feature is not yet implemented).

If the player falls, then the move count is reset to whatever it was at the beginning of the level.

# Untitled Cosmic Horror Game
An experiment in capturing the horror atmosphere.

## Images

### Portals 

![portal1](https://github.com/Pablo-Arevalo-Escobar/Unreal-Unity/assets/63361048/3af44dc6-d23e-4834-9d28-83a90d95a2c3)

![recursive_portal](https://github.com/Pablo-Arevalo-Escobar/Unreal-Unity/assets/63361048/910efd54-d1d8-48b4-a686-e9e32f437d87)

### Lab 
![computer_lighting](https://github.com/Pablo-Arevalo-Escobar/Unreal-Unity/assets/63361048/4c1b5fe9-535f-4639-b371-b1e97d1bf29e)

### Outdoors
![forest](https://github.com/Pablo-Arevalo-Escobar/Unreal-Unity/assets/63361048/abc22b8f-a39b-4433-9d04-1090dcf213e7)


### Observatory
![observatory](https://github.com/Pablo-Arevalo-Escobar/Unreal-Unity/assets/63361048/03588e37-3768-4e79-888a-16d13440d34b)

### Notes
![journal](https://github.com/Pablo-Arevalo-Escobar/Unreal-Unity/assets/63361048/fb369886-b186-495a-9a07-813afa1b03c5)


# **Boids** 
A C++ Unreal implementation of simple boid behaviour based on the principles described by the following wikipedia page:
https://en.wikipedia.org/wiki/Boids

Three key steps in the algorithm:

1. Alignment:

- Steer towards the average heading of local flockmates
	
2. Separation:

- Steer to avoid local flockmates
	
3. Cohesion:

- Steer to move towards the average position (center of mass) of local flockmates
	
  
Current Screenshots:

![](Unreal/Images/Boid1.png)
![](Unreal/Images/Boid2.png)
![](Unreal/BoidParam.png)

# **BattleShips** 

A simple battleship game made in my free time using C++ and blueprints in Unreal Engine.


Current Screenshots:
![](Unreal/Images/BattleShips.png)

![](Unreal/Images/Missile.png)

![](Unreal/Images/MissileArc.png)

![](Unreal/Images/BattleshipMissile.png)

![](Unreal/Images/DamagedShip.png)

![](Unreal/Images/SinkingShip.png)



## Unity Projects

### **Ocean Surface** 


https://github.com/user-attachments/assets/46abca55-cf18-4c6b-b64f-43c7d5e20c78



https://github.com/user-attachments/assets/cc2435c7-c04b-4e9b-8a33-aab5b6f3d069


### **Flappy Bird** January 2023

A flappy bird clone made over a weekend using Unity and Photoshop.
The purpose of this project was to learn the basic functionality of Unity.
Note - Game will automatically restart 2 seconds after you die

Controls:

Space -> Jump


Playable at: https://pablo-arevalo-escobar.github.io/Unreal-Unity/
![](Flappy-Bird/FlappyBirdTheme.png)


