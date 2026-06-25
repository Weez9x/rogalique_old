#include "pch.h"
#include "GameWorld.h"

namespace EngineGame
{
GameWorld* GameWorld::Instance()
{
    static GameWorld world;
    return &world;
}

void GameWorld::Update(float deltaTime)
{
    for (int i = 0; i < gameObjects.size(); i++)
    {
        gameObjects[i]->Update(deltaTime);
    }
}
void GameWorld::FixedUpdate(float deltaTime)
{
    fixedCounter += deltaTime;
    if (fixedCounter > PhysicsSystem::Instance()->GetFixedDeltaTime())
    {
        // Physics advances at a fixed step even when render frames vary.
        fixedCounter -= PhysicsSystem::Instance()->GetFixedDeltaTime();
        PhysicsSystem::Instance()->Update();
    }
}
void GameWorld::Render()
{
    for (int i = 0; i < gameObjects.size(); i++)
    {
        gameObjects[i]->Render();
    }
}
void GameWorld::LateUpdate()
{
    // Delayed destruction keeps object arrays stable during Update/Render iteration.
    for (int i = markedToDestroyGameObjects.size() - 1; i >= 0; i--)
    {
        DestroyGameObjectImmediate(markedToDestroyGameObjects[i]);
    }

    auto actions = lateActions;
    lateActions.clear();

    for (auto& action : actions)
    {
        if (action)
        {
            action();
        }
    }
}

GameObject* GameWorld::CreateGameObject()
{
    GameObject* newGameObject = new GameObject();
    gameObjects.push_back(newGameObject);
    return newGameObject;
}
GameObject* GameWorld::CreateGameObject(std::string name)
{
    GameObject* newGameObject = new GameObject(name);
    gameObjects.push_back(newGameObject);
    return newGameObject;
}
void GameWorld::DestroyGameObject(GameObject* gameObject)
{
    markedToDestroyGameObjects.push_back(gameObject);
}
void GameWorld::Clear()
{
    // Clear root objects only; child objects are deleted through their parent's hierarchy.
    for (int i = gameObjects.size() - 1; i >= 0; i--)
    {
        if (gameObjects[i] == nullptr)
        {
            continue;
        }

        if (gameObjects[i]->GetComponent<TransformComponent>()->GetParent() == nullptr)
        {
            DestroyGameObjectImmediate(gameObjects[i]);
        }
    }

    fixedCounter = 0.f;
}

void GameWorld::EnqueueLateAction(std::function<void()> action)
{
    lateActions.push_back(action);
}

void GameWorld::Print() const
{
    for (auto& obj : gameObjects)
    {
        if (obj == nullptr)
        {
            continue;
        }
        if (obj->GetComponent<TransformComponent>()->GetParent() == nullptr)
        {
            obj->Print();
        }
    }
}

void GameWorld::DestroyGameObjectImmediate(GameObject* gameObject)
{
    auto parent = gameObject->GetComponent<TransformComponent>()->GetParent();
    if (parent != nullptr)
    {
        parent->GetGameObject()->RemoveChild(gameObject);
    }

    for (auto transform : gameObject->GetComponentsInChildren<TransformComponent>())
    {
        GameObject* gameObjectToDelete = transform->GetGameObject();

        gameObjects.erase(std::remove_if(gameObjects.begin(), gameObjects.end(),
                                         [gameObjectToDelete](GameObject* obj) { return obj == gameObjectToDelete; }),
                          gameObjects.end());
        markedToDestroyGameObjects.erase(
            std::remove_if(markedToDestroyGameObjects.begin(), markedToDestroyGameObjects.end(),
                           [gameObjectToDelete](GameObject* obj) { return obj == gameObjectToDelete; }),
            markedToDestroyGameObjects.end());

        delete gameObjectToDelete;
    }
}
} // namespace EngineGame
