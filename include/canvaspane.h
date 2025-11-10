/*
    Contributors: Bryce Wiley and Leo Martinez
    Date: 11/06/2025
*/

#ifndef CANVASPANE_H
#define CANVASPANE_H

#include <QWidget>
#include <QLabel>

#include "project.h"

class CanvasPane : public QWidget
{
    Q_OBJECT

public:
    explicit CanvasPane(Project *project, QWidget *parent = nullptr);

signals:
    /// @brief Signal to the project model that the user has clicked on the
    /// canvas at a specific coordinate point.
    /// @param coordinates - The QPointF coordinate point of the click with
    /// respect to the QImage frame itself.
    void pixelClicked(QPoint coordinates);

public slots:
    /// @brief Recieve a QImage frame from the project model and display it.
    /// @param frame - A QImage to be displayed in the CanvasPane QWidget.
    void showFrame(const QImage &frame);

protected:
    /// @brief Sets isDrawing to true and emit pointClicked.
    /// @param event - A mouse press QMouseEvent.
    void mousePressEvent(QMouseEvent *event) override;

    /// @brief Sets isDrawing to false.
    /// @param event - A mouse release QMouseEvent.
    void mouseReleaseEvent(QMouseEvent *event) override;

    /// @brief If isDrawing emits pointClicked.
    /// @param event - A mouse move QMouseEvent.
    void mouseMoveEvent(QMouseEvent *event) override;

    /// @brief Draws currentFrame scaled to fit the canvas widget.
    void paintEvent(QPaintEvent*) override;

private:
    /// If the user is currently drawing on the frame,
    /// that is they have clicked on the canvas and are yet to release.
    bool isDrawing;

    /// The sprite frame currently being displayed.
    QImage currentFrame;

    /// @brief Maps canvas coordinates to pixel coordinates relative to the sprite.
    /// @param widgetPos - The cursor position relative to the canvas.
    QPoint mapToSprite(const QPoint &widgetPos) const;

    /// Scale factor applied to the frame to fit the canvas.
    int scaleFactor;

    /// Offset to center the frame horizontally.
    int xOffset;

    /// Offset to center the frame vertically.
    int yOffset;
};

#endif
