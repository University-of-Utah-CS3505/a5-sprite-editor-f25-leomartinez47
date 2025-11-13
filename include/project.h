/*
    Written by TODO
*/

#ifndef PROJECT_H
#define PROJECT_H

#include <filesystem>
#include <functional>

#include <QObject>
#include <QFile>
#include <QString>

#include "sprite.h"
#include "tools.h"

const QString PROJECT_FILE_EXTENSION = ".sprite";
const QString PROJECT_FILE_EXTENSION_DESCRIPTION = "Sprite Project (*.sprite)";

/// This is a Model for a Sprite Editor program. A Sprite can have multiple frames
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

    // get the sprite pointer?? legal?? - leo and sean previewpane workers
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
    /// @return A Tool object.
    ///
    Tool &getCurrentTool() const;

signals:
    // To Canvas, emit whenever the canvas needs to be update
    // like on frame change and on editing the image
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
    /// @brief Change the current color.
    /// @param color - The new current color.
    ///
    void onColorChanged(QColor color);

    ///
    /// @brief Change the color of the pixel based on current tool and current color.
    /// @param point - The point to change.
    ///
    void onPixelClicked(QPoint point);

    // From Frame Selection
    ///
    /// @brief Change the current frame.
    /// @param index - Indicates the ordering of the new current frame.
    ///
    void onCurrentFrameChanged(int index);

    // Frame Selection Methods
    void onFrameAdded();
    void onFrameRemoved(int index);

    // From Preview Pane, sets frame rate in the sprite
    void onFrameRateSet(int frameRate);

    // void addFrame();
    // void deleteFrame();
    // void nextFrame();
    // void previousFrame();

private:
    QJsonObject toJson();

    Sprite *sprite;

    Tool *currentTool;
    QColor currentColor;
    int currentFrame;
    std::filesystem::path *path;
};

#endif // PROJECT_H
