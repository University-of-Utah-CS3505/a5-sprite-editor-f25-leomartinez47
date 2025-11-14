/*
    Contributors: Natalie Bonilla, Grant Handy, Sean Ho, Kailee Kim, Leo Martinez,
    and Bryce Wiley.
    Date: 11/13/2025
*/

#include "project.h"
#include "sprite.h"

QJsonArray colorToJson(QColor color) {
    QJsonArray rgb;
    rgb.push_back(color.red());
    rgb.push_back(color.green());
    rgb.push_back(color.blue());
    return rgb;
}

QColor colorFromJson(QJsonArray rgb) {
    return QColor(
        rgb.takeAt(0).toInteger(),
        rgb.takeAt(0).toInteger(),
        rgb.takeAt(0).toInteger()
    );
}

Project::Project(QSize dimensions, QObject *parent)
    : QObject{parent}
{
    this->sprite = new Sprite(dimensions);
    this->currentFrame = 0;
    this->path = nullptr;
    this->currentTool = new Pencil();
    this->currentColor = Qt::black;
}

Project::Project(const QString &path, QObject *parent)
    : QObject{parent}
{
    this->path = new std::filesystem::path(path.toStdString());

    QFile file = QFile(path);
    if(!file.open(QIODevice::ReadOnly)){
        throw std::invalid_argument("File could not be opened.");
    }

    QJsonObject json = QJsonDocument::fromJson(file.readAll()).object();
    if(!json.contains("sprite") || !json.contains("currentFrame") || !json.contains("currentTool")
        || !json.contains("currentColor")) {
        throw std::invalid_argument("Project information could not be retrieved.");
    }

    this->sprite = new Sprite(json.value("sprite").toObject());
    this->currentFrame = json.value("currentFrame").toInteger();
    this->currentTool = toolFromString(json.value("currentTool").toString());
    this->currentColor = colorFromJson(json.value("currentColor").toArray());
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

const QImage &Project::frameAt(int index) const
{
    return this->sprite->getFrame(index);
}  
  
Sprite *Project::getSprite() const
{
    return this->sprite;
}

Tool &Project::getCurrentTool() const
{
    return *(this->currentTool);
}

void Project::onToolChanged(Tool *tool)
{
    if (tool != nullptr) {
        this->currentTool = tool;
    }
}

void Project::onRedChanged(int red)
{
    this->currentColor.setRed(red);
    emit this->sendColor(currentColor);
}

void Project::onGreenChanged(int green)
{
    this->currentColor.setGreen(green);
    emit this->sendColor(currentColor);
}

void Project::onBlueChanged(int blue)
{
    this->currentColor.setBlue(blue);
    emit this->sendColor(currentColor);
}

void Project::onAlphaChanged(int alpha)
{
    this->currentColor.setAlpha(alpha);
    emit this->sendColor(currentColor);
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
    emit this->stopAnimation();

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
        emit this->stopAnimation();
        emit this->frameRemoved(index);
        this->sprite->deleteFrame(index);
        this->onCurrentFrameChanged(next);
    }
}

void Project::onFrameRateSet(int frameRate) {
    this->sprite->setFrameRate(frameRate);
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

        emit this->nameChanged(this->getName());
    }

    QFile saveFile = QFile(*this->path);

    if(!saveFile.open(QIODevice::ReadWrite | QIODevice::Truncate)) {
        throw std::invalid_argument("Could not open selected file.");
    }

    QTextStream qStream = QTextStream(&saveFile);
    qStream << QJsonDocument(this->toJson()).toJson(QJsonDocument::Indented);
    qStream.flush();

    saveFile.close();
}

void Project::exportFile(const QString &path) {
    if (path.endsWith("gif")) {
        this->sprite->writeToGif(path);
    } else { // assumed to be .png
        if(!this->getCurrentFrame().save(path, "PNG")){
            throw std::invalid_argument("File was not saved.");
        }
    }
}

QJsonObject Project::toJson()
{
    return QJsonObject({
        { "sprite", this->sprite->toJson() },
        { "currentFrame", this->currentFrame },
        { "currentTool", this->currentTool->toString() },
        { "currentColor", colorToJson(this->currentColor) }
    });
}

QString Project::getName() const {
    if (this->path != nullptr) {
        return QString::fromStdString(this->path->stem().string());
    }

    return QString();
}

QString Project::getPath() const {
    if (this->path != nullptr) {
        return QString::fromStdString(this->path->string());
    }

    return QString();
}

std::vector<QImage> Project::initialImages(){
    std::vector<QImage> outList;
    for (int i = 0; i < this->sprite->frameCount(); i++) {
        outList.push_back(this->sprite->getFrame(i));
    }
    return outList;
}

void Project::sendInitialImages() {
    emit this->initialFrames(this->initialImages());
}

int Project::frameCount() const {
    return this->sprite->frameCount();
}

