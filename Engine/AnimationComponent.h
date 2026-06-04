#pragma once

#include "Component.h"
#include "SpriteRendererComponent.h"

#include <string>
#include <vector>
#include <map>

namespace EngineGame
{
struct AnimationClip
{
    // Animation frames reference indices inside a ResourceSystem texture map.
    std::string textureMapName;
    std::vector<int> frames;
    float frameTime = 0.1f;
    bool loop = true;
};

class AnimationComponent : public Component
{
public:
    AnimationComponent(GameObject* gameObject);

    void Update(float deltaTime) override;
    void Render() override;

    void AddAnimation(const std::string& name, const std::string& textureMapName, const std::vector<int>& frames,
                      float frameTime, bool loop);

    void Play(const std::string& name);
    void Stop();

    bool IsPlaying(const std::string& name) const;
    bool IsCurrentAnimation(const std::string& name) const;

private:
    SpriteRendererComponent* spriteRenderer = nullptr;

    std::map<std::string, AnimationClip> animations;

    // Playback state is kept per component so one sprite can switch named clips cheaply.
    std::string currentAnimationName;
    int currentFrameIndex = 0;
    float currentTime = 0.0f;
    bool isPlaying = false;
};
} // namespace EngineGame
