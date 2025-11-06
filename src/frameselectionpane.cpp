#include "frameselectionpane.h"
#include "ui_frameselectionpane.h"
#include "project.h"

FrameSelectionPane::FrameSelectionPane(Project *project, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FrameSelectionPane)
{
    ui->setupUi(this);
}

FrameSelectionPane::~FrameSelectionPane()
{
    delete ui;
}

void FrameSelectionPane::onUpdate(){

}

void FrameSelectionPane::displaySpriteFrames(){

}
