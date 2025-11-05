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
    // Note: the framerate (in gap ms) should probably be stored here to be serialized.

public:
    /// Construct a Sprite with dimensions selected by the user.
    Sprite(QSize dimensions);

    /// Construct a Sprite from a path to our JSON format.
    Sprite(const std::string &path);

    /// Add a new frame to this Sprite.
    void addFrame();

    /// Delete the currently selected frame of this Sprite.
    void deleteFrame(int currentFrame);

    /// Get a frame by its index.
    const QImage &getFrame(int index) const;

    /// Get the number of frames this Sprite contains.
    int frameCount();

    /// Serialize this Sprite to JSON and return the serialized string.
    void saveSprite(const std::string &filePath);
};

#endif
