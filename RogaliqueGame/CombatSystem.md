# Combat System

## Overview

Combat is built from small components attached to game objects. The player and enemies use the same health and melee-damage primitives, while input, AI, respawn, UI, and game-state transitions stay in separate components.

## Key files

- `Player.cpp` creates the player object, adds movement, health, lives, HUD, melee attack, player attack input, respawn, collider, and camera.
- `Slime.cpp` and `Orc.cpp` create enemies with health, health bars, melee attack, respawn, collider, and `EnemyFollowComponent`.
- `MeleeAttackComponent.cpp` applies damage to a target `HealthComponent`.
- `PlayerAttackComponent.cpp` handles Space input, cooldown, attack timing, and target selection through `EnemySpawner`.
- `EnemyFollowComponent.cpp` moves enemies toward the player and starts enemy attacks when the player is in range.
- `RespawnComponent.cpp` handles death, respawn delay, invulnerability blinking, and enemy kill counting.
- `PlayerLivesComponent.cpp` subtracts player lives and switches to `GameState::GameOver` when lives reach zero.
- `ExitPortalComponent.cpp` opens the portal after enough kills and switches to `GameState::Win` when the player enters it.
- `GameStateUIComponent.cpp` renders Win/GameOver screens and queues Restart or NextLevel actions.

## Player attack flow

1. `PlayerAttackComponent::Update` runs only while `GameStateManager::IsPlaying()` is true.
2. Pressing Space starts an attack if the cooldown is ready.
3. The attack animation begins immediately.
4. At `damageMoment`, the component asks `EnemySpawner` for the closest enemy in range.
5. `MeleeAttackComponent::Attack` applies damage to the target's `HealthComponent`.
6. If the target dies, `RespawnComponent` counts one kill and starts the enemy respawn cycle.

## Enemy attack flow

1. `EnemyFollowComponent::Update` runs only while the game state is `Playing`.
2. The enemy idles outside detection range.
3. Inside detection range, the enemy follows the player.
4. Inside attack range, movement stops and an attack starts after cooldown.
5. At the configured damage moment, `MeleeAttackComponent` damages the player.
6. If the player dies, `PlayerLivesComponent` removes one life.

## Progress and level flow

- `GameProgress::CurrentKills` increases only when an enemy death is first handled by `RespawnComponent`.
- `GameProgress::RequiredKills` controls when the exit portal opens.
- Entering an opened portal sets `GameState::Win`.
- Pressing `R` on Win queues `GameScene::NextLevel`.
- `GameProgress::NextLevel` increments the level, resets current kills, and increases required kills.

## Game over and restart

- The player starts with `PLAYER_LIVES`.
- Each player death removes one life.
- If no lives remain, `PlayerLivesComponent` sets `GameState::GameOver`.
- Pressing `R` on GameOver queues `GameScene::RestartLevel`.
- `GameProgress::Reset` returns the run to level 1, zero kills, and the initial required kill count.

## State gate

`GameStateManager` is the lightweight state machine for the game:

- `Playing` allows movement, AI, attacks, respawn timers, and portal logic.
- `Win` shows the victory overlay and waits for NextLevel or Exit input.
- `GameOver` shows the defeat overlay and waits for Restart or Exit input.

Scene rebuilds are queued through `GameWorld::EnqueueLateAction` so Restart and NextLevel do not clear the world while the current `Update` loop is still iterating objects.
