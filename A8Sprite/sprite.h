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

    /// Add a new frame to this Sprite.
    void addFrame();

    /// Delete the currently selected frame of this Sprite.
    void deleteFrame(int currentFrame);

    /// Load a Sprite project from a JSON file.
    void loadSprite(string filePath);

    /// Save a Sprite project to a JSON file.
    void saveSprite(string filePath);

};

#endif
