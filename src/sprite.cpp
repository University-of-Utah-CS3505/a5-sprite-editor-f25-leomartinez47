/*
    Written by Leo Martinez, Kailee Kim, and Grant Handy
*/

#include "sprite.h"

Sprite::Sprite(const QJsonObject &sprite)
{
    this->dimensions = QSize(
        sprite.value("width").toInteger(),
        sprite.value("height").toInteger()
    );

    // TODO: fix QJsonObject::value ambiguous warning?
    QJsonArray jsonFrames = sprite.value("frames").toArray();

    qDebug() << this->dimensions << " sprite created with " << jsonFrames.size() << " frames";

    for (QJsonValue &&frame : jsonFrames) {
        QImage image = QImage::fromData(QByteArray::fromBase64(frame.toString().toUtf8()));

        // TODO: throw exception and catch in parent?
        Q_ASSERT(this->dimensions == image.size());

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
    QImage frame(dimensions, QImage::Format_ARGB32);
    frame.fill(0);
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
    // TODO: handle errors?
    return this->frames[index];
}

int Sprite::frameCount()
{
    return this->frames.size();
}

QJsonObject Sprite::toJson(){
    QJsonArray jsonFrames;

    for (const QImage &image : frames) {
        QByteArray data = QByteArray::fromRawData((const char*)image.bits(), image.sizeInBytes());
        jsonFrames.push_back(QString(data.toBase64()));
    }

    return QJsonObject({
        { "frames", jsonFrames },
        { "width", this->dimensions.width() },
        { "height", this->dimensions.height() },
    });
}
