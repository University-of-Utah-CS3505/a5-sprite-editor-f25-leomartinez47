#include "frameselectionpane.h"
#include "project.h"
#include "ui_frameselectionpane.h"
#include <QPushButton>
#include <QListWidget>
#include <QListWidgetItem>

FrameSelectionPane::FrameSelectionPane(Project *project, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FrameSelectionPane)
{
    ui->setupUi(this);

    currentIndex = project->getCurrentFrameIndex();

    connect(ui->AddFrame, &QPushButton::clicked, this, &FrameSelectionPane::addFrameToList);

    connect(ui->DeleteFrame, &QPushButton::clicked, project, [this, project]{emit deleteFrame(project->getCurrentFrameIndex());});

    this->setupQList();
}

FrameSelectionPane::~FrameSelectionPane() {
    delete ui;
}

void FrameSelectionPane::onUpdate(int index) {
    currentIndex = index;
}

void FrameSelectionPane::setupQList() {

}

void FrameSelectionPane::addFrameToList() {

    emit addFrame(currentIndex);
}
