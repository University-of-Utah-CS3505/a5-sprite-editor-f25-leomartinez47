#include "project.h"

Project::Project(QSize dimensions, QObject *parent)
    : QObject{parent}
{
    this->sprite = new Sprite(dimensions);
    this->currentFrame = 0;
    this->path = nullptr;
    this->currentTool = new Pencil();
}

Project::Project(const std::string &path, QObject *parent)
    : QObject{parent}
{
    this->sprite = new Sprite(path);
    this->currentFrame = 0;
    this->path = new std::string(path);
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

void Project::onFrameAdded(int index)
{
    // adds a frame at the index to the sprite
    this->sprite->addFrame(index);
    // changes the current frame to the newest frame
    this->onCurrentFrameChanged(index);
    emit this->frameListChanged();
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
    if (0 < index && index < this->sprite->frameCount()) {
        this->onCurrentFrameChanged(index);
    }
    emit this->frameListChanged();
}

void Project::onSaveRequested()
{
    if (!this->path) {
        // TODO (grant): prompt user for save file, then set it.
        return;
    }

    std::string json = this->sprite->toJson();

    // TODO: write JSON to path
}
