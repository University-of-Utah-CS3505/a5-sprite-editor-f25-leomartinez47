/*
    Contributors: Bryce Wiley and Leo Martinez
    Date: 11/06/2025
*/

#ifndef CANVASPANE_H
#define CANVASPANE_H

#include <QWidget>
#include "project.h"

namespace Ui {
class CanvasPane;
}

class CanvasPane : public QWidget
{
    Q_OBJECT

public:
    explicit CanvasPane(Project *project, QWidget *parent = nullptr);
    ~CanvasPane();

signals:
    /// @brief Signal to the project model that the user has clicked on the
    /// canvas at a specific coordinate point.
    /// @param coordinates - The QPointF coordinate point of the click with
    /// respect to the QImage frame itself.
    void pointClicked(QPointF coordinates);

public slots:
    /// @brief Recieve a QImage frame from the project model and display it.
    /// @param frame - A QImage to be displayed in the CanvasPane QWidget.
    void showFrame(const QImage &frame);

protected:
    /// @brief Enter a drawing loop and emit pointClicked until released.
    /// @param event - A mouse press QMouseEvent.
    void mousePressEvent(QMouseEvent *event) override;

    /// @brief Sets isDrawing to false therefore exiting drawing loop.
    /// @param event - A mouse release QMouseEvent.
    void mouseReleaseEvent(QMouseEvent *event) override;
private:
    /// The CanvasPane ui form.
    Ui::CanvasPane *ui;

    /// If the user is currently drawing on the frame,
    /// that is they have clicked on the canvas and are yet to release.
    bool isDrawing;
};

#endif
