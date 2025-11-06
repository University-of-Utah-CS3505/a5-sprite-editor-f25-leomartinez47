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
    // To Canvas, emit whenever the canvas needs to be update
    // like on frame change and on editing the image
    void frameChanged(const QImage &frame);

public slots:
    void onToolChanged(/* TODO: add tool here */);
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
