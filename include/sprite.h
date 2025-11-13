/*
    Written by Leo Martinez and Kailee Kim

    This object matches this JSON schema:

    {
        "frames": [ "<image data encoded as base64>", ... ],
        "frameRate": <integer>,
        "width": <integer>,
        "height": <integer>
    }

    All frames are checked on deserialization to verify that they
    match the specified width and height.
*/

#ifndef SPRITE_H
#define SPRITE_H

#include <vector>

#include <QImage>
#include <QSize>
#include <QJsonArray>
#include <QJsonObject>

/// This represents a Sprite. A Sprite can have multiple frames. Frames are put in an array by their ordering.
class Sprite {

public:
    /// Construct a Sprite with dimensions selected by the user.
    Sprite(QSize dimensions);

    ///
    /// @brief Construct a Sprite from our JSON format.
    /// @param json - Contains information on the Sprite
    ///
    Sprite(const QJsonObject &json);

    ///
    /// @brief Add a new frame to this Sprite.
    ///
    void addFrame();

    ///
    /// @brief Delete the currently selected frame of this Sprite.
    /// @param currentFrame - The index of 'frames' where the current frame is stored
    ///
    void deleteFrame(std::size_t currentFrame); 

    ///
    /// @brief Get a frame by its index.
    /// @param index - The index of 'frames' where the wanted frame is stored
    /// @return The frame held in 'frames' at index
    ///
    QImage &getFrame(std::size_t index);


    ///
    /// @brief Get the number of frames this Sprite contains.
    /// @return The number of frames in the 'frames' vector
    ///
    int frameCount();

    ///
    /// @brief Serialize this Sprite to JSON.
    /// @return The Sprite serialized as a QJsonObject
    ///
    QJsonObject toJson();

    ///
    /// @brief Export this Sprite as a GIF
    /// @param path - The location the GIF is exported to
    ///
    void writeToGif(const QString &path) const;

    ///
    /// @brief Set the frame rate of this Sprite's animation.
    /// @param frameRate - The frame rate in frames per millisecond
    ///
    void setFrameRate(int frameRate);

    ///
    /// @brief Get the frame rate of this Sprite's animation.
    /// @return The frame rate
    ///
    int getFrameRate();

private:
    /// The frames of this Sprite.
    std::vector<QImage> frames;

    /// The dimensions of the QImages that represent each frame.
    QSize dimensions;

    /// Frame Rate of this Sprite's animation.
    int frameRate;
};

#endif
