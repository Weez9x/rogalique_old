#pragma once

#include <string>

namespace RogaliqueGame
{
const std::string RESOURCES_PATH = "Resources/";
const std::string TEXTURES_PATH = RESOURCES_PATH + "Textures/";
const std::string FONTS_PATH = RESOURCES_PATH + "Fonts/";
const std::string SOUNDS_PATH = RESOURCES_PATH + "Sounds/";
const std::string MUSIC_PATH = RESOURCES_PATH + "Music/";

constexpr unsigned int SCREEN_WIDTH = 800;
constexpr unsigned int SCREEN_HEIGHT = 600;
constexpr float TIME_PER_FRAME = 1.f / 60.f;
constexpr float CHARACTER_SPRITE_SIZE = 576.f;

// Maze
constexpr int MAZE_WIDTH = 21;
constexpr int MAZE_HEIGHT = 15;
constexpr int TILE_SIZE = 100;

constexpr int PORTAL_CLOSED_TILE = 17;
constexpr int PORTAL_OPEN_TILE = 16;

// PlayerUI
constexpr unsigned int PLAYER_UI_FONT_SIZE = 22;

constexpr float PLAYER_UI_X = 20.f;
constexpr float PLAYER_UI_Y = 20.f;

// Player
constexpr float PLAYER_START_X = 400.f;
constexpr float PLAYER_START_Y = 300.f;
constexpr float PLAYER_MAX_HEALTH = 100.f;
constexpr float PLAYER_ARMOR = 5.f;
constexpr int PLAYER_LIVES = 3;

// Player attack
constexpr float PLAYER_ATTACK_RANGE = 180.f;
constexpr float PLAYER_ATTACK_COOLDOWN = 0.5f;
constexpr float PLAYER_ATTACK_DURATION = 0.45f;
constexpr float PLAYER_DAMAGE_MOMENT = 0.22f;
constexpr float PLAYER_DAMAGE = 20.f;

// Enemies
constexpr int START_SLIME_COUNT = 3;
constexpr int START_ORC_COUNT = 1;

constexpr float SLIME_MAX_HEALTH = 50.f;
constexpr float SLIME_ARMOR = 2.f;
constexpr float SLIME_DAMAGE = 10.f;

constexpr float ORC_MAX_HEALTH = 100.f;
constexpr float ORC_ARMOR = 4.f;
constexpr float ORC_DAMAGE = 20.f;

constexpr float ENEMY_DETECTION_RADIUS = 250.f;
constexpr float ENEMY_ATTACK_RANGE = 95.f;
constexpr float ENEMY_ATTACK_COOLDOWN = 1.f;
constexpr float ENEMY_ATTACK_DURATION = 0.45f;
constexpr float ENEMY_DAMAGE_MOMENT = 0.22f;

constexpr float ENEMY_SPAWN_DISTANCE_FROM_PLAYER = 500.f;
constexpr float ENEMY_SPAWN_BORDER_PADDING = 200.f;

constexpr float ENEMY_MOVE_SPEED = 1.5f;

// Respawn
constexpr float RESPAWN_DELAY = 1.f;
constexpr float INVULNERABILITY_TIME = 5.f;
constexpr float BLINK_INTERVAL = 0.12f;

// Level builder
constexpr int RANDOM_POSITION_ATTEMPTS = 100;
constexpr float SPAWN_BORDER_PADDING = 200.f;

// Health bar
constexpr float DEFAULT_HEALTH_BAR_WIDTH = 70.f;
constexpr float DEFAULT_HEALTH_BAR_HEIGHT = 8.f;

constexpr float DEFAULT_HEALTH_BAR_OFFSET_X = 0.f;
constexpr float DEFAULT_HEALTH_BAR_OFFSET_Y = -70.f;

} // namespace RogaliqueGame