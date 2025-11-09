#include "project.h"

Project::Project(QSize dimensions, QObject *parent)
    : QObject{parent}
{
    this->sprite = new Sprite(dimensions);
    this->currentFrame = 0;
    this->path = nullptr;
    this->currentTool = new Pencil();
}

Project::Project(const QString &path, QObject *parent)
    : QObject{parent}
{
    //TODO error checking?
    //read in a file and call the Sprite constructor that takes a Json
    QFile jsonFile(QString::fromStdString(path));
    jsonFile.open(QIODevice::ReadWrite);
    QJsonDocument doc = QJsonDocument::fromJson(jsonFile.readAll());
    QJsonObject json = doc.object();

    this->sprite = new Sprite(json);
    this->currentFrame = 0;
    this->path = new QString(path);
    this->currentTool = new Pencil();
}

Project::~Project()
{
    if (this->path) {
        delete this->path;
    }

    delete this->sprite;
    delete this->currentTool;
}

const QColor &Project::getCurrentColor() const
{
    return this->currentColor;
}

int Project::getCurrentFrameIndex() const
{
    return this->currentFrame;
}

QImage &Project::getCurrentFrame() const
{
    return this->sprite->getFrame(this->currentFrame);
}

void Project::onToolChanged(Tool *tool)
{
    if (tool != nullptr) {
        this->currentTool = tool;
    }
}

void Project::onColorChanged(QColor color)
{
    this->currentColor = color;
}

void Project::onPixelClicked(QPoint point)
{
    this->currentTool->apply(point, this->getCurrentFrame(), this->currentColor);
}

void Project::onCurrentFrameChanged(int index)
{
    if (index < 0 || index >= this->sprite->frameCount()) {
        return;
    }

    this->currentFrame = index;
    emit this->frameChanged(this->getCurrentFrame());
}

void Project::onFrameAdded()
{
    this->sprite->addFrame();
    this->currentFrame++;

    emit this->frameChanged(this->getCurrentFrame());
}

void Project::onFrameRemoved(int index)
{
    if (index < 0 || index >= this->sprite->frameCount()) {
        return;
    }

    if (this->currentFrame == index && index != 0) {
        this->currentFrame--;
    }

    this->sprite->deleteFrame(index);
    emit this->frameChanged(this->getCurrentFrame());
}

void Project::onSaveRequested(){
    if (!this->path) {
        // TODO (grant): prompt user for save file, then set it.
        return;
    }

    QJsonObject json = this->sprite->toJson();

    // TODO: add to json any other information we want

    // write JSON to path
    QByteArray jsonArr = QJsonDocument(json).toJson();
    QFile saveFile(*path);
    saveFile.open(QIODevice::ReadWrite);

    QTextStream qStream(&saveFile);
    qStream << jsonArr;
}
