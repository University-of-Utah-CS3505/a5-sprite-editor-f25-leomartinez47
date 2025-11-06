#include "canvaspane.h"
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPixmap>
#include <QWheelEvent>
#include "project.h"
#include "ui_canvaspane.h"

CanvasPane::CanvasPane(Project *project, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CanvasPane)
{
    ui->setupUi(this);

    this->scene = new QGraphicsScene(this);

    ui->view->setScene(scene);
    ui->view->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    ui->view->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);

    connect(project, &Project::frameChanged, this, &CanvasPane::showFrame);
}

CanvasPane::~CanvasPane()
{
    delete ui;
    delete scene;
}

void CanvasPane::showFrame(const QImage &frame)
{
    // remove current frame from scene??

    QPixmap pixmap = QPixmap::fromImage(frame);
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pixmap);
    scene->addItem(item);
}

void CanvasPane::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && !isPanning) {
        emit pointClicked(ui->view->mapToScene(event->pos()));
    }
}

void CanvasPane::wheelEvent(QWheelEvent *event)
{
    const double factor = 1.15;
    if (event->angleDelta().y() > 0) {
        ui->view->scale(factor, factor);
    } else {
        ui->view->scale(1.0 / factor, 1.0 / factor);
    }
}

void CanvasPane::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space && !isPanning) {
        isPanning = true;
        ui->view->setDragMode(QGraphicsView::ScrollHandDrag);
        setCursor(Qt::OpenHandCursor);
    }
}

void CanvasPane::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space) {
        isPanning = false;
        ui->view->setDragMode(QGraphicsView::NoDrag);
        setCursor(Qt::ArrowCursor);
    }
}
