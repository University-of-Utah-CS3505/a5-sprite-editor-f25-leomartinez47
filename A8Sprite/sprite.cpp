/*
    Written by Leo Martinez and Kailee Kim
*/

#include "sprite.h"

Sprite::Sprite() {

}

void Sprite::deleteFrame(int currentFrame)
{
    frames.erase(frames.begin() + currentFrame);
}

void Sprite::saveSprite(string filePath)
{
    // TODO: serialize here
}



