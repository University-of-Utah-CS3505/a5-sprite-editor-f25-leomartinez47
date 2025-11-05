#include "canvaspane.h"
#include "ui_canvaspane.h"

CanvasPane::CanvasPane(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CanvasPane)
{
    ui->setupUi(this);
}

CanvasPane::~CanvasPane()
{
    delete ui;
}
