/*
    Contributors: Bryce Wiley and Leo Martinez
    Date: 11/13/2025
*/

#include "canvaspane.h"

#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>

#include "project.h"

CanvasPane::CanvasPane(Project *project, QWidget *parent) : QWidget(parent) {
    // Draw the initial frame
    this->onFrameChanged(project->getCurrentFrame());

    this->setMinimumSize(200, 200);

    this->connect(project, &Project::frameChanged, this, &CanvasPane::onFrameChanged);

    this->connect(this, &CanvasPane::pixelClicked, project, &Project::onPixelClicked);
}

void CanvasPane::onFrameChanged(const QImage &frame) {
    this->currentFrame = &frame;
    this->update();
}

void CanvasPane::mousePressEvent(QMouseEvent *event) {
    if (event->button() != Qt::LeftButton) {
        return;
    }

    this->isDrawing = true;

    QPoint spritePos = mapToSprite(event->pos());
    if (spritePos.x() >= 0) {
        emit this->pixelClicked(spritePos);
    }

    this->update();
}

void CanvasPane::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && this->isDrawing) {
        this->isDrawing = false;
    }
}

void CanvasPane::mouseMoveEvent(QMouseEvent *event) {
    if (!rect().contains(event->pos()) || !this->isDrawing) {
        return;
    }

    QPoint spritePos = mapToSprite(event->pos());
    if (spritePos.x() >= 0) {
        emit pixelClicked(spritePos);
    }

    update();
}

void CanvasPane::paintEvent(QPaintEvent *) {
    if (this->currentFrame->isNull()) {
        return;
    }

    QPainter painter = QPainter(this);
    QPixmap framePixmap = QPixmap::fromImage(*this->currentFrame);

    // Calculate the scale factor and offsets for the current frame
    int scaleFactorX = this->width() / this->currentFrame->width();
    int scaleFactorY = this->height() / this->currentFrame->height();
    this->scaleFactor = qMax(1, qMin(scaleFactorX, scaleFactorY));

    int scaledWidth = this->currentFrame->width() * this->scaleFactor;
    int scaledHeight = this->currentFrame->height() * this->scaleFactor;
    this->xOffset = (this->width() - scaledWidth) / 2;
    this->yOffset = (this->height() - scaledHeight) / 2;

    // Transparency grid
    QRect gridArea(this->xOffset, this->yOffset, scaledWidth, scaledHeight);

    const int gridSize = qMax(1, this->scaleFactor / 2);
    QColor lightGray(0xCC, 0xCC, 0xCC);
    QColor darkGray(0xAA, 0xAA, 0xAA);

    // Loop through the scaled area, drawing alternating squares
    for (int y = gridArea.top(); y < gridArea.bottom(); y += gridSize) {
        for (int x = gridArea.left(); x < gridArea.right(); x += gridSize) {
            QColor squareColor = (((x - this->xOffset) / gridSize +
                                   (y - this->yOffset) / gridSize) %
                                      2 ==
                                  0)
                                     ? lightGray
                                     : darkGray;

            int drawWidth = qMin(gridSize, gridArea.right() - x);
            int drawHeight = qMin(gridSize, gridArea.bottom() - y);

            // Draw the clamped rectangle
            painter.fillRect(x, y, drawWidth, drawHeight, squareColor);
        }
    }

    // Draw the scaled frame
    painter.drawPixmap(this->xOffset, this->yOffset,
                       framePixmap.scaled(scaledWidth, scaledHeight,
                                          Qt::KeepAspectRatio,
                                          Qt::FastTransformation));
}

QPoint CanvasPane::mapToSprite(const QPoint &widgetPos) const {
    if (this->currentFrame->isNull()) {
        // Invalid QPoint if no frame
        return QPoint(-1, -1);
    }

    int imgX = (widgetPos.x() - this->xOffset) / this->scaleFactor;
    int imgY = (widgetPos.y() - this->yOffset) / this->scaleFactor;

    if (imgX < 0 || imgX >= this->currentFrame->width() || imgY < 0 ||
        imgY >= this->currentFrame->height()) {
        // Invalid QPoint if out of bounds
        return QPoint(-1, -1);
    }

    return QPoint(imgX, imgY);
}
