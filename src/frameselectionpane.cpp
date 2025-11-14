/*
    Contributors: Sean Ho and Bryce Wiley
    Date: 11/13/2025
*/

#include "frameselectionpane.h"
#include "ui_frameselectionpane.h"

FrameSelectionPane::FrameSelectionPane(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FrameSelectionPane)
{
    ui->setupUi(this);
}

FrameSelectionPane::~FrameSelectionPane()
{
    delete ui;
}
