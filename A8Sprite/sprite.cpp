/*
    Written by Leo Martinez and Kailee Kim
*/

#include "sprite.h"

Sprite::Sprite() {}


Sprite::Sprite(QSize dimensions) : dimensions(dimensions)
{
    addFrame();
}

void Sprite::addFrame()
{
    QImage frame(dimensions, QImage::Format_ARGB32);
    frame.fill(0);
    frames.push_back(frame);
}

void Sprite::deleteFrame(int currentFrame)
{
    frames.erase(frames.begin() + currentFrame);
}

string Sprite::saveSprite(string filePath)
{
    // TODO: serialize here
}



