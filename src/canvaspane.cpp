/*
    Contributors: Bryce Wiley and Leo Martinez
    Date: 11/06/2025
*/

#include "canvaspane.h"
#include "ui_canvaspane.h"
#include "project.h"
#include <QPixmap>
#include <QMouseEvent>

CanvasPane::CanvasPane(Project *project, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CanvasPane)
{
    ui->setupUi(this);

    connect(project,
            &Project::frameChanged,
            this,
            &CanvasPane::showFrame);
}

CanvasPane::~CanvasPane()
{
    delete ui;
}

void CanvasPane::showFrame(const QImage &frame)
{
    QPixmap framePixmap = QPixmap::fromImage(frame);
    framePixmap = framePixmap.scaled(ui->view->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->view->setPixmap(framePixmap);
    ui->view->setAlignment(Qt::AlignCenter);
}

void CanvasPane::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        this->isDrawing = true;
        while(this->isDrawing) {
            emit pointClicked(event->position());
        }
    }
}

void CanvasPane::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && this->isDrawing) {
        this->isDrawing = false;
    }
}
