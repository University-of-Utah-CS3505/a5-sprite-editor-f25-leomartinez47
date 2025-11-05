#ifndef PROJECT_H
#define PROJECT_H

#include <QObject>
#include <string>
#include "sprite.h"


class Project : public QObject
{
    Q_OBJECT

public:
    explicit Project(QSize dimensions, QObject *parent = nullptr);
    explicit Project(const std::string &path, QObject *parent = nullptr);
    ~Project();

    const QColor &getCurrentColor() const;
    const QImage &getCurrentFrame() const;
    int getCurrentFrameIndex() const;

signals:
    void frameChanged(const QImage &frame);

public slots:
    void onToolChanged(/* TODO: add tool here */);
    void onColorChanged(QColor color);
    void onPixelClicked(QPoint point);
    void onCurrentFrameChanged(int index);
    void onFrameAdded();
    void onFrameRemoved(int index);
    void onSaveRequested();

private:
    Sprite *sprite;

    // TODO: store the tool here
    QColor currentColor;
    int currentFrame;

    // the saved path to the sprite
    // possibly null if not saved yet.
    std::string *path;
};

#endif // PROJECT_H
