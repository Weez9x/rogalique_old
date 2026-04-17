#include "GameScene.h"
#include "GameWorld.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "SpriteRendererComponent.h"
#include "ResourceSystem.h"
#include "GameSettings.h"

namespace RogaliqueGame
{
	void GameScene::Start()
	{
		//Load texture, name "test"
		EngineGame::ResourceSystem::Instance()->LoadTexture("test", TEXTURES_PATH + "/test.png");
		//Create new object
		EngineGame::GameObject* obj = EngineGame::GameWorld::Instance()->CreateGameObject("TestObject");
		//Create start position TestObject
		auto transform = obj->GetComponent<EngineGame::TransformComponent>();
		transform->SetWorldPosition(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
		//Add SpriteRenderComponent
		auto spriteRender = obj->AddComponent<EngineGame::SpriteRendererComponent>();
		//Set texture
		spriteRender->SetTexture(*EngineGame::ResourceSystem::Instance()->GetTextureShared("test"));
		//Set size sprite
		spriteRender->SetPixelSize(100, 100);

	}
	void GameScene::Restart()
	{
		//Пока пусто
	}
	void GameScene::Stop()
	{
		//Пока пусто
	}
}