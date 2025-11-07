/*
    Written by Leo Martinez, Kailee Kim, and Grant Handy

    JSON Schema:

    {
        "frames": [ "<image data encoded as base64>", ... ],
        "width": ...,
        "height": ...
    }

    All frames are checked on deserialization to verify that they
    match the specified width and height.
*/

#include "sprite.h"

Sprite::Sprite(const std::string &json)
{
    // TODO: deserialize JSON

    this->addFrame();
}

Sprite::Sprite(QSize dimensions)
    : dimensions(dimensions)
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

QImage &Sprite::getFrame(int index)
{
    // TODO: handle errors?
    return this->frames[index];
}

int Sprite::frameCount()
{
    return this->frames.size();
}

QString imageToString(const QImage &image) {
    return QByteArray::fromRawData((const char*)image.bits(), image.sizeInBytes()).toBase64();
}

QImage imageFromString(const QString &base64) {
    return QImage::fromData(QByteArray::fromBase64(base64.toUtf8()));
}

std::string Sprite::toJson()
{
    // TODO: serialize JSON to string
    return std::string("{}");
}
