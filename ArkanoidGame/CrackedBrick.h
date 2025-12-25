#pragma once
#include "Brick.h"

namespace Arkanoid
{
    class CrackedBrick : public Brick
    {
    private:
        int hitsRemaining = 2;
        sf::Texture crackedTexture;
        bool cracked = false;

    public:
        CrackedBrick(float x, float y, float width, float height, int typeIndex);

        void destroy() override;
    };
}