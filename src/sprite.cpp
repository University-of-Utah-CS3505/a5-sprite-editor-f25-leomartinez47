/*
    Written by Leo Martinez, Kailee Kim, and Grant Handy
*/

#include <QBuffer>
#include <QDebug>
#include <QIODevice>
#include <QMessageBox>
#include <QPainter>
#include <QProcess>
#include <QStringList>
#include <QStringLiteral>
#include <QTemporaryDir>

#include "sprite.h"


// QImage expects a C-style string.
const char *FORMAT = "PNG";

Sprite::Sprite(const QJsonObject &sprite) {
    if (!sprite.contains("frames") || !sprite.contains("width") ||
        !sprite.contains("height") || !sprite.contains("frameRate")) {
        throw std::invalid_argument(
            "Sprite information could not be retrieved.");
    }

    this->dimensions = QSize(sprite.value("width").toInteger(),
                             sprite.value("height").toInteger());

    this->frameRate = sprite.value("frameRate").toInteger();

    QJsonArray jsonFrames = sprite.value("frames").toArray();
    for (QJsonValue &&frame : jsonFrames) {
        QImage image;
        if (!image.loadFromData(QByteArray::fromBase64(frame.toString().toUtf8()), FORMAT)) {
            throw std::invalid_argument("Unsupported format.");
        }

        this->frames.push_back(image);
    }
}

Sprite::Sprite(QSize dimensions)
    : dimensions(dimensions), frameRate(30)
{
    addFrame(0);
}

void Sprite::addFrame(int index)
{
    QImage frame(dimensions, QImage::Format_ARGB32);
    frame.fill(Qt::transparent);
    frames.insert(frames.begin() + index, frame);
}

void Sprite::deleteFrame(std::size_t currentFrame) {
    if (currentFrame >= frames.size()) {
        return;
    }

    frames.erase(frames.begin() + currentFrame);
}

QImage &Sprite::getFrame(std::size_t index) {
    if (index >= frames.size()) {
        throw std::invalid_argument("Invalid index.");
    }
    return this->frames[index];
}

int Sprite::frameCount() {
    return this->frames.size();
}

QJsonObject Sprite::toJson() {
    QJsonArray jsonFrames;

    for (const QImage &image : frames) {
        QByteArray data;

        QBuffer buffer = QBuffer(&data);
        buffer.open(QIODevice::WriteOnly);
        if (!image.save(&buffer, FORMAT)) {
            throw std::invalid_argument("Could not save to file");
        }
        buffer.close();

        jsonFrames.push_back(QString(data.toBase64()));
    }

    return QJsonObject({
        { "frames", jsonFrames },
        { "frameRate", this->frameRate },
        { "width", this->dimensions.width() },
        { "height", this->dimensions.height() },
    });
}

void Sprite::writeToGif(const QString &path) const {
    QTemporaryDir *dir = new QTemporaryDir();
    // TODO: check dir->isValid()

    for (std::size_t i = 0; i < this->frames.size(); i++) {
        QString framePath = dir->path()
            + QDir::separator()
            + QStringLiteral("frame%1.png").arg(i, 3, 10, QLatin1Char('0'));

        this->frames[i].save(framePath, FORMAT);
    }

    QStringList ffmpegArgs;
    ffmpegArgs
        // Framerate settings:
        << "-framerate" << QString::number(this->frameRate)

        // Input sources schema:
        << "-i" << (dir->path() + QDir::separator() + "frame%03d.png")

        // Palette/Filter Settings:
        << "-filter_complex"
        << "[0:v]split[a][b];[a]palettegen=reserve_transparent=on[p];[b][p]"
           "paletteuse=dither=sierra2_4a"

        // Output path
        << "-y" << path;

    QProcess *process = new QProcess();
    process->setProcessChannelMode(QProcess::MergedChannels);

    QObject::connect(
        process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
        process,
        [process, dir, path](int exitCode, QProcess::ExitStatus exitStatus) {
            qDebug() << "ffmpeg finished";

            QByteArray output = process->readAll();

            if (exitStatus != QProcess::NormalExit || exitCode != 0) {
                QMessageBox::critical(
                    nullptr, "GIF Export Error",
                    QString("FFmpeg process failed.\n\n"
                            "Exit Code: %1\n"
                            "Status: %2\n\n"
                            "Output:\n%3")
                        .arg(exitCode)
                        .arg(exitStatus == QProcess::NormalExit ? "Normal"
                                                                : "Crashed")
                        .arg(QString::fromLocal8Bit(output)));
            } else {
                qDebug() << "GIF saved successfully to" << path;
                qDebug() << "ffmpeg output:" << QString::fromLocal8Bit(output);
            }

            dir->remove();
            delete dir;
            process->deleteLater();
        });

    QObject::connect(process, &QProcess::errorOccurred, process,
                     [process, dir](QProcess::ProcessError error) {
                         if (error == QProcess::FailedToStart) {
                             QMessageBox::critical(
                                 nullptr, "GIF Export Error",
                                 QString("FFmpeg process failed to start.\n\n"
                                         "Error: %1\n\n"
                                         "Please make sure 'ffmpeg' is "
                                         "installed and in your system's PATH.")
                                     .arg(process->errorString()));

                             dir->remove();
                             delete dir;
                             process->deleteLater();
                         }
                     });

    qDebug() << "Starting ffmpeg with args:" << ffmpegArgs;
    process->start("ffmpeg", ffmpegArgs); 
}

void Sprite::setFrameRate(int frameRate) {
    this->frameRate = frameRate;
}

int Sprite::getFrameRate() {
    return this->frameRate;
}
