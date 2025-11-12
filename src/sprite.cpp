/*
    Written by Leo Martinez, Kailee Kim, and Grant Handy
*/

#include <QIODevice>
#include <QBuffer>
#include <QDebug>

#include "sprite.h"

// QImage expects a C-style string.
const char *FORMAT = "PNG";

Sprite::Sprite(const QJsonObject &sprite)
{
    if(!sprite.contains("frames") || !sprite.contains("width") || !sprite.contains("height")
        || !sprite.contains("frameRate")) {
        throw std::invalid_argument("Sprite information could not be retrieved.");
    }

    this->dimensions = QSize(
        sprite.value("width").toInteger(),
        sprite.value("height").toInteger()
    );

    this->frameRate = sprite.value("frameRate").toInteger();

    QJsonArray jsonFrames = sprite.value("frames").toArray();
    for (QJsonValue &&frame : jsonFrames) {
        QImage image;
        if(!image.loadFromData(QByteArray::fromBase64(frame.toString().toUtf8()), FORMAT)) {
            throw std::invalid_argument("Unsupported format.");
        }

        this->frames.push_back(image);
    }
}

Sprite::Sprite(QSize dimensions)
    : dimensions(dimensions)
{
    addFrame();
}

void Sprite::addFrame()
{
    QImage frame = QImage(dimensions, QImage::Format_ARGB32);
    frame.fill(Qt::transparent);
    frames.push_back(frame);
}

void Sprite::deleteFrame(std::size_t currentFrame)
{
    if (currentFrame >= frames.size()) {
        return;
    }

    frames.erase(frames.begin() + currentFrame);
}

QImage &Sprite::getFrame(std::size_t index)
{
    if(index < 0 || index >= frames.size()) {
        throw std::invalid_argument("Invalid index.");
    }
    return this->frames[index];
}

int Sprite::frameCount()
{
    return this->frames.size();
}

QJsonObject Sprite::toJson()
{
    QJsonArray jsonFrames;

    for (const QImage &image : frames) {
        QByteArray data;

        QBuffer buffer = QBuffer(&data);
        buffer.open(QIODevice::WriteOnly);
        if(!image.save(&buffer, FORMAT)){
            throw std::invalid_argument("Could not save the file.");
        }
        buffer.close();

        jsonFrames.push_back(QString(data.toBase64()));
    }

    return QJsonObject({
        { "frames", jsonFrames },
        { "frameRate", this->frameRate },
        { "width", this->dimensions.width() },
        { "height", this->dimensions.height() },
    });
}
