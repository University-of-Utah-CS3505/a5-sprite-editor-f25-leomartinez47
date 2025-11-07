/*
    Written by Leo Martinez and Kailee Kim
*/

#include "sprite.h"

Sprite::Sprite(const std::string &json)
{
    // TODO: deserialize JSON

    this->addFrame(0);
}

Sprite::Sprite(QSize dimensions)
    : dimensions(dimensions)
{
    addFrame(0);
}

void Sprite::addFrame(int index)
{
    QImage frame(dimensions, QImage::Format_ARGB32);
    frame.fill(0);
    frames.insert(frames.begin() + index, frame);
}

void Sprite::deleteFrame(int currentFrame)
{
    if (currentFrame < 0 || currentFrame >= frames.size()) {
        return;
    }

    frames.erase(frames.begin() + currentFrame);
}

QImage &Sprite::getFrame(int index)
{
    // TODO: handle errors?
    return this->frames[index];
}

int Sprite::frameCount()
{
    return this->frames.size();
}

std::string Sprite::toJson()
{
    // TODO: serialize JSON to string
    return std::string("{}");
}
