#include "project.h"

Project::Project(QSize dimensions, QObject *parent)
    : QObject{parent}
{
    this->sprite = new Sprite(dimensions);
    this->currentFrame = 0;
    this->path = nullptr;
    this->currentTool = new Pencil();

    emit this->initialFrames(this->initialImages());
}

Project::Project(const std::string &path, QObject *parent)
    : QObject{parent}
{
    this->sprite = new Sprite(path);
    this->currentFrame = 0;
    this->path = new std::string(path);
    this->currentTool = new Pencil();

    emit this->initialFrames(this->initialImages());
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
    emit this->frameSelectionChanged(index);
    emit this->frameChanged(this->getCurrentFrame());
}

void Project::onFrameAdded(int index)
{
    // adds a frame at the index to the sprite
    this->sprite->addFrame(index);
    emit this->frameAdded(index);

    // changes the current frame to the newest frame
    this->onCurrentFrameChanged(index);
}

void Project::onFrameRemoved(int index)
{
    if (index < 0 || index >= this->sprite->frameCount()) {
        return;
    }

    // 3 Cases:
    // - only 1 frame in list: skip frame selection signal
    // - between frames or first frame: stay in same index
    // - deleting last frame: select previous index
    int next;
    if (this->sprite->frameCount() == 1) {
        next = -1;
    } else if (index == this->sprite->frameCount() - 1) {
        next = index - 1;
    } else {
        next = index;
    }

    if (next >= 0) {
        this->onCurrentFrameChanged(next);
    }

    this->sprite->deleteFrame(index);
    emit this->frameRemoved(index);
}

std::vector<QImage> Project::initialImages(){
    std::vector<QImage> outList;
    for (int i = 0; i < this->sprite->frameCount(); i++) {
        outList.push_back(this->sprite->getFrame(i));
    }
    return outList;
}
