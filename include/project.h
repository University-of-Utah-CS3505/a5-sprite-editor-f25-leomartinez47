#ifndef PROJECT_H
#define PROJECT_H

#include <filesystem>
#include <functional>

#include <QObject>
#include <QFile>
#include <QString>
#include <QGraphicsOpacityEffect>
#include <QColor>

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

signals:
    // To Canvas, emit whenever the canvas needs to be update
    // like on frame change and on editing the image
    void frameChanged(const QImage &frame);
    void nameChanged(const QString &name);

public slots:
    void onToolChanged(Tool *tool);
    //void onColorChanged(QColor color); //Split into four slots that get each color value/alpha

    //From toolpane's signals that alert the slider's changed values for the RGB values.
    void redChanged(int newRed);
    void blueChanged(int newBlue);
    void greenChanged(int newGreen);
    void alphaChanged(int newOpacity);

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

    //Instance variables to track and update the individual RGB sliders.
    int currentRed;
    int currentGreen;
    int currentBlue;
    int currentOpacity;

    std::filesystem::path *path;
};

#endif // PROJECT_H
