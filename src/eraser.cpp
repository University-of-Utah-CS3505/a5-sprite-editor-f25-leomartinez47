#include "tool.h"
#include "eraser.h"
#include "ui_toolpane.h"

Eraser::Eraser(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Eraser){

}

void Tool::applyChange(QPoint currentPoint, QColor color){

}

void Eraser::drawPoint(QPoint currentPoint, QColor color){

}

Eraser::~Eraser(){
    delete ui;
}
