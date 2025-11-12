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

class Project : public QObject
{
    Q_OBJECT

public:
    explicit Project(QSize dimensions, QObject *parent = nullptr);
    explicit Project(const QString &path, QObject *parent = nullptr);
    ~Project();

    const QColor &getCurrentColor() const;
    QImage &getCurrentFrame() const;
    int getCurrentFrameIndex() const;
    QString getName() const;
    QString getPath() const;
    void save(std::function<QString()> requestPath);
    Tool &getCurrentTool() const;

    // TEMP: Both getters below are only used for frameSelectionPane
    // TODO: Either centralize here if we dont want chained getters
    //       or keep. More info in commit message.
    int frameCount() const;
    const QImage &frameAt(int index) const;

signals:
    // To Canvas, emit whenever the canvas needs to be update
    // like on frame change and on editing the image
    void frameChanged(const QImage &frame);
    void nameChanged(const QString &name);

    // Called when the frame selected is changed (ie, whenever another frame is set active)
    void frameSelectionChanged(int index);
    void frameAdded(int index);
    void frameRemoved(int index);
    void initialFrames(std::vector<QImage> frames);

public slots:
    void onToolChanged(Tool *tool);
    void onColorChanged(QColor color);
    void onPixelClicked(QPoint point);

    // From Frame Selection
    void onCurrentFrameChanged(int index);

    // Frame Selection Methods

    ///
    /// \brief onFrameAdded : When a frame needs to be added, adds it at the
    /// index provided, move current frame to the added frame
    /// \param index : The index to add a frame
    ///
    void onFrameAdded(int index);

    ///
    /// \brief onFrameRemoved : When a frame needs to be deleted, delete it at
    /// the index provided, move the current frame to the one before the deleted one.
    /// \param index ; The index to delete a frame
    ///
    void onFrameRemoved(int index);


private:
    QJsonObject toJson();

    Sprite *sprite;

    Tool *currentTool;
    QColor currentColor;
    int currentFrame;
    std::filesystem::path *path;

    std::vector<QImage> initialImages();
};

#endif // PROJECT_H
