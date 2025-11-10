/*
    Contributors: Bryce Wiley and Leo Martinez
    Date: 11/06/2025
*/

#include <QPixmap>
#include <QMouseEvent>
#include <QPainter>

#include "canvaspane.h"
#include "project.h"


CanvasPane::CanvasPane(Project *project, QWidget *parent)
    : QWidget(parent)
{
    showFrame(project->getCurrentFrame());

    connect(project,
            &Project::frameChanged,
            this,
            &CanvasPane::showFrame);

    connect(this,
            &CanvasPane::pixelClicked,
            project,
            &Project::onPixelClicked);
}

void CanvasPane::showFrame(const QImage &frame)
{
    currentFrame = frame;
    update();
}

void CanvasPane::mousePressEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton) {
        return;
    }

    isDrawing = true;

    QPoint spritePos = mapToSprite(event->pos());
    if (!spritePos.isNull()) {
        emit pixelClicked(spritePos);
    }
}

void CanvasPane::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && this->isDrawing) {
        this->isDrawing = false;
    }
}

void CanvasPane::mouseMoveEvent(QMouseEvent *event)
{
    if (!rect().contains(event->pos()) || !this->isDrawing) {
        return;
    }

    QPoint spritePos = mapToSprite(event->pos());
    if (!spritePos.isNull()) {
        emit pixelClicked(spritePos);
    }
}

void CanvasPane::paintEvent(QPaintEvent*)
{
    if (currentFrame.isNull()) {
        return;
    }

    QPainter painter(this);
    QPixmap framePixmap = QPixmap::fromImage(currentFrame);

    // Calculate the scale factor and offsets for the current frame
    int scaleFactorX = this->width() / currentFrame.width();
    int scaleFactorY = this->height() / currentFrame.height();
    this->scaleFactor = qMax(1, qMin(scaleFactorX, scaleFactorY));

    int scaledWidth = currentFrame.width() * this->scaleFactor;
    int scaledHeight = currentFrame.height() * this->scaleFactor;
    this->xOffset = (this->width() - scaledWidth) / 2;
    this->yOffset = (this->height() - scaledHeight) / 2;

    // Draw the scaled frame
    painter.drawPixmap(xOffset, yOffset,
                       framePixmap.scaled(
                           scaledWidth, scaledHeight,
                           Qt::KeepAspectRatio, Qt::FastTransformation));

}

QPoint CanvasPane::mapToSprite(const QPoint &widgetPos) const
{
    if (currentFrame.isNull()) {
        // Null QPoint if no frame
        return QPoint();
    }

    int imgX = (widgetPos.x() - this->xOffset) / this->scaleFactor;
    int imgY = (widgetPos.y() - this->yOffset) / this->scaleFactor;

    if (imgX < 0 || imgX >= currentFrame.width() ||
        imgY < 0 || imgY >= currentFrame.height()) {
        // Null QPoint if out of bounds
        return QPoint();
    }

    return QPoint(imgX, imgY);
}
