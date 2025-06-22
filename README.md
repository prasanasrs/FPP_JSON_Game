# FPP_JSON_Game

Project Overview
This project is a First-Person Shooter (FPS) built in Unreal Engine 5 using C++. The player can shoot destructible target boxes that spawn dynamically in the game world based on online JSON data. Each box has its own type, color, health, and score value, making the game extendable and configurable from a remote server.

Key Features
1. First-Person Character
  Player moves, looks around, and shoots using line trace (hitscan).

  Basic camera, input bindings, and fire logic are set up in C++.

2. Dynamic Box Spawning
  On game start, a JSON file is fetched from a remote URL using HTTP.

  JSON describes a list of box types and their properties, and object placements.

  Each box is spawned in the world with:

  Custom position, rotation, and scale.

  Dynamic material color.

  Health and score attributes.

3. Damage and Destruction
  Shooting performs a line trace from the camera.

  If a target is hit, it receives damage.

  When health reaches zero:

  A hit particle effect is spawned.

  A destroy particle effect plays.

  The box is destroyed.

4. Scoring System
  Each box awards points to the player based on its score value.

  The game mode tracks total player score, which can be expanded for leaderboards.

5. Visual Feedback
  Particle effects on hit and destroy.

  Impact direction is respected for realism.
