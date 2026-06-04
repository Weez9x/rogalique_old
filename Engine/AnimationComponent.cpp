#include "pch.h"
#include "AnimationComponent.h"

#include "GameObject.h"
#include "ResourceSystem.h"
#include "Logger.h"

#include <cassert>

namespace EngineGame
{
AnimationComponent::AnimationComponent(GameObject* gameObject) : Component(gameObject)
{
    spriteRenderer = gameObject->GetComponent<SpriteRendererComponent>();

    if (spriteRenderer == nullptr)
    {
        Logger::Instance()->Error("AnimationComponent requires SpriteRendererComponent");
    }

    assert(spriteRenderer != nullptr && "AnimationComponent requires SpriteRendererComponent");
}

void AnimationComponent::Update(float deltaTime)
{
    if (!isPlaying || spriteRenderer == nullptr)
    {
        return;
    }

    auto animationIt = animations.find(currentAnimationName);
    if (animationIt == animations.end())
    {
        Logger::Instance()->Warning("Animation not found: " + currentAnimationName);
        isPlaying = false;
        return;
    }

    AnimationClip& clip = animationIt->second;

    if (clip.frames.empty())
    {
        Logger::Instance()->Warning("Animation has no frames: " + currentAnimationName);
        isPlaying = false;
        return;
    }

    currentTime += deltaTime;

    if (currentTime < clip.frameTime)
    {
        return;
    }

    // Advance by whole frames; this keeps animation state simple for fixed-size sprite sheets.
    currentTime = 0.0f;
    currentFrameIndex++;

    if (currentFrameIndex >= static_cast<int>(clip.frames.size()))
    {
        if (clip.loop)
        {
            currentFrameIndex = 0;
        }
        else
        {
            currentFrameIndex = static_cast<int>(clip.frames.size()) - 1;
            isPlaying = false;
        }
    }

    int textureIndex = clip.frames[currentFrameIndex];

    spriteRenderer->SetTexture(
        *ResourceSystem::Instance()->GetTextureMapElementShared(clip.textureMapName, textureIndex));
}

void AnimationComponent::Render() {}

void AnimationComponent::AddAnimation(const std::string& name, const std::string& textureMapName,
                                      const std::vector<int>& frames, float frameTime, bool loop)
{
    if (frames.empty())
    {
        Logger::Instance()->Warning("Trying to add animation without frames: " + name);
        return;
    }

    if (frameTime <= 0.0f)
    {
        Logger::Instance()->Warning("Animation frameTime <= 0. Default value used.");
        frameTime = 0.1f;
    }

    AnimationClip clip;
    clip.textureMapName = textureMapName;
    clip.frames = frames;
    clip.frameTime = frameTime;
    clip.loop = loop;

    animations[name] = clip;

    Logger::Instance()->Info("Animation added: " + name);
}

void AnimationComponent::Play(const std::string& name)
{
    if (currentAnimationName == name && isPlaying)
    {
        // Avoid restarting a loop every frame when gameplay asks to play the same animation.
        return;
    }

    auto animationIt = animations.find(name);
    if (animationIt == animations.end())
    {
        Logger::Instance()->Warning("Cannot play animation. Animation not found: " + name);
        return;
    }

    currentAnimationName = name;
    currentFrameIndex = 0;
    currentTime = 0.0f;
    isPlaying = true;

    const AnimationClip& clip = animationIt->second;

    spriteRenderer->SetTexture(
        *ResourceSystem::Instance()->GetTextureMapElementShared(clip.textureMapName, clip.frames[currentFrameIndex]));
}

void AnimationComponent::Stop()
{
    isPlaying = false;
}

bool AnimationComponent::IsPlaying(const std::string& name) const
{
    return isPlaying && currentAnimationName == name;
}
bool AnimationComponent::IsCurrentAnimation(const std::string& name) const
{
    return currentAnimationName == name;
}
} // namespace EngineGame
