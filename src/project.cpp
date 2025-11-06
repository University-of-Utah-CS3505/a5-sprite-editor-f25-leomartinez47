#include "project.h"

Project::Project(QSize dimensions, QObject *parent)
    : QObject{parent}
{
    this->sprite = new Sprite(dimensions);
    this->currentFrame = 0;
    this->path = nullptr;
}

Project::Project(const std::string &path, QObject *parent)
    : QObject{parent}
{
    this->sprite = new Sprite(path);
    this->currentFrame = 0;

    // make a copy to own it.
    this->path = new std::string(path);
}

Project::~Project()
{
    if (this->path) {
        delete this->path;
    }

    delete this->sprite;
}

const QColor &Project::getCurrentColor() const
{
    return this->currentColor;
}

int Project::getCurrentFrameIndex() const
{
    return this->currentFrame;
}

const QImage &Project::getCurrentFrame() const
{
    return this->sprite->getFrame(this->currentFrame);
}

void Project::onToolChanged(/* TODO: add tool here */)
{
    // this->currentTool = tool;
}

void Project::onColorChanged(QColor color)
{
    this->currentColor = color;
}

void Project::onPixelClicked(QPoint point)
{
    // this->currentTool->apply(point, this->getCurrentFrame(), this->currentColor);
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

void Project::onSaveRequested()
{
    if (!this->path) {
        // TODO (grant): prompt user for save file, then set it.
        return;
    }

    this->sprite->saveSprite(*this->path);
}
