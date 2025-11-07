#ifndef PROJECT_H
#define PROJECT_H

#include <QObject>
#include <string>
#include "sprite.h"
#include "tools.h"

class Project : public QObject
{
    Q_OBJECT

public:
    explicit Project(QSize dimensions, QObject *parent = nullptr);
    explicit Project(const std::string &path, QObject *parent = nullptr);
    ~Project();

    const QColor &getCurrentColor() const;
    QImage &getCurrentFrame() const;
    int getCurrentFrameIndex() const;

signals:
    // To Canvas, emit whenever the canvas needs to be update
    // like on frame change and on editing the image
    void frameChanged(const QImage &frame);

public slots:
    void onToolChanged(Tool *tool);
    void onColorChanged(QColor color);
    void onPixelClicked(QPoint point);
    // From Frame Selection
    void onCurrentFrameChanged(int index);

    // Frame Selection Methods
    void onFrameAdded();
    void onFrameRemoved(int index);
    void onSaveRequested();

    // void addFrame();
    // void deleteFrame();
    // void nextFrame();
    // void previousFrame();

private:
    Sprite *sprite;

    Tool *currentTool;
    QColor currentColor;
    int currentFrame;

    // the saved path to the sprite
    // possibly null if not saved yet.
    std::string *path;
};

#endif // PROJECT_H
