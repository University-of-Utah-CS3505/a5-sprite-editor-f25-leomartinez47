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

QString imageToString(const QImage &image);
QImage imageFromString(const QString &base64);


Sprite::Sprite(QJsonObject &json)
{
    //TODO : error checking for json?
    // deserialize JSON
    QJsonObject sprite = json.value("sprite").toObject();
    QJsonArray jsonFrames = sprite.value("frames").toArray();

    QJsonValue frame;
    foreach(frame, jsonFrames){
        //call imageFromString
        QImage image = imageFromString(frame.toString());
        //take returned image and put in frames vector
        this->frames.push_back(image);
    }

    //this->addFrame();
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

QJsonObject Sprite::toJson(){
    QJsonArray spriteFrames;
    QImage frame;
    foreach(frame, frames){
        //QImage to byte array; byte array as a string
        QString base64 = imageToString(frame);
        //put string in JsonArray
        spriteFrames.push_back(base64);
    }
    QJsonObject sprite;
    sprite["frames"] = spriteFrames;

    sprite["width"] = this->dimensions.width();
    sprite["height"] = this->dimensions.height();

    QJsonObject spriteInfo;
    spriteInfo["sprite"] = sprite;

    return spriteInfo;
}
















