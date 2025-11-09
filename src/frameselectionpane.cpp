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

    // Buttons -> code
    connect(ui->AddFrame, &QPushButton::clicked, this, &FrameSelectionPane::addFrameToList);
    connect(ui->DeleteFrame, &QPushButton::clicked, project, [this, project]{emit deleteFrame(project->getCurrentFrameIndex());});
    connect(ui->listWidget, &QListWidget::currentRowChanged, project, &Project::onCurrentFrameChanged);

    // Pane -> Project
    connect(this, &FrameSelectionPane::addFrame, project, &Project::onFrameAdded);
    connect(this, &FrameSelectionPane::deleteFrame, project, &Project::onFrameRemoved);

    // Project -> Pain
    connect(project, &Project::frameListChanged, this, &FrameSelectionPane::setupQList);
    connect(project, &Project::frameChanged, this, [this, project](const QImage&){
        this->onUpdate(project->getCurrentFrameIndex());
    });

    this->setupQList();
}

FrameSelectionPane::~FrameSelectionPane() {
    delete ui;
}

void FrameSelectionPane::onUpdate(int index) {
    // TODO: Figure out how to redraw.
    //       Redraws the current frame, maybe refresh the icon.
    if (index >= 0 && index < ui->listWidget->count())
        ui->listWidget->setCurrentRow(index);
}

void FrameSelectionPane::setupQList() {
    ui->listWidget->clear();
    // TODO: My idea was to refresh the list every time the list is updated.
    //       But I realized that view doesn't have access to project, and therefore
    //       woudln't be able to access frameCount and frameAt
}

void FrameSelectionPane::addFrameToList() {
    emit addFrame(ui->listWidget->currentRow() + 1);
}
