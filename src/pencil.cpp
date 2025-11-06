#include "pencil.h"
#include "tool.h"
#include "ui_toolpane.h"
#include <QWidget>

Pencil::Pencil(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Pencil)
{

}

void Tool::applyChange(QPoint currentPoint, QColor currentColor){

}

void Pencil::drawPoint(QPoint currentPoint, QColor currentColor){

}

Pencil::~Pencil()
{
    delete ui;
}
