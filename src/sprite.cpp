/*
    Written by Leo Martinez and Kailee Kim
*/

#include "sprite.h"

Sprite::Sprite(const std::string &path) {
    // TODO (grant): read from path and deserialize format.
    // for now this is a stub.

    this->addFrame();
}

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
    if (currentFrame < 0 || currentFrame >= frames.size()) {
        return;
    }

    frames.erase(frames.begin() + currentFrame);
}

const QImage &Sprite::getFrame(int index) const {
    // TODO: handle errors?
    return this->frames[index];
}

int Sprite::frameCount() {
    return this->frames.size();
}

void Sprite::saveSprite(const std::string &filePath)
{
    // TODO (grant): serialize here
}
