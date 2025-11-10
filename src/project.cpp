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
    this->path = new std::filesystem::path(path.toStdString());

    // TODO: check for errors or propagate exceptions?
    QFile file = QFile(path);
    file.open(QIODevice::ReadOnly);

    QJsonObject json = QJsonDocument::fromJson(file.readAll()).object();
    this->sprite = new Sprite(json.value("sprite").toObject());

    // TODO: parse tool, current color, current frame, etc. from JSON
    this->currentFrame = 0;
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

void Project::save(std::function<QString()> requestPath) {
    if (!this->path) {
        QString userPath = requestPath();

        if (userPath.isEmpty()) {
            return;
        }

        this->path = new std::filesystem::path(userPath.toStdString());

        if (!this->path->has_extension()) {
            this->path->replace_extension(PROJECT_FILE_EXTENSION.toStdString());
        }

        emit this->nameChanged(this->name());
    }

    QFile saveFile = QFile(*this->path);
    saveFile.open(QIODevice::ReadWrite);

    QTextStream qStream = QTextStream(&saveFile);
    qStream << QJsonDocument(this->toJson()).toJson();
}

QJsonObject Project::toJson() {
    // TODO: add tool, current color, current frame, etc.
    return QJsonObject({
        { "sprite", this->sprite->toJson() }
    });
}

QString Project::name() {
    if (this->path != nullptr) {
        return QString::fromStdString(this->path->stem().string());
    }

    return QString();
}
