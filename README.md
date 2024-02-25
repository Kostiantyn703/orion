Orion.

Simple endless vertical scroller shooter.

Tools used:
  - SDL
  - OpenGL
  - Glad
  - Freetype

Game systems.

Gameplay.

Whole process is calculates in the world module.
Ship spawner spawns enemies based on the data taken from script, parsed in the script module.
Frequency of spawns based on difficulty value.
Meteors are spawned close to the player, accelerating on difficulty rise.
Objects are removed from global storage if intersect with opponent (player with enemy bullet), or moving behind the lower border.
Player bullets removed when intersect with upper border.

Script module.

On the game launch, system parses "behavior" scripts defined by user.
The template for the script:
  - type - the number of ships texture to be displayed
  - shooter - if item is present, the enemy will shoot
  - spawn - position or range where the ship should be spawned
  - behavior - consists of blocks, which define the flight path:
      1. direction
      2. position/range when to change direction
      3. axis rule when to change direction
    Example: { forward, [20-40], y_pos } means "fly forward until the range of 20-40 in y axis".

Renderer.

Simple 2D renderer
Used different shaders for drawing scolling background, textues, text. 

Collision system.

Simple aabb calculations. Bit flags are used for objects to know with whom the are intersected.
When player intersects with anything - game ends.
Objects of type border were added to not let player go outside the screen.


