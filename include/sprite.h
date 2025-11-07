/*
    Written by Leo Martinez and Kailee Kim
*/

#ifndef SPRITE_H
#define SPRITE_H

#include <vector>
#include <QImage>
#include <string>
#include <QSize>
#include <QJsonArray>
#include <QJsonObject>
#include "external/base64.h"

class Sprite {
    /// The frames of this Sprite.
    std::vector<QImage> frames;
    QSize dimensions;
    // Note: the framerate (in gap ms) should probably be stored here to be serialized.

public:
    /// Construct a Sprite with dimensions selected by the user.
    Sprite(QSize dimensions);

    /// Construct a Sprite from our JSON format.
    Sprite(QJsonObject &json);

    /// Add a new frame to this Sprite.
    void addFrame();

    /// Delete the currently selected frame of this Sprite.
    void deleteFrame(int currentFrame);

    /// Get a frame by its index.
    QImage &getFrame(int index);

    /// Get the number of frames this Sprite contains.
    int frameCount();

    /// Serialize this Sprite to JSON.
    QJsonObject toJson();
};

#endif
