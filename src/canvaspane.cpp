/*
    Contributors: Bryce Wiley and Leo Martinez
    Date: 11/06/2025
*/

#include <QPixmap>
#include <QMouseEvent>
#include <QPainter>

#include <QDebug>


#include "canvaspane.h"
#include "project.h"


CanvasPane::CanvasPane(Project *project, QWidget *parent)
    : QWidget(parent)
{
    // Draw the initial frame
    onFrameChanged(project->getCurrentFrame());

    connect(project,
            &Project::frameChanged,
            this,
            &CanvasPane::onFrameChanged);

    connect(this,
            &CanvasPane::pixelClicked,
            project,
            &Project::onPixelClicked);
}

void CanvasPane::onFrameChanged(const QImage &frame)
{
    currentFrame = &frame;
    update();
}

void CanvasPane::mousePressEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton) {
        return;
    }

    isDrawing = true;

    QPoint spritePos = mapToSprite(event->pos());
    if (spritePos.x() >= 0) {
        emit pixelClicked(spritePos);
    }

    update();
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
    if (spritePos.x() >= 0) {
        emit pixelClicked(spritePos);
    }

    update();
}

void CanvasPane::paintEvent(QPaintEvent*)
{
    if (currentFrame->isNull()) {
        return;
    }

    QPainter painter(this);
    QPixmap framePixmap = QPixmap::fromImage(*currentFrame);

    // Calculate the scale factor and offsets for the current frame
    int scaleFactorX = this->width() / currentFrame->width();
    int scaleFactorY = this->height() / currentFrame->height();
    this->scaleFactor = qMax(1, qMin(scaleFactorX, scaleFactorY));

    int scaledWidth = currentFrame->width() * this->scaleFactor;
    int scaledHeight = currentFrame->height() * this->scaleFactor;
    this->xOffset = (this->width() - scaledWidth) / 2;
    this->yOffset = (this->height() - scaledHeight) / 2;


    // Transparency grid
    QRect gridArea(xOffset, yOffset, scaledWidth, scaledHeight);

    const int gridSize = this->scaleFactor;
    QColor lightGray(0xCC, 0xCC, 0xCC);
    QColor darkGray(0xAA, 0xAA, 0xAA);

    // Loop through the scaled area, drawing alternating squares
    for (int y = gridArea.top(); y < gridArea.bottom(); y += gridSize) {
        for (int x = gridArea.left(); x < gridArea.right(); x += gridSize) {
            QColor squareColor = (((x - xOffset) / gridSize + (y - yOffset) / gridSize) % 2 == 0) ? lightGray : darkGray;

            int drawWidth = qMin(gridSize, gridArea.right() - x);
            int drawHeight = qMin(gridSize, gridArea.bottom() - y);

            // Draw the clamped rectangle
            painter.fillRect(x, y, drawWidth, drawHeight, squareColor);
        }
    }

    // Draw the scaled frame
    painter.drawPixmap(xOffset, yOffset,
                       framePixmap.scaled(
                           scaledWidth, scaledHeight,
                           Qt::KeepAspectRatio, Qt::FastTransformation));

}

QPoint CanvasPane::mapToSprite(const QPoint &widgetPos) const
{
    if (currentFrame->isNull()) {
        // Invalid QPoint if no frame
        return QPoint(-1, -1);
    }

    int imgX = (widgetPos.x() - this->xOffset) / this->scaleFactor;
    int imgY = (widgetPos.y() - this->yOffset) / this->scaleFactor;

    if (imgX < 0 || imgX >= currentFrame->width() ||
        imgY < 0 || imgY >= currentFrame->height()) {
        // Invalid QPoint if out of bounds
        return QPoint(-1, -1);
    }

    return QPoint(imgX, imgY);
}
