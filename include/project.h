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
    QString name();
    void save(std::function<QString()> requestPath);

signals:
    // To Canvas, emit whenever the canvas needs to be update
    // like on frame change and on editing the image
    void frameChanged(const QImage &frame);
    void nameChanged(const QString &name);

public slots:
    void onToolChanged(Tool *tool);
    void onColorChanged(QColor color);
    void onPixelClicked(QPoint point);
    // From Frame Selection
    void onCurrentFrameChanged(int index);

    // Frame Selection Methods
    void onFrameAdded();
    void onFrameRemoved(int index);

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
