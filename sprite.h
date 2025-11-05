/*
    Written by Leo Martinez and Kailee Kim
*/

#ifndef SPRITE_H
#define SPRITE_H

#include <vector>
#include <QImage>
#include <string>
#include <QSize>

using std::vector;
using std::string;

class Sprite {
    /// The frames of this Sprite.
    vector<QImage> frames;
    QSize dimensions;

public:
    /// Construct a Sprite with dimensions selected by the user.
    Sprite(QSize dimensions);

    /// Eventually construct from a deserialized JSON sprite project
    /// Note: this is currently replacing loadSprite since we don't
    /// necessarily want the deserialization to happen in a Sprite itself.
    Sprite();

    /// Add a new frame to this Sprite.
    void addFrame();

    /// Delete the currently selected frame of this Sprite.
    void deleteFrame(int currentFrame);

    /// Serialize this Sprite to JSON and return the serialized string.
    string saveSprite(string filePath);

};

#endif
