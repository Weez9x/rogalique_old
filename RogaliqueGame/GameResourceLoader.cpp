#include "GameResourceLoader.h"
#include "ResourceSystem.h"
#include "GameSettings.h"
#include "Logger.h"

namespace RogaliqueGame
{
void GameResourceLoader::LoadAll()
{
    auto resources = EngineGame::ResourceSystem::Instance();

    resources->LoadTexture("test", TEXTURES_PATH + "test.png");
    resources->LoadTextureMap("floor", TEXTURES_PATH + "Floor.png", {16, 16}, 49, false);
    resources->LoadTextureMap("walls", TEXTURES_PATH + "Wall.png", {16, 16}, 48, false);
    resources->LoadTextureMap("player", TEXTURES_PATH + "Human_Soldier_Sword_Shield-Sheet.png", {96, 96}, 80, false);
    resources->LoadTextureMap("slime", TEXTURES_PATH + "Monster_Slime-Sheet.png", {96, 96}, 80, false);
    resources->LoadTextureMap("orc", TEXTURES_PATH + "Orc.png", {100, 100}, 48, false);
    resources->LoadMusic("main_theme", MUSIC_PATH + "Danger.ogg");
    resources->LoadSound("player_attack_1", SOUNDS_PATH + "sword-unsheathe.wav");
    resources->LoadSound("player_attack_2", SOUNDS_PATH + "sword-unsheathe2.wav");
    resources->LoadSound("player_attack_3", SOUNDS_PATH + "sword-unsheathe3.wav");
    resources->LoadSound("player_step_1", SOUNDS_PATH + "footstep05.ogg");
    resources->LoadSound("player_step_2", SOUNDS_PATH + "footstep06.ogg");

    EngineGame::Logger::Instance()->Info("Resources loaded");
}
} // namespace RogaliqueGame
