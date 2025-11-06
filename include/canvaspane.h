/*
    Contributors: Bryce Wiley and Leo Martinez
    Date: 11/06/2025
*/

#ifndef CANVASPANE_H
#define CANVASPANE_H

#include <QWidget>
#include "project.h"
#include <QGraphicsScene>

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
    void pointClicked(QPointF coordinates);

public slots:
    // Recieve what frame to display from the project model
    void showFrame(const QImage &frame);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
private:
    Ui::CanvasPane *ui;


    // scene queen
    QGraphicsScene* scene;


    // cant draw while panning
    bool isPanning;

};

#endif
