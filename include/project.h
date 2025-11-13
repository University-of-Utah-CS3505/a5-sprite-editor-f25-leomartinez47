/*
    Contributors: Natalie Bonilla, Grant Handy, Sean Ho, Kailee Kim, Leo Martinez,
    and Bryce Wiley.
    Date: 11/13/2025
*/

#ifndef PROJECT_H
#define PROJECT_H

#include <filesystem>
#include <functional>

#include <QObject>
#include <QFile>
#include <QString>
#include <QColor>

#include "sprite.h"
#include "tools.h"

const QString PROJECT_FILE_EXTENSION = ".sprite";
const QString PROJECT_FILE_EXTENSION_DESCRIPTION = "Sprite Project (*.sprite)";

/// This is a Model for a Sprite Editor program.
class Project : public QObject
{
    Q_OBJECT

public:
    ///
    /// @brief Construct a new Project.
    /// @param dimensions - The dimensions of the Sprite in this project.
    /// @param parent
    ///
    explicit Project(QSize dimensions, QObject *parent = nullptr);

    ///
    /// @brief Construct a Project from a .sprite file.
    /// @param path - The file path of the .sprite file.
    /// @param parent
    ///
    explicit Project(const QString &path, QObject *parent = nullptr);

    ///
    /// @brief Destructor for Project.
    ///
    ~Project();

    ///
    /// @brief Get the current drawing color.
    /// @return The color.
    ///
    const QColor &getCurrentColor() const;

    ///
    /// @brief Get the Sprite frame that is being edited.
    /// @return A QImage that represents the current Sprite frame.
    ///
    QImage &getCurrentFrame() const;

    ///
    /// @brief Get the Sprite associated with this Project.
    /// @return The Sprite.
    ///
    Sprite *getSprite() const;

    ///
    /// @brief Get an index that represents the ordering of the current frame.
    /// @return The index.
    ///
    int getCurrentFrameIndex() const;

    ///
    /// @brief Get the name of this Project file from the stored file path.
    /// @return The Project name.
    ///
    QString getName() const;

    ///
    /// @brief Get the file path of the file this Project saves to. Will be a
    /// nullptr if Project has not been saved.
    /// @return The file path.
    ///
    QString getPath() const;

    ///
    /// @brief Save this Project.
    /// @param requestPath - The path the Project will be saved to.
    ///
    void save(std::function<QString()> requestPath);

    ///
    /// @brief Export the Project as either a GIF or a PNG.
    /// @param path - The path the Project will be exported to.
    ///
    void exportFile(const QString &path);

    ///
    /// @brief Get the currently selected tool.
    /// @return The selected tool.
    ///
    Tool &getCurrentTool() const;

signals:
    ///
    /// @brief Emit when current frame is changed.
    /// @param frame - The new current frame.
    ///
    void frameChanged(const QImage &frame);

    ///
    /// @brief Emit when the Project name is changed.
    /// @param name - The new Project name.
    ///
    void nameChanged(const QString &name);

public slots:
    ///
    /// @brief Change the current tool.
    /// @param tool - The new current tool.
    ///
    void onToolChanged(Tool *tool);

    ///
    /// @brief Change the color of the pixel based on current tool and current color.
    /// @param point - The point to change.
    ///
    void onPixelClicked(QPoint point);

    //From toolpane's signals that alert the slider's changed values for the RGB values.
    void redChanged(int red);
    void blueChanged(int blue);
    void greenChanged(int green);
    void alphaChanged(int alpha);

    // From Frame Selection
    ///
    /// @brief Change the current frame.
    /// @param index - Identifies the new current frame.
    ///
    void onCurrentFrameChanged(int index);

    // Frame Selection Methods
    ///
    /// @brief Add a frame. It is placed last in the frame ordering.
    ///
    void onFrameAdded();

    ///
    /// @brief Remove a frame.
    /// @param index - Indicates the frame to remove.
    ///
    void onFrameRemoved(int index);

    ///
    /// @brief Set the frame rate of the Sprite.
    /// @param frameRate - The new frame rate.
    ///
    void onFrameRateSet(int frameRate);

private:
    ///
    /// @brief Serialize this Project as a Json.
    /// @return A QJsonObject that stores the Project information.
    ///
    QJsonObject toJson();

    /// The Sprite associated with this Project.
    Sprite *sprite;

    /// The currently selected tool.
    Tool *currentTool;

    /// The currently selected color.
    QColor currentColor;

    /// This indicates the order of the currently selected frame with respect to
    /// the other frames of the Sprite.
    int currentFrame;

    /// This is the file path to the file this Project saves to. If the Project
    /// has not been saved, this will be a nullptr.
    std::filesystem::path *path;
};

#endif
